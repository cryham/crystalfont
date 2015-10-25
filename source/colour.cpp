#include "header.h"
#include "colour.h"


/*  =   = 	 = 	  =							 = 	 =   ==  settings  ==   = 	 = 							= 	 = 	 =   =  */
CFclr::CFclr() :
	ax(1), bx(1), ay(0), by(0),
	Ea(1), 	fbold(0), fix(0),  ql(1),  bRect(0),
	sy(21), Sy(21),  z1(32), z2('z'), zi('z'-32),

	Ty(128), Ux(128), Uy(128), f(0),
	sx(0), ss(0), grcur(0),
	LcurRng(1.f), zm(1.f), mz(1.f),
	zoomf(1.f), ofsx(0.f), ofsy(0.f),

	xt(0), xr(0),yr(0), xr2(0),
	xp(0),yp(0), px(0),py(0),
	xz(0),yz(0), zx(0), zy(0), gz(0),
	xf(0),xf2(0), yf(0), fp(0),
	cLY(0), 

	clrx(0), clry(0), curChan(0),
	fontx(0), fonty(0),  glowx(0), glowy(0),  alphx(0), alphy(0),
	savex(0), savey(0),  editx(0), edity(0),

	tFont(0), tGlow(0), tAlpha(0),
	tClrF(0), tClrG(0), tChan(0), tPrv(0),
	TexFnt(0), rTexAll(0), rTexChan(0), rTexPrv(0),
	
	bckA(4),amin(0),amax(255), aofsF(0),aofsG(0),aofsC(0),
	amulF(1.f), amulG(1.f),

	edT(0), edTL(0),
		x(0), y(0), n(0),  w(0), b(0),
		onR(1), onG(1), onB(1),
		timeg(0), timec(0),

	isGlow(0), isFont(1), isAll(1), showChar(0), addGlow(0),

	gmul1(0.8f),gmul2(0.8f), gpow(0.3f),gpowm(0.7f), gmulall(1.f),
	gsub(768),  gamul(2.4f), gamax(128),
	fgd(0.f), gd(8),  gd2(0), gdy(0), gdt(0),

	yClrL(0), pgClrL(0), nClrL(0),  neditx(0),
	yChrL(0), pgChrL(0), ChPage(0), chLY(0)
{
	scpy( fontName, "Tahoma" );
	ZeroMemory( &nedit[0], sizeof(nedit));
	ZeroMemory( &phc[0], sizeof(phc));
	ZeroMemory( &statusAll, sizeof(statusAll));
	
	ZeroMemory( &h[0], sizeof(h));
	for (int g=0; g < MaxGroups + 1; g++)
	{	grw[g]=0;  grwi[g]=0;  }

	bAc[0]=40; bAc[1]=30; bAc[2]=20;
	bAd[0]=120; bAd[1]=80; bAd[2]=60;
#if 0
	CTE cte, ctE[clrY][clrX];
	Ct  ct, lct;	
	CLR	bckFrame,
		bckSliOn, bckSliOff;
	ICO ico;
	CLE cle[MaxList];
#endif
}

bool CFclr::settings()
{
	/*Font*/
	scpy( fontName, "Tahoma" );
	sy = 33;
	z1 = ' ';	z2 = 'z';	zi = z2 - z1;
	Ea = 1;		fix = 0;	fbold = 0;   ql = 1;

	/*Glow*/
	addGlow = 0;
	gamax = 128;	gamul = 2.4;

	gmulall = 1.;	gsub = 768;
	gmul1 = 0.8;	gmul2 = 0.8;
	gpow = 0.3;		gpowm = 0.7;
	gd = 8;

	updGlow();
	
	/**/nedit[0] = 0;
	onR = onG = onB = 1;	grcur = 1;

	isAll = 1;	 isFont = 1;	isGlow = 0;
	zoomf = 1.f;
	setDim();

	/*.clr path*/
	scpy( phc, pathClr0 );
	clrList();

	/* MakeFont */
	TexFnt = 0;
	if (!MakeFont())
		return false;
	updZoom();

	Colour();
	Colorize();

	return true;
}


void CFclr::updGlow()
{
	fgd = 1.f / float( gd ) / sqrt( 2.f );
	gd  = range( 1, MaxGlow, gd );
	gd2 = 2 * gd;
	gdy = gd * 256;
}

