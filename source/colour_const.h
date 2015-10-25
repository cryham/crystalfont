#pragma once

#include "d3dbasic.h"


//  main const
const int
	MaxTex = 2048*2,  /*max texture size*/
	MaxSY  =  512*2,  /*max char size, rect*/

	MaxList = 1024,  /*max list count*/
	ICOsize = 21,	/*icon size*/

	MaxGlow = 36,  /*max glow size*/ mdg = 2*64,
	MaxGroups = 16,  /*max smooth groups*/
	NameLen = 16,  /*edit name field length*/
	CommLen = 90;  /*set file comment max lenght*/


// Char data type
struct Char
{
	int bx, by,  // begin x,y
		wi,  // width
		of,  // offset x
		h[3], // abc widths
		ps, pp, psi;  // empty width| check
	BYTE wi0,  // abc != width
		s, ch,  // code
		gr;  // smooth group
	int xx, yy, ss,  /*!*/xt, yt;	// +/-
	int tw[10];  // else..
};
		

/* color List element */
struct CLE
{
	char na[NameLen], d;	/*name, dir*/
	LPDIRECT3DTEXTURE9 ico;	/*icon*/
};

/* color Table element */
struct CTE
{
	float x, y;  /*position*/
	char s[10];  /*string*/
	int f;		 /* pointer to ct*/
	float m, w;  /* small+ , big+*/
};


/* general paths */
const char
	pathClr0[] = "..\\.clr\\",  lpaClr0 = sizeof( pathClr0 ) - 3,
	pathFnt0[] = "..\\.fnt\\",  lpaFnt0 = sizeof( pathFnt0 ) - 3,
	pathSave[] = "..\\saved\\",
	setFile[] = "CrystalFont.set";

/* Table sizes */
const int
	clrX  = 4, clrY  = 4,	// 1 Color
	fontX = 3, fontY = 4,	// 2 Font
	glowX = 2, glowY = 4,	// 3 Glow
	alphX = 3, alphY = 5,	// 4 Alpha
	saveX = 2, saveY = 2,	// 5 Save
	editX = 1, editY = 2;	// 6 Edit


/* channels count */
const int
	CH = 12, CH2 = CH/2;

// Color Table type
typedef float  Ct[CH][32];	
typedef float Ct2[CH2][32];	

// icon
typedef BYTE  ICO[ICOsize][ICOsize][3];	


// Tab positions
const int
	ntabT = 6,
	ntabL = 4;
const int
	xtabT[ntabT + 1] = { 0, 50, 98, 147, 202, 250, 294 },
	xtabL[ntabL + 1] = { 0, 27, 60, 110, 160 };


/* Tab names */
const char stabT[ntabT][10] = {	"Color", "Font", "Glow", "Alpha", "save", "edit" };

const char stabL[ntabL][10] = {	".clr", ".fnt", "Chars", "Fonts" };


/* channel types */
const int nChanTypes = 5;

const char sChanTypes[nChanTypes + 1][12] = {
	"simple", "circle", "line", "point", "star", "diamond" };
	// polygon, cycloid ... texture, noise,..



/*  -   - 	 - 	  - 				- 	 -  -- const --  - 	 - 				- 	 - 	 -   -  */

/* glow table elements*/
const struct GTE
{
	int x, y, yy, w;
}
gte[glowY][glowX] =
{
	{  { 0, 0, 5, 70  }, { 200, 0, 5, 250 }  },
	{  { 0, 2, 0, 100 }, { 150, 2, 0, 250 }  },
	{  { 0, 3, 0, 100 }, { 150, 3, 0, 250 }  },
	{  { 0, 4, 0, 100 }, { 150, 4, 0, 250 }  }
};


/* color table elements*/
const int Xp[clrX] =
	{ 15, 95, 175, 245};
