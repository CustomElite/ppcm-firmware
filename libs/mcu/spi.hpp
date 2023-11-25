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
        Peripheral tPeriph,
        typename tSCLK,
        typename tMOSI,
        typename tMISO,
        BitOrder tBitOrder = BitOrder::MSB_First,
        DataWidth tWidth = DataWidth::_16bit,
        ClockPhase tClkPhase = ClockPhase::LeadingEdge,
        ClockPolarity tClkPolarity = ClockPolarity::Low,
        ClockPrescaler tClkDiv = ClockPrescaler::Div8,
        DataDirection tDirection = DataDirection::FullDuplex,
        Mode tMode = Mode::Master
    >
    struct Configuration : tSCLK, tMOSI, tMISO
    {
        using sclk_t = tSCLK;
        using mosi_t = tMOSI;
        using miso_t = tMISO;

        using regs_t = MemoryMap::Registers<Common::Tools::EnumValue(tPeriph)>;

        Configuration() noexcept :
            sclk_t{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz },
            mosi_t{ IO::Alternate::PushPull, IO::OutputSpeed::_50MHz },
            miso_t{ IO::Input::Floating }
        {
            using CR1 = typename regs_t::CR1_t;

            CR1{}.SetBitOrder(tBitOrder);
            CR1{}.SetDataWidth(tWidth);
            CR1{}.SetClockPhase(tClkPhase);
            CR1{}.SetClockPolarity(tClkPolarity);
            CR1{}.SetClockPrescaler(tClkDiv);
            CR1{}.SetDataDirection(tDirection);
            CR1{}.SetMode(tMode);
        }

        static constexpr auto Peripheral = tPeriph;

    private:
        using clk_t = CLK::Kernal<GetClockID<tPeriph>()>;

        clk_t const m_kernal{};
    };

    template <typename tConfig, typename tCallback>
    class Module : private tConfig
    {
    public:
        template <typename CB>
        Module(CB && callback) noexcept :
            m_callback{ std::forward<CB>(callback) }
        {
            CR1{}.Enable();
        }
        Module(tConfig, tCallback && callback) noexcept :
            Module{ std::forward<tCallback>(callback) }
        {}
    private:
        using tConfig::Peripheral;
        using regs_t = typename tConfig::regs_t;

        using CR1 = typename regs_t::CR1_t;
        using CR2 = typename regs_t::CR2_t;
        using SR = typename regs_t::SR_t;
        using DR = typename regs_t::DR_t;
        using CRCPR = typename regs_t::CRCPR_t;
        using RXCRCR = typename regs_t::RXCRCR_t;
        using TXCRCR = typename regs_t::TXCRCR_t;

        using callback_t = Common::StaticLambda<tCallback>;
        using isr_t = ISR::Interrupt<Module, GetInterruptSource<Peripheral>()>;

    private:
        callback_t m_callback;
        isr_t m_isr;
    };
}