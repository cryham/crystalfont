#include "header.h"
#include "keys.h"


/* -    -    -    -    -    -    -    -    -   keys   -    -    -    -    -    -    -    -   - */

CFkeys::CFkeys() :
	key(0), showfps(0), sp(1.f),
	kAlt(0), Alt(0), Shift(0), Ctrl(0)
{}

// exiting updates
#define ret  return true;

// Color Table
#define updClr	upChr = 1;  upRct = 1; \
				Colour();	Colorize();  ret
// Font Table
#define updFnt	clearAll = 2;  updGlow();  \
				if (!MakeFont())  return false; \
				updZoom();	updClr

// Color List, preview
#define updList	if (!bRect  &&  !cle[pgClrL + yClrL].d)  {	\
					clrLoad( lct, 0, cle[pgClrL + yClrL].na);	upRct = 2;	\
					Colour( MaxSY, Sy, ss, lct, tPrv);  }	ret
// All
#define updAll	if (isAll)  {  updFnt  }  ret


bool CFkeys::KeyPress( WPARAM k )
{
	int s_ = max( 1, sp * 2 ), l, a;
	//float f_ = sp*.. fine
		
	/*alt exit*/
	if (Alt)
		switch (k)
		{
			case VK_UP:			case VK_DOWN:	case VK_LEFT:	case VK_RIGHT:
			case VK_SUBTRACT:	case VK_ADD:	case VK_DIVIDE:	case VK_MULTIPLY:
				return false;	
		}

	/* focus ALL*/
	if (edTL != 2  &&  edTL != 3)
		switch (k)
		{
			case VK_TAB:
				edTL = 1 - edTL;
				if (!( edTL == 0  &&  edL[edT] != 0 ))
					upRct = 3;
				ret
	
			/*Help*/
			case VK_F11:
				isHelp = 1 - isHelp;	updHelp = 2;
				if (!isHelp)
				{	clearAll = 2;  upRct = 3;	}	ret

			/*Save*/
			case VK_F9:		SaveFont();		ret
		}

	/* All - help */
	if (!( edTL == 2  ||  edTL == 3  ||  edT == 5 && edTL == 1  || Shift || Ctrl ) )
	switch (k)
	{
		/*Help*/
		case VK_LEFT: case VK_UP:
		case VK_PRIOR: case VK_SUBTRACT: case VK_DIVIDE:	if (isHelp)
			{	if (HelpPage > 0)  HelpPage--;
				updHelp = 2;	ret		}	break;

		case VK_RIGHT: case VK_DOWN:
		case VK_NEXT: case VK_ADD: case VK_MULTIPLY:	if (isHelp)
			{	if (HelpPage < HelpPages)  HelpPage++;
				updHelp = 2;	ret		}	break;

		case 'I':	showfps = !showfps;		ret
		case 'F':	isFont = 1 - isFont;	updAll
		case 'G':	isGlow = 1 - isGlow;	updAll

		case 'C':	isAll = 1 - isAll;
			if (isAll)  scpy( statusAll, "" );
			else  scpy( statusAll, "off" );		updAll

		case'H':	showChar = 1 - showChar;
			clearAll = 2;	upRct = 1;
			if (showChar)  upChr = 1;	ret	

		case VK_SPACE:	// Font - Glow
			if (curChan < CH2 )  curChan += CH2;
			else  curChan -= CH2;
			upRct = 1;	Colour();	ret

		case 'Q':	atexFilR = 1.f;  texFilR++;  if (texFilR == nTexFil)  texFilR = 0;	upRct = 1;	ret	
		case 'W':	atexFilH = 1.f;  texFilH++;  if (texFilH == nTexFil)  texFilH = 0;	upChr = 1;	ret
	}


	/* edTL <> */
	switch( edTL )
	{
		/*save .fnt*/
		case 3:
			if (k >= 32  &&  k <= 223)
			{
				if (k == VK_DELETE)	{	edTL = 0;	ret  }
				BYTE b = kz[Shift][k - 32];
				if (Alt == 1  &&  k >= 'A'  &&  k <= 'Z')
					b = pz[Shift][k - 'A'];
				if (b > 0  &&  nfx < NameLen - 1)
				{	nfe[nfx] = b;	nfe[++nfx] = 0;  ret  }
			}
			switch (k)
			{
				case VK_BACK:	if (nfx > 0)  nfe[--nfx] = 0;	ret
				case VK_DELETE:	edTL = 0;	ret
				case VK_RETURN:
					if (!fntSave())
					{	saveTime = 2.f;
						scpy( saveInfo, "ERROR: " );	scat( saveInfo, s );
					} else {
						scpy( saveInfo, "" );	fntList();	}
					edTL = 0;	ret
			}	ret	
			
		/*save .clr*/
		case 2:
			if (k >= 32  &&  k <= 223)
			{
				if (k == VK_DELETE)	{	edTL = 0;	ret  }
				BYTE b = kz[Shift][k - 32];
				if (Alt == 1  &&  k >= 'A'  &&  k <= 'Z')	b = pz[Shift][k - 'A'];
				if (b > 0  &&  neditx < NameLen - 1)
				{	nedit[neditx] = b;	nedit[++neditx] = 0;	ret  }
			}
			switch (k)
			{
				case VK_BACK:	if (neditx > 0)  nedit[--neditx] = 0;	ret
				case VK_DELETE:	edTL = 0;	ret
				case VK_RETURN:
					if (!clrSave())
					{	saveTime = 2.f;
						scpy( saveInfo, "ERROR: " );	scat( saveInfo, s );
					} else {
						scpy( saveInfo, "" );	clrList();	}
					edTL = 0;	ret
			}	ret	

		/*T*/
		case 1:
			if (k >= VK_F1  &&  k <= VK_F6)
			{
				edT = k - VK_F1;	upRct = 3;

				if (edT == 5)  //edit end-
					ex[ey] = strlen( es[ey] );
				ret
			}
			switch( edT )
			{

				/*Color Table*/
				case 0:
					switch (k)
					{
						case VK_DIVIDE:
							if (curChan > 0)  curChan--;		upRct = 1;	Colour();	ret
						case VK_MULTIPLY:
							if (curChan < CH - 1)  curChan++;	upRct = 1;	Colour();	ret

						/*off*/
						case VK_RETURN:
							if (f[10] > 0) {  f[16] = f[10];  f[10] = 0;  }
							else{	f[10] = f[16];	if (f[10] == 0)  f[10] = 255;	}	updClr

						/* -,= zoom */
						case VK_OEM_MINUS:
							zm -= sp;	if (zm < 1.f) zm = 1.f;  clearAll = 2;	updClr
						case VK_OEM_PLUS:
							zm += sp;	if (zm > mz)  zm = mz;	clearAll = 2;	updClr
							
						/*RGB*/
						case'1':  onR = 1 - onR;	updClr
						case'2':  onG = 1 - onG;	updClr
						case'3':  onB = 1 - onB;	updClr

						/*type*/
						case'A': case VK_SUBTRACT:	w = Flt2Int( f[12] );
											if (w > 0)	Flt2Int( f[12] ) = w - 1;	updClr
						case'S': case VK_ADD:		w = Flt2Int( f[12] );
								if (w < nChanTypes )	Flt2Int( f[12] ) = w + 1;	updClr

						// change value
						case VK_HOME:	cte = ctE[clry][clrx];	ct[curChan][cte.f] += cte.w*sp;		updClr
						case VK_PRIOR:	cte = ctE[clry][clrx];	ct[curChan][cte.f] += cte.m*sp;		updClr
						case VK_END:	cte = ctE[clry][clrx];	ct[curChan][cte.f] -= cte.w*sp;		updClr
						case VK_NEXT:	cte = ctE[clry][clrx];	ct[curChan][cte.f] -= cte.m*sp;		updClr
						
						// move
						case VK_LEFT:	if (clrx > 0) clrx--;  else  clrx = clrX - 1;	ret
						case VK_RIGHT:  if (clrx < clrX - 1) clrx++;  else  clrx = 0;	ret
						case VK_UP:		if (clry > 0) clry--;  else  clry = clrY - 1;	ret
						case VK_DOWN:	if (clry < clrY - 1) clry++;  else  clry = 0;	ret
					}
					break;	

				
				/* Font Table*/
				case 1:
					if (bRect)
					switch (k)
					{
						case VK_ADD:	bRect = !bRect;		updFnt

						case VK_LEFT:	if (editx > 0)  editx--;			ret
						case VK_RIGHT:	if (editx < editX - 1)  editx++;	ret
						case VK_UP:		if (edity > 0)  edity--;			ret
						case VK_DOWN:	if (edity < editY - 1)  edity++;	ret

						case VK_NEXT:
							switch( edity )
							{
								case 0:
									if (Ctrl ) rect_sx /= 2;
									else rect_sx -= sp*4;	break;
								case 1:
									if (Ctrl ) rect_sy /= 2;
									else rect_sy -= sp*4;	break;
							}
							rect_sx = range( 1, MaxSY, rect_sx );
							rect_sy = range( 1, MaxSY, rect_sy );
							updAll

						case VK_PRIOR:
							switch( edity )
							{
								case 0:
									if (Ctrl ) rect_sx *= 2;
									else rect_sx += sp*4;	break;
								case 1:
									if (Ctrl ) rect_sy *= 2;
									else rect_sy += sp*4;	break;
							}
							rect_sx = range( 1, MaxSY, rect_sx );
							rect_sy = range( 1, MaxSY, rect_sy );
							updAll
					}
					else  // ! bRect
					switch (k)
					{
						case VK_LEFT:	if (fontx > 0)  fontx--;			ret
						case VK_RIGHT:	if (fontx < fontX - 1)  fontx++;	ret
						case VK_UP:		if (fonty > 0)  fonty--;			ret
						case VK_DOWN:	if (fonty < fontY - 1)  fonty++;	ret

						case VK_RETURN:		edL[edT] = 3;	edTL = 0;		ret
						case VK_ADD:		bRect = !bRect;		updFnt

						/*sy*/
						case VK_MULTIPLY:
							if (clearAll > 0)  return false;
							sy += s_;	sy = min( sy, MaxSY );	updAll
						case VK_DIVIDE:
							if (clearAll > 0)  return false;
							sy -= s_;	sy = max( sy, 2 );	updAll

						#define z12		z1 = range( 0, 255, z1 );	 z2 = range( 0, 255, z2 );\
							if (z1 > z2 ) {  a = z1;	z1 = z2;	z2 = a;  }	zi = z2 - z1;\
							LcurRng( yChrL, pgChrL, chLY, zi )  upChr = 1;
						#define qlchk	ql = range( 0, 4, ql );

						case VK_NEXT:
							switch( fonty*fontX + fontx )
							{
								case 0: fbold = 1 - fbold;	 break;
								case 1: z1 -= s_;	z12  break;
								case 2: z2 -= s_;	z12  break;

								case 3: fix = 1 - fix;	break;
								case 4: Ea = 1 - Ea;	break;
								case 5: ql--;	qlchk	break;

								case 6: ax -= s_;	break;
								case 7: bx -= s_;	break;
								case 9: ay -= s_;	break;
								case 10:by -= s_;	break;

								case 8: Txy = !Txy;	break;
								case 11: oneLine = !oneLine;	break;
							}
							updAll

						case VK_PRIOR:
							switch( fonty*fontX + fontx )
							{
								case 0: fbold = 1 - fbold;	 break;
								case 1: z1 += s_;	z12  break;
								case 2: z2 += s_;	z12	 break;

								case 3: fix = 1 - fix;	break;
								case 4: Ea = 1 - Ea;	break;
								case 5: ql++;  qlchk	break;

								case 6: ax += s_;	break;
								case 7: bx += s_;	break;
								case 9: ay += s_;	break;
								case 10:by += s_;	break;

								case 8: Txy = !Txy;	break;
								case 11: oneLine = !oneLine;	break;
							}
							updAll
					}
					break;

					
				/* glow Table */
				case 2:
					switch (k)
					{
						case VK_LEFT:	if (glowx > 0)  glowx--;			ret
						case VK_RIGHT:	if (glowx < glowX - 1)  glowx++;	ret
						case VK_UP:		if (glowy > 0)  glowy--;			ret
						case VK_DOWN:	if (glowy < glowY - 1)  glowy++;	ret
						
						case VK_DIVIDE:		if (gd > 1)  gd -= s_;	updGlow();	updAll
						case VK_MULTIPLY:	if (gd < 32) gd += s_;	updGlow();	updAll
						case VK_ADD:		addGlow = 1 - addGlow;		updAll
					}
					if (addGlow)
						switch (k)
						{	case VK_NEXT:
								switch( glowy*glowX + glowx )
								{	case 0:	if (gd > 1)  gd -= s_;	updGlow();	break;
									case 1: addGlow = 1 - addGlow;	break;
									case 2: gamul -= s_*0.1f;	break;
									case 3: gamax -= s_*2;	break;	
									case 6: gmulall -= s_*0.1f;	break;
									case 7: gsub -= s_*128;	break;
								}	updAll
							case VK_PRIOR:
								switch( glowy*glowX + glowx )
								{	case 0:	if (gd < 32) gd += s_;	updGlow();	break;
									case 1: addGlow = 1 - addGlow;	break;
									case 2: gamul += s_*0.1f;	break;
									case 3: gamax += s_*2;	break;
									case 6: gmulall += s_*0.1f;	break;
									case 7: gsub += s_*128;	break;
								}	updAll
						}
					else
						switch (k)
						{	case VK_NEXT:
								switch( glowy*glowX + glowx )
								{	case 0: if (gd > 1)  gd -= s_;	updGlow();	break;
									case 1: addGlow = 1 - addGlow;	break;
									case 2: gmul1 -= s_*0.1f;	break;
									case 3: gpow  -= s_*0.01f;	break;
									case 4: gmul2 -= s_*0.1f;	break;
									case 5: gpowm -= s_*0.05f;	break;
									case 6: gmulall  -= s_*0.1f;	break;
									case 7: gsub -= s_*128;	break;
								}	updAll
							case VK_PRIOR:
								switch( glowy*glowX + glowx )
								{	case 0: if (gd < 32) gd += s_;	updGlow();	break;
									case 1: addGlow = 1 - addGlow;	break;
									case 2: gmul1 += s_*0.1f;	break;
									case 3: gpow  += s_*0.01f;	break;
									case 4: gmul2 += s_*0.1f;	break;
									case 5: gpowm += s_*0.05f;	break;
									case 6: gmulall  += s_*0.1f;	break;
									case 7: gsub += s_*128;	break;
								}	updAll
						}	break;


				/* alpha Table */
				case 3:
					switch (k)
					{
						case VK_LEFT:	if (alphx > 0)  alphx--;			ret
						case VK_RIGHT:	if (alphx < alphX - 1)  alphx++;	ret
						case VK_UP:		if (alphy > 0)  alphy--;			ret
						case VK_DOWN:	if (alphy < alphY - 1)  alphy++;	ret
						
						case VK_DIVIDE:		--bckA;  if (bckA<0) bckA=0;  clearAll = 2;  ret
						case VK_MULTIPLY:	++bckA;  if (bckA>4) bckA=4;  clearAll = 2;  ret

						#define AddB(v,a)  v += a;  if (v>255) v=255;
						#define SubB(v,a)  v -= a;  if (v<0) v=0;
						case VK_NEXT:
							switch( alphy*alphX + alphx )
							{	case 2: --bckA;  if (bckA<0) bckA=0;  clearAll = 2;  ret
								case 0:	SubB(amin,s_)  updAll
								case 1: SubB(amax,s_)  updAll
								case 3: amulF -= s_*0.05f;  updAll
								case 4:	amulG -= s_*0.05f;  updAll
								case 6:	 aofsF -= s_;  updAll    case 7:  aofsG -= s_;  updAll    case 8:  aofsC -= s_;   updAll
								case 9:  SubB(bAc[0],s_) break;  case 10: SubB(bAc[1],s_) break;  case 11: SubB(bAc[2],s_) break;
								case 12: SubB(bAd[0],s_) break;  case 13: SubB(bAd[1],s_) break;  case 14: SubB(bAd[2],s_) break;
							}	break;
						case VK_PRIOR:
							switch( alphy*alphX + alphx )
							{	case 2: ++bckA;  if (bckA>4) bckA=4;  clearAll = 2;  ret
								case 0:	AddB(amin,s_)  updAll
								case 1: AddB(amax,s_)  updAll
								case 3: amulF += s_*0.05f;  updAll
								case 4:	amulG += s_*0.05f;  updAll
								case 6:	 aofsF += s_;  updAll    case 7:  aofsG += s_;  updAll    case 8:  aofsC += s_;   updAll
								case 9:  AddB(bAc[0],s_) break;  case 10: AddB(bAc[1],s_) break;  case 11: AddB(bAc[2],s_) break;
								case 12: AddB(bAd[0],s_) break;  case 13: AddB(bAd[1],s_) break;  case 14: AddB(bAd[2],s_) break;
							}	break;
					}


				/* save Table */
				case 4:
					switch (k)
					{
						case VK_LEFT:	if (savex > 0)  savex--;			ret
						case VK_RIGHT:	if (savex < saveX - 1)  savex++;	ret
						case VK_UP:		if (savey > 0)  savey--;			ret
						case VK_DOWN:	if (savey < saveY - 1)  savey++;	ret
						
						case VK_PRIOR:
							switch( savex )
							{
								case 0:
									switch( savey )
									{	case 1:  fmt++;	 if (fmt > nFormats)  fmt = 0;	break;
										case 2:	break;
										case 3:	break;
										case 0:	fileNum++;	break;
									}	break;
								case 1:
									switch( savey )
									{	case 0:	if (cfp < CFp)  cfp++;	break;
										case 1:	if (cfd < CFd)  cfd++;	break;
										case 2:	if (cft < CFt)  cft++;	break;
									}	break;
							}	break;
							
						case VK_NEXT:
							switch( savex )
							{
								case 0:
									switch( savey )
									{	case 1:  fmt--;	if (fmt < 0)  fmt = nFormats;	break;
										case 2: break;
										case 3: break;
										case 0:	if (fileNum > 0)  fileNum--;	break;
									}	break;
								case 1:
									switch( savey )
									{
										case 0:	if (cfp > 0)  cfp--;	break;
										case 1:	if (cfd > 0)  cfd--;	break;
										case 2:	if (cft > 0)  cft--;	break;
									}	break;
							}	break;
					}
					break;


				/* edit Table */
				case 5:
				{
					int l = strlen( es[ey] ), n;
					#define x_	ex[ey]
					
					if (k >= 32  &&  k <= 223)
					{
						BYTE b = kz[Shift][k - 32];
						if (Alt == 1  &&  k >= 'A' && k <= 'Z')
							b = pz[Shift][k - 'A'];
							if (b != 0 && l < EdX)
							{
								if (l == x_)
								{	/*|e*/
									es[ey][x_++] = b;
									es[ey][x_] = 0;  l++;
								}
								else if (!edIns)
								{	/*|->*/
									for (n = l;	n > x_;	n--)
										es[ey][n] = es[ey][n - 1];
									/*ins*/	es[ey][x_++] = b;
								}else
								{	/*ovr*/	es[ey][x_++] = b;	}
							}
					}
					
					switch (k)
					{
						case VK_INSERT: edIns = 1 - edIns;	ret

						case VK_HOME:	x_ = 0;	 ret
						case VK_END:	x_ = l;	 ret

						case VK_LEFT:	if (x_ > 0) --x_;	 ret
						case VK_RIGHT:	if (x_ < l) ++x_;	 ret
						case VK_DOWN:	if (ey < EdY)  ey++; ret
						case VK_UP:		if (ey > 0)  ey--;	 ret

						case VK_DELETE:
							if (x_ < l)  /* | <- */
								for (n = x_; n < l;	n++)
									es[ey][n] = es[ey][n + 1];	ret

						case VK_BACK:
							if (Ctrl)
							{	zi = z2 - z1;
								for (n = 0;	n <= 255; n++)	h[n].ch = 0;
									str = false;
								updAll
							}	//off str
							else
							{	/* <Back */
								if (x_ == 0 || l == 0)	ret	
								if (x_ == l )	{	/* <- | */
									es[ey][--l] = 0;	--x_;  }
								else {	/* < | - */
									--x_;	for (n = x_; n < l; n++)  es[ey][n] = es[ey][n + 1];  }
							}	ret
							
						case VK_RETURN:		//upd str
							if (Ctrl)
							{
								int l, i = 0;
								for (y = 0; y <= EdY; y++)
								{
									l = strlen( es[y] );
									for (x = 0;	x < l; x++)
									{	h[i++].ch = es[y][x];	}
									if (l > 0)  h[i++].ch = 13;
								}
								zi = max( 0, i - 1 );
								if (i == 0)  h[0].ch = ' ';
								if (h[zi].ch == 13)  zi--;
								str = true;		updAll
							}
					}
				}
				break;
				
				/**/

			/* < */
			}
			break;	

		/* List */		/* List */		/* List */		/* List */
		case 0:
			if (k >= VK_F1  &&  k <= VK_F4 )
			{
				edL[edT] = k - VK_F1;	upRct = 3;	ret
			}
			
			switch( edL[edT] )
			{	/* > */

			/*.clr List*/
			case 0:
				switch (k)
				{
					ListKeys( yClrL, pgClrL, cLY, nClrL - 1, updList )
					/*dir*/
					case VK_BACK:
						char dn[60];
						l = strlen( phc ) - 2;
						a = l + 1;
						while( l > lpaClr0  &&  phc[l] != '\\' )  l--;	//back
						if (l > lpaClr0)
						{
							phc[a] = 0;	 scpy( dn, &phc[l + 1] );
							phc[l + 1] = 0;		clrList();
							//  path
							yClrL = pgClrL = 0;	l = 0;
							while( l++ < nClrL )
								if (!strcmp( cle[l].na, dn ) )
								{	//  find
									yClrL = l;
									/* range */
									if (l > cLY)
									{	pgClrL = l/cLY*cLY;
										yClrL = l - pgClrL;  }
									ret
								}
						}	ret
						
					/*clr - load*/
					case VK_RETURN:
						l = pgClrL + yClrL;
						if (!cle[l].d)
						{
							if (!clrLoad( ct, curChan >= CH2, cle[l].na ))
							{	saveTime = 2.f;
								scpy( saveInfo, "ERROR: no file" );
							}	updClr
						}else
						if (cle[l].na)
						{
							scat( phc, cle[l].na );  scat( phc, "\\" );
							clrList();
							yClrL = pgClrL = 0;		updList
						}	// dir

					/*clr - save*/
					case'S':
						edTL = 2;	ret
				}
				break;	

			/*.fnt List*/
			case 1:
				switch (k)
				{
					ListKeys( yFntL, pgFntL, cLY, nFntL - 1, ret )

					/*dir*/
					case VK_BACK:
						char dn[60];
						l = strlen( phf ) - 2;
						a = l + 1;
						while( l > lpaFnt0  &&  phf[l] != '\\' )  l--;	//back
						if (l > lpaFnt0)
						{
							phf[a] = 0;
							scpy( dn, &phf[l + 1] );
							phf[l + 1] = 0;		fntList();
							//  path
							yFntL = pgFntL = 0;	l = 0;
							while( l++ < nFntL )
								if (!strcmp( fL[l].na, dn ))
								{	//  find
									yFntL = l;
									/* range */
									if (l > cLY)
									{	pgFntL = l/cLY*cLY;
										yFntL = l - pgFntL;  }
									ret
								}
						}	ret
						
					/*fnt - load*/
					case VK_RETURN:
						l = pgFntL + yFntL;
						if (!fL[l].d)
						{
							if (!fntLoad( fL[l].na ))
							{	saveTime = 2.f;
								scpy( saveInfo, "ERROR: no file" );
							}	updAll
						}else
						if (fL[l].na)
						{
							scat( phf, fL[l].na );	scat( phf, "\\" );
							fntList();
							yFntL = pgFntL = 0;		ret
						}	// dir

					/*fnt - save*/
					case'S':
						edTL = 3;	ret
				}
				break;	

			/*Chars List*/
			case 2:
				a = pgChrL + yChrL;

				/* ch */
				if (Ctrl && ChPage == 1  &&  k >= 32 && k <= 223)
				{
					BYTE b = kz[Shift][k - 32];
					if (Alt == 1  &&  k >= 'A' && k <= 'Z' )
						b = pz[Shift][k - 'A'];	
					if (b != 0 )
					{	h[a].ch = b;	updAll	}
				}

				/* grp */
				if (ChPage == 5 )
				{
					switch (k)
					{	case VK_DIVIDE:		ChPage--;	ret
						case VK_MULTIPLY:	ChPage++;	ret

						case VK_UP:		if (grcur > 1)  grcur--;			ret
						case VK_DOWN:	if (grcur < MaxGroups)  grcur++;	ret
						case VK_LEFT:	grwi[grcur]--;	updAll
						case VK_RIGHT:	grwi[grcur]++;	updAll
					}	ret
				}

				/* norm */
				if (!Shift)
					switch (k)
					{
						ListKeys( yChrL, pgChrL, chLY, zi, upChr = 1; ret  )
						//k >= 32 && k <= 223	// seek...
						case VK_DIVIDE:		if (ChPage > 0 )  ChPage--;			ret
						case VK_MULTIPLY:	if (ChPage < ChSubPgs )  ChPage++;	ret
							
						case VK_RETURN:		if (Ctrl && ChPage == 1 )	h[a].ch = 13;	updAll
						case VK_DELETE:		if (ChPage == 1 )	h[a].ch = 0;			updAll
					}
					
				/* subpg */
				switch( ChPage )
				{
					/*gr*/
					case 4:	switch (k)
						{	case VK_LEFT:	if (h[a].gr > 0 )  h[a].gr--;	updAll
							case VK_RIGHT:	if (h[a].gr < MaxGroups )  h[a].gr++;	updAll
						}	break;
					/*x +  y + */
					case 3:
						switch (k)
						{	case VK_LEFT:	h[a].xx--;	updAll
							case VK_RIGHT:	h[a].xx++;	updAll
							case VK_UP:		h[a].yy--;	updAll
							case VK_DOWN:	h[a].yy++;	updAll
						}	break;	
					/*ss ps*/
					case 2:	switch (k)
						{	case VK_LEFT:	h[a].ss--;	updAll
							case VK_RIGHT:	h[a].ss++;	updAll
							case VK_DOWN:	h[a].pp = 1 - h[a].pp;	updAll
							case VK_UP:		h[a].pp = 1 - h[a].pp;	updAll
						}	break;	
					/*fileNum ch*/
					case 1:	switch (k)
						{	case VK_LEFT:	h[a].ch--;	updAll
							case VK_RIGHT:	h[a].ch++;	updAll
							case VK_DOWN:	h[a].ch -= 10;	updAll
							case VK_UP:		h[a].ch += 10;	updAll
						}	break;
				}	break;

			/*Fonts List*/
			case 3:
				if (k >= 'A' && k <= 'Z' )
				for (l = 0;	l < iFonts;	l++)
					if (fontNames[l][0] == k)
					{
						yfn = l % chLY;	 pfn = l / chLY * chLY;		ret
					}	// seek
				switch (k)
				{
					ListKeys( yfn, pfn, chLY, iFonts, ret	 )
					
					case VK_BACK: edL[edT] = 1;	 ret	
					case VK_RETURN:
						if (strlen( fontNames[pfn + yfn] ) < 80)
						{	scpy( fontName, fontNames[pfn + yfn] );		updFnt  }
						else	ret
				}	break;	

		/* < */
		}	break;
			
	}/* <> edTL*/
			
	return false;
}
