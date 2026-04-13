#include <Arduino.h>
//Package formatting [ motor_id | opcode | value ]

namespace SerialDecoder {
    enum class motorID : uint8_t 
    {
        A = 0x00,
        B = 0x01,
        C = 0x02,
        D = 0x03
    };

    enum class Opcode : uint8_t
    {
        move = 0x00,
        setSpeed = 0x01,
        stop = 0x02
    };

    void handleSerialData(byte b);
    void handlePacket(uint8_t motorId, uint8_t opcode, int8_t value);
}