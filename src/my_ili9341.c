/**
  ******************************************************************************
  * @file    ili9341.c
  * @author  MCD Application Team
  * @version V1.0.2
  * @date    02-December-2014
  * @brief   This file includes the LCD driver for ILI9341 LCD.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "my_ili9341.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup Components
  * @{
  */

/** @addtogroup ILI9341
  * @brief This file provides a set of functions needed to drive the
  *        ILI9341 LCD.
  * @{
  */

/** @defgroup ILI9341_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */

/** @defgroup ILI9341_Private_Defines
  * @{
  */

#define swap(type, i, j) {type t = i; i = j; j = t;}

/**
  * @}
  */

/** @defgroup ILI9341_Private_Macros
  * @{
  */
/**
  * @}
  */

/** @defgroup ILI9341_Private_Variables
  * @{
  */

uint32_t color;
char orientacion = LANDSCAPE;

/**
  * @}
  */

/** @defgroup ILI9341_Private_FunctionPrototypes
  * @{
  */

/**
  * @}
  */

/** @defgroup ILI9341_Private_Functions
  * @{
  */

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
void ili9341_Init(void)
{
	color = 0;

	LCD_IO_Init();

	Chip_GPIO_SetPinOutHigh(LCD_RST);
	LCD_Delay(5);
	Chip_GPIO_SetPinOutLow(LCD_RST);
	LCD_Delay(15);
	Chip_GPIO_SetPinOutHigh(LCD_RST);
	LCD_Delay(15);

	Chip_GPIO_SetPinOutLow(LCD_CS);

	    ili9341_WriteReg(LCD_POWERA);
	    ili9341_WriteData(0x39);
	    ili9341_WriteData(0x2C);
	    ili9341_WriteData(0x00);
	    ili9341_WriteData(0x34);
	    ili9341_WriteData(0x02);

	    ili9341_WriteReg(LCD_POWERB);
	    ili9341_WriteData(0x00);
	    ili9341_WriteData(0X81);
	    ili9341_WriteData(0X30);

	    ili9341_WriteReg(LCD_DTCA);
	    ili9341_WriteData(0x85);
	    ili9341_WriteData(0x00);
	    ili9341_WriteData(0x78);

	    ili9341_WriteReg(LCD_DTCB);
	    ili9341_WriteData(0x00);
	    ili9341_WriteData(0x00);

	    ili9341_WriteReg(LCD_POWER_SEQ);
	    ili9341_WriteData(0x64);
	    ili9341_WriteData(0x03);
	    ili9341_WriteData(0X12);
	    ili9341_WriteData(0X81);

	    ili9341_WriteReg(LCD_PRC);
	    ili9341_WriteData(0x20);

	    ili9341_WriteReg(LCD_POWER1);    //Power control
	    ili9341_WriteData(0x23);   //VRH[5:0]

	    ili9341_WriteReg(LCD_POWER2);    //Power control
	    ili9341_WriteData(0x10);   //SAP[2:0];BT[3:0]

	    ili9341_WriteReg(LCD_VCOM1);    //VCM control
	    ili9341_WriteData(0x3e);   //Contrast
	    ili9341_WriteData(0x28);

	    ili9341_WriteReg(LCD_VCOM2);    //VCM control2
	    ili9341_WriteData(0x86);   //--

	    ili9341_WriteReg(LCD_MAC);    // Memory Access Control
	    ili9341_WriteData(0x48);

	    ili9341_WriteReg(LCD_PIXEL_FORMAT);
	    ili9341_WriteData(0x55);

	    ili9341_WriteReg(LCD_FRMCTR1);
	    ili9341_WriteData(0x00);
	    ili9341_WriteData(0x18);

	    ili9341_WriteReg(LCD_DFC);    // Display Function Control
	    ili9341_WriteData(0x08);
	    ili9341_WriteData(0x82);
	    ili9341_WriteData(0x27);

	    ili9341_WriteReg(LCD_SLEEP_OUT);    //Exit Sleep
	    LCD_Delay(120);

	    ili9341_WriteReg(LCD_DISPLAY_ON);    //Display on
	    ili9341_WriteReg(LCD_GRAM);

		setColor(255, 255, 255);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval LCD Register Value.
  */
uint16_t ili9341_ReadID(void)
{
  LCD_IO_Init();
  return ((uint16_t)ili9341_ReadData(LCD_READ_ID4, LCD_READ_ID4_SIZE));
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOn(void)
{
  /* Display On */
  ili9341_WriteReg(LCD_DISPLAY_ON);
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOff(void)
{
  /* Display Off */
  ili9341_WriteReg(LCD_DISPLAY_OFF);
}

/**
  * @brief  Writes  to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9341_WriteReg(uint8_t LCD_Reg)
{
  LCD_IO_WriteReg(LCD_Reg);
}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9341_WriteData(uint16_t RegValue)
{
  LCD_IO_WriteData(RegValue);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  RegValue: Address of the register to read
  * @param  ReadSize: Number of bytes to read
  * @retval LCD Register Value.
  */
uint32_t ili9341_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
  /* Read a max of 4 bytes */
  return (LCD_IO_ReadData(RegValue, ReadSize));
}

/**
  * @brief  Get LCD PIXEL WIDTH.
  * @param  None
  * @retval LCD PIXEL WIDTH.
  */
uint16_t ili9341_GetLcdPixelWidth(void)
{
  /* Return LCD PIXEL WIDTH */
  return ILI9341_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Get LCD PIXEL HEIGHT.
  * @param  None
  * @retval LCD PIXEL HEIGHT.
  */
uint16_t ili9341_GetLcdPixelHeight(void)
{
  /* Return LCD PIXEL HEIGHT */
  return ILI9341_LCD_PIXEL_HEIGHT;
}

/**
  * @}
  */

void setColor(uint16_t r, uint16_t g, uint16_t b)
{

	color =((g&28)<<3|b>>3)| ((r&248)|g>>5)<<8;
	//color = ( ((r&248)<<8) || ((g&252)<<3) || (b>>3) );
}

/**
  * @}
  */

void fillRect(int x1, int y1, int x2, int y2)
{
	if (x1>x2)
	{
		swap(int, x1, x2);
	}
	if (y1>y2)
	{
		swap(int, y1, y2);
	}

	setXY(x1, y1, x2, y2);
	_fast_fill_16(color, (((x2-x1)+1)*((y2-y1)+1)));
}

/**
  * @}
  */
void clrScr()
{
	clrXY();

	_fast_fill_16(0,((ILI9341_LCD_PIXEL_WIDTH+1)*(ILI9341_LCD_PIXEL_HEIGHT+1)));
}

/**
  * @}
  */

void clrXY()
{
	if (orientacion==PORTRAIT)
		setXY(0,0,ILI9341_LCD_PIXEL_HEIGHT,ILI9341_LCD_PIXEL_WIDTH);
	else
		setXY(0,0,ILI9341_LCD_PIXEL_WIDTH,ILI9341_LCD_PIXEL_HEIGHT);

}

/**
  * @}
  */

void setXY(int x1, int y1, int x2, int y2)
{
	if (orientacion==LANDSCAPE)
	{
		swap(int, x1, y1);
		swap(int, x2, y2);
		y1=ILI9341_LCD_PIXEL_HEIGHT-y1;
		y2=ILI9341_LCD_PIXEL_HEIGHT-y2;
		swap(int, y1, y2);
	}

	ili9341_WriteReg(LCD_COLUMN_ADDR);
	ili9341_WriteData(x1>>8);
	ili9341_WriteData(x1);
	ili9341_WriteData(x2>>8);
	ili9341_WriteData(x2);
	ili9341_WriteReg(LCD_PAGE_ADDR);
	ili9341_WriteData(y1>>8);
	ili9341_WriteData(y1);
	ili9341_WriteData(y2>>8);
	ili9341_WriteData(y2);
	ili9341_WriteReg(LCD_GRAM);
}
/**
  * @}
  */

void _fast_fill_16(uint16_t dato, int pix)
{
	int blocks;
	int i;

	Chip_GPIO_SetPinOutLow(LCD_CS);
	Chip_GPIO_SetPinState(LCD_RS,1);	//ESCRIBIR DATOS

	Chip_GPIO_SetPinState(LCD_D0,( dato >> 0 & 0x01));
	Chip_GPIO_SetPinState(LCD_D1,( dato >> 1 & 0x01));
	Chip_GPIO_SetPinState(LCD_D2,( dato >> 2 & 0x01));
	Chip_GPIO_SetPinState(LCD_D3,( dato >> 3 & 0x01));
	Chip_GPIO_SetPinState(LCD_D4,( dato >> 4 & 0x01));
	Chip_GPIO_SetPinState(LCD_D5,( dato >> 5 & 0x01));
	Chip_GPIO_SetPinState(LCD_D6,( dato >> 6 & 0x01));
	Chip_GPIO_SetPinState(LCD_D7,( dato >> 7 & 0x01));
	Chip_GPIO_SetPinState(LCD_D8,( dato >> 8 & 0x01));
	Chip_GPIO_SetPinState(LCD_D9,( dato >> 9 & 0x01));
	Chip_GPIO_SetPinState(LCD_D10,( dato >> 10 & 0x01));
	Chip_GPIO_SetPinState(LCD_D11,( dato >> 11 & 0x01));
	Chip_GPIO_SetPinState(LCD_D12,( dato >> 12 & 0x01));
	Chip_GPIO_SetPinState(LCD_D13,( dato >> 13 & 0x01));
	Chip_GPIO_SetPinState(LCD_D14,( dato >> 14 & 0x01));
	Chip_GPIO_SetPinState(LCD_D15,( dato >> 15 & 0x01));

	blocks = pix/16;

	for (int i=0; i<blocks; i++)
	{
		int c=0;

		for(c=0;c<16;c++)
		{
			Chip_GPIO_SetPinOutLow(LCD_WR);
			Chip_GPIO_SetPinOutHigh(LCD_WR);
		}

	}
	if ((pix % 16) != 0)
		for (i = 0; i<(pix % 16)+1; i++)
		{
			Chip_GPIO_SetPinOutLow(LCD_WR);
			Chip_GPIO_SetPinOutHigh(LCD_WR);
		}

	Chip_GPIO_SetPinOutHigh(LCD_CS);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
