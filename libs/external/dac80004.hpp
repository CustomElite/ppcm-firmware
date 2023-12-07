#pragma once

#include "common/tools.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <stdint.h>
#include <type_traits>

namespace External::DAC80004
{
    inline namespace Settings
    {
        enum class Access : bool
        {
            Write = false,
            Read = true
        };
        enum class OutputState : uint8_t
        {
            On = 0b00,
            Off_1k = 0b01,
            Off_100K = 0b10,
            Off_HiZ = 0b11
        };
        enum class ClearMode : uint8_t
        {
            ZeroScale = 0b00,
            MidScale = 0b01,
            FullScale = 0b10
        };
        enum class LoadMode : bool
        {
            LDAC_Pin = false,
            Auto = true
        };
        enum class CurrentLimit : bool
        {
            _40mA = false,
            _30mA = true
        };
        enum class DataOutput : bool
        {
            Off = false,
            On = true
        };
    }

    enum class Channel : uint8_t
    {
        A = 0b0000,
        B = 0b0001,
        C = 0b0010,
        D = 0b0011,
        ALL = 0b1111
    };

    struct OutputCommand
    {
        enum Command : uint8_t { SET, UPDATE, SET_LDAC, SET_UPDATE };

        explicit OutputCommand(Channel channel, uint16_t value, Command cmd, bool read = false)
            : Value{ value }
            , Channel{ Common::Tools::EnumValue(channel) }
            , Command{ cmd }
            , RW{ read }
        {}

        uint32_t : 4;
        uint32_t Value : 16;
        uint32_t Channel : 4;
        uint32_t Command : 4;
        uint32_t RW : 4;
    };

    template <typename SPI_Module>
    class Module
    {
    public:
        enum CMD : uint8_t
        {
            Write = 0b0000,
            Update = 0b0001,
            Write_LDAC = 0b0010,
            Write_Update = 0b0011,
            PowerState = 0b0100,
            ClearMode = 0b0101,
            LDAC = 0b0110,
            SW_Reset = 0b0111,
            DisableSDO = 0b1000,
            CurrentLimit = 0b1010,
            SW_Clear = 0b1011,
            Status = 0b1101,
            NOP = 0b1110
        };
    
    public:
        Module(float const voltage_reference) noexcept :
            m_VoltageRef{voltage_reference}
        {}

        template <Channel tChannel>
        static constexpr uint32_t SetOutputBuffer(uint16_t const value) noexcept
        {
            return (CMD::Write << cmd_pos) | (Common::Tools::EnumValue(tChannel) << ch_pos) | (value << val_pos);
        }

        static void insert_cmd(CMD const cmd, uint32_t& output) noexcept
        {
            output &= ~cmd_mask;
            output |= (cmd << cmd_pos);
        }

    private:
        

        static constexpr std::size_t cmd_pos = 24u;
        static constexpr uint32_t cmd_mask = (0xF << cmd_pos);
        static constexpr std::size_t ch_pos = 20u;
        static constexpr uint32_t ch_mask = (0xF << ch_pos);
        static constexpr std::size_t val_pos = 4u;
        static constexpr uint32_t val_mask = (0xFFFF << val_pos);
        static constexpr std::size_t reg_pos = 0u;
        static constexpr uint32_t reg_mask = (0xF << reg_pos);

        using spi_t = SPI_Module;

        struct DAC_ValueType
        {
            using type = uint16_t;
            static constexpr type Max = std::numeric_limits<type>::max();
            static constexpr float MaxValue = static_cast<float>(Max);
        };

        struct SPI_DataType
        {
            uint16_t LSB{0};
            uint16_t MSB{0};

            constexpr SPI_DataType() = default;
            explicit SPI_DataType(uint32_t input) :
                LSB{ static_cast<uint16_t>((input & 0xFF)) },
                MSB{ static_cast<uint16_t>(((input >> 16u) & 0xFF)) }
            {}
            explicit SPI_DataType(uint16_t msb, uint16_t lsb) :
                LSB{ lsb },
                MSB{ msb }
            {}
        };

        

    private:
        float m_VoltageRef;
    };
}