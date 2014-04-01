/******************** (C) COPYRIGHT 2012 RadioSHack ********************
 * File Name          : strip.pde
 * Author             : TRS
 * Version            : V1.0
 * Date               : 27/04/2012
 * Description        : Main program body
 ********************************************************************************
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
 * AS A RESULT, RS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
 * INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
 * CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
 * INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *******************************************************************************/

#include <avr/pgmspace.h>

void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate);
void send_strip(uint32_t data);
void	reset_strip();

// ******** DEBUG ==== should auto config to adapt different mother board *********
//#define DATA_1 (PORTF |=  0X01)    // DATA 1    // for ATMEGA
//#define DATA_0 (PORTF &=  0XFE)    // DATA 0    // for ATMEGA
//#define STRIP_PINOUT DDRF=0xFF  // for ATMEGA
#define DATA_1 (PORTC |=  0X01)    // DATA 1    // for UNO
#define DATA_0 (PORTC &=  0XFE)    // DATA 0    // for UNO
#define STRIP_PINOUT (DDRC=0xFF)    // for UNO

PROGMEM const unsigned long pattern_test_red[10][10]={
	{0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xff0000},
};

PROGMEM const unsigned long pattern_test_blue[10][10]={
	{0x00ff00,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x00ff00,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x00ff00,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x00ff00,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x00ff00,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x00ff00,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ff00,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ff00,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ff00,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x00ff00},
};

PROGMEM const unsigned long pattern_test_green[10][10]={
	{0x0000ff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x0000ff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x0000ff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x0000ff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x0000ff,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x0000ff,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x0000ff,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x0000ff,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x0000ff,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x0000ff},
};

PROGMEM const unsigned long pattern_test_white[10][10]={
	{0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff},
};

PROGMEM const unsigned long pattern_test_comet1[][10]={
	{0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000},
	{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff},
};

PROGMEM const unsigned long pattern_test_comet2[][10]={
	{0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000},
	{0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000},
	{0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000},
	{0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000},
	{0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff},
	{0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000},
	{0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000},
	{0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000},
	{0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000},
	{0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0x111111,0x444444,0xffffff},
};

PROGMEM const unsigned long pattern_test_comet3[][10]={
	{0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff},
	{0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0xffffff,0x444444},
	{0x111111,0x444444,0xffffff,0x000000,0x000000,0x000000,0x000000,0xffffff,0x444444,0x111111},
	{0x000000,0x111111,0x444444,0xffffff,0x000000,0x000000,0xffffff,0x444444,0x111111,0x000000},
	{0x000000,0x000000,0x111111,0x444444,0xffffff,0xffffff,0x444444,0x111111,0x000000,0x000000},
	{0x000000,0x000000,0x111111,0x444444,0xffffff,0xffffff,0x444444,0x111111,0x000000,0x000000},
	{0x000000,0x000000,0x000000,0xffffff,0x444444,0x444444,0xffffff,0x000000,0x000000,0x000000},
	{0x000000,0x000000,0xffffff,0x444444,0x111111,0x111111,0x444444,0xffffff,0x000000,0x000000},
	{0x000000,0xffffff,0x444444,0x111111,0x000000,0x000000,0x111111,0x444444,0xffffff,0x000000},
	{0xffffff,0x444444,0x111111,0x000000,0x000000,0x000000,0x000000,0x111111,0x444444,0xffffff},
};

PROGMEM const unsigned long pattern_test_rainbow[10][10]={
	{0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000},
	{0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000},
	{0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000},
	{0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff},
	{0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff},
	{0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00,0x0000ff},
	{0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00,0x00ff00},
	{0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00,0xffff00},
	{0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000,0xff7f00},
	{0xff7f00,0xffff00,0x00ff00,0x0000ff,0x6f00ff,0x8f00ff,0x000000,0x000000,0x000000,0xff0000},
};

////////////////////////////////////////////////////////////////////////////////

PROGMEM const unsigned long blink_green_pink[2][10]={
	{0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF,0x0099FF},
	{0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000,0xFF0000},
};

								 //GGBBRR
