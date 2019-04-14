#include <windows.h>

namespace Senior {
    class SerialInterface {
        public:
            SerialInterface();
            bool Open();
            void Close();
            bool WriteMessage(bool dir, int steps);
        private:
            HANDLE mSerialPort;

            DCB mSerialParams;
    };
}