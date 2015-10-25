#include "header.h"
#include "graph.h"


/* . . .	.	 .					. .. graph .. .					 .	 .	. . . */

bool CFgraph::graph()
{
	Ti.update();
	if (Ti.dt > 0.1f )	Ti.dt = 0.f;
	
	//int a;

	/*speed*/
	sp = 1.f;
	if (isKey( VK_SHIFT ) )  sp *= 0.25f;
	if (isKey( VK_CONTROL ) )  sp *= 4.f;  //sp *= 2.f;
	
	Alt  = isKey( VK_MENU );
	Shift= isKey( VK_SHIFT );
	Ctrl = isKey( VK_CONTROL );
	
	/*KeyPress*/
	if (key )
	{
		KeyPress( key );
		key = 0;
	}

	if (clearAll > 0 )
	{
		clearAll--;
		dev->Clear( 0, 0, D3DCLEAR_TARGET, 0, 1.f, 0 );
	}


	/*Begin*/
	dev->BeginScene();	
	FontBegin( 1 );
	RndSt( ALPHABLENDENABLE, TRUE )		//Font


	/*tab T*/
	anim( ac, 0 );
	Clear( xp, py, xp + xtabT[ntabT], py + Fy + 3,  ac*bckT[0].t );

	for (x = 0;	x < ntabT; x++)
	{
		if (edT != x )  Fclr = ac * CLR( 0.6f, 0.7f, 0.7f,  1 );
		else
		{
			Fclr = ac * CLR( 0.7f, 1, 1,  1 );
			Clear( xp + xtabT[x], py, xp + xtabT[x + 1], py + Fy + 3,  ac*CLR( 0.f, 0.2f, 0.4f, 1 ) );
		}
		scpy(s, stabT[x] );
		Write( xp + xtabT[x] + 7, py + 1 );
	}
	
	/*tab L*/
	anim( ah, 1 );
	Clear( xt, ( chLY + 2 )*Fy, xt + xtabL[ntabL], ( chLY + 2 )*Fy + Fy + 3,  ah*bckL[1].t );

	for (x = 0;	x < ntabL; x++)
	{
		if (edL[edT] != x )  Fclr = ah * CLR( 0.6f, 0.7f, 0.7f,  1 );	
		else
		{
			Fclr = ah * CLR( 0.7f, 1, 1,  1 );
			Clear( xt + xtabL[x], ( chLY + 2 )*Fy, xt + xtabL[x + 1], ( chLY + 2 )*Fy + Fy + 3,  ah*CLR( 0.f, 0.2f, 0.4f, 1 ) );
		}
		scpy(s, stabL[x] );
		Write( xt + xtabL[x] + 5, ( chLY + 2 )*Fy + 1 );
	}


	graphLT();


	/* status */
	Clear( xp, ye - Fy, xe, ye,  RGB( 50, 30, 10 ) );
	if (!bRect )
	{
		/*q*/
		if (atexFilR > 0.7f )
		{
			wrTex( atexFilR, texFilR, 5 );
		}
		else	/*rgb*/
		{
			Fclr = CLR( 0.6f, 0.6f, 0.7f,  1 );
			x = xp;
			wrRGB( onR, 'R' );
			wrRGB( onG, 'G' );
			wrRGB( onB, 'B' );
		}	}

		/*w*/
		if (atexFilH > 0.7f )
		{
			wrTex( atexFilH, texFilH, 80 );
		}
		else	/*zoom*/
		{
			Fclr = CLR( 0.6f, 0.6f, 0.7f,  1 );
			if (!bRect )
			{
				format(s,S, "%3.1f", zm );
				Write( xp + 70, ye - Fy );
			}
			if (showChar )
				format(s,S, "%3.1f", LcurRng );
			else
			{
				/*zoomf*/
				Fclr = CLR( 0, 0.87f, 0.95f, 1 );
				if (zoomf > 10.f )
					format(s,S, "%3.1f", zoomf );
				else
					format(s,S, "%3.2f", zoomf );
			}
			Write( xp + 110, ye - Fy );
		}

		/*F,G*/
		Fclr =  isFont ? CLR( 0.9f, 0.9f, 1, 1 ) : CLR( 0.5f, 0.5f, 0.6f, 1 );
		format(s,S, "F" );	WriteL( xp + 160, ye - Fy );
		Fclr =  isGlow ? CLR( 0.9f, 0.9f, 1, 1 ) : CLR( 0.5f, 0.5f, 0.6f, 1 );
		format(s,S, "G" );	WriteL( xp + 180, ye - Fy );

		/*char - of*/
		if (!isAll )
		{
			Fclr = CLR( 0.8f, 1, 1, 1 );
			scpy(s, statusAll );
			Write( xp + 203, ye - Fy );
		}

		/* saveInfo */
		if (saveInfo[0] )
		{
			if (1.5f * saveTime > 1.f )
				Clear( xp + 275, ye - Fy, xp + 330, ye,  RGB( 0, 20, 70 ) );
			Fclr =  range( 0.f, 1.f, 1.5f * saveTime ) * CLR( 1.0f, 0.6f, 0.3f,  1 );
			scpy(s, saveInfo );
			Write( xp + 280, ye - Fy );	
			/*znik*/
			saveTime -= ( ( saveInfo[0] == 'S' ) ? 1.f : 0.4f ) * Ti.dt;
			if (saveTime < 0.f )
				saveInfo[0] = 0;
		}

		/*times*/
		else
		{
			Fclr = CLR( 0.f, 0.7f, 0.6f,  1 );
			if (timeg > 1000 )
			{
				format(s,S, "%3.1f s %d", float( timeg ) / 1000.f, timec );
				Write( xp + 280, ye - Fy );
			} else {
				format(s,S, "%3d ms %d", timeg, timec );
				Write( xp + 280, ye - Fy );
			}
		}

		/*fps*/
		if (showfps )
		{
			Fclr = CLR( 1, 1, 1,  1 );
			format(s,S, "%4.0f", Ti.FR );
			Write( xe - 4*Fx, ye - Fy );
		}
		else	/*Tex dim*/
		{
			Fclr = CLR( 0.5f, 1.f, 0.7f,  1 );
			if (Ux == Uy )
			{
				format(s,S, "%4d", Ty );
				Write( xe - 4*Fx, ye - Fy );
			}
			else	/*x!=y*/
			{
				format(s,S, "%4dx%4d", Ux, Uy );
				Write( xe - 9*Fx, ye - Fy );
			}
		}


	/* Help */
	if (isHelp )  Help();
	else
	
	/*[ Font_zoom ]*/
	if (!showChar )
	{
		/*:. Full (no char) .:*/
		float a = sp * 4 *Ti.dt*85.f;
		if (Alt )
		{
			if (isKey( VK_DIVIDE ) )
			{
				if (zoomf > 1.f && !kAlt )
				{
					float zz = zoomf;	zoomf = int( zoomf );
					if (zz - zoomf == 0.f )
						zoomf -= 1.f;
					clearAll = 2;
				}
				kAlt = 1;
			}
			else
			if (isKey( VK_MULTIPLY ) )
			{
				if (!kAlt )
				{
					zoomf = int( zoomf ) + 1.f;
					clearAll = 2;
				}
				kAlt = 1;
			}
			else
				kAlt = 0;

			if (isKey( VK_SUBTRACT ) )
				if (zoomf > 0.1f )
				{
					zoomf -= zoomf * 0.01f*sp;
					clearAll = 2;
				}
			if (isKey( VK_ADD ) )
			{
				zoomf += zoomf * 0.01f*sp;
				clearAll = 2;
			}
		}

		/*[ico]*/
		x = min( xf2, Ux*zoomf );	 y = min( yf, Uy*zoomf );
		if (Alt )
		{
			if (isKey( VK_LEFT ) )	if (ofsx > a ) ofsx -= a;	 else ofsx = 0.f;	
			if (isKey( VK_UP ) )	if (ofsy > a ) ofsy -= a;	 else ofsy = 0.f;	
			if (isKey( VK_RIGHT ) ) if (ofsx + a < Ux - x/zoomf ) ofsx += a;	 else ofsx = Ux - x/zoomf;	
			if (isKey( VK_DOWN ) )	if (ofsy + a < Uy - y/zoomf ) ofsy += a;	 else ofsy = Uy - y/zoomf;
		}

		/*range*/
		if (ofsx > Ux - x/zoomf ) ofsx = Ux - x/zoomf;		if (ofsx < 0 )  ofsx = 0;
		if (ofsy > Uy - y/zoomf ) ofsy = Uy - y/zoomf;		if (ofsy < 0 )  ofsy = 0;

		/*fEnd*/
		FontEnd();
		
		//*  backgr for alpha
		CLR clt[2] = { RGB( bAc[0], bAc[1], bAc[2] ),
					   RGB( bAd[0], bAd[1], bAd[2] ) };
		switch (bckA)
		{
		case 0:  break;
		case 1:
			Clear( 0, 0, x, y,  clt[0] );
			break;
		case 2:
			Clear( 0, 0, x, y,  clt[1] );
			break;
		case 3:  // checker
		{
			const int s = 8;
			for (int j = 0; j < y; j+=s)  {
			for (int i = 0; i < x; i+=s)  {
				CLR cl = clt[ ((i+j)/s) % 2 ];
				Clear( i, j, i+s, j+s, cl );
			}	}
		}	break;
		case 4:  // gradient
		{
			int cd[3] = {bAd[0]-bAc[0], bAd[1]-bAc[1], bAd[2]-bAc[2]};
			for (int j = 0; j < y; ++j)
			{
				float c = float(y-j) / float(y);
				CLR cl = RGB( bAc[0]+c*cd[0], bAc[1]+c*cd[1], bAc[2]+c*cd[2] );
				Clear( 0, j, x, j+1, cl );
			}
		}	break;
		}

		/*draw*/
		RndSt( ALPHABLENDENABLE, TRUE )	//Rect
		RndSt( SRCBLEND, D3DBLEND_SRCALPHA);
		RndSt( DESTBLEND,D3DBLEND_INVSRCALPHA);

		uTexFil( zoomf < 1.f ? 1 : texFilH );
		UVadr( 1 );
		drawRect( 0, 0, xf2, yf,  ofsx, ofsy, xf2/zoomf, yf/zoomf,  Ty, TexFnt );
		UVadr( 0 );
		RndSt( ALPHABLENDENABLE, FALSE )	//Rect
		RndSt( SRCBLEND, D3DBLEND_ZERO);
		RndSt( DESTBLEND,D3DBLEND_ONE);

		/*fBeg*/
		FontBegin( 1 );
		RndSt( ALPHABLENDENABLE, TRUE )		//sliders

		/*_*/
		if (x == xf2)
		{
			Clear( 0, y, xf2, y + fp, bckSliOff );
			float xn = float( xf2 ) / float( Ux );
			Clear( int( ofsx*xn ), y, int( ( ofsx + float( xf2 )/zoomf )*xn ), y + fp, bckSliOn );
		}
		else
			Clear( 0, y, x, y + 2, bckSliOn );
		/*|*/
		if (y == yf)
		{
			Clear( x, 0, x + fp, yf, bckSliOff );
			float yFntL = float( yf ) / float( Uy );
			Clear( x, int( ofsy*yFntL ), x + fp, int( ( ofsy + float( yf )/zoomf )*yFntL ), bckSliOn );
		}
		else
			Clear( x, 0, x + 2, y, bckSliOn );

		/*fEnd*/
		FontEnd();
		RndSt( ALPHABLENDENABLE, FALSE )	//Rect
		
	}
	else	//:. show Char .://
	{
	
		/*[ico]*/
		x = min( xf, Ux );	 y = min( yf, Uy );
		if (Alt )
		{
			float a = sp*8.f *Ti.dt*85.f;	
			if (isKey( VK_LEFT ) )	if (ofsx > a ) ofsx -= a;  else ofsx = 0.f;	
			if (isKey( VK_UP ) )	if (ofsy > a ) ofsy -= a;  else ofsy = 0.f;	
			if (isKey( VK_RIGHT ) ) if (ofsx + a < Ux - x ) ofsx += a;  else ofsx = Ux - x;	
			if (isKey( VK_DOWN ) )	if (ofsy + a < Uy - y ) ofsy += a;  else ofsy = Uy - y;
		}
		/*range*/
		if (ofsx > Ux - x/zoomf ) ofsx = Ux - x/zoomf;		if (ofsx < 0 )  ofsx = 0;
		if (ofsy > Uy - y/zoomf ) ofsy = Uy - y/zoomf;		if (ofsy < 0 )  ofsy = 0;

		/*[Font]*/
		RECT re = { ofsx, ofsy, ofsx + x, ofsy + y };
		Fspr->Draw( TexFnt, &re, 0, &D3DXVECTOR3( 0, 0, 0 ), CLR( 1, 1, 1, 1 ) );

		/*sliders*/
			/*_*/
			if (x < Ux )
			{
				Clear( 0, y, xf, y + fp,  bckSliOff );
				float xn = float( xf ) / float( Ux );
				Clear( int( ofsx*xn ), y, int( ( ofsx + float( xf ) )*xn ), y + fp,  bckSliOn );
			}
			else
				Clear( 0, y, x + 1, y + 1, bckSliOn );
			/*|*/
			if (y < Uy )
			{
				Clear( x, 0, x + fp, yf,  bckSliOff );
				float yFntL = float( yf ) / float( Uy );
				Clear( x, int( ofsy*yFntL ), x + fp, int( ( ofsy + float( yf ) )*yFntL ),  bckSliOn );
			}
			else
				Clear( x, 0, x + 1, y, bckSliOn );
				
		/*fEnd*/
		FontEnd();
		RndSt( ALPHABLENDENABLE, FALSE );	//Rect

		/*[Char]*/
		if (!bRect && upChr > 0 )
		{
			x = h[pgChrL + yChrL].wi;	 y = Sy;
			zx = xz + x*LcurRng + gz;
			Clear( xz, yz - gz,  xz + ss*LcurRng + gz, zy + gz,  CLR( 0, 0, 0, 1 ) );
			
			/*rys*/
			uTexFil( texFilH );
			drawRect( xz, yz, x*LcurRng, y*LcurRng,  h[pgChrL + yChrL].bx, h[pgChrL + yChrL].by, x, y,  Ty, TexFnt );
			
			/*frame*/
			Clear( xz - gz, yz - gz, zx, yz, bckFrame );
			Clear( xz - gz, zy, zx, zy + gz, bckFrame );
			Clear( xz - gz, yz, xz, zy, bckFrame );
			Clear( zx - gz, yz, zx, zy, bckFrame );
			if (clearAll == 0 )
				upChr = 0;
		}

	}	//:. .:
	

	/* upd Rects */
	if (!bRect && upRct > 0 )
	{
		uTexFil( texFilR );
		if (clearAll == 0 )
		{
			if (upRct == 2 )
				updPrv();
			else
				if (upRct == 1 )	updRect();
			upRct = 0;
		}
		/* rect All */
		drawRect( xr, yr, ss*zm, Sy*zm,  0, 0, ss, Sy,  MaxSY, rTexAll );
		/* rect2 Chan/prv */
		drawRect( xr2, yr, ss*zm, Sy*zm,  0, 0, ss, Sy,  MaxSY, edTL == 1 ? rTexChan : rTexPrv );
	}

	/*End*/
	dev->EndScene();
	dev->Present( 0, 0, 0, 0 );
	return true;
}


