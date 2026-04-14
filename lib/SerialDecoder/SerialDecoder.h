#include <Arduino.h>
//Package formatting [ start_byte | type_id | motor_id | opcode | value ]

namespace SerialDecoder {
    enum class typeID : uint8_t 
    {
        motor = 0x00,
        servo = 0x01
    };

    enum class motorID : uint8_t 
    {
        A = 0x00,
        B = 0x01,
        C = 0x02,
        D = 0x03
    };

    enum class servoID : uint8_t
    {
        A = 0x00
    };

    enum class motorOpcode : uint8_t
    {
        move = 0x00,
        setSpeed = 0x01,
        stop = 0x02
    };

    enum class servoOpcode : uint8_t
    {
        setAngle = 0x00
    };

    void handleSerialData(byte b);
    void handlePacket(uint8_t typeId, uint8_t motorId, uint8_t opcode, uint8_t value);
}