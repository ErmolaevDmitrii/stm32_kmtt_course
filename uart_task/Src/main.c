#include "stm32f746xx.h"

int main() {

    // GPIO init
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOFEN;

    //set uart pins to alternate function mode
    GPIOF->MODER |= (0b10 << GPIO_MODER_MODER7_Pos) | (0b10 << GPIO_MODER_MODER6_Pos);
    GPIOC->MODER |= (0b10 << GPIO_MODER_MODER7_Pos) | (0b10 << GPIO_MODER_MODER6_Pos);

    //uart alternate function on pins
    GPIOF->AFR[0] |= 0x08 << GPIO_AFRL_AFRL7_Pos | 0x08 << GPIO_AFRL_AFRL6_Pos;
    GPIOC->AFR[0] |= 0x08 << GPIO_AFRL_AFRL7_Pos | 0x08 << GPIO_AFRL_AFRL6_Pos;

    //set pin with led to output mode
    GPIOI->MODER |= (0b01 << 2);

    //UART init
    //turn on clock for uarts
    RCC->APB1ENR |= RCC_APB1ENR_UART7EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART6EN;

    UART7->BRR = 139; // baud rate 115200
    UART7->CR1 |= USART_CR1_TE; // transmit enable
    UART7->CR1 |= USART_CR1_UE; // enable uart7

    USART6->BRR = 139; // baud rate 115200
    USART6->CR1 |= USART_CR1_RE; // receive enable
    USART6->CR1 |= USART_CR1_UE; // enable usart6

    while(1) {
        //wait for button click
        while ((GPIOI->IDR & GPIO_IDR_ID11) != GPIO_IDR_ID11);

        //wait until uart7 is not busy
        while(UART7->ISR & USART_ISR_BUSY);
        UART7->TDR |= 14; // transmit 14

        while(UART7->ISR & USART_ISR_BUSY); // wait until transmittion is ended
        while(USART6->ISR & USART_ISR_BUSY); // wait until reception is ended

        volatile uint32_t rec_val = USART6->RDR; // put received value in variable
                                                 // (for debug purpose only)
        GPIOI->ODR ^= GPIO_ODR_ODR_1; // toogle led on pi1 pin
    }
    return 0;
}