const CTE cte0[clrY][clrX] =
	{  {
		{ 2, 1, "i%5.1f",  3,  1.f,  0.5f },
		{ 0, 1, "s%6.3f",  5,0.05f,0.005f },
		{ 2, 1, "c %3.0f", 7,  4.f,   1.f },
		{ 9, 1, "<%3.0f",  9,  4.f,   1.f }
	},{
		{ 0, 2, "j%5.1f",  4,  1.f,  0.5f },
		{-8, 2,"yx%6.3f",  6,0.01f,0.001f },
		{ 1, 2, "u%5.2f",  8, 0.1f, 0.01f },
		{ 9, 2, ">%3.0f", 10,  4.f,   1.f }
	},{
		{ 0, 3, "k%5.2f", 13, 0.1f, 0.01f },
		{ 3, 3,"r %5.2f", 14, 0.1f, 0.01f },
		{ 1, 3, "z%5.2f", 15, 0.1f, 0.02f },
		{ 0, 3,"->%3.0f", 11,  4.f,   1.f }
	},{
		{ 0, 4.5f, "R %4.2f", 0,  0.1f, 0.01f },
		{ 0, 4.5f, "G %4.2f", 1,  0.1f, 0.01f },
		{ 0, 4.5f, "B %4.2f", 2,  0.1f, 0.01f },
		{ 0,	4,  "", 10,  0.f, 0.f }
	}  };


// element text colors depending on channel type
const CLR
	c0 = CLR( 0.4, 0.4, 0.4, 1 ),
	c1 = CLR( 1, 1, 1, 1 ),
	c2 = CLR( 0.2, 0.85, 0.95, 1 ),
	c3 = CLR( 0.7, 0.85, 0.9, 1 ),
	c4 = CLR( 0.9, 0.82, 1, 1 ),
	c5 = CLR( 0.9, 0.7, 1.0, 1 ),

	ctp[nChanTypes + 1][clrY][clrX] =
	{
		{  { c1, c4, c4, c3 }, { c1, c1, c3, c3 }, { c0, c0, c0, c3 }, { c2, c2, c2, c2 }  },
		{  { c5, c4, c4, c3 }, { c1, c5, c3, c3 }, { c1, c1, c0, c3 }, { c2, c2, c2, c2 }  },
		{  { c0, c4, c4, c3 }, { c1, c0, c3, c3 }, { c1, c0, c0, c3 }, { c2, c2, c2, c2 }  },
		{  { c1, c4, c4, c3 }, { c1, c5, c3, c3 }, { c0, c0, c0, c3 }, { c2, c2, c2, c2 }  },
		{  { c1, c4, c4, c3 }, { c1, c1, c3, c3 }, { c1, c1, c5, c3 }, { c2, c2, c2, c2 }  },
		{  { c1, c4, c4, c3 }, { c1, c1, c3, c3 }, { c1, c1, c5, c3 }, { c2, c2, c2, c2 }  }
	};


/* table & list  element Background colors*/
const struct bckTL
{
	CLR	t,  // background
		q,  // cursor
		f[2],  // font[0-normal, 1-selected]
		s,  // status
		p;  // status %
}