bool CFgraph::newRect( LPDIRECT3DTEXTURE9& tx )
{
	Warng(
		D3DXCreateTexture( dev, MaxSY, MaxSY, 0, D3DUSAGE_DYNAMIC, D3DFMT_X8B8G8R8, D3DPOOL_DEFAULT, &tx ),
		"create rect tex", "" );
	Warng(
		tx->LockRect( 0, &lrect, 0, 0 ) ,
		"lock", "Begin" );
	UINT a;
	UINT* o_ = ( UINT* ) lrect.pBits;
	UINT yO = lrect.Pitch >> 2;
	
	for (UINT y = 0; y < MaxSY; ++y)
	{
		a = y * yO;
		for (UINT x = 0; x < MaxSY; ++x, ++a)
			o_[a] = 0;
	}
	tx->UnlockRect( 0 );
	
	return true;
}

//	_	 _	_ _ __ ___ ____	begin	__ _	_
bool CFgraph::initGraph()
{
	newRect( rTexPrv );
	newRect( rTexAll );
	newRect( rTexChan );
	
	/*st, rs*/D3DXMATRIXA16 i;		D3DXMatrixIdentity( &i );	
	dev->SetTransform( D3DTS_VIEW, &i );
	dev->SetTransform( D3DTS_WORLD, &i );
	dev->SetTransform( D3DTS_PROJECTION, &i );
	
	RndSt( LIGHTING, FALSE );
	RndSt( CULLMODE, D3DCULL_NONE );
	RndSt( ZENABLE,  D3DZB_FALSE );

	/*alpha*/
	RndSt( SRCBLEND,  D3DBLEND_SRCALPHA );
	RndSt( DESTBLEND, D3DBLEND_INVDESTALPHA );
	
	UVadr( 0 );
	return true;
}

