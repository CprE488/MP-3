/*
 * gs_to_color.c
 *
 *  Created on: Oct 2, 2014
 *      Author: vens
 */

#include "camera_app.h"

typedef struct RGB_STRUCT
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}rgb_color;

typedef union
{
	struct YCBCR_STRUCT
	{
		unsigned char y0;
		unsigned char cb;
		unsigned char y1;
		unsigned char cr;
	}data;
	Xuint32 value;
}ycbcr_color;

#define R_TO_Y  65.738/256
#define G_TO_Y  129.057/256
#define B_TO_Y  25.064/256
#define R_TO_CB -37.945/256
#define G_TO_CB -74.494/256
#define B_TO_CB 112.439/256
#define R_TO_CR 112.439/256
#define G_TO_CR -94.154/256
#define B_TO_CR -18.285/256
#define Y_OFFSET 16
#define CR_OFFSET 128
#define CB_OFFSET 128

//#define R_TO_Y  0.183
//#define G_TO_Y  0.614
//#define B_TO_Y  0.062
//#define R_TO_CR 0.439
//#define G_TO_CR -0.399
//#define B_TO_CR -0.040
//#define R_TO_CB -0.101
//#define G_TO_CB -0.338
//#define B_TO_CB 0.439

//inline ycbcr_color rgb_to_ycbcr(rgb_color pixel0, rgb_color pixel1)
//{
//	ycbcr_color color;
//	color.data.y0 = (unsigned char)(R_TO_Y*pixel0.red + G_TO_Y*pixel0.green + B_TO_Y*pixel0.blue + Y_OFFSET);
//	color.data.y1 = (unsigned char)(R_TO_Y*pixel1.red + G_TO_Y*pixel1.green + B_TO_Y*pixel1.blue + Y_OFFSET);
//	color.data.cr = (unsigned char)(R_TO_CR*(pixel0.red/2+pixel1.red/2) + G_TO_CR*(pixel0.green/2+pixel1.green/2) + B_TO_CR*(pixel0.blue/2+pixel1.blue/2) + CR_OFFSET);
//	color.data.cb = (unsigned char)(R_TO_CB*(pixel0.red/2+pixel1.red/2) + G_TO_CB*(pixel0.green/2+pixel1.green/2) + B_TO_CB*(pixel0.blue/2+pixel1.blue/2) + CB_OFFSET);
//	return color;
//}

inline ycbcr_color rgb_to_ycbcr(rgb_color pixel0, rgb_color pixel1)
{
	ycbcr_color color;
	color.data.y0 = (unsigned char)(R_TO_Y*pixel0.red + G_TO_Y*pixel0.green + B_TO_Y*pixel0.blue + Y_OFFSET);
	color.data.y1 = color.data.y0;//(unsigned char)(R_TO_Y*pixel1.red + G_TO_Y*pixel1.green + B_TO_Y*pixel1.blue + Y_OFFSET);
	color.data.cr = (unsigned char)(R_TO_CR*(pixel0.red) + G_TO_CR*(pixel0.green) + B_TO_CR*(pixel0.blue) + CR_OFFSET);
	color.data.cb = (unsigned char)(R_TO_CB*(pixel0.red) + G_TO_CB*(pixel0.green) + B_TO_CB*(pixel0.blue) + CB_OFFSET);
	return color;
}

