#include <SerialDecoder.h>
#include <Motor.h>

namespace SerialDecoder
{
    uint8_t buffer[5];
    int index = 0;
    const uint8_t START_BYTE = 0xff;

    void handleSerialData(byte b)
    {
        if (b == START_BYTE)
        {
            index = 0;
        }

        if (SerialDecoder::index == 0)
        {
            if (b != START_BYTE)
            {
                return;
            }
        }
        Serial.print("Byte: ");
        Serial.print(b);
        Serial.print("\t");
        Serial.print("Index: ");
        Serial.println(index);

        SerialDecoder::buffer[SerialDecoder::index++] = b;

        if(index == 5)
        {
            Serial.print("handlePacket: "); 
            Serial.print("Index[1]: "); Serial.print(buffer[1]); 
            Serial.print("\t");
            Serial.print("Index[2]: "); Serial.print(buffer[2]);
            Serial.print("\t");
            Serial.print("Index[3]: ");Serial.print(buffer[3]);
            Serial.print("\t");
            Serial.print("Index[4]: ");Serial.println(buffer[4]);
            handlePacket(buffer[1], buffer[2], buffer[3], buffer[4]);
            SerialDecoder::index = 0;
        }
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
            case motorOpcode::setTargetSpeed:
                m->setTargetSpeed(value);
                break;
            case motorOpcode::setRampTime_ms:
                m->setrampTime_ms(value);
                break;
            case motorOpcode::startMove:
                m->startMove(value);
                break;
            }
            break;
        }
    }
}