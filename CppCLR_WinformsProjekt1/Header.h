#pragma once

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

	int moveLeft;
	int moveRight;

	int targetDistance;
	bool pointofEntry; // false is right and true is left
	double sunPos;
};

extern DataExchange* GetExchangeInstance();
extern int GUI_main();