#define GREEN_1_ 0xFF0000
#define GREEN_2_ 0x440000
#define GREEN_3_ 0x110000

#define PINK__1_ 0x0099FF
//saturation
// #define PINK__2_ 0x1BA4FF //3
// #define PINK__3_ 0x36AFFF //3
// #define PINK__2_ 0x36AFF8 //6 mod
// #define PINK__3_ 0x6CC4F0 //6 mod
#define PINK__2_ 0x36AFFF //6
#define PINK__3_ 0x6CC4FF //6

//value
// #define PINK__2_ 0x0079C9 //6
// #define PINK__3_ 0x005893 //6

#define ________ 0x000000

PROGMEM const unsigned long green_pink_cross[][10]={
	{PINK__1_,________,________,________,________, ________,________,________,________,GREEN_1_},
	{PINK__2_,PINK__1_,________,________,________, ________,________,________,GREEN_1_,GREEN_2_},
	{PINK__3_,PINK__2_,PINK__1_,________,________, ________,________,GREEN_1_,GREEN_2_,GREEN_3_},
	{________,PINK__3_,PINK__2_,PINK__1_,________, ________,GREEN_1_,GREEN_2_,GREEN_3_,________},
	{________,________,PINK__3_,PINK__2_,PINK__1_, GREEN_1_,GREEN_2_,GREEN_3_,________,________},
	{________,________,________,PINK__3_,GREEN_1_, PINK__1_,GREEN_3_,________,________,________},
	{________,________,________,GREEN_1_,GREEN_2_, PINK__2_,PINK__1_,________,________,________},
	{________,________,GREEN_1_,GREEN_2_,GREEN_3_, PINK__3_,PINK__2_,PINK__1_,________,________},
	{________,GREEN_1_,GREEN_2_,GREEN_3_,________, ________,PINK__3_,PINK__2_,PINK__1_,________},
	{GREEN_1_,GREEN_2_,GREEN_3_,________,________, ________,________,PINK__3_,PINK__2_,PINK__1_},
	{GREEN_2_,GREEN_3_,________,________,________, ________,________,________,PINK__3_,PINK__2_},
	{GREEN_3_,________,________,________,________, ________,________,________,________,PINK__3_},
	{________,________,________,________,________, ________,________,________,________,________},
	{GREEN_1_,________,________,________,________, ________,________,________,________,PINK__1_},
	{GREEN_2_,GREEN_1_,________,________,________, ________,________,________,PINK__1_,PINK__2_},
	{GREEN_3_,GREEN_2_,GREEN_1_,________,________, ________,________,PINK__1_,PINK__2_,PINK__3_},
	{________,GREEN_3_,GREEN_2_,GREEN_1_,________, ________,PINK__1_,PINK__2_,PINK__3_,________},
	{________,________,GREEN_3_,GREEN_2_,GREEN_1_, PINK__1_,PINK__2_,PINK__3_,________,________},
	{________,________,________,GREEN_3_,PINK__1_, GREEN_1_,PINK__3_,________,________,________},
	{________,________,________,PINK__1_,PINK__2_, GREEN_2_,GREEN_1_,________,________,________},
	{________,________,PINK__1_,PINK__2_,PINK__3_, GREEN_3_,GREEN_2_,GREEN_1_,________,________},
	{________,PINK__1_,PINK__2_,PINK__3_,________, ________,GREEN_3_,GREEN_2_,GREEN_1_,________},
	{PINK__1_,PINK__2_,PINK__3_,________,________, ________,________,GREEN_3_,GREEN_2_,GREEN_1_},
	{PINK__2_,PINK__3_,________,________,________, ________,________,________,GREEN_3_,GREEN_2_},
	{PINK__3_,________,________,________,________, ________,________,________,________,GREEN_3_},
	{________,________,________,________,________, ________,________,________,________,________},
};


// *****************************************************************************

