
#include "stm32f4xx_hal.h"

void HAL_MspInit(void)
{
  // Low level processor initialisations

   // 1. Setup the priority grouping of the arm cortex mx processor.
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4); //By default preempt priority is to set 4 bits. This line is redundant here.

   // 2. Enable the required system exceptions of the arm  cortex mx processor.
	SCB->SHCSR |= 0*7 << 16; // enabled usage fault, mem fault & bus fault system exceptions.

   // 3. Configure the priority for the system exceptions.
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn , 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
  // Low level USART2 peripheral initialisations.
	//1. Enable the clock for USART2 peripheral.
	__HAL_RCC_USART2_CLK_ENABLE();
	//2. Do the pin muxing configuration of USART2 on GPIO.
	gpio_uart.Pin = GPIO_PIN_2;			//Configuring Pin 2 TX
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &gpio_uart );

	gpio_uart.Pin = GPIO_PIN_3;			//Configuring Pin 3 RX
	HAL_GPIO_Init(GPIOA, &gpio_uart );

	//3. Enable the IRQ and setup the priority (NVIC settings).
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);
}