void CFgraph::destroyGraph()
{
	for (n = 0;	n <= iFonts; n++)
		DELETEA( fontNames[n] );

	for (n = 0;	n < MaxList;	n++)
		RELEASE( cle[n].ico );

	RELEASE( TexFnt );

	RELEASE( rTexAll );
	RELEASE( rTexPrv );
	RELEASE( rTexChan );
}


//  utility
void CFgraph::clrHead( float val, int yChrL, int yy )
{
	if (y == yChrL)
	{
		Fclr = val * CLR( 1.f, 1.1f, 1.2f,  1 );
		Clear( xt, yy, xe, yy + Fy, val * bckL[2].q );	//bck q[]
	}	// Chars clr
	else
		Fclr = val * CLR( 0.7f, 0.8f, 0.9f,  1 );
		//Fclr = val * CLR( 1.f - y * 0.009f,  1.1f - y % 8 * 0.04f,  1.f,  1 );

	float mod = ((y%2==0)?1:0) + ((y%4==0)?1:0) + ((y%8==0)?1:0);
	Clear( xt+1, yy+1, xe-1, yy + Fy-1,
		(0.9f + 0.06f* mod) * val * bckL[2].t );
}

void CFgraph::wrRGB( int onR, char ch )
{
	if (onR )
		Fclr = CLR( 0.7f, 0.7f, 0.7f,  1 );
	else
		Fclr = CLR( 0.4f, 0.4f, 0.4f,  1 );

	format(s,S, "%c", ch );
	Write( x, ye - Fy );
	x += Fx*2;
}

void CFgraph::wrTex( float& atexFil, int texFil, int xx )
{
	atexFil -= atexFil * 0.007f *Ti.dt*85.f;
	Fclr = atexFil * CLR( 1.0f, 0.9f, 1.0f,  1 );
	scpy(s, sTexFil[texFil] );
	Write( xp + xx, ye - Fy );
}

void CFgraph::anim( float& a, int w )
{
	ar = a - ( ( edTL == w || w == 0 && edTL > 1 ) ? 0.65f : 1.f );
	a -= ( ( ar > 0.f ) ? 0.05f : 0.1f ) * ar * Ti.dt*85.f;
}
