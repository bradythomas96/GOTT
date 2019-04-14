#ifndef __DATAEXCHANGE_H__
#define __DATAEXCHANGE_H__

class DataExchange {
public:
	DataExchange();
	static DataExchange* Instance();
	bool Serialize();
	bool Deserialize();
	int motorAlpha;
	int motorBeta;
	int targetPositionX;
	int targetPositionY;
	int SNR;
	int deltaX;
	int deltaY;
	int estCamStatus;
	int powerStatus;
	int velocity;

	int moveLeft;
	int moveRight;

	int targetDistance;
	bool pointofEntry; // false is right and true is left
	double sunPos;

	private:
	static DataExchange* mInstance;
};



#endif