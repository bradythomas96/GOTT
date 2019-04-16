#ifndef __DATAEXCHANGE_H__
#define __DATAEXCHANGE_H__

typedef void (*fCallBack)(void);

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

	DataExchange();
	static DataExchange* Instance();
	bool Serialize(char* databuffer);
	bool Deserialize(char* databuffer);
	bool RegisterCallback(fCallBack);
	void Event();
	void SetMode(DE_MODE mode);

	int acq_data[ACQ_TYPES];
	int gui_data[GUI_TYPES];

	private:
	std::vector<std::string> DataExchange::SplitString(std::string);
	DE_MODE mMode;
	static DataExchange* mInstance;
	fCallBack mEventCallback;
};



#endif