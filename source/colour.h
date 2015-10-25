#pragma once

#include "d3dbasic.h"
#include "colour_const.h"


//  -   - 	 - 					- 	 -     class     - 	 - 					- 	 - 	 -  */

class CFclr : public D3Dbasic
{
public:
	CFclr();
	
	/*procedures*/
	virtual bool settings();

	bool updRect(), updPrv(),
		setDim(), updZoom(),

		clrList(),  // .clr
		clrLoad( Ct&ct, int tGlow, char*na ),
		clrSave();		/* +  sav in .fnt*/
		
	void Colour( int sY, int sy, int ss, Ct& ct, BYTE* tClrF, BYTE* tClrG = NULL, BYTE* tChan = NULL);
	void Colour();
			
	virtual bool Colorize() = 0;
	virtual bool MakeFont() = 0;
	

	/*FONT*/
	char fontName[80];
	int ax, bx, ay, by,  // [ + ] additional sizes
		Ea,   //empty-all
		ql,   //quality
		sy, Sy, // size
		fbold,  // bold
		fix,    // fixed size
		z1, z2, zi;  // chars range

	Char h[256];

	bool bRect;
	
	/*Font dim*/
	int Ty,		/*texture*/
		Ux, Uy,	/*surface*/
		sx, ss,	/*cahr width*/
		// groups
		grw[MaxGroups + 1],	/*grp  width*/
		grwi[MaxGroups + 1], grcur;  /*width + */


	/*char display*/
	float LcurRng, zm, mz,	//zoom
		zoomf, ofsx, ofsy;	//offset


	/*Dimensions*/
	int xt,  /*charL*/
		xr, yr, xr2,  /*rectAll, rectChan*/
		xp, yp, px, py,    /*Table*/
		xz, yz, zx, zy, gz,/*char*/
		xf, xf2, yf, fp,   /*font*/
		cLY;  /*clr List*/


	/* position of cursor in tables*/
	int clrx, clry, curChan,	//current channel edit
		fontx, fonty,
		glowx, glowy,
		alphx, alphy,
		savex, savey,
		editx, edity;
		

	/*Clr*/
	CTE cte, ctE[clrY][clrX];
	Ct  ct, lct;
	float* f;	// float parameters
	

	/* big arrays */
	BYTE *tFont, *tGlow, *tAlpha,
		 *tClrF, *tClrG, *tChan, *tPrv;

	/* textures */
	LPDIRECT3DTEXTURE9  TexFnt, rTexAll, rTexChan, rTexPrv;
	UINT *oo;  // direct writing pointers
	BYTE *ob;

	/*Background colors*/
	CLR	bckFrame,
		bckSliOn, bckSliOff;	//sliders light/dark
	

	//  backgr alpha params
	int bckA, bAc[3],bAd[3];
	/*  alpha vars  */
	int amin,amax, aofsF,aofsG,aofsC;
	float amulF,amulG;

	
	/* common */
	int edT, edL[ntabT], edTL,  // current edit selections
		x, y, n,  w, b,  // universal
		onR, onG, onB,	// R,G,B on/off
		timeg, timec;	// computation times


	/*Glow vars*/

	float gmul1, gmul2,  gpow, gpowm,  gmulall;
	int gsub,
		isGlow, isFont, isAll, showChar,  addGlow;	/* 0,1 opt*/
	float gamul;	int gamax;	//additive

	float fgd;	//glow distance
	int	   gd,  gd2, gdy,
		  *gdt;  //glow dist table

	void updGlow();

	
	/* - */
	char statusAll[30];  // on/off all

	/*icon - read*/
	ICO ico;


	/* clr List */
	CLE cle[MaxList];

	int yClrL, pgClrL, nClrL,  neditx;
	char nedit[NameLen],  phc[90];

	// chars list
	int yChrL, pgChrL, ChPage, chLY;

};
