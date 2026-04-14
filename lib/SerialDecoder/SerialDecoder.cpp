#include <SerialDecoder.h>
#include <Motor.h>

namespace SerialDecoder
{
    uint8_t buffer[4];
    int index = 0;

    void handleSerialData(byte b)
    {
        Serial.print("This byte is being read");
        Serial.println(b);
        SerialDecoder::buffer[SerialDecoder::index++] = b;

        if (index < 4)
            return;
        index = 0;
        Serial.println("handlePacket called");
        handlePacket(buffer[0], buffer[1], buffer[2], buffer[3]);
    }

    void handlePacket(uint8_t typeId, uint8_t id, uint8_t opcode, uint8_t value)
    {
        switch ((typeID)typeId)
        {
        default:
            Serial.print(typeId);
            Serial.println(":Invaild typeID bozo");
            break;
        case typeID::servo:
            if (id != 0)
            {
                Serial.print(id);
                Serial.println(":Invaild ID bozo");
                return;
            }
            switch ((servoOpcode)opcode)
            {
            default:
                Serial.print(opcode);
                Serial.println(":Invaild opcode bozo");
                break;
            case servoOpcode::setAngle:
                robotMovement.servo.write(value);
                break;
            }
            break;
        case typeID::motor:
            if (id >= 4)
            {
                Serial.print(id);
                Serial.println(":Invaild ID bozo");
                return;
            }
            Motor *m = motors[id];
            if (!m)
                return;

            switch ((motorOpcode)opcode)
            {
            default:
                Serial.print(opcode);
                Serial.println(":Invaild opcode bozo");
                break;
            case motorOpcode::move:
                m->move(value);
                break;
            case motorOpcode::setSpeed:
                m->setSpeed(value);
                break;
            case motorOpcode::stop:
                m->stop();
                break;
            }
            break;
        }
    }
}