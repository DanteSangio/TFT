/*
 * lcd.c
 *
 *  Created on: 13 de jun. de 2017
 *      Author: grama
 */
#include <chip.h>
#include <lcd.h>

extern uint32_t contador;
extern uint32_t contador_overflow;
extern uint32_t timer_set;
/*
 * Funcion: LCD_IO_Init()
 * Configura los pines a utilizar como salida digitales.
 */
void     LCD_IO_Init(void)
{
	Chip_GPIO_SetPinDIROutput(LPC_GPIO,0,22);

	Chip_GPIO_SetPinDIROutput(LCD_RST);
	Chip_GPIO_SetPinDIROutput(LCD_CS);
	Chip_GPIO_SetPinDIROutput(LCD_RS);
	Chip_GPIO_SetPinDIROutput(LCD_WR);
	Chip_GPIO_SetPinDIROutput(LCD_RD);	//creo que este no es necesario utilizar

	Chip_GPIO_SetPinDIROutput(LCD_D0);
	Chip_GPIO_SetPinDIROutput(LCD_D1);
	Chip_GPIO_SetPinDIROutput(LCD_D2);
	Chip_GPIO_SetPinDIROutput(LCD_D3);
	Chip_GPIO_SetPinDIROutput(LCD_D4);
	Chip_GPIO_SetPinDIROutput(LCD_D5);
	Chip_GPIO_SetPinDIROutput(LCD_D6);
	Chip_GPIO_SetPinDIROutput(LCD_D7);
	Chip_GPIO_SetPinDIROutput(LCD_D8);
	Chip_GPIO_SetPinDIROutput(LCD_D9);
	Chip_GPIO_SetPinDIROutput(LCD_D10);
	Chip_GPIO_SetPinDIROutput(LCD_D11);
	Chip_GPIO_SetPinDIROutput(LCD_D12);
	Chip_GPIO_SetPinDIROutput(LCD_D13);
	Chip_GPIO_SetPinDIROutput(LCD_D14);
	Chip_GPIO_SetPinDIROutput(LCD_D15);

	Chip_GPIO_SetPinState(LCD_RST,0);
	Chip_GPIO_SetPinState(LCD_CS,1);//IGNORA TODO, PARA MANDAR COMANDOS Y DATOS PONER CS EN 0
	Chip_GPIO_SetPinState(LCD_RS,1);
	Chip_GPIO_SetPinState(LCD_WR,1);
	Chip_GPIO_SetPinState(LCD_RD,1);
}

void     LCD_IO_WriteData(uint16_t RegValue)
{
	Chip_GPIO_SetPinState(LCD_CS,0);	//PUEDE RECIBIR INSTRUCCIONES

	Chip_GPIO_SetPinState(LCD_RS,1);	//ESCRIBIR DATOS

	Chip_GPIO_SetPinState(LCD_WR,0);

	Chip_GPIO_SetPinState(LCD_D0,( (RegValue >> 0) & 0x01));
	Chip_GPIO_SetPinState(LCD_D1,( (RegValue >> 1) & 0x01));
	Chip_GPIO_SetPinState(LCD_D2,( (RegValue >> 2) & 0x01));
	Chip_GPIO_SetPinState(LCD_D3,( (RegValue >> 3) & 0x01));
	Chip_GPIO_SetPinState(LCD_D4,( (RegValue >> 4) & 0x01));
	Chip_GPIO_SetPinState(LCD_D5,( (RegValue >> 5) & 0x01));
	Chip_GPIO_SetPinState(LCD_D6,( (RegValue >> 6) & 0x01));
	Chip_GPIO_SetPinState(LCD_D7,( (RegValue >> 7) & 0x01));
	Chip_GPIO_SetPinState(LCD_D8,( (RegValue >> 8) & 0x01));
	Chip_GPIO_SetPinState(LCD_D9,( (RegValue >> 9) & 0x01));
	Chip_GPIO_SetPinState(LCD_D10,( (RegValue >> 10) & 0x01));
	Chip_GPIO_SetPinState(LCD_D11,( (RegValue >> 11) & 0x01));
	Chip_GPIO_SetPinState(LCD_D12,( (RegValue >> 12) & 0x01));
	Chip_GPIO_SetPinState(LCD_D13,( (RegValue >> 13) & 0x01));
	Chip_GPIO_SetPinState(LCD_D14,( (RegValue >> 14) & 0x01));
	Chip_GPIO_SetPinState(LCD_D15,( (RegValue >> 15) & 0x01));


	Chip_GPIO_SetPinState(LCD_WR,1);


	Chip_GPIO_SetPinState(LCD_CS,1);	//NO PUEDE RECIBIR INSTRUCCIONES
}

void     LCD_IO_WriteReg(uint8_t Reg)
{
	Chip_GPIO_SetPinState(LCD_CS,0);	//PUEDE RECIBIR INSTRUCCIONES

	Chip_GPIO_SetPinState(LCD_RS,0);	//ESCRIBIR COMANDO

	Chip_GPIO_SetPinState(LCD_WR,0);



	Chip_GPIO_SetPinState(LCD_D0,( Reg >> 0 & 0x01));
	Chip_GPIO_SetPinState(LCD_D1,( Reg >> 1 & 0x01));
	Chip_GPIO_SetPinState(LCD_D2,( Reg >> 2 & 0x01));
	Chip_GPIO_SetPinState(LCD_D3,( Reg >> 3 & 0x01));
	Chip_GPIO_SetPinState(LCD_D4,( Reg >> 4 & 0x01));
	Chip_GPIO_SetPinState(LCD_D5,( Reg >> 5 & 0x01));
	Chip_GPIO_SetPinState(LCD_D6,( Reg >> 6 & 0x01));
	Chip_GPIO_SetPinState(LCD_D7,( Reg >> 7 & 0x01));


	Chip_GPIO_SetPinState(LCD_WR,1);


	Chip_GPIO_SetPinState(LCD_CS,1);	//NO PUEDE RECIBIR INSTRUCCIONES
}

uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
	return 0;
}

void     LCD_Delay (uint32_t delay)
{
	contador = 0;
	contador_overflow = delay;
	timer_set = 0;
	while(timer_set==0);
	int a=delay;
}
