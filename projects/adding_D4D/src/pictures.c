/************************************************************************
*
*  Freescale INC.
*  ALL RIGHTS RESERVED
*  (c) Copyright 2008 Freescale, Inc.
*
*************************************************************************
*
*  FILE NAME: fsl_menu_pictures.c
*
*  PURPOSE: Bitmaps used in fsl menu.
*
*  AUTHOR: 
*
***********************************************************************/

#include "pictures.h"

#include "../d4d/d4d.h"

const Byte icon_fsl[];
const Byte check_box_checked[];

const Word palette_Equ[];
const Byte Equ_frame_0012[];
const Byte Equ_frame_0011[];
const Byte Equ_frame_0010[];
const Byte Equ_frame_0009[];
const Byte Equ_frame_0008[];
const Byte Equ_frame_0007[];
const Byte Equ_frame_0006[];
const Byte Equ_frame_0005[];
const Byte Equ_frame_0004[];
const Byte Equ_frame_0003[];
const Byte Equ_frame_0002[];
const Byte Equ_frame_0001[];

/* Color palette */
const Word palette_gauge[];
const Byte gauge[]; 


/*****************************************************************************
*
* Bitmap declarations
*
*
*****************************************************************************/

D4D_DECLARE_BMP(bmpFreescale, icon_fsl, NULL)
                            
D4D_DECLARE_BMP(bmpGauge, gauge, palette_gauge)

D4D_DECLARE_BMP(bmpCheckBCheck,  check_box_checked, NULL)

D4D_DECLARE_BMP(bmpAnimEqu1, Equ_frame_0001, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu2, Equ_frame_0002, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu3, Equ_frame_0003, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu4, Equ_frame_0004, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu5, Equ_frame_0005, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu6, Equ_frame_0006, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu7, Equ_frame_0007, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu8, Equ_frame_0008, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu9, Equ_frame_0009, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu10, Equ_frame_0010, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu11, Equ_frame_0011, palette_Equ)
D4D_DECLARE_BMP(bmpAnimEqu12, Equ_frame_0012, palette_Equ)




/* Compression ratio: 39% */
const Byte icon_fsl[] = {

/* Bitmap dimension (W x H) */
0x00, 0x18, 0x00, 0x18,

/* Color mode */
0x80, 0x05,

/* Data */
0xFF, 0xFF, 0x39, 0xF6, 0xF6, 0x00, 0xF7, 0xFF, 0xFF, 0x11, 0xFA, 0xF1, 0xEC, 0xEC, 0x01, 0xF7,
0xFF, 0xFF, 0x0F, 0xF6, 0xEC, 0xEC, 0x01, 0xF1, 0xFF, 0xFF, 0x00, 0xFE, 0xFE, 0x00, 0xFF, 0xFF,
0x0E, 0xF6, 0xF1, 0xFA, 0xFF, 0xFF, 0x00, 0xFE, 0xFE, 0x02, 0xFF, 0xFF, 0x10, 0xFE, 0xFE, 0x03,
0xFF, 0xFF, 0x00, 0xFA, 0xF6, 0xF7, 0xFF, 0xFF, 0x0D, 0xFE, 0xFE, 0x00, 0xFF, 0xFF, 0x00, 0xF7,
0xF1, 0xEC, 0xEC, 0x01, 0xFA, 0xFF, 0xFF, 0x0F, 0xF6, 0xEC, 0xEC, 0x01, 0xF1, 0xFA, 0xFF, 0xFF,
0x11, 0xF6, 0xF1, 0xF6, 0xFF, 0xFF, 0x0F, 0xFE, 0xFE, 0x01, 0xFF, 0xFF, 0x11, 0xFE, 0xFE, 0x03,
0xFF, 0xFF, 0x10, 0xFE, 0xFE, 0x02, 0xFF, 0xFF, 0x00, 0xF7, 0xF1, 0xF1, 0x00, 0xF6, 0xFF, 0xFF,
0x09, 0xFA, 0xF6, 0xFF, 0xFF, 0x01, 0xFE, 0xFF, 0xFF, 0x00, 0xF6, 0xEC, 0xEC, 0x01, 0xF1, 0xF7,
0xFF, 0xFF, 0x06, 0xF7, 0xF1, 0xEC, 0xEC, 0x00, 0xF1, 0xF7, 0xFF, 0xFF, 0x01, 0xF6, 0xEC, 0xEC,
0x00, 0xF1, 0xF6, 0xFF, 0xFF, 0x07, 0xF6, 0xEC, 0xEC, 0x01, 0xF1, 0xFA, 0xFF, 0xFF, 0x00, 0xFE,
0xFF, 0xFF, 0x01, 0xF6, 0xFF, 0xFF, 0x09, 0xF7, 0xF1, 0xF1, 0x00, 0xF6, 0xFF, 0xFF, 0x00, 0xFE,
0xFE, 0x02, 0xFF, 0xFF, 0x10, 0xFE, 0xFE, 0x04, 0xFF, 0xFF, 0x11, 0xFE, 0xFE, 0x01, 0xFF, 0xFF,
0x0E, 0xF7, 0xF1, 0xF1, 0x00, 0xF6, 0xFF, 0xFF, 0x11, 0xF6, 0xEC, 0xEC, 0x01, 0xF1, 0xF7, 0xFF,
0xFF, 0x0F, 0xF1, 0xEC, 0xEC, 0x00, 0xF1, 0xF6, 0xFF, 0xFF, 0x12, 0xFA, 0xF6, 0xFF, 0xFF, 0x29
};

