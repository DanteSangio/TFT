/*
 * lcd.h
 *
 *  Created on: 13 de jun. de 2017
 *      Author: grama
 */

#ifndef LCD_H_
#define LCD_H_

#include <chip.h>

/*DEFINES DE PINES*/
//Por ahora solo de ejemplo estos pines
#define LCD_RST	LPC_GPIO,1,24
#define LCD_CS	LPC_GPIO,1,25	//CHIP-SELECT HABILITA O DESABILITA EL ILI9341, SI ESTA DESABILITADO NO LE DA BOLA A NADA
#define LCD_RS	LPC_GPIO,1,22	//DATA/COMAND SELECTION
#define LCD_WR	LPC_GPIO,1,19
#define LCD_RD	LPC_GPIO,1,21	//creo que este no es necesario utilizar, ESTE DEBE SER PARA LEER DATOS. SI NO SE USA, SIEMPRE HIGH

#define LCD_D0	LPC_GPIO,0,10
#define LCD_D1	LPC_GPIO,0,5
#define LCD_D2	LPC_GPIO,0,4
#define LCD_D3	LPC_GPIO,3,26
#define LCD_D4	LPC_GPIO,2,12
#define LCD_D5	LPC_GPIO,2,11
#define LCD_D6	LPC_GPIO,2,10
#define LCD_D7	LPC_GPIO,3,25
#define LCD_D8	LPC_GPIO,2,7
#define LCD_D9	LPC_GPIO,2,6
#define LCD_D10	LPC_GPIO,2,5
#define LCD_D11	LPC_GPIO,2,4
#define LCD_D12	LPC_GPIO,2,3
#define LCD_D13	LPC_GPIO,2,2
#define LCD_D14	LPC_GPIO,2,1
#define LCD_D15	LPC_GPIO,2,0



/* LCD IO functions */
void     LCD_IO_Init(void);
void     LCD_IO_WriteData(uint16_t RegValue);
void     LCD_IO_WriteReg(uint8_t Reg);
uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize);
void     LCD_Delay(uint32_t delay);

#endif /* LCD_H_ */
