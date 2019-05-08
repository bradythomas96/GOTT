//=============================================================================
// Copyright (c) 2001-2018 FLIR Systems, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

/**
 *  @example Acquisition.cpp
 *
 *  @brief Acquisition.cpp shows how to acquire images. It relies on
 *  information provided in the Enumeration example. Also, check out the
 *  ExceptionHandling and NodeMapInfo examples if you haven't already.
 *  ExceptionHandling shows the handling of standard and Spinnaker exceptions
 *  while NodeMapInfo explores retrieving information from various node types.
 *
 *  This example touches on the preparation and cleanup of a camera just before
 *  and just after the acquisition of images. Image retrieval and conversion,
 *  grabbing image data, and saving images are all covered as well.
 *
 *  Once comfortable with Acquisition, we suggest checking out
 *  AcquisitionMultipleCamera, NodeMapCallback, or SaveToAvi.
 *  AcquisitionMultipleCamera demonstrates simultaneously acquiring images from
 *  a number of cameras, NodeMapCallback serves as a good introduction to
 *  programming with callbacks and events, and SaveToAvi exhibits video creation.
 */

#include "Spinnaker.h"
#include <opencv2/opencv.hpp>
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core/cuda.hpp>
#include "SpinGenApi/SpinnakerGenApi.h"
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <string>
#include <iostream>
#include <sstream> 
#include <ctime>
#include <opencv2/features2d/features2d.hpp>
#include "SerialInterface.h"
#include "math.h"
#include <vector>
#include <chrono>
#include <cstdlib>
#include <algorithm>
#include <tuple>

using namespace Spinnaker;
using namespace Spinnaker::GenApi;
using namespace Spinnaker::GenICam;
using namespace std;
using namespace cv;
using namespace Senior;
using namespace chrono;

SerialInterface stepperControl;

Mat frame;
Mat fgMaskMOG2;
Mat thresh;
vector<Point> locs;
vector<int> xloc;
vector<int> yloc;
int stepSet = 800;
int targetDist = 0;
string entry;
bool POE;
bool dirLogic;
Ptr <BackgroundSubtractorMOG2> pMOG2;
int imageCnt = 0;
long long timeDelay = 0.320;
#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()


tuple<int,bool> calcStep(vector<int> xloc, int targetDist, int count, unsigned int timeDelay);
int xError(vector<int> xloc, int count);
int yError(vector<int> yloc, int count);

