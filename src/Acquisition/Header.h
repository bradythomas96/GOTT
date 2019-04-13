#pragma once

extern DataExchange* GetExchangeInstance();
class DataExchange {
public:
	DataExchange();
	void update();
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

	int targetDistance;
	bool pointofEntry; // false is right and true is left
	double sunPos;
};