/* Compression ratio = 21% */
const Byte check_box_checked[] = {
/* Image dimensions: (W x H) */
0x00, 0x0A, 0x00, 0x0A, 

/* Color mode */
0x80, 0x05,

/* Data */
0xFF, 0xFF, 0x05, 0xBE, 0xBE, 0x00, 0xFF, 0xFF, 0x06, 0x3C, 0x1C, 0xBE, 0xFF, 0xFF, 0x04, 0xBE, 
0x1C, 0x1C, 0x00, 0xFF, 0xFF, 0x05, 0x5D, 0x1C, 0x9E, 0xFF, 0xFF, 0x04, 0xDF, 0x1C, 0x1C, 0x00, 
0xFF, 0xFF, 0x05, 0x5D, 0x1C, 0x7D, 0xFF, 0xFF, 0x00, 0xDF, 0x5D, 0x5D, 0x00, 0xFF, 0xDF, 0x1C, 
0x1C, 0x00, 0xFF, 0xFF, 0x01, 0xDF, 0x1C, 0x1C, 0x00, 0x7D, 0x3D, 0x1C, 0x7D, 0xFF, 0xFF, 0x02, 
0xDF, 0x1C, 0x1C, 0x02, 0xFF, 0xFF, 0x04, 0xDF, 0x5D, 0x5D, 0x00, 0xDF, 0xFF, 0xFF, 0x02
};

/* MUSIC ANIMATION PICTURES */

/* Color palette */
const Word palette_Equ[] = {
 (Word)D4D_COLOR_RGB565(D4D_COLOR_GET_R(D4D_COLOR_BCKG_NORM), D4D_COLOR_GET_G(D4D_COLOR_BCKG_NORM), D4D_COLOR_GET_B(D4D_COLOR_BCKG_NORM)), 
 (Word)D4D_COLOR_RGB565(D4D_COLOR_GET_R(D4D_COLOR_FORE_NORM), D4D_COLOR_GET_G(D4D_COLOR_FORE_NORM), D4D_COLOR_GET_B(D4D_COLOR_FORE_NORM))
};