// This function acquires and saves 10 images from a device.  
int AcquireImages(CameraPtr pCam, INodeMap & nodeMap, INodeMap & nodeMapTLDevice)
{
    int result = 0;
	int i = 0;
	int step = 0;
	int stepCount = 0;
	long long maxTime = 0.0;
    // cout << endl << endl << "*** IMAGE ACQUISITION ***" << endl << endl;

    try
    {
        //
        // Set acquisition mode to continuous
        //
        // *** NOTES ***
        // Because the example acquires and saves 10 images, setting acquisition 
        // mode to continuous lets the example finish. If set to single frame
        // or multiframe (at a lower number of images), the example would just
        // hang. This would happen because the example has been written to
        // acquire 10 images while the camera would have been programmed to 
        // retrieve less than that.
        // 
        // Setting the value of an enumeration node is slightly more complicated
        // than other node types. Two nodes must be retrieved: first, the 
        // enumeration node is retrieved from the nodemap; and second, the entry
        // node is retrieved from the enumeration node. The integer value of the
        // entry node is then set as the new value of the enumeration node.
        //
        // Notice that both the enumeration and the entry nodes are checked for
        // availability and readability/writability. Enumeration nodes are
        // generally readable and writable whereas their entry nodes are only
        // ever readable.
        // 
        // Retrieve enumeration node from nodemap
        CEnumerationPtr ptrAcquisitionMode = nodeMap.GetNode("AcquisitionMode");
        if (!IsAvailable(ptrAcquisitionMode) || !IsWritable(ptrAcquisitionMode))
        {
            cout << "Unable to set acquisition mode to continuous (enum retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve entry node from enumeration node
        CEnumEntryPtr ptrAcquisitionModeContinuous = ptrAcquisitionMode->GetEntryByName("Continuous");
        if (!IsAvailable(ptrAcquisitionModeContinuous) || !IsReadable(ptrAcquisitionModeContinuous))
        {
            cout << "Unable to set acquisition mode to continuous (entry retrieval). Aborting..." << endl << endl;
            return -1;
        }

        // Retrieve integer value from entry node
        int64_t acquisitionModeContinuous = ptrAcquisitionModeContinuous->GetValue();

        // Set integer value from entry node as new value of enumeration node
        ptrAcquisitionMode->SetIntValue(acquisitionModeContinuous);

        cout << "Acquisition mode set to continuous..." << endl;



        //
        // Begin acquiring images
        //
        // *** NOTES ***
        // What happens when the camera begins acquiring images depends on the
        // acquisition mode. Single frame captures only a single image, multi 
        // frame captures a set number of images, and continuous captures a 
        // continuous stream of images. Because the example calls for the 
        // retrieval of 10 images, continuous mode has been set.
        // 
        // *** LATER ***
        // Image acquisition must be ended when no more images are needed.
        //
        pCam->BeginAcquisition();

        cout << "Acquiring images..." << endl;

        //
        // Retrieve device serial number for filename
        //
        // *** NOTES ***
        // The device serial number is retrieved in order to keep cameras from 
        // overwriting one another. Grabbing image IDs could also accomplish
        // this.
        //
        gcstring deviceSerialNumber("");
        CStringPtr ptrStringSerial = nodeMapTLDevice.GetNode("DeviceSerialNumber");
        if (IsAvailable(ptrStringSerial) && IsReadable(ptrStringSerial))
        {
            deviceSerialNumber = ptrStringSerial->GetValue();

            // cout << "Device serial number retrieved as " << deviceSerialNumber << "..." << endl;
        }
        cout << endl;

        // Retrieve, convert, and save images
        const unsigned int k_numImages = 5;
		char userInput;
		// cin >> userInput;
		pMOG2 = createBackgroundSubtractorMOG2(10,32,false);
		
		

        // for (unsigned int imageCnt = 0; imageCnt < k_numImages; imageCnt++)
		while (/* userInput != 'q'*/ 1)
        {
			auto start = high_resolution_clock::now();
            try
            {
                //
                // Retrieve next received image
                //
                // *** NOTES ***
                // Capturing an image houses images on the camera buffer. Trying
                // to capture an image that does not exist will hang the camera.
                //
                // *** LATER ***
                // Once an image from the buffer is saved and/or no longer 
                // needed, the image must be released in order to keep the 
                // buffer from filling up.
                //
                ImagePtr pResultImage = pCam->GetNextImage();

                //
                // Ensure image completion
                //
                // *** NOTES ***
                // Images can easily be checked for completion. This should be
                // done whenever a complete image is expected or required.
                // Further, check image status for a little more insight into
                // why an image is incomplete.
                //
                if (pResultImage->IsIncomplete())
                {
                    // Retreive and print the image status description
                    // cout << "Image incomplete: "
                     //   << Image::GetImageStatusDescription(pResultImage->GetImageStatus())
                     //   << "..." << endl << endl;
                }
				else
				{
					//
					// Print image information; height and width recorded in pixels
					//
					// *** NOTES ***
					// Images have quite a bit of available metadata including
					// things such as CRC, image status, and offset values, to
					// name a few.
					//
					//size_t width = pResultImage->GetWidth();

					//size_t height = pResultImage->GetHeight();

					// cout << "Grabbed image " << imageCnt << ", width = " << width << ", height = " << height << endl;

					//
					// Convert image to mono 8
					//
					// *** NOTES ***
					// Images can be converted between pixel formats by using 
					// the appropriate enumeration value. Unlike the original 
					// image, the converted one does not need to be released as 
					// it does not affect the camera buffer.
					//
					// When converting images, color processing algorithm is an
					// optional parameter.
					// 

					ImagePtr convertedImage = pResultImage->Convert(PixelFormat_Mono8, HQ_LINEAR);
					unsigned int xpadding = convertedImage->GetXPadding();
					unsigned int ypadding = convertedImage->GetYPadding();
					unsigned int rowsize = convertedImage->GetWidth();
					unsigned int colsize = convertedImage->GetHeight();

					int cvFormat = CV_8UC1;

					Mat cvMat = Mat(colsize + ypadding, rowsize + xpadding, cvFormat, convertedImage->GetData(), convertedImage->GetStride());




					/*Ptr<Tracker> tracker;
					tracker = TrackerKCF::create();
					Rect2d bbox(287, 23, 86, 320);
					rectangle(cvMat, bbox, Scalar(255, 0, 0), 2, 1);

					imshow("Tracking", cvMat);
					tracker->init(frame, bbox);
					waitKey(1); */
					// Create a unique filename
					// ostringstream filename;

					/*filename << "Acquisition-";
					if (deviceSerialNumber != "")
					{
						filename << deviceSerialNumber.c_str() << "-";
					}
					filename << imageCnt << ".png";
					*/

					//
					// Save image
					// 
					// *** NOTES ***
					// The standard practice of the examples is to use device
					// serial numbers to keep images of one device from 
					// overwriting those of another.
					//
					//convertedImage->Save(filename.str().c_str());

				   //  cout << "Image saved at " << filename.str() << endl;




					if (imageCnt % 10 == 0) {
						namedWindow("Current Frame", WINDOW_AUTOSIZE);
						pMOG2->apply(cvMat, fgMaskMOG2);
						threshold(fgMaskMOG2, thresh, 0, 255, 0);
						Moments m = moments(thresh, true);
						int x = m.m10 / m.m00;
						int y = m.m01 / m.m00;
						Point p(m.m10 / m.m00, m.m01 / m.m00);
						locs.push_back(p);
						xloc.push_back(x);
						yloc.push_back(y);
						if (i > 0) {
							xError(xloc, i);
							yError(yloc, i);
							auto stepData = calcStep(xloc, targetDist, i, timeDelay);
							step = get<0>(stepData);
							dirLogic = get<1>(stepData);

							
							

						}
						i += 1;
						cout << Mat(p) << endl;
						circle(cvMat, p, 5, Scalar(255, 255, 255), -1);
						imshow("Current Frame", cvMat);
						waitKey(1);

					}
					imageCnt = imageCnt + 1;
					// cin >> userInput;

					if (targetDist == 300)
					{
						//step this much
						printf("%d, %d\r\n", dirLogic, step);
						stepperControl.WriteMessage(dirLogic, step);
						stepCount += step;
						if ((stepCount >= 298) && (imageCnt > 1400)) {
							break;
						}

					}

					else if (targetDist == 50) {
						//step this much
						printf("%d, %d\r\n", dirLogic, step);
						stepperControl.WriteMessage(dirLogic, step);
						stepCount += step;
						if ((stepCount >= 556) && (imageCnt > 590)) {
							break;
						}
					}
					
					
					auto stop = high_resolution_clock::now();
					auto duration = duration_cast<milliseconds>(stop - start);
					unsigned int timeDelay = (unsigned int) duration.count();
					cout << duration.count() << endl;
					
					
					
					



                }

                //
                // Release image
                //
                // *** NOTES ***
                // Images retrieved directly from the camera (i.e. non-converted
                // images) need to be released in order to keep from filling the
                // buffer.
                //

			
                pResultImage->Release();

                cout << endl;
            }
            catch (Spinnaker::Exception &e)
            {
                cout << "Error: " << e.what() << endl;
                result = -1;
            }
        }

        //
        // End acquisition
        //
        // *** NOTES ***
        // Ending acquisition appropriately helps ensure that devices clean up
        // properly and do not need to be power-cycled to maintain integrity.
        //

        pCam->EndAcquisition();


    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function prints the device information of the camera from the transport
// layer; please see NodeMapInfo example for more in-depth comments on printing
// device information from the nodemap.
int PrintDeviceInfo(INodeMap & nodeMap)
{
    int result = 0;

    cout << endl << "*** DEVICE INFORMATION ***" << endl << endl;

    try
    {
        FeatureList_t features;
        CCategoryPtr category = nodeMap.GetNode("DeviceInformation");
        if (IsAvailable(category) && IsReadable(category))
        {
            category->GetFeatures(features);

            FeatureList_t::const_iterator it;
            for (it = features.begin(); it != features.end(); ++it)
            {
                CNodePtr pfeatureNode = *it;
                cout << pfeatureNode->GetName() << " : ";
                CValuePtr pValue = (CValuePtr)pfeatureNode;
                cout << (IsReadable(pValue) ? pValue->ToString() : "Node not readable");
                cout << endl;
            }
        }
        else
        {
            cout << "Device control information not available." << endl;
        }
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

// This function acts as the body of the example; please see NodeMapInfo example 
// for more in-depth comments on setting up cameras.
int RunSingleCamera(CameraPtr pCam)
{
    int result = 0;

    try
    {
        // Retrieve TL device nodemap and print device information
        INodeMap & nodeMapTLDevice = pCam->GetTLDeviceNodeMap();

        // result = PrintDeviceInfo(nodeMapTLDevice);

        // Initialize camera
        pCam->Init();

        // Retrieve GenICam nodemap
        INodeMap & nodeMap = pCam->GetNodeMap();

        // Acquire images
        result = result | AcquireImages(pCam, nodeMap, nodeMapTLDevice);

        // Deinitialize camera
        pCam->DeInit();
    }
    catch (Spinnaker::Exception &e)
    {
        cout << "Error: " << e.what() << endl;
        result = -1;
    }

    return result;
}

int xError(vector<int> xloc, int count) {
	int xErr = abs(xloc.at(count) - xloc.at(count - 1));

	return xErr;
}

int yError(vector<int> yloc, int count) {
	int yErr = abs(yloc.at(count) - yloc.at(count - 1));

	return yErr;
}

tuple<int,bool> calcStep(vector<int> centLoc, int targetDist, int count, unsigned int time) {
	int stepSize = 0;
	int vCount = 0;
	vector<int> step4V;
	int vdiff = 0;
	double velocity = 0.0;
	int pixelVal = 0;
	int currentX = centLoc.at(count);
	if (vCount >= 1) {
		vdiff = abs(step4V.at(vCount) - step4V.at(vCount - 1));
	}


	if ((vCount < 1) || (vdiff > 0.01)) {
		if (targetDist == 50) {
			if (currentX > stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(.345*pixelVal/10);
				dirLogic = false;
			}

			else if (currentX < stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(.345*pixelVal/10);
				dirLogic = true;
			}
		}

		else if (targetDist == 300) {
			if (currentX > stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(0.186*pixelVal/5);
				stepSize += ceil(0.3*stepSize);
				dirLogic = false;
			}

			else if (currentX < stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(0.186*pixelVal/5);
				stepSize += ceil(0.3*stepSize);
				dirLogic = true;
			}
		}
	}

	
	/*else {
		if (targetDist == 50) {
			if (currentX > stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(.345*pixelVal);
				stepSize = vdiff * time + stepSize;
				dirLogic = false;
			}

			else if (currentX < stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(.345*pixelVal);
				stepSize = vdiff * time + stepSize;
				dirLogic = true;
			}
		}

		else if (targetDist == 300) {
			if (currentX > stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(0.1858*pixelVal);
				stepSize = vdiff * time + stepSize;
				dirLogic = false;
			}

			else if (currentX < stepSet) {
				pixelVal = abs(currentX - stepSet);
				stepSize = ceil(0.1858*pixelVal);
				stepSize = vdiff * time + stepSize;
				dirLogic = true;
			} 
		} 
	}*/
	

	step4V.push_back(stepSize);
	stepSet = currentX;
	return make_tuple(stepSize, dirLogic);
}

// Example entry point; please see Enumeration example for more in-depth 
// comments on preparing and cleaning up the system.
int main(int /*argc*/, char** /*argv*/)
{
    // Since this application saves images in the current folder
    // we must ensure that we have permission to write to this folder.
    // If we do not have permission, fail right away.
   
	/* FILE *tempFile = fopen("test.txt", "w+");
    if (tempFile == nullptr)
    {
        cout << "Failed to create file in current folder.  Please check "
            "permissions."
            << endl;
        cout << "Press Enter to exit..." << endl;
        getchar();
        return -1;
    }
    fclose(tempFile);
    remove("test.txt");
	*/

    int result = 0;
	string centerCheck;
	int centerStep = 0;
	int calStep = 0;

    stepperControl.Open();


    // Print application build information
    // cout << "Application build date: " << __DATE__ << " " << __TIME__ << endl << endl;

    // Retrieve singleton reference to system object
    SystemPtr system = System::GetInstance();

    // Print out current library version
    /* const LibraryVersion spinnakerLibraryVersion = system->GetLibraryVersion();
    cout << "Spinnaker library version: "
        << spinnakerLibraryVersion.major << "."
        << spinnakerLibraryVersion.minor << "."
        << spinnakerLibraryVersion.type << "."
        << spinnakerLibraryVersion.build << endl << endl;
		*/

    // Retrieve list of cameras from the system
    CameraList camList = system->GetCameras();

    unsigned int numCameras = camList.GetSize();

    // cout << "Number of cameras detected: " << numCameras << endl << endl;

    // Finish if there are no cameras
    if (numCameras == 0)
    {
        // Clear camera list before releasing system
        camList.Clear();

        // Release system
        system->ReleaseInstance();

        cout << "Not enough cameras!" << endl;
        cout << "Done! Press Enter to exit..." << endl;
        getchar();

        return -1;
    }

    //
    // Create shared pointer to camera
    //
    // *** NOTES ***
    // The CameraPtr object is a shared pointer, and will generally clean itself
    // up upon exiting its scope. However, if a shared pointer is created in the
    // same scope that a system object is explicitly released (i.e. this scope),
    // the reference to the shared point must be broken manually.
    //
    // *** LATER ***
    // Shared pointers can be terminated manually by assigning them to nullptr.
    // This keeps releasing the system from throwing an exception.
    //
    CameraPtr pCam = nullptr;

    // Run example on each camera
    for (unsigned int i = 0; i < numCameras; i++)
    {
        // Select camera
        pCam = camList.GetByIndex(i);

        // cout << endl << "Running example for camera " << i << "..." << endl;

        // Run example
		cout << "Adjust laser to center position (enter r and l to adjust, done when centered): ";
		cin >> centerCheck;
		cout << endl;
		while (centerCheck.compare("done") != 0) {
			if (centerCheck.compare("r") == 0) {
				cout << "Enter step size: ";
				cin >> centerStep;
				cout << endl;
				dirLogic = false;
				// Pass in direction and step size to motor movement function
				stepperControl.WriteMessage(dirLogic, centerStep);
			}

			else if (centerCheck.compare("l") == 0) {
				cout << "Enter step size: ";
				cin >> centerStep;
				cout << endl;
				dirLogic = true;
				// Pass in direction and step size to motor movement function
				stepperControl.WriteMessage(dirLogic, centerStep);
			}

			cout << "Adjust laser to center position (enter r and l to adjust, done when centered): ";
			cin >> centerCheck;
			cout << endl;

		}


		cout << "Enter distance: ";
		cin >> targetDist;
		/* cout << endl;
		cout << "Enter point of entry (r or l): ";
		cin >> entry;
		cout << endl;
		while ((entry.compare("r") != 0) && (entry.compare("l") != 0)) {
			cout << "Incorrect input, please enter r or l: ";
			cin >> entry;
			cout << endl;
		}

		if (entry.compare("r") == 0) {
			if (targetDist == 50) {
				dirLogic = false;
				calStep = 276;
				// Pass in motor to move to right most position for 50 meters
				stepperControl.WriteMessage(dirLogic, calStep);
				// then set dirLogic to be ready to move to the left
				dirLogic = true;
			}

			else if (targetDist == 300) {
				calStep = 149;
				dirLogic = false;
				// Pass in motor to move to right most position for 300 meters
				stepperControl.WriteMessage(dirLogic, calStep);
				// then set dirLogic to be ready to move to the left
				dirLogic = true;
			}

		}

		else if (entry.compare("l") == 0) {
			if (targetDist == 50) {
				dirLogic = true;
				calStep = 276;
				// Pass in motor to move to left most position for 50 meters
				stepperControl.WriteMessage(dirLogic, calStep);
				// then set dirLogic to be ready to move to the right
				dirLogic = false;
			}

			else if (targetDist == 300) {
				calStep = 149;
				dirLogic = true;
				// Pass in motor to move to left most position for 300 meters
				stepperControl.WriteMessage(dirLogic, calStep);
				// then set dirLogic to be ready to move to the right
				dirLogic = false;

			}
		}*/


        result = result | RunSingleCamera(pCam);
		
        // cout << "Camera " << i << " example complete..." << endl << endl;
    }

    //
    // Release reference to the camera
    //
    // *** NOTES ***
    // Had the CameraPtr object been created within the for-loop, it would not
    // be necessary to manually break the reference because the shared pointer
    // would have automatically cleaned itself up upon exiting the loop.
    //
    pCam = nullptr;

    // Clear camera list before releasing system
    camList.Clear();

    // Release system
    system->ReleaseInstance();
    
    stepperControl.Close();

    cout << endl << "Done! Press Enter to exit..." << endl;
    getchar();

    return result;
}




