#pragma once

#include "common/static_lambda.hpp"
#include "common/tools.hpp"
#include "mcu/gpio.hpp"
#include "mcu/interrupt.hpp"
#include "mcu/rcc.hpp"
#include "rcc.hpp"
#include "interrupt.hpp"

#include "spi_registers.hpp"

#include <type_traits>
#include <utility>

namespace MCU::SPI 
{
    enum class PeripheralID : uint8_t
    {
        SPI_1 = 1u,
        SPI_2
    };

    namespace 
    {
        template <PeripheralID tPeriph>
        constexpr auto ClockID() noexcept
        {
            if constexpr (tPeriph == PeripheralID::SPI_1) { return CLK::ClockID::APB2_SPI1; }
            if constexpr (tPeriph == PeripheralID::SPI_2) { return CLK::ClockID::APB1_SPI2; }
        }
        template <PeripheralID tPeriph>
        constexpr auto InterruptSource() noexcept
        {
            if constexpr (tPeriph == PeripheralID::SPI_1) { return ISR::InterruptSource::eSPI1; }
            if constexpr (tPeriph == PeripheralID::SPI_2) { return ISR::InterruptSource::eSPI2; }
        }
    }

    template 
    <
          PeripheralID tPeriphID
        , typename tSCLK
        , typename tMOSI
        , typename tMISO
        , Mode tMode = Mode::Master
        , BitOrder tBitOrder = BitOrder::MSB_First
        , DataWidth tWidth = DataWidth::_16bit
        , ClockPhase tClkPhase = ClockPhase::LeadingEdge
        , ClockPolarity tClkPolarity = ClockPolarity::Low
        , ClockPrescaler tClkDiv = ClockPrescaler::Div8
        , DataDirection tDirection = DataDirection::FullDuplex
    >
    struct Configuration : tSCLK, tMOSI, tMISO
    {
        using HAL = HWInterface<Common::Tools::EnumValue(tPeriphID)>;
        using REGS = typename HAL::Registers;

        using DataType = std::conditional_t<Common::Tools::EnumValue(tWidth), uint16_t, uint8_t>;

        static constexpr auto s_PeriphID = tPeriphID;
        static constexpr auto s_Mode = tMode;
        static constexpr auto s_BitOrder = tBitOrder;
        static constexpr auto s_DataWidth = tWidth;
        static constexpr auto s_Phase = tClkPhase;
        static constexpr auto s_Polarity = tClkPolarity;
        static constexpr auto s_ClockDiv = tClkDiv;
        static constexpr auto s_DataDirection = tDirection;

        constexpr Configuration() noexcept
            : tSCLK{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz }
            , tMOSI{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz }
            , tMISO{ IO::Input::Floating }
        {
            HAL::Set(tMode);
        }

    //private:
    //    sclk_pin_t const m_sclk{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz };
    //    mosi_pin_t const m_mosi{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz };
    //    miso_pin_t const m_miso{ IO::Input::Floating };
    };

    template <typename tConfig, typename tCallback>
    class Module : private tConfig, Common::StaticLambda<tCallback>
    {
    private:
        using Config = tConfig;
        using Config::s_PeriphID
            , Config::s_Mode
            , Config::s_BitOrder
            , Config::s_DataWidth
            , Config::s_Phase
            , Config::s_Polarity
            , Config::s_ClockDiv
            , Config::s_DataDirection;

    public:
        template <typename C>
        Module(C && callback) noexcept
            : Config{ s_Mode, s_BitOrder, s_DataWidth, s_Phase, s_Polarity, s_ClockDiv, s_DataDirection }
            , m_Callback{ std::forward<C>(callback) }
            , m_CLK{}
            , m_ISR{}
        {
            HAL::Enable();
        }
        Module(tConfig, tCallback && callback) noexcept
            : Module{ std::forward<tCallback>(callback) }
        {}
        ~Module()
        {
            HAL::Disable();
        }

    private:
        //using Registers = typename Peripheral<Common::Tools::EnumValue(s_PeriphID)>::Type;
        using HAL = typename Config::HAL;
        using REG = typename Config::Registers;

        Common::StaticLambda<tCallback> const m_Callback;
        CLK::Kernal<ClockID<s_PeriphID>()> const m_CLK;
        ISR::Kernal<Module, InterruptSource<s_PeriphID>()> const m_ISR;
    };

    template <typename P, typename C>
    Module(P, C) -> Module<P, C>;
}