void gs_to_color(Xuint32* color, Xuint16* gray)
{
	int row, col;
	int index = 2;//0
	static int count = 0;
	rgb_color rgb_black = {0,0,0};
	rgb_color color1 = {0x93, 0x16, 0xB5};
	rgb_color pixel0, pixel1, red = {0x00, 0x00, 0xFF};
	ycbcr_color black = rgb_to_ycbcr(rgb_black, rgb_black);
	ycbcr_color r =  rgb_to_ycbcr(red, red);
	printf("%d\n", count++);
	//printf("0x%08X == 0x%08X, y0=0x%02X, y1=0x%02X, Cr=0x%02X, Cb=0x%02X\n", 0x6E29F029, (unsigned int)r.value, r.data.y0, r.data.y1, r.data.cr, r.data.cb);

//	printf("-----------------------------------------------------\n");
//	for(row=0;row<8;row++)
//	{
//		for(col=0;col<8;col++)
//		{
//			printf("0x%02X  ", gray[row*1920+col]&0xFF);
//		}
//		printf("\n");
//	}

	for(col=0;col<1920;col++)
	{
		*color++ = black.value;
	}
	for(row=2;row<1078;row++)
	{
		*color++ = black.value;
		for(col=2;col<1918;col+=2)
		{
			switch(index)
			{
//			case 0:
//				// Green
//				pixel0.red = gray[(row-1)*1920+col] & 0x00FF;
//				pixel0.green = gray[row*1920+col] & 0x00FF;
//				pixel0.blue = gray[(row)*1920+col-1] & 0x00FF;
//				// Blue
//				pixel1.red = gray[(row-1)*1920+col] & 0x00FF;
//				pixel1.green = gray[row*1920+col] & 0x00FF;
//				pixel1.blue = gray[row*1920+col+1] & 0x00FF;
//				break;
//			case 1:
//				// Blue
//				pixel0.red = gray[(row-1)*1920+col-1] & 0x00FF;
//				pixel0.green = gray[row*1920+col-1] & 0x00FF;
//				pixel0.blue = gray[row*1920+col] & 0x00FF;
//				// Green
//				pixel1.red = gray[(row-1)*1920+col+1] & 0x00FF;
//				pixel1.green = gray[row*1920+col+1] & 0x00FF;
//				pixel1.blue = gray[row*1920+col] & 0x00FF;
//				break;
//			case 2:
//				// Red
//				pixel0.red = gray[row*1920+col] & 0x00FF;
//				pixel0.green = gray[row*1920+col-1] & 0x00FF;
//				pixel0.blue = gray[(row-1)*1920+col-1] & 0x00FF;
//				// Green
//				pixel1.red = gray[row*1920+col] & 0x00FF;
//				pixel1.green = gray[row*1920+col+1] & 0x00FF;
//				pixel1.blue = gray[(row-1)*1920+col+1] & 0x00FF;
//				break;
//			case 3:
//				// Green
//				pixel0.red = gray[row*1920+col-1] & 0x00FF;
//				pixel0.green = gray[row*1920+col] & 0x00FF;
//				pixel0.blue = gray[(row-1)*1920+col] & 0x00FF;
//				// Red
//				pixel1.red = gray[row*1920+col+1] & 0x00FF;
//				pixel1.green = gray[row*1920+col] & 0x00FF;
//				pixel1.blue = gray[(row-1)*1920+col] & 0x00FF;
//				break;
			case 0:
				// Green
				pixel0.blue = gray[row*1920+col-1] & 0x00FF;
				pixel0.green = gray[row*1920+col] & 0x00FF;
				pixel0.red = gray[(row-1)*1920+col] & 0x00FF;
				// Blue
				pixel1.red = gray[(row-1)*1920+col-1] & 0x00FF;
				pixel1.green = gray[row*1920+col] & 0x00FF;
				pixel1.blue = gray[row*1920+col+1] & 0x00FF;
				pixel1 = pixel0;
				*color++ = rgb_to_ycbcr(pixel0, pixel1).value;
				break;
			case 1:
				// Blue
				pixel0.red = gray[(row-1)*1920+col-1] & 0x00FF;
				pixel0.green = gray[row*1920+col-1] & 0x00FF;
				pixel0.blue = gray[row*1920+col] & 0x00FF;
				// Green
				pixel1.red = gray[(row-1)*1920+col+1] & 0x00FF;
				pixel1.green = gray[row*1920+col+1] & 0x00FF;
				pixel1.blue = gray[row*1920+col] & 0x00FF;
				break;
			case 2:
//				// Red
//				pixel0.red = gray[row*1920+col] & 0x00FF;
//				pixel0.green = gray[row*1920+col-1] & 0x00FF;
//				pixel0.blue = gray[(row-1)*1920+col-1] & 0x00FF;
//				// Green
//				pixel1.red = gray[row*1920+col] & 0x00FF;
//				pixel1.green = gray[row*1920+col+1] & 0x00FF;
//				pixel1.blue = gray[(row-1)*1920+col+1] & 0x00FF;
//				pixel0.red = 0x00;
//				pixel0.green = 0x00;
//				pixel0.blue = 0x00;
//				pixel1.red = 0x00;
//				pixel1.green = 0x00;
//				pixel1.blue = 0x00;
				*color++ = black.value;
				break;
			case 3:
				// Green
				pixel0.red = gray[row*1920+col-1] & 0x00FF;
				pixel0.green = gray[row*1920+col] & 0x00FF;
				pixel0.blue = gray[(row-1)*1920+col] & 0x00FF;
				// Red
				pixel1.red = gray[row*1920+col+1] & 0x00FF;
				pixel1.green = gray[row*1920+col] & 0x00FF;
				pixel1.blue = gray[(row-1)*1920+col] & 0x00FF;
				break;
			}
			//*color++ = rgb_to_ycbcr(pixel0, pixel1).value;
			//*color++ = 0x22913691;//rgb_to_ycbcr(color1, color1).value;//0xF0525A52; //
		}
		index ^= 2;//2
		*color++ = black.value;
	}
	for(col=0;col<1920;col++)
	{
		*color++ = black.value;
	}
	return;
}