/* Compression ratio: 51% */
const Byte Equ_frame_0012[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x3B, 0xF8, 0x3F, 0xFF, 0xFF, 0x09, 0x83, 0xFF, 0xFF, 0x08, 0xFC, 0x18, 0x3F, 0xFF, 
0xFF, 0x08, 0xC1, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0xFF, 0x07, 0xFC, 0x18, 0x3F, 0xFF, 0xFF, 0x04, 
0xFC, 0x1F, 0xF0, 0x7F, 0xC1, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0xFF, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 
0xFF, 0x04, 0xFC, 0x1F, 0xF0, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 34% */
const Byte Equ_frame_0011[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x7A, 0x83, 0xFF, 0xFF, 0x08, 0xFC, 0x18, 0x3F, 0xFF, 0xFF, 0x06, 0xF0, 0x7F, 0xC1, 
0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 
0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 
0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 
0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};

/* Compression ratio: 30% */
const Byte Equ_frame_0010[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x8E, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0x83, 0xFE, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};

/* Compression ratio: 32% */
const Byte Equ_frame_0009[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x84, 0xFE, 0x0F, 0xFF, 0xFF, 0x08, 0xF0, 0x60, 0xFF, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xFF, 0xFF, 0x00, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0F, 0xF8, 0x30, 0x60, 0xC1, 
0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xFF, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 
0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 
0xFF, 0x03, 0xFC
};


/* Compression ratio: 30% */
const Byte Equ_frame_0008[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x8E, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0x83, 0xFE, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 42% */
const Byte Equ_frame_0007[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x50, 0xC1, 0xFF, 0xFF, 0x09, 0xFC, 0x1F, 0xFF, 0xFF, 0x09, 0xC1, 0xFF, 0xFF, 0x08, 
0xFE, 0x0C, 0x1F, 0xFF, 0xFF, 0x08, 0xE0, 0xC1, 0xFF, 0x07, 0xFF, 0xFF, 0x06, 0xFE, 0x0C, 0x18, 
0x30, 0x7F, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x07, 0xFC, 0x18, 0x3F, 0xFF, 0xFF, 
0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 30% */
const Byte Equ_frame_0006[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x8E, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0x83, 0xFE, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};

/* Compression ratio: 38% */
const Byte Equ_frame_0005[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x75, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0xFF, 0xFF, 0x01, 
0xF8, 0x3F, 0xFF, 0xFF, 0x04, 0xFC, 0x1F, 0xFF, 0xE0, 0xFF, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 
0x83, 0xFE, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 
0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 
0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 
0xFC
};


/* Compression ratio: 30% */
const Byte Equ_frame_0004[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x8E, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0x83, 0xFE, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 42% */
const Byte Equ_frame_0003[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x54, 0xF8, 0x3F, 0xFF, 0xFF, 0x09, 0x83, 0xFF, 0xFF, 0x09, 0xF8, 0x3F, 0xFF, 0xFF, 
0x08, 0xC1, 0x83, 0xFF, 0xFF, 0x07, 0x07, 0xFC, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0F, 0xFF, 
0xF0, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0xFF, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 
0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 30% */
const Byte Equ_frame_0002[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x8E, 0xFC, 0x1F, 0xFF, 0xFF, 0x01, 0x83, 0xFF, 0xFF, 0x05, 0xC1, 0x83, 0xFE, 0x0C, 
0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 
0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 
0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFC
};


/* Compression ratio: 40% */
const Byte Equ_frame_0001[] = {

/* Bitmap dimension (W x H) */
0x00, 0x32, 0x00, 0x23, 

/* Color mode */
0x87, 0x0D, 

/* Data */
0xFF, 0xFF, 0x6D, 0xF8, 0x3F, 0xFF, 0xFF, 0x09, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xFF, 0xFF, 0x00, 
0x07, 0xFF, 0xF8, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0F, 0xF8, 0x30, 0x60, 0xFF, 0x83, 0xFF, 0xFF, 
0x04, 0xE0, 0xFF, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 0x0C, 0x18, 0x30, 0x60, 
0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 0xFF, 0xFF, 0x03, 0xFE, 
0x0C, 0x18, 0x30, 0x60, 0xC1, 0x83, 0xFF, 0xFF, 0x04, 0xE0, 0xC1, 0x83, 0x06, 0x0C, 0x18, 0x3F, 
0xFF, 0xFF, 0x03, 0xFC
};

/* Color palette */
const Word palette_gauge[] = {
0x0700, 0x2600, 0x2700, 0x4508, 0x4600, 0x4608, 0x4700, 0x6408, 0x6508, 0x6600, 0x6700, 0x8308, 0x8408, (Word)D4D_COLOR_RGB565(D4D_COLOR_GET_R(D4D_COLOR_LIGHT_GREY), D4D_COLOR_GET_G(D4D_COLOR_LIGHT_GREY), D4D_COLOR_GET_B(D4D_COLOR_LIGHT_GREY)), 0x8508, 0x8600, 
0x8700, 0xA208, 0xA308, 0xA408, 0xA508, 0xA600, 0xA700, 0xC100, 0xC200, 0xC300, 0xC400, 0xC408, 0xC500, 0xC600, 0xC700, 0xE000, 
0xE100, 0xE200, 0xE300, 0xE400, 0xE500, 0xE600, 0xE700
};



/* Compression ratio: 26% */
const Byte gauge[] = {

/* Bitmap dimension (W x H) */
0x00, 0x3A, 0x00, 0x3A, 

/* Color mode */
0x80, 0x07, 

/* Data */
0x0D, 0x0D, 0x33, 0x0C, 0x0B, 0x0D, 0x0D, 0x2E, 0x0B, 0x12, 0x11, 0x18, 0x18, 0x00, 0x17, 0x20, 
0x1F, 0x1F, 0x01, 0x0D, 0x0D, 0x29, 0x0B, 0x0B, 0x00, 0x12, 0x18, 0x21, 0x21, 0x00, 0x20, 0x20, 
0x03, 0x1F, 0x1F, 0x02, 0x0D, 0x0D, 0x25, 0x0C, 0x12, 0x19, 0x22, 0x22, 0x00, 0x21, 0x21, 0x03, 
0x20, 0x20, 0x03, 0x1F, 0x1F, 0x02, 0x0D, 0x0D, 0x23, 0x0C, 0x1B, 0x23, 0x22, 0x22, 0x02, 0x21, 
0x21, 0x03, 0x20, 0x20, 0x03, 0x1F, 0x1F, 0x02, 0x0B, 0x0D, 0x0D, 0x1F, 0x0C, 0x13, 0x1A, 0x23, 
0x23, 0x01, 0x22, 0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 0x20, 0x03, 0x1F, 0x1F, 0x02, 0x0B, 0x0D, 
0x0D, 0x1D, 0x0C, 0x1A, 0x23, 0x23, 0x04, 0x22, 0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 0x20, 0x03, 
0x1F, 0x1F, 0x02, 0x0B, 0x0D, 0x0D, 0x1B, 0x0C, 0x1C, 0x24, 0x24, 0x00, 0x23, 0x23, 0x04, 0x22, 
0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 0x20, 0x03, 0x1F, 0x1F, 0x02, 0x11, 0x0D, 0x0D, 0x19, 0x0C, 
0x1C, 0x24, 0x24, 0x02, 0x23, 0x23, 0x04, 0x22, 0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 0x20, 0x03, 
0x1F, 0x1F, 0x02, 0x11, 0x0D, 0x0D, 0x17, 0x0C, 0x14, 0x24, 0x24, 0x04, 0x23, 0x23, 0x04, 0x22, 
0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 0x20, 0x03, 0x1F, 0x1F, 0x02, 0x11, 0x0D, 0x0D, 0x16, 0x0C, 
0x25, 0x25, 0x01, 0x24, 0x24, 0x03, 0x23, 0x23, 0x04, 0x22, 0x22, 0x02, 0x21, 0x21, 0x03, 0x20, 
0x20, 0x03, 0x1F, 0x1F, 0x02, 0x17, 0x0D, 0x0D, 0x14, 0x0C, 0x14, 0x25, 0x25, 0x02, 0x24, 0x24, 
0x03, 0x23, 0x23, 0x04, 0x22, 0x22, 0x02, 0x21, 0x21, 0x04, 0x18, 0x18, 0x00, 0x11, 0x12, 0x12, 
0x00, 0x0B, 0x0B, 0x01, 0x0D, 0x0D, 0x14, 0x0C, 0x1D, 0x25, 0x25, 0x03, 0x24, 0x24, 0x03, 0x23, 
0x23, 0x04, 0x22, 0x22, 0x04, 0x19, 0x12, 0x0B, 0x0D, 0x0D, 0x1C, 0x0C, 0x25, 0x25, 0x05, 0x24, 
0x24, 0x03, 0x23, 0x23, 0x04, 0x22, 0x22, 0x00, 0x19, 0x12, 0x0B, 0x0D, 0x0D, 0x1F, 0x14, 0x26, 
0x26, 0x00, 0x25, 0x25, 0x04, 0x24, 0x24, 0x03, 0x23, 0x23, 0x04, 0x12, 0x0B, 0x0D, 0x0D, 0x21, 
0x14, 0x26, 0x26, 0x01, 0x25, 0x25, 0x04, 0x24, 0x24, 0x03, 0x23, 0x23, 0x01, 0x1A, 0x13, 0x0C, 
0x0D, 0x0D, 0x22, 0x14, 0x26, 0x26, 0x02, 0x25, 0x25, 0x04, 0x24, 0x24, 0x03, 0x23, 0x13, 0x0C, 
0x0D, 0x0D, 0x24, 0x14, 0x26, 0x26, 0x03, 0x25, 0x25, 0x04, 0x24, 0x24, 0x02, 0x1A, 0x0C, 0x0D, 
0x0D, 0x25, 0x14, 0x26, 0x26, 0x04, 0x25, 0x25, 0x04, 0x24, 0x24, 0x01, 0x0C, 0x0D, 0x0D, 0x26, 
0x0C, 0x1E, 0x26, 0x26, 0x04, 0x25, 0x25, 0x04, 0x24, 0x1A, 0x0C, 0x0D, 0x0D, 0x26, 0x0C, 0x16, 
0x26, 0x26, 0x05, 0x25, 0x25, 0x03, 0x24, 0x13, 0x0D, 0x0D, 0x28, 0x0F, 0x1E, 0x26, 0x26, 0x05, 
0x25, 0x25, 0x02, 0x24, 0x0C, 0x0D, 0x0D, 0x28, 0x0E, 0x16, 0x1E, 0x26, 0x26, 0x05, 0x25, 0x25, 
0x01, 0x24, 0x0C, 0x0D, 0x0D, 0x28, 0x07, 0x10, 0x16, 0x1E, 0x26, 0x26, 0x05, 0x25, 0x25, 0x00, 
0x24, 0x0C, 0x0D, 0x0D, 0x28, 0x0C, 0x0A, 0x10, 0x16, 0x1E, 0x26, 0x26, 0x05, 0x25, 0x25, 0x00, 
0x0C, 0x0D, 0x0D, 0x29, 0x08, 0x0A, 0x10, 0x16, 0x1E, 0x26, 0x26, 0x05, 0x25, 0x0C, 0x0D, 0x0D, 
0x29, 0x07, 0x06, 0x0A, 0x10, 0x16, 0x1E, 0x26, 0x26, 0x04, 0x25, 0x0C, 0x0D, 0x0D, 0x2A, 0x08, 
0x06, 0x0A, 0x10, 0x16, 0x1E, 0x26, 0x26, 0x04, 0x14, 0x0D, 0x0D, 0x2A, 0x07, 0x02, 0x06, 0x0A, 
0x10, 0x16, 0x1E, 0x26, 0x26, 0x03, 0x1D, 0x0D, 0x0D, 0x2B, 0x05, 0x02, 0x06, 0x0A, 0x10, 0x16, 
0x1E, 0x26, 0x26, 0x02, 0x25, 0x0C, 0x0D, 0x0D, 0x2A, 0x07, 0x02, 0x02, 0x00, 0x06, 0x0A, 0x10, 
0x16, 0x1E, 0x26, 0x26, 0x02, 0x14, 0x0D, 0x0D, 0x2B, 0x03, 0x00, 0x02, 0x06, 0x0A, 0x10, 0x16, 
0x1E, 0x26, 0x26, 0x01, 0x25, 0x0D, 0x0D, 0x2C, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0A, 0x10, 0x16, 
0x1E, 0x26, 0x26, 0x01, 0x0C, 0x0D, 0x0D, 0x2B, 0x07, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0A, 0x10, 
0x16, 0x1E, 0x26, 0x26, 0x00, 0x1D, 0x0D, 0x0D, 0x2C, 0x03, 0x00, 0x00, 0x00, 0x02, 0x06, 0x0A, 
0x10, 0x16, 0x1E, 0x26, 0x26, 0x00, 0x0C, 0x0D, 0x0D, 0x2C, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0A, 
0x10, 0x16, 0x1E, 0x26, 0x1E, 0x0D, 0x0D, 0x2C, 0x07, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0A, 0x10, 
0x16, 0x1E, 0x26, 0x14, 0x0D, 0x0D, 0x2C, 0x01, 0x00, 0x00, 0x01, 0x02, 0x06, 0x0A, 0x10, 0x16, 
0x1E, 0x1E, 0x00, 0x0C, 0x0D, 0x0D, 0x2C, 0x00, 0x00, 0x02, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x1E, 
0x1D, 0x0D, 0x0D, 0x2C, 0x07, 0x00, 0x00, 0x02, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x1E, 0x14, 0x0D, 
0x0D, 0x2C, 0x07, 0x00, 0x00, 0x02, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x1E, 0x0C, 0x0D, 0x0D, 0x2C, 
0x03, 0x00, 0x00, 0x02, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x16, 0x00, 0x0D, 0x0D, 0x2D, 0x01, 0x00, 
0x00, 0x02, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x15, 0x0D, 0x0D, 0x2D, 0x00, 0x00, 0x03, 0x02, 0x06, 
0x0A, 0x10, 0x16, 0x0E, 0x0D, 0x0D, 0x2C, 0x07, 0x00, 0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x16, 
0x0C, 0x0D, 0x0D, 0x2C, 0x07, 0x00, 0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x16, 0x0C, 0x0D, 0x0D, 
0x2C, 0x03, 0x00, 0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x10, 0x00, 0x0D, 0x0D, 0x2D, 0x01, 0x00, 
0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x0F, 0x0D, 0x0D, 0x2D, 0x01, 0x00, 0x00, 0x03, 0x02, 0x06, 
0x0A, 0x10, 0x0E, 0x0D, 0x0D, 0x2D, 0x01, 0x00, 0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x0E, 0x0D, 
0x0D, 0x2D, 0x01, 0x00, 0x00, 0x03, 0x02, 0x06, 0x0A, 0x10, 0x0E, 0x0D, 0x0D, 0x2D, 0x00, 0x00, 
0x04, 0x02, 0x06, 0x0A, 0x10, 0x0E, 0x0D, 0x0D, 0x2D, 0x00, 0x00, 0x04, 0x02, 0x06, 0x0A, 0x10, 
0x0C, 0x0D, 0x0D, 0x2D, 0x00, 0x00, 0x04, 0x02, 0x06, 0x0A, 0x10, 0x0C, 0x0D, 0x0D, 0x2D, 0x00, 
0x00, 0x04, 0x02, 0x06, 0x0A, 0x10, 0x0C, 0x0D, 0x0D, 0x2C, 0x07, 0x00, 0x00, 0x04, 0x02, 0x06, 
0x0A, 0x10, 0x0C, 0x0D, 0x0D, 0x2C, 0x07, 0x07, 0x00, 0x03, 0x03, 0x02, 0x04, 0x04, 0x00, 0x09, 
0x09, 0x00, 0x0F, 0x0D, 0x0D, 0x67
};
