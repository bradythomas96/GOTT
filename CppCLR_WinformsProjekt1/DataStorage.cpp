#include "stdafx.h"
#include "DataStorage.h"
#include <string>
#include <vector>


DWORD WINAPI Thread(LPVOID lpparm) {
	DataExchange::Instance()->ReadThread();

	return 0;
}

DataExchange::DataExchange(){
    mMode = GUI;
}
DataExchange* DataExchange::Instance() {
	static DataExchange instance;

	return &instance;
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
	const char* del = " ";

    if ( GUI == mMode) {
        token = strtok(databuffer, del);

        for (int i = 1; i < ACQ_TYPES; i++) {
            acq_data[i] = std::stoi(token);
        }
    } else if ( ACQ == mMode ) {
        token = strtok(databuffer, del);

        for (int i = 1; i < GUI_TYPES; i++) {
            gui_data[i] = std::stoi(token);
        }
    } else {
        retval = false;
    }
    
    this->Event(UPDATE_TYPE::DATA_UPDATE);
    
    return retval;
}

void DataExchange::Event(UPDATE_TYPE t) {
    if (mEventCallback)
        mEventCallback(t);
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
        Thread,
        NULL,
        0,
        &mThreadID
    );

	return true;
}

bool DataExchange::Disconnect() {
    TerminateThread(mHandle, NULL);

    mConnection->Close();
    delete mConnection;
    mConnection = 0;

	return true;
}

void DataExchange::Update() {
    char databuff[1024];
    Serialize(databuff);
    std::string dataToSend(databuff);
    mConnection->SendLine(dataToSend);
}

void DataExchange::MoveLaser(bool dir){
    if (!dir) { 
        mConnection->SendLine(std::string("r"));
    } else {
        mConnection->SendLine(std::string("l"));
    }
}

void DataExchange::ReadThread(){
    while(true){
        std::string data = mConnection->ReceiveLine();
		size_t i = data.length();
		char* dataptr = new char[i];
		strcpy(dataptr, data.c_str());

        if (GUI == mMode) {
            this->Deserialize((dataptr));
            this->Event(UPDATE_TYPE::DATA_UPDATE);
        } else {
            if ((data.c_str())[0] == 'r'){
                this->Event(UPDATE_TYPE::MOVE_RIGHT);
            } else if ((data.c_str())[0] == 'l') {
                this->Event(UPDATE_TYPE::MOVE_LEFT);
            } else {
                this->Event(UPDATE_TYPE::DATA_UPDATE);
            }
        }

		delete dataptr;

    }
}