#define TELEOP_PIN 8
void setup() {                

	STRIP_PINOUT;        // set output pin - DEBUG: should auto detect which mother board for use

	reset_strip();
	//noInterrupts();
	
	pinMode(TELEOP_PIN, OUTPUT);

}
// *****************************************************************************
void loop() 
{
	if(digitalRead(TELEOP_PIN)){
	  send_1M_pattern(green_pink_cross, 26, 200);
	}
	else
	{
		send_1M_pattern(blink_green_pink, 2, 600);
	}
	// while (1)
	// {
		
	// 	//send_1M_pattern(pattern_test_comet1, 10, 70);
	// 	//send_1M_pattern(green_pink_cross, 10, 200);
	// 	// ;
	// }




	// #define NUMROWS 255
	// #define NUMCOLS	10
	// #define delayMiliseconds delay

	// while(1)
	// {
	// 	int temp = 0;
	// 	for(int row=0; row<NUMROWS; row++){
	// 			for(int col=0; col<NUMCOLS; col++){
	// 					send_strip(temp<<8);//0xggbbrr //temp<<16|temp<<8|temp
	// 			}
	// 			temp++;
	// 			delayMiliseconds(25);
	// 	}
	// 	for(int col=0; col<NUMCOLS; col++){
	// 			send_strip(0x000000); //0xggbbrr
	// 	}
	// 	delayMiliseconds(1000);
	// }

	

	// send_1M_pattern(pattern_test_red, 10, 500);
	// delay(500);
	// send_1M_pattern(pattern_test_blue, 10, 500);
	// delay(500);
	// send_1M_pattern(pattern_test_green, 10, 500);
	// delay(500);
	// send_1M_pattern(pattern_test_white, 10, 500);
	// delay(500);
	// send_1M_pattern(pattern_test_comet1, 10, 70); //Slow to end
	// delay(500);
	// send_1M_pattern(pattern_test_comet2, 10, 70); //faster to end
	// delay(500);
	// send_1M_pattern(pattern_test_comet3, 10, 70); //comeigntogether
	// delay(500);
	
	// while (1)
	// {
	// 	send_1M_pattern(pattern_test_rainbow, 10, 70);
	// }

	


	/*
	frame++;
		if(frame<=10) LEDSTRIP_PATTERN_0();
		if(10<frame<=20) LEDSTRIP_PATTERN_0();
		if(20<frame<=30) LEDSTRIP_PATTERN_0();
		if(frame>30) frame=1;
	 */
	//delay(1);
}


/*******************************************************************************
 * Function Name  : send_1M_pattern
 * Description    : Transmit pattern to whole 1 meter strip
 *                  
 * Input          : pointer to ROM pattern
 *                : pattern length (Number of rows)
 *                : frame rate (Larger number is slower)
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_1M_pattern(const unsigned long data[][10], int pattern_no, int frame_rate)
{
	int i=0;
	int j=0;
	uint32_t temp_data;

	for (i=0;i<pattern_no;i++)
	{
		noInterrupts();
		for (j=0;j<10;j++)
		{
			temp_data=pgm_read_dword_near(&data[i][j]);
			send_strip(temp_data);
		}
		interrupts();

		delay(frame_rate);

	}
}


/*******************************************************************************
 * Function Name  : send_strip
 * Description    : Transmit 24 pulse to LED strip
 *                  
 * Input          : 24-bit data for the strip
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void send_strip(uint32_t data)
{
	int i;
	unsigned long j=0x800000;
	
 
	for (i=0;i<24;i++)
	{
		if (data & j)
		{
			DATA_1;
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");    
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			
/*----------------------------*/
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");  
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");  
			__asm__("nop\n\t");  
			__asm__("nop\n\t");        
/*----------------------------*/      
			DATA_0;
		}
		else
		{
			DATA_1;
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");    
			DATA_0;
/*----------------------------*/      
			__asm__("nop\n\t");
			__asm__("nop\n\t");
			__asm__("nop\n\t");      
/*----------------------------*/         
		}

		j>>=1;
	}
}

/*******************************************************************************
 * Function Name  : reset_strip
 * Description    : Send reset pulse to reset all color of the strip
 *                  
 * Input          : None
 *                  
 * Output         : None
 * Return         : None
 *******************************************************************************/
void	reset_strip()
{
	DATA_0;
	delayMicroseconds(20);
}











