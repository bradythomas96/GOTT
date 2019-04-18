#ifndef __DATAEXCHANGE_H__
#define __DATAEXCHANGE_H__

#include "Socket.h"
#include <vector>
#include <Windows.h>

typedef void (*fCallBack)(int t);

class DataExchange {
public:
	enum DE_MODE {
		ACQ,
		GUI
	};

	enum FIELD_ACQ {
		MOTOR_ALPHA,
		MOTOR_BETA,
		TARGET_X,
		TARGET_Y,
		SNR,
		DELTA_X,
		DELTA_Y,
		EST_CAM_STATUS,
		POWER_STATUS,
		VELOCITY,
		ACQ_TYPES
	};

	enum FIELD_GUI {
		TARGET_DISTANCE,
		POINT_OF_ENTRY,
		SUN_POS,
		GUI_TYPES
	};

	enum UPDATE_TYPE {
		MOVE_LEFT,
		MOVE_RIGHT,
		DATA_UPDATE
	};

	DataExchange();
	void SetMode(DE_MODE mode);
	static DataExchange* Instance();
	bool Connect();
	bool Disconnect();

	bool Serialize(char* databuffer);
	bool Deserialize(char* databuffer);
	bool RegisterCallback(fCallBack);
	
	// We need to push data across the socket.
	void Update();
	void MoveLaser(bool dir);

	int acq_data[ACQ_TYPES];
	int gui_data[GUI_TYPES];
	void ReadThread();

	private:
	// An event has occured from the socket
	void Event(UPDATE_TYPE t);


	Socket* mConnection;
	std::vector<std::string> DataExchange::SplitString(std::string);
	DE_MODE mMode;
	fCallBack mEventCallback;
	DWORD mThreadID;
	HANDLE mHandle;
};



#endif