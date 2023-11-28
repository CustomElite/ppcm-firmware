#pragma once

#include "common/static_lambda.hpp"
#include "common/tools.hpp"
#include "mcu/gpio.hpp"
#include "mcu/gpio_registers.hpp"
#include "mcu/interrupt.hpp"
#include "mcu/rcc.hpp"
#include "mcu/spi_registers.hpp"
#include "rcc.hpp"
#include "interrupt.hpp"

#include "spi_registers.hpp"

#include "common/run_once.hpp"
#include <utility>

namespace MCU::SPI 
{
    enum class Peripheral : uint8_t
    {
        SPI_1 = 1u,
        SPI_2
    };

    namespace 
    {
        template <Peripheral tPeriph>
        constexpr auto GetClockID() noexcept
        {
            if constexpr (tPeriph == Peripheral::SPI_1) { return CLK::ClockID::APB2_SPI1; }
            if constexpr (tPeriph == Peripheral::SPI_2) { return CLK::ClockID::APB1_SPI2; }
        }
        template <Peripheral tPeriph>
        constexpr auto GetInterruptSource() noexcept
        {
            if constexpr (tPeriph == Peripheral::SPI_1) { return ISR::InterruptSource::eSPI1; }
            if constexpr (tPeriph == Peripheral::SPI_2) { return ISR::InterruptSource::eSPI2; }
        }
    }

    template 
    <
        Peripheral tPeriph
        , typename tSCLK
        , typename tMOSI
        , typename tMISO
        , BitOrder tBitOrder = BitOrder::MSB_First
        , DataWidth tWidth = DataWidth::_16bit
        , ClockPhase tClkPhase = ClockPhase::LeadingEdge
        , ClockPolarity tClkPolarity = ClockPolarity::Low
        , ClockPrescaler tClkDiv = ClockPrescaler::Div8
        , DataDirection tDirection = DataDirection::FullDuplex
        , Mode tMode = Mode::Master
    >
    struct Properties
    {
        using SCLK_t = tSCLK;
        using MOSI_t = tMOSI;
        using MISO_t = tMISO;

        static constexpr auto s_Peripheral = tPeriph;
        static constexpr auto s_BitOrder = tBitOrder;
        static constexpr auto s_DataWidth = tWidth;
        static constexpr auto s_Phase = tClkPhase;
        static constexpr auto s_Polarity = tClkPolarity;
        static constexpr auto s_ClockDiv = tClkDiv;
        static constexpr auto s_DataDirection = tDirection;
        static constexpr auto s_Mode = tMode;
    };

    template <typename tProperties, typename tCallback>
    class Module : private tProperties::SCLK_t, tProperties::MOSI_t, tProperties::MISO_t
    {
    public:
        template <typename CB>
        Module(CB && callback) noexcept :
            SCLK_t{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz }
            , MOSI_t{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz }
            , MISO_t{ IO::Input::Floating }
            , m_callback{ std::forward<CB>(callback) }
        {
            Regs_t{}.EnablePeriph();
        }
        Module(tProperties, tCallback && callback) noexcept :
            Module{ std::forward<tCallback>(callback) }
        {}
        ~Module()
        {
            Regs_t{}.DisablePeriph();
        }

    private:
        using   tProperties::s_Peripheral
              , tProperties::s_BitOrder
              , tProperties::s_DataWidth
              , tProperties::s_Phase
              , tProperties::s_Polarity
              , tProperties::s_ClockDiv
              , tProperties::s_DataDirection
              , tProperties::s_Mode;

        using typename tProperties::SCLK_t;
        using typename tProperties::MOSI_t;
        using typename tProperties::MISO_t;

        using Regs_t = Registers<Common::Tools::EnumValue(s_Peripheral)>;

        using clk_t = CLK::Kernal<GetClockID<s_Peripheral>()>;
        using callback_t = Common::StaticLambda<tCallback>;
        using isr_t = ISR::Interrupt<Module, GetInterruptSource<s_Peripheral>()>;

    private:
        clk_t const m_clk;
        callback_t const m_callback;
        isr_t const m_isr;
    };
}