bckT[ ntabT + 1 ] =	// Table
{
	{ 0.8f*CLR( 0.11, 0.20, 0.23, 1), CLR( 0.1, 0.24, 0.42, 1),  CLR( 1.3, 1.5, 1.0, 1), CLR( 1, 0.77,1.0, 1) },  /*color*/
	{ 0.8f*CLR( 0.03, 0.23, 0.16, 1), CLR( 0.1, 0.30, 0.18, 1),  CLR( 1.0, 1.0, 0.9, 1), CLR( 1.0,1.0,0.9, 1) },  /*font*/
	{ 0.8f*CLR( 0.18, 0.14, 0.23, 1), CLR( 0.22,0.17, 0.33, 1),  CLR( 0.95,0.77,1.0, 1), CLR( 1, 1.0, 1.0, 1) },  /*glow*/
	{ 0.8f*CLR( 0.13, 0.13, 0.22, 1), CLR( 0.16,0.16, 0.33, 1),  CLR( 0.88,0.88,1.0, 1), CLR( 1, 1.0, 1.0, 1) },  /*alpha*/
	{ 0.8f*CLR( 0.0 , 0.23, 0.21, 1), CLR( 0.0, 0.28, 0.22, 1),  CLR( 0.0, 1.0, 0.8, 1), CLR( 0, 0.8, 0.6, 1) },  /* Save*/
	{ 0.7f*CLR( 0.20, 0.20, 0.10, 1), CLR( 0.3, 0.2 , 0.35, 1),  CLR( 1.0, 0.9, 0.2, 1), CLR( 1, 0.95,1.0, 1) },  /* edit*/
	{ 0.7f*CLR( 0.19, 0.24, 0.10, 1), CLR( 0.2, 0.28, 0.09, 1),  CLR( 1.0, 0.6, 0.2, 1), CLR( 1, 0.9, 0.4, 1) }   /*Rect*/
},

bckL[ ntabL ] =	  // List
{
	{	CLR( 0.0, 0.23, 0.23, 1), CLR( 0.02,0.18,0.19,1), CLR( 0.7, 0.7, 0.8, 1),	//.clr
		CLR( 1,   1,    1,    1), CLR( 1,   1,   1,   1), CLR( 0.5, 0.7, 0.7, 1)	},
	{	CLR( 0.1, 0.25, 0.18, 1), CLR( 0.06,0.2, 0.1, 1), CLR( 0.5, 0.9, 0.65,1),	//.fnt
		CLR( 0.6, 1,    0.7,  1), CLR( 0,   1,   0.5, 1), CLR( 0.4, 0.7, 0.5, 1)	},
	{	CLR( 0.15,0.15, 0.26, 1), CLR( 0.3, 0.3, 0.45,1), CLR( 0.7, 0.7, 0.8, 1),	// Chars
		CLR( 0.7, 0.9,  0.9,  1), CLR( 0.7, 0.9, 0.9, 1), CLR( 0.5, 0.6, 0.7, 1)	},
	{	CLR( 0.0, 0.13, 0.25, 1), CLR( 0.10,0.21,0.35,1), CLR( 0.7, 0.9, 0.9, 1),	// Fonts
		CLR( 0.9, 0.96, 1.0,  1), CLR( 1.5, 1.5, 1,   1), CLR( 0.5, 0.7, 0.85,1) }
};


const Ct ct0 =  // first color table values
{
	{ 1, 0, 0,  1, 4,  0.6f,  1,  220, 0, 0, 255, 255 },
	{ 0, 1, 0,  1, 4,  0.55f, 1,  260, 0, 0, 255, 255 },
	{ 0, 0, 1,  1, 2,  0.5f,  1,  280, 0, 0, 255, 255 }, 
	{ 0, 0, 0,  0, 0,  0.6f,  1,  225, 0, 0,   0, 255 },
	{ 0, 0, 0,  0, 0,  0.5f,  1,  280, 0, 0,   0, 255 },
	{ 0, 0, 0,  1, 4,  0.6f,  1,  225, 0, 0,   0, 255 }, 

	{ 1, 0, 0,  4, 4,  0.5f,  1,  180, 0, 0, 255, 255 },
	{ 0, 1, 0,  2, 2,  0.45f, 1,  230, 0, 0, 255, 255 },
	{ 0, 0, 1,  0, 0,  0.4f,  1,  260, 0, 0, 255, 255 }, 
	{ 0, 0, 0,  0, 0,  0.6f,  1,  225, 0, 0,   0, 255 },
	{ 0, 0, 0,  0, 0,  0.5f,  1,  280, 0, 0,   0, 255 },
	{ 0, 0, 0,  1, 4,  0.6f,  1,  225, 0, 0,   0, 255 }
};

