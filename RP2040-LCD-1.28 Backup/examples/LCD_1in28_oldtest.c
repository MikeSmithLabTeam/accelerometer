/*****************************************************************************
* | File      	:   LCD_1in28_test.c
* | Author      :   Waveshare team
* | Function    :   1.3inch LCD  test demo
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-08-20
* | Info        :
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
******************************************************************************/
#include "LCD_Test.h"
#include "LCD_1in28.h"
#include "QMI8658.h"
#include <math.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

int LCD_1in28_test(void)
{
    if (DEV_Module_Init() != 0)
    {
        return -1;
    }
    printf("LCD_1in28_test Demo\r\n");
    adc_init();
    adc_gpio_init(29);
    adc_select_input(3);
    /* LCD Init */
    printf("1.28inch LCD demo...\r\n");
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(WHITE);
    DEV_SET_PWM(60);
    // LCD_SetBacklight(1023);
    UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // /* GUI */
    printf("drawing...\r\n");
    // /*2.Drawing on the image*/


#if 1

    float acc[3], gyro[3];
    unsigned int tim_count = 0;
    QMI8658_init();
	QMI8658_config_acc(QMI8658AccRange_8g);
    QMI8658_config_ae();

    int numpts = 8000;
	
	float mean_acc_x = 0;
	float mean_acc_y = 0;
	float mean_acc_z = 0;
	
	float temp_acc_x;
	float temp_acc_y;
	float temp_acc_z;
	
	float pk_acc_x;
	float pk_acc_y;
	float pk_acc_z;
	

    while (true)
    {   
		const float conversion_factor = 3.3f / (1 << 12) * 2;
		
		//reset
		temp_acc_x=0;
		temp_acc_y=0;
		temp_acc_z=0;
		
		pk_acc_x=0;
		pk_acc_y=0;
		pk_acc_z=0;
		
		printf("Measuring\n");
		for (int i=0; i<numpts;i++){
			
			//uint16_t result = adc_read();
			//printf("Raw value: 0x%03x, voltage: %f V\n", result, result * conversion_factor);
			uint16_t result = adc_read();
			QMI8658_read_xyz(acc, gyro, &tim_count);
			
			//Output values to Serial
			//printf("tim_count = %d\r\n", tim_count);
			//printf("acc = %4.3fmg, %4.3fmg, %4.3fmg\r\n", acc[0], acc[1], acc[2]);
			//printf("gyr = %4.3fmg, %4.3fmg, %4.3fmg\r\n", gyro[0], gyro[1], gyro[2]);
			
			temp_acc_x += acc[0];
			temp_acc_y += acc[1];
			temp_acc_z += acc[2];
			
			//Sum of square differences from mean
			pk_acc_x += (acc[0]-mean_acc_x)*(acc[0]-mean_acc_x);
			pk_acc_y += (acc[1]-mean_acc_y)*(acc[1]-mean_acc_y);
			pk_acc_z += (acc[2]-mean_acc_z)*(acc[2]-mean_acc_z);
		}
		
		mean_acc_x = temp_acc_x /numpts;
		mean_acc_y = temp_acc_y/ numpts;
		mean_acc_z = temp_acc_z / numpts;
		
		//Pk amplitude of sin wave
		pk_acc_x = sqrt(2 * pk_acc_x / numpts);
		pk_acc_y = sqrt(2 * pk_acc_y / numpts);
		pk_acc_z = sqrt(2 * pk_acc_z / numpts);
        
		//printf("drawing\n");
		//Paint_Clear(WHITE);
		//Paint_DrawString_EN(30, 50, "PK_ACC_X = ", &Font16, WHITE, BLACK);
        //Paint_DrawString_EN(30, 75, "PK_ACC_Y = ", &Font16, WHITE, BLACK);
        //Paint_DrawString_EN(30, 100, "PK_ACC_Z = ", &Font16, WHITE, BLACK);
        //Paint_DrawString_EN(30, 125, "AV_ACC_X = ", &Font16, WHITE, BLACK);
		//Paint_DrawString_EN(30, 150, "AV_ACC_Y = ", &Font16, WHITE, BLACK);
		//Paint_DrawString_EN(30, 175, "AV_ACC_Z = ", &Font16, WHITE, BLACK);
        
        //Paint_DrawNum(120, 50, pk_acc_x, &Font16, 2, BLACK, WHITE);
        //Paint_DrawNum(120, 75, pk_acc_y, &Font16, 2, BLACK, WHITE);
        //Paint_DrawNum(120, 100, pk_acc_z, &Font16, 2, BLACK, WHITE);
        //Paint_DrawNum(120, 125, mean_acc_x, &Font16, 2, BLACK, WHITE);
        //Paint_DrawNum(120, 150, mean_acc_y, &Font16, 2, BLACK, WHITE);
        //Paint_DrawNum(120, 175, mean_acc_z, &Font16, 2, BLACK, WHITE);

        //LCD_1IN28_Display(BlackImage);
    }

#endif

    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;

    DEV_Module_Exit();
    return 0;
}
