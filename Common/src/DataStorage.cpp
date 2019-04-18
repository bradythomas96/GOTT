#include "DataStorage.h"
#include <string>
#include <vector>


DataExchange::DataExchange(){
    mMode = GUI;
}
DataExchange* DataExchange::Instance() {
    if( 0 == mInstance ) {
        mInstance = new DataExchange();
    }
}

void DataExchange::SetMode(DataExchange::DE_MODE mode){
    mMode = mode;
}

bool DataExchange::RegisterCallback(fCallBack cb) {
    mEventCallback = cb;
    return true;
}

bool DataExchange::Serialize(char* databuffer) {
    bool retval = false;
    if (mMode == DE_MODE::GUI){
        std::string message;
        
        for (int i=0; i < GUI_TYPES; i++) {
            message = message + std::to_string(gui_data[i]);
        }

        strcpy(databuffer, message.c_str());
        retval = true;
    } else if (mMode == DE_MODE::ACQ) {
        std::string message;

        for (int i=0; i < ACQ_TYPES; i++){
            message = message + std::to_string(acq_data[i]);
            if (i < (ACQ_TYPES - 1) ) {
                message += " ";
            } 
        }

        strcpy(databuffer, message.c_str());
        retval = true;
    }
    
    return retval;
}

bool DataExchange::Deserialize(char* databuffer) {
    bool retval = true;
    char* token;

    if ( GUI == mMode) {
        token = strtok(databuffer, " ");

        for (int i = 1; i < ACQ_TYPES; i++) {
            acq_data[i] = std::stoi(token);
        }
    } else if ( ACQ == mMode ) {
        token = strtok(databuffer, " ");

        for (int i = 1; i < GUI_TYPES; i++) {
            gui_data[i] = std::stoi(token);
        }
    } else {
        retval = false;
    }
    
    this->Event();
    
    return retval;
}

void DataExchange::Event() {
    if (mEventCallback)
        mEventCallback();
}

bool DataExchange::Connect() {
    if (GUI == mMode) {
        mConnection = new SocketServer(3000, 1 );
    } else {
        mConnection = new SocketClient("127.0.0.1", 3000);
    }

    mHandle = CreateThread(
        NULL,
        0,
        this->ReadThread,
        NULL,
        0,
        &mThreadID
    );
}

bool DataExchange::Disconnect() {
    TerminateThread(mHandle, NULL);

    mConnection->Close();
    delete mConnection;
    mConnection = 0;
}

void DataExchange::Update() {
    char databuff[1024];
    Serialize(databuff);
    std::string dataToSend(databuff);

    mConnection->SendLine(dataToSend);
}

void DataExchange::ReadThread(){
    while(true){
        std::string data = mConnection->ReceiveLine();
        this->Deserialize();
        this->Event();
    }
}