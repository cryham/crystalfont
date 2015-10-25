#include "header.h"
#include "font.h"


//* == -- -   - 	 -			  -   -= 	Create Font	 =  -   - 			- 	 -  -- -  == */
bool CFfont::MakeFont()
{
	if (!isAll || (!isFont && !isGlow))
	{
		timeg = 0;
		return true;
	}
	
	int sTy = Ty, a;

	if (bRect)
	{
		Ux = rect_sx;	Uy = rect_sy;
		timeg = 0;	Ty = MinTex;
		while( rect_sx > Ty  ||  rect_sy > Ty )
			Ty *= 2;
		Sy = sx = Ty;
		/*chk*/
		if (Ty > MaxTex )
		{
			format(s,S, "%d", Ty );
			WrnMsg( s, "Texture size too big" );
		}
	}
	else  // ! bRect
	{
		//  clear --
		//size_t size = MaxTex * MaxTex;
		//memset(tFont, 0, size);
		//memset(tGlow, 0, size);
		//memset(tAlpha, 0, size);
	
		/*crt fnt*/
		DeleteObject( hf );	 hf = 0;

		DWORD qla[5] = {NONANTIALIASED_QUALITY, ANTIALIASED_QUALITY, PROOF_QUALITY, CLEARTYPE_QUALITY, CLEARTYPE_NATURAL_QUALITY};
		hf = CreateFontA( sy, 0, 0, 0, (fbold == 0) ? FW_NORMAL : FW_BOLD, 0, 0, 0,
			DEFAULT_CHARSET, //EASTEUROPE_CHARSET, ANSI_CHARSET
			OUT_TT_PRECIS, CLIP_TT_ALWAYS,  qla[ql], DEFAULT_PITCH, fontName );
		if (hf == 0 )
			WrnMsg( "create font fail", "MakeFont" );
			
		int i, j, k, yy;

		Sy =  max( 1, sy + ay + by );
		if (Sy > MaxSY )
			WrnMsg( "Texture size too big.", "MakeFont" );

		/*Codes:*/
		ForEachChar
			if (h[n].ch )
				h[n].s = h[n].ch;
			else
				h[n].s = n + z1;

		/*[Width]*/
		static ABCFLOAT A[256];
		SelectObject( dc, hf );
		GetCharABCWidthsFloat( dc, 0, 255, A );
		ssn = 0;	ss = 0;
		
		ForEachChar
		{
			h[n].h[0] = i = A[h[n].s].abcfA;
			h[n].h[1] = j = A[h[n].s].abcfB;
			h[n].h[2] = k = A[h[n].s].abcfC;
			if (i < 0 )  i = - i;
			if (k < 0 )  k = - k;
			w = j + max( k,  ax + bx );
			h[n].wi = w  + h[n].ss;
			if (w > ss )
			{
				ssn = n;	ss = w;
			}
		}

		/*fixed width > */
		if (fix )
		{
			int s0 = 0;
			ForEachChar
				if (h[n].wi > s0 )
					s0 = h[n].wi;	//max width
			ForEachChar
			{
				h[n].of = ( s0 - h[n].wi ) / 2;
				h[n].ps = 1;
				h[n].wi = s0 + ax + bx;
			}
			ss = s0;
		}
		/*variable width > */
		else
			ForEachChar
			{
				h[n].of = 0;
				h[n].ps = h[n].pp;
				/*enter*/
				if (h[n].ch == 13 )
					h[n].wi = - bx;
			}

		// width (smooth) groups
		if (!fix )
		{
			ZeroMem( grw );
			int g;
			ForEachChar
			{
				g = h[n].gr;	
				if (g > 0 && g <= MaxGroups )
					if (h[n].wi > grw[g] )
						grw[g] = h[n].wi + grwi[g];
			}

			//mx wi gr
			/*of*/
			for (g = 1;	g <= MaxGroups;	g++)
				if (grw[g] > 0 )
				ForEachChar
					if (h[n].gr == g )
					{
						h[n].of = ( grw[g] - h[n].wi ) / 2;
						h[n].ps = 1;
						h[n].wi = grw[g];
					}
		}

		/*[Dim Ty]*/
		Ty = MinTex;	sx = 0;
		/*sx = */
		ForEachChar
			sx +=  h[n].wi;		//sum all

		if (str )
		{
			/*lin = */
			lin = 1;
			ForEachChar
				if (h[n].ch == 13)
					lin++;
			int ml = 0;
			int sl = 0;
			/*sx = */
			ForEachChar
			{
				if (h[n].ch == 13)
					sl = 0;
				else
					sl += h[n].wi;
				if (sl > ml)
					ml = sl;
			}	//max line
			
			while (ml > Ty || lin*Sy > Ty)	Ty *= 2;

			if (!Txy)	Ux = Uy = Ty;
			else	{	Ux = ml;	Uy = lin*Sy;	}
		}
		else	// !str
		{
			if (!oneLine)
				do{
					x = 0;	y = 0;	lin = 1;
					/*[Pos]*/
					ForEachChar
					{
						/*next line*/
						if (x + h[n].wi >= Ty)
						{
							x = 0;	 y += Sy;	lin++;
						}
						h[n].bx = x;	h[n].by = y;
						x += h[n].wi;
					}

					if (y + Sy >= Ty)
					{
						i = 1;	 Ty *= 2;
					}
					else
						i = 0;
				}while (i);
			else
			{
				x = 0;	y = 0;	 lin = 1;
				/*[Pos] 1line*/
				ForEachChar
				{
					h[n].bx = x;	h[n].by = y;
					x += h[n].wi;
				}
				while (x > Ty || Sy > Ty)	Ty *= 2;
			}
			
			if (!Txy)	Ux = Uy = Ty;
			else	{	Ux = Ty;	Uy = y + Sy;	}
		}
		
		
		/*chk*/
		if (Ty > MaxTex)
		{
			format(s,S, "%d", Ty );
			WrnMsg( s, "Texture size too big" );
		}

		/*dist_glw array*/
		int l, su;	float xx;
		if (isGlow)
			for (j = - gd; j <= gd; ++j )
				for (i = - gd; i <= gd; ++i )
				{
					xx = float( i*i + j*j ) * fgd;
					gdt[ ( gd + j ) * mdg + gd + i ] =
						min( 8192,
							int( 8192.f * gmulall / (
								0.0001f + gmul2 * pow( xx,  gpow * gpowm )
										+ gmul1 * pow( xx,  gpow ) )  - gsub ) );
				}

		DWORD tst = timeGetTime(),  tz, tzs = tst;		//time begin
		
		/**/Clear( xp + 203, ye - Fy, xp + 268, ye,  RGB( 50, 30, 10 ) );
			//Clear( xp + 203, ye - 14, xp + 268, ye - 6,  RGB( 90, 75, 60 ) );	//

		int xb = 0, yb = 0,  aa, me, e, ee, *ea,
			at = ( MaxSY - 1 - MaxGlow  + ay ) * MaxSY + MaxGlow,  ab;
		psx = 0;	yy = 0;	

		/*[DrawChars]*/
		#define oy	at - y*MaxSY	//bmp from bottom
		ForEachChar
		{
			h[n].psi =  Ea == 0 || fix ? 0 : min( 0, - bx );
			
			/* progress bar % */
			//
				tz = timeGetTime();
				if (tz - tzs > 50)		// upd time, ms
				{
					/*Begin*/
					dev->BeginScene();
					float p = float( n ) / float( zi );
					
					Clear( xp + 203, ye - 14,  xp + 203 + 65*p, ye - 6,
						RGB( 240 - 180*p, 170 - 120*p, 70 - 70*p ) );
					/*End*/
					dev->EndScene();
					dev->Present( 0, 0, 0, 0 );
					tzs = tz;
				}
			//
			
			s[0] = h[n].s;
			/*clear + */
			for (y =  - gd; y < sy + gd; ++y )
			{
				a = oy;
				for (x =  - gd;	x < ss + gd; ++x )
					oo[++a] = 0;
			}
			/* > */
			if (h[n].ch != 13 )  // draw
			{
				x =  - h[n].h[0] + h[n].of  + MaxGlow + ax  + h[n].xx;
				y =  MaxGlow + h[n].yy;
				TextOutA( dc,  x, y,  s, 1 );
			}

			/*empty width check*/
			if (!fix && Ea)
			{
				if (h[n].ps == 0  &&  h[n].s != ' '/*?*/ )
				{
					x = h[n].wi - 1;
					j = 1;
					while( j  &&  x > 0 )
					{
						w = 1;	 y = 0;
						while( w  &&  y < Sy )
						{
							if (oo[oy + x] > 0 ) w = 0;
							++y;
						}
						if (y == Sy  &&  w == 1 )
						{
							--x;	h[n].wi--;	h[n].psi++;
						}
						else
							j = 0;
					}
					h[n].wi += bx;
				}

				/*next line*/
				if (( !str && xb + h[n].wi >= Ty )  ||  h[n].ch == 13 )
				{
					xb = 0;
					yb += Sy;
				}
				h[n].bx = xb;	h[n].by = yb;
				xb += h[n].wi;
			}

			if (h[n].wi < 0 )
				h[n].wi = 0;
			psx += h[n].wi;
			
			/*byx*/
			ab =  ( h[n].by /* + h[n].yt*/ ) * MaxTex  + h[n].bx /* + h[n].xt*/;

			/* tFont write */
			for (y = 0;	y < Sy;	++y )
			{
				w = y * MaxTex + ab;
				a = oy;
				for (x = 0;	x < h[n].wi; ++x )
				{
					tFont[w] = BYTE( oo[a] );
					++a;  ++w;
				}
			}

			/* < GLOW > */
			if (isGlow)
				if (!addGlow )
					/*distance glow*/
					for (y = 0;	y < Sy;	++y )
					{
						w = y * MaxTex + ab;
						aa = oy  - gd - gd * MaxSY;
						for (x = 0; x < h[n].wi; ++x )
						{
							me = 0;	
							for (j = 0; j <= gd2; j++)
							{
								a = aa + j * MaxSY;  a *= 4;
								ea = &gdt[j * mdg];
								for (i = 0;	i <= gd2; i++, a += 4 )
								{
									e = ea[i];	ee = e*ob[a];
									if (ee > me )  me = ee;
								}
							}
							tGlow[w++] =  min( 255, me / 8192 );
							++aa;
						}
					}
				else
					/*additive glow*/
					for (y = 0;	y < Sy;	y++)
					{
						w = y * MaxTex + ab;
						aa = oy  - gd - gd*MaxSY;
						for (x = 0; x < h[n].wi; ++x )
						{
							l = 0;	su = 1;	
							for (j = 0; j <= gd2; j++)
							{
								a = aa + j * MaxSY;  a *= 4;
								ea = &gdt[j * mdg];
								for (i = 0; i <= gd2; i++, a += 4 )
								{
									e = ea[i];	l += e*ob[a];	su += e;
								}
							}
							tGlow[w++] = BYTE( min( 255,  gamul * min( gamax, l / su )  ) );
							++aa;
						}
					}

			/* {Alpha} */
			int mF = isFont ? amulF*1024 : 0;
			int mG = isGlow ? amulG*1024 : 0;
			if (isGlow)
			for (y = 0;	y < Sy;	++y )
			{	w = y * MaxTex + ab;	a = oy;
				for (x = 0;	x < h[n].wi; ++x )
				{
					int v = (mF * (tFont[w]+aofsF) + mG * (tGlow[w]+aofsG))/1024 + aofsC;
					//int v = (mF * tFont[w]) + mG * tGlow[w])/1024;
					tAlpha[w] = max(amin, min(amax, v));	++a;  ++w;
				}
			}else
			for (y = 0;	y < Sy;	++y )
			{	w = y * MaxTex + ab;	a = oy;
				for (x = 0;	x < h[n].wi; ++x )
				{
					int v = (mF * (tFont[w]+aofsF) )/1024 + aofsC;
					//int v = (mF * tFont[w] )/1024;
					tAlpha[w] = max(amin, min(amax, v));	++a;  ++w;
				}
			}

			/*width difference*/
			y = h[n].h[0] + h[n].h[1] + h[n].h[2];
			h[n].wi0 =  y > h[n].wi ? '+' : y < h[n].wi ? '-' : ' ';
		}
		/*[DrawChars]*/
		
		timeg = timeGetTime() - tst;		//time end
		pps = 100.f * float( sx - psx ) / float( sx );
	}

	/*TexFnt*/
	if (sTy != Ty)
	{
		RELEASE( TexFnt );
		format(s,S, "%d", Ty );
		Warng(
			D3DXCreateTexture( dev, Ty, Ty, 0, D3DUSAGE_DYNAMIC, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &TexFnt ) ,
			s, "Can't create texture" );
		}

	/*clear*/
	if (TexFnt)
	{
		Warng(
			TexFnt->LockRect( 0, &lrect, 0, 0 ) ,
			"lock TexFnt", "MakeFont" );
		
		UINT aa;
		UINT* o_ = (UINT*) lrect.pBits;
		UINT yO = lrect.Pitch >> 2;
		
		for (UINT y = 0; y < Ty; ++y)
		{
			aa = y*yO;
			for (UINT x = 0; x < Ty; ++x,++aa)
				o_[aa] = 0;
		}

		TexFnt->UnlockRect( 0 );
	}
	return true;
}
