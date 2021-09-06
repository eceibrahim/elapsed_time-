#include "serial.h"
#include "Main.h"

#define SERIAL_MAX_MASSAGE_SIZE                (22)
#define SERIAL_MAX_TRANSFER_DURATION_MS        (1000)

typedef enum timeout_state_tag
{
	STOP = 0, 
	START 
}timeout_state_t ; 

char massage[SERIAL_MAX_MASSAGE_SIZE] ;

static serial_state_t serial_state ;

void serial_init(void) 
{
	uint8_t current_index ;
	USART_InitTypeDef  usart_cfgr_pin ;
	GPIO_InitTypeDef gpio_cfgr_pin ;
	
	/*Configure pin a2  */ 
	gpio_cfgr_pin.GPIO_Pin = GPIO_Pin_2 ;
	gpio_cfgr_pin.GPIO_Speed =GPIO_Speed_10MHz; 
	gpio_cfgr_pin.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio_cfgr_pin);
	
	
	/*Configure pin a3 */
	gpio_cfgr_pin.GPIO_Pin = GPIO_Pin_3 ;
	gpio_cfgr_pin.GPIO_Speed =GPIO_Speed_10MHz;
	gpio_cfgr_pin.GPIO_Mode=GPIO_Mode_AF_PP ;
	GPIO_Init(GPIOA, &gpio_cfgr_pin);
	
	/*Remap pins for usart*/
	GPIO_PinRemapConfig(GPIO_Remap_USART2 , ENABLE);
	
	/*Configure usart2 */
	usart_cfgr_pin.USART_BaudRate = 9600 ;
	usart_cfgr_pin.USART_WordLength =  USART_WordLength_8b ;
	usart_cfgr_pin.USART_StopBits = USART_StopBits_1 ;
	usart_cfgr_pin.USART_Parity = USART_Parity_No ;
	usart_cfgr_pin.USART_Mode =  USART_Mode_Rx | USART_Mode_Tx;
	usart_cfgr_pin.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	
	USART_Cmd(USART2 , ENABLE );
	
	USART_Init(USART2 , &usart_cfgr_pin);
	
	serial_state = SERIAL_NORMAL; 
	
	for(current_index =0  ; current_index < SERIAL_MAX_MASSAGE_SIZE ; ++current_index)
	{
		massage[current_index] ='\r' ;
	}
}

void serial_update(void) 
{
	static timeout_state_t timeout_state = STOP ; 
	static uint8_t current_index  = 0 ;
	static uint16_t time_out  = 0 ;
	
	switch(serial_state)
	{
		case SERIAL_NORMAL :
		{
			if(timeout_state == STOP )
			{
				USART_SendData(USART2,massage[current_index]);
				time_out = 0 ;
				current_index = (current_index + 1)  % SERIAL_MAX_MASSAGE_SIZE ;
				timeout_state = START ; 
			}
			else if (timeout_state == START)
			{
				
				time_out += SERIAL_TASK_PERIOD_MS ;
				if(USART_GetFlagStatus(USART2 , USART_FLAG_TC) == SET)
				{
					time_out = 0 ; 
					timeout_state = STOP ; 
				}
				else if (time_out >= SERIAL_MAX_TRANSFER_DURATION_MS)
				{
					time_out = 0 ; 
					USART_DeInit(USART2);
					GPIO_DeInit(GPIOA);
					serial_state =SERIAL_FAULT ; 
				}
		  }
			break ;
		}
		case SERIAL_FAULT :
		{
			/*do nothing here */ 
			break ;
		}
		default :
		{
			/*Should not be here !*/
			break ; 
		}
	}
}

serial_state_t serial_get_state(void)
{
	serial_state_t ret ; 
	ret = serial_state ; 
	return ret ; 
}
