#include "stm32f746xx.h"

int main() {

    // GPIO init
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOFEN;

    GPIOF->MODER |= (0b10 << GPIO_MODER_MODER7_Pos) | (0b10 << GPIO_MODER_MODER6_Pos);
    GPIOC->MODER |= (0b10 << GPIO_MODER_MODER7_Pos) | (0b10 << GPIO_MODER_MODER6_Pos);

    GPIOF->AFR[0] |= 0x08 << GPIO_AFRL_AFRL7_Pos | 0x08 << GPIO_AFRL_AFRL6_Pos;
    GPIOC->AFR[0] |= 0x08 << GPIO_AFRL_AFRL7_Pos | 0x08 << GPIO_AFRL_AFRL6_Pos;

    GPIOI->MODER |= (0b01 << 2);

    //UART init
    RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

    UART7->BRR = 139; // baud rate 115200
    UART7->CR1 |= USART_CR1_TE;
    UART7->CR1 |= USART_CR1_UE;

    USART6->BRR = 139;
    USART6->CR1 |= USART_CR1_RE;
    USART6->CR1 |= USART_CR1_UE;

    while(1) {
        while ((GPIOI->IDR & GPIO_IDR_ID11) != GPIO_IDR_ID11);

        while(UART7->ISR & USART_ISR_BUSY);
        UART7->TDR |= 14;

        while(UART7->ISR & USART_ISR_BUSY);
        while(USART6->ISR & USART_ISR_BUSY);

        volatile uint32_t rec_val = USART6->RDR;
        GPIOI->ODR ^= GPIO_ODR_ODR_1;
    }
    return 0;
}
