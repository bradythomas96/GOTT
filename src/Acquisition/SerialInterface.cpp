#include "SerialInterface.h"
#include <stdlib.h>

using namespace Senior;

SerialInterface::SerialInterface()
:mSerialPort(NULL)
{
    mSerialParams = { 0 };
    mSerialParams.DCBlength = sizeof(mSerialParams);
}

bool SerialInterface::Open()
{
    mSerialPort = CreateFile("\\\\.\\COM4", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

    if (!GetCommState(mSerialPort, &mSerialParams)) {
        return false;
    }
    mSerialParams.BaudRate = CBR_115200;
    mSerialParams.ByteSize = 8;
    mSerialParams.StopBits = ONESTOPBIT;
    mSerialParams.Parity = NOPARITY;
    SetCommState(mSerialPort, &mSerialParams);
    return true;
}

void SerialInterface::Close()
{
    CloseHandle(mSerialPort);
}

bool SerialInterface::WriteMessage(bool dir, int step)
{
    char message[10] = { 0 };
    LPDWORD bytesWritten = 0;

    // Set the direction flag
    if(dir) {
        message[0] = 'l';
    } else {
        message[0] = 'r';
    }

    // Skip over the first byte and place the number of steps.
    itoa(step, &message[1], 10);

    // Skip over the direction and steps and add the line termination
    int index = strlen(message);
    strncpy(&message[index], "\r\n", 3);

    return WriteFile(mSerialPort, message, strlen(message), bytesWritten, NULL);
}