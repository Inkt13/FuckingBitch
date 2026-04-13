#include <SerialDecoder.h>
#include <Motor.h>

namespace SerialDecoder {
    uint8_t buffer[3];
    int index = 0;

    void handleSerialData(byte b)
    {
        Serial.print("This byte is being read");
        Serial.println(b);
        SerialDecoder::buffer[SerialDecoder::index++] = b;

        if(index < 3)return;
        index = 0;
        handlePacket(buffer[0],buffer[1],buffer[2]);
    }

    void handlePacket(uint8_t motorId, uint8_t opcode, int8_t value)
    {
        if (motorId >= 4) return;
        Motor* m = motor1234[motorId];
        if (!m) return;

        switch ((Opcode)opcode)
        {
            case Opcode::move:
                m->move(value);
                break;
                case Opcode::setSpeed:
                m->setSpeed(value);
                break;
                case Opcode::stop:
                m->stop();
                break;
        }
    }
}