bool CFclr::updZoom()
{
	LcurRng = 10;
	while( ( ss*LcurRng > xt - xz - 30  ||  Sy*LcurRng > yp )  &&  LcurRng > 0.5f )
		LcurRng -= 0.5f;
	zy = yz + Sy * LcurRng;
	
	zm = 16;
	while( ss*zm > xr2  &&  zm >= 0.4f )
		zm -= 0.2f;
	while( Sy*zm > ye - yr  &&  zm >= 0.4f )
		zm -= 0.2f;
	mz = zm;	// rect zoom
	
	return true;
}


bool CFclr::setDim()
{
	/*rects rTexAll, rTexChan*/
	xr = 0;	 xr2 = 230;	 yr = ye * 580 / 768;	// after MakeFont

	/*font*/
	xf = xe * 60 / 102;  yf = yr - 40;

	/*sliders*/
	bckSliOff = CLR( 0.2f, 0.2f, 0.4f,  1 );
	bckSliOn  = CLR( 0.3f, 0.3f, 0.6f,  1 );
	fp = 12;

	/*char*/
	xz = xf + 40;	yz = 10;

	/*frame*/
	bckFrame = 0.5f * CLR( 0.3f, 0.7f, 1.f,  1 );
	gz = 1;	

	/*List*/
	xt = xe - 160;

	/*no char*/
	xf2 = xt - 40;
	/*lists*/
	chLY = 32;  cLY = 25;  //chLY = 24;  cLY = 18;	

	/*T*/
	xp = xr2 * 2;	px = xp + 370;
	yp = yr;		py = yp + 140;
	//* */updZoom();


	/*icons*/
	x = 0;
	for (n = 0; n < MaxList; n++)
		if (FAILED(
			D3DXCreateTexture( dev, ICOsize, ICOsize, 1, D3DUSAGE_DYNAMIC, D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, &cle[n].ico )	) )
		x++;	
	
	format(s,S, "%d", x );
	if (x > 0 )
		WrnMsg( "create icon", s )


	/* ct elem */
	for (y = 0;	y < clrY; y++)
		for (x = 0;	x < clrX; x++)
		{
			ctE[y][x] = cte0[y][x];
			ctE[y][x].x += Xp[x];
			ctE[y][x].y = ctE[y][x].y * Fy + Fy / 2;
		}

	/* first ct */
	memcpy( &ct, &ct0, sizeof( ct0 ) );

	return true;
}


/* - 	  - 	  - 	  - 	  - 	Colour		- 	  - 	  - 	  - 	  - 	 - */
// float table f[..]:
//   012 = rgb	3 i  4 j    5 s  6 yx  7 c    13 k  14 r   15 z  16 of
//   8 <  9 >  10 u  11->  (range)
//   12^ channel type
//--------------------------------------------------------------------------------------------------

void CFclr::Colour( int sY, int sy, int ss, Ct& ct, BYTE* tClrF, BYTE* tClrG, BYTE* tChan)
{
	if (!isAll || ( !isFont && !isGlow && edT != 0 ) )
		if (sY != 21 )
			return;
	
	DWORD tst = timeGetTime();	/*t*/
	
	float i, j, ii, jj,  h[CH], c,  k, r;
	int x, y, a, t;
	float
		xs = 20.f / float( ss - 1 ),
		ys = 20.f / float( sy - 1 );
	
	for (y = 0;	y < sy;	++y )
	{
		b = y * sY * 3;
		for (x = 0;	x < ss;	++x )
		{
			for (a = 0;	a < CH;	++a )
			{
				f = &ct[a][0];
				t = Flt2Int( f[12] );

				/*empty-off*/
				if (f[10] == 0 )
					h[a] = 0;
				else
				{
					c = f[7];
					switch( t )
					{
						/*diamond*/
						case 5:
							i = float( x ) * xs - f[3];
							j = float( sy - 1 - y ) * ys - f[4];
							
							k = atan2( i, j );   r = sqrt( i*i + j*j );

							r *= pow( abs( 	1.f - f[15] - abs( sinf( - PI/4.f + 0.5f*( f[14]*k + f[13] )  ) ) ), f[6] );
							c -=  10.f * r * f[5];
							break;

						/*star*/
						case 4:
							i = float( x ) * xs - f[3];
							j = float( sy - 1 - y ) * ys - f[4];

							k = atan2( i, j );   r = sqrt( i*i + j*j );
							r *= f[15] + 0.5f  + 0.5f*sinf( f[14]*k + f[13] );
							
							c -=  10.f * pow( r, f[6] ) * f[5];
							break;

						/*circle*/
						case 1:
							i = float( x ) * xs - f[3];
							j = float( sy - 1 - y ) * ys;
							
							f[14] = max( 0.001f, f[14] );
							i += f[4] * cosf( f[13] );
							j += f[4] * sinf( f[13] );
							
							i -= 10.f * cosf( f[13] ) * f[14] + 10.f;
							j -= 10.f * sinf( f[13] ) * f[14] + 10.f;
							
							c +=  f[5] * ( i*i + j*j * f[6] ) / f[14] / f[14];
							break;
							
						/*line*/
						case 2:
							i = float( x ) * xs;
							j = float( sy - 1 - y ) * ys;
							
							ii = cosf( f[13] );
							jj = sinf( f[13] );
							
							k = 10.f * ( ii + jj );

							i += f[4] * cosf( f[13] );
							j += f[4] * sinf( f[13] );
							
							c -=  10.f * ( ii*i + jj*j - k ) * f[5];
							break;
						
						/*point*/
						case 3:
							i = float( x ) * xs - f[3];
							j = float( sy - 1 - y ) * ys - f[4];
							
							c -=  10.f * pow( i*i + j*j, f[6] - 0.5f ) * f[5];
							break;
							
						/*simple*/
						case 0:
							i = float( x ) * xs + f[3];
							j = float( sy - 1 - y ) * ys * f[6] + f[4];
							
							c -=  i * j * f[5];
							break;
					}
					
					// range
					if (c < f[9] )
					{
						c *= -f[8];
						c = min( c, f[11] );
					}
					else
						c = min( c, f[10] );
					
					h[a] = c;
				}
			}
		 
		 	
			if (tClrG && tChan)
			{
				/*rTexChan*/
				for (n = 0; n < 3; n++)
				{
					c = ct[curChan][n]*h[curChan];
					c = range( 0.f, 255.f, c );
					tChan[b++] = c;
				}
				b -= 3;
			
				/*tClrG*/
				for (n = 0; n < 3; n++)
				{
					c = 0.f;
					for (a = 0;	a < 6; ++a )
						c += ct[a + 6][n] * h[a + 6];
					c = range( 0.f, 255.f, c );

					tClrG[b++] = c;
				}
				b -= 3;
			}

			/*tClrF*/
			for (n = 0; n < 3; n++)
			{
				c = 0.f;
				for (a = 0;	a < 6; ++a )
					c += ct[a][n] * h[a];
				c = range( 0.f, 255.f, c );

				tClrF[b++] = c;
			}
		
		}
	}
	
	timec = timeGetTime() - tst;	/*t*/
}


void CFclr::Colour()
{
	if (bRect )
		Colour( MaxSY, Uy, Ux, ct, tClrF );
	else
		Colour( MaxSY, Sy, ss, ct, tClrF, tClrG, tChan );
}


//--------------------------------------------------------------------------------------------------
// update Rects		/* borders _| +1 pix */
#define ssy( cc )	if (y == Sy ) c = &cc[ ( ( Sy - 1 ) * MaxSY + x ) * 3 ];	\
					if (x == ss ) c = &cc[ ( y*MaxSY + ss - 1 ) * 3 ];
bool CFclr::updRect()
{
	static BYTE *c, *cc;
	UINT *o_, yO, *q_;
	DWORD a, b;
	
	if (curChan < CH2)
		cc = tClrF;
	else
		cc = tClrG;
		
	if (FAILED( rTexAll->LockRect( 0, &lrect, 0, 0 ) ) )
		MsgInf( "lock rTexAll", "" );
	
	o_ = (UINT*) lrect.pBits;
	yO = lrect.Pitch >> 2;
	
	if (FAILED( rTexChan->LockRect( 0, &lrect, 0, 0 ) ) )
		MsgInf( "lock rTexChan", "" );
	
	q_ = (UINT*) lrect.pBits;
	
	for (y = 0;	y <= Sy; y++)
	{
		a = y * yO;
		b = y * MaxSY * 3;
		for (x = 0;	x <= ss; x++)
		{	//updRect
			c = &cc[b];	 ssy( cc )
			o_[a] = RGB( onB*c[2], onG*c[1], onR*c[0] );

			c = &tChan[b];	 ssy( tChan )
			q_[a] = RGB( c[2], c[1], c[0] );		b += 3;		++a;
		}
	}

	rTexAll->UnlockRect( 0 );
	rTexChan->UnlockRect( 0 );

	return true;
}


