#pragma once

#include "colour.h"


const int
	ChSubPgs = 6,	// Char list sub-pages
	HelpPages = 2,  // keyboard Help pages
	EdX = 38, EdY = 4,  // edit field size
	MinTex = 128;   // min font texture size
	
const char ver[] = "4.45";	// program version


// texture filters
const int nTexFil = 2;
const char sTexFil[nTexFil][10] =
	{"point", "best"};


/*save formats*/
const int nFormats = 4;
const D3DXIMAGE_FILEFORMAT fmtIFF[nFormats + 1] =
	{ D3DXIFF_BMP, D3DXIFF_TGA, D3DXIFF_PNG, D3DXIFF_DDS, D3DXIFF_JPG };
const char fmtExt[nFormats + 1][5] =
	{"bmp", "tga", "png", "dds", "jpg"};


/*save options*/
const int CFp = 1;
const char Cfp[CFp + 1][10] =
	{"none", "file .cf"};

const int CFd = 1;
const char Cfd[CFd + 1][10] =
	{"text", "xml-"};

const int CFt = 3;
const char Cft[CFt + 1][10] =
	{"minimal", "extended", "abc", "full"};	


/* font list element */
struct FLE
{
	char na[NameLen], d;
	//FLE() : d(0) {  na[0] = 0;  }
};	


class CFfont : public CFclr
{
	public:
		CFfont();
		
		// main procedures
		bool
			settings(),  Colorize(),
			MakeFont(),  SaveFont(), 
		/*.fnt*/
			fntList(),  fntLoad( char* ),  fntSave();

		bool str,  /*edit*/
			Txy,  /*texture x != y*/
			oneLine;
		int rect_sx, rect_sy;   /*rect size*/
		
		/*dc*/
		HDC dc;
		HBITMAP hb;
		HFONT hf;
		
		// begin procedures
		bool CreateDC();
		void DestroyDC(),  EnumFonts();
	

	/*help*/
		int isHelp, HelpPage, updHelp;
		int lin,  /*i*/psx;
		float pps;	BYTE ssn;

	/*update screen*/
		int clearAll, upRct, upChr;
	/*anim*/
		float ar,  ah, ac,  at, nqt;
	
	/*txt*/
		bool uTexFil( int );
		void UVadr( bool );
		int texFilR, texFilH;
		float atexFilR, atexFilH;

	/*save options*/
		int fileNum, fmt,  cfp, cfd, cft;
	/*inf*/
		float saveTime;
		char saveInfo[90];
	/*set*/
		void optSave(), optLoad();
		char co[60][CommLen];

	/*edit*/
		char es[EdY + 1][EdX + 1];
		int ex[EdY + 1], ey,
			edIns/*insert*/;
		float eqt;
	
	/*Fonts*/
		static char *fontNames[MaxList];
		static int iFonts;
		int yfn, pfn;

	/*fnt List*/
		int yFntL, pgFntL, nFntL,  nfx;
		char nfe[NameLen], phf[90];
		FLE fL[MaxList];

};

#define ForEachChar  for (n = 0; n <= zi; ++n)
