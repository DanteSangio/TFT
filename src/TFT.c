/*
===============================================================================
 Name        : TFT.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include<my_ili9341.h>
#include "math.h"

// TODO: insert other definitions and declarations here
#define TICKRATE_HZ1 (1000)	/* 10 ticks per second */

#define BLACK		0x0000
#define WHITE		0xFFFF
#define RED			0xF800
#define GREEN		0x07E0
#define BLUE		0x102E
#define CYAN		0x07FF
#define MAGENTA		0xF81F
#define NAVY		0x000F
#define DARKGREEN	0x03E0
#define PURPLE		0x780F
#define OLIVE		0x7BE0
#define DARKGREY	0x7BEF
#define DARKCYAN	0x001F
#define YELLOW		0xFFE0
#define ORANGE		0xFD20

#define PI	3.14159265359

uint16_t indexed_color[] = { BLACK, WHITE, RED, GREEN, BLUE, CYAN, MAGENTA, NAVY, DARKGREEN, PURPLE, OLIVE, DARKGREY, DARKCYAN, YELLOW, ORANGE};

#define BACKGROUND BLACK

uint32_t contador=0;
uint32_t contador_overflow=0;
uint32_t timer_set=0;
int espera = 0;
int led_count=0;
uint16_t fase = 0;

char pantalla[320] = {0};
char pantalla_anterior[320] = {0};


void InitSystem(void);

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */

void SysTick_Handler(void)
{
	led_count++;
	if(led_count==500)
	{
		led_count=0;
		Chip_GPIO_SetPinToggle(LPC_GPIO,0,22);
	}



	if(timer_set == 0 && contador_overflow!=0)
	{
		contador++;
		if(contador==contador_overflow)
		{
			timer_set = 1;
			contador_overflow = 0;
		}
		espera++;
	}
}

int main(void)
{


	InitSystem();
	setColor(0,0,0);
	fillRect(0,0,319,239);

	uint16_t i = 0;

    while(1)
    {
    	armarSeno();

		for(i = 0; i < 320; i++) {
			setColor(0,0,0);
			fillRect(i,pantalla_anterior[i],i,pantalla_anterior[i]);

			setColor(255,0,0);
			fillRect(i,pantalla[i],i,pantalla[i]);
			pantalla_anterior[i] = pantalla[i];
		}
    }
    return 0 ;
}

void InitSystem(void)
{
	#if defined (__USE_LPCOPEN)
	// Read clock settings and update SystemCoreClock variable
	SystemCoreClockUpdate();
	#if !defined(NO_BOARD_LIB)
	// Set up and initialize all required blocks and
	// functions related to the board hardware
	Board_Init();
	// Set the LED to the state of "On"
	Board_LED_Set(0, true);
	#endif
	#endif
	// TODO: insert code here
	Chip_SystemInit();

	/* Initializes GPIO */
	Chip_GPIO_Init(LPC_GPIO);
	Chip_IOCON_Init(LPC_IOCON);

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(SystemCoreClock / TICKRATE_HZ1);

    ili9341_Init();
}

void armarSeno(void) {
    uint16_t pos, tamano, amplitudMax;
    uint16_t tmp = 0;
    tamano = 320;
    amplitudMax = 119;
    float delta = (2 * PI) / tamano;
    for(pos = 0; pos < tamano; pos++)
    {
        tmp = (amplitudMax + 1) + (amplitudMax * 0.9) * sinf(pos * delta + fase * delta);
        pantalla[pos] = tmp;
    }
    fase++;
    if(fase * delta > 2 * PI) fase = 0;
}