bool CFclr::updPrv()
{
	static BYTE *c;
	DWORD a;
	UINT *q_, yO;	

	if (FAILED(
		rTexPrv->LockRect( 0, &lrect, 0, 0 ) ) )
		MsgInf( "lock rTexAll", "" )

	q_ = (UINT*) lrect.pBits;
	yO = lrect.Pitch >> 2;
	
	for (y = 0; y <= Sy; y++)
	{
		a = y * yO;
		b = y * MaxSY * 3;
		for (x = 0; x <= ss; x++)
		{
			//prv
			c = &tPrv[b];
			ssy( tPrv );
			q_[a] = RGB( c[2], c[1], c[0] );
			b += 3;
			++a;
		}
	}
	rTexPrv->UnlockRect( 0 );

	return true;
}


//	 Lists		//	.clr
//--------------------------------------------------------------------------------------------------
bool CFclr::clrSave()
{
	Ct ct_;
	memcpy( ct_, ( curChan >= CH2 ) ? &ct[CH2][0] : &ct[0][0], sizeof( Ct2 ) );
	Colour( 21, 21, 21, ct_, ( BYTE* ) ico );
	
	BYTE *c = &ico[9][9][0];
	int cc = RGB( c[0], c[1], c[2] );

	ofstream fout;
	sadd(s, phc, nedit );
	scat( s, ".clr" );

	fout.open( s, fileOut );
	if (fout.fail() )
		return false;
	fout.write( ( char* ) &cc, sizeof( int ) );
	fout.write( ( char* ) ico, sizeof( ico ) );
	fout.write( ( char* ) ct_, sizeof( Ct2 ) );

	fout.close();
	return true;
}


bool CFclr::clrLoad( Ct& ct, int g, char* na )
{
	ifstream fin;
	sadd(s, phc, na );
	scat( s, ".clr" );
	
	fin.open( s, fileIn );
	if (fin.fail() )
		return false;
	
	fin.seekg( sizeof( int ) + sizeof( ico ) );
	if (g )
		fin.read( ( char* ) &ct[CH2][0], sizeof( Ct2 ) );
	else
		fin.read( ( char* ) &ct, sizeof( Ct2 ) );
	
	fin.close();
	return true;
}


bool CFclr::clrList()
{
	WIN32_FIND_DATAA fd;
	ifstream fin;
	UINT w, x, y, a;
	BYTE *c;		//upd
	
	sadd(s, phc, "*.*" );

	HANDLE hs = FindFirstFileA( s, &fd );
	if (hs == INVALID_HANDLE_VALUE )
		return false;
	
	int dn = 1;		nClrL = 0;
	while (dn)
	{
		if (nClrL < MaxList  &&  fd.cFileName[0] != '.' )
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				/*file name*/
				scpy( cle[nClrL].na, fd.cFileName );
				cle[nClrL].d = 1;
				nClrL++;
			}
			else
			{
				char *pe;
				/*file extension*/
				pe = strrchr( fd.cFileName, '.' );
				if (pe)
				{
					scpy(s, pe + 1 );
					if (_strnicmp( s, "clr", 3 ) == 0 )
					{
						/*open*/
						sadd(s, phc, fd.cFileName );
						fin.open( s, fileIn );
						if (fin.fail() )
							WrnMsg( s, "no file" );
						/*name*/
						pe[0] = 0;
						scpy( cle[nClrL].na, fd.cFileName );
						/*1clr*/
						fin.read( ( char* ) &w, sizeof( int ) );
						/*ico*/
						fin.read( ( char* ) ico, sizeof( ico ) );
						fin.close();

						/*copy_ico*/
						UINT *o_, yO;
						Warng(
							cle[nClrL].ico->LockRect( 0, &lrect, 0, 0 ) ,
							"lock lk", "clrList" );
							
						o_ = ( UINT* ) lrect.pBits;
						yO = lrect.Pitch >> 2;
						
						for (y = 0;	y < ICOsize; y++)
						{
							a = y * yO;
							for (x = 0;	x < ICOsize; x++)
							{
								c = &ico[y][x][0];
								o_[++a] = RGB( c[2], c[1], c[0] );
							}
						}
						cle[nClrL].ico->UnlockRect( 0 );
						cle[nClrL].d = 0;
						nClrL++;
					}
				}
			}
		}
	
		if (!FindNextFileA( hs, &fd ) ) dn = 0;
	}
	
	FindClose( hs );	

	//dirs first
	int i, j;
	CLE e;

	for (j = 0;	j < nClrL;	j++)
		for (i = 0;	i < nClrL - j;	i++)
			if (cle[i].d < cle[j].d )
			{
				e = cle[i];
				cle[i] = cle[j];
				cle[j] = e;
			}

	return true;
}
