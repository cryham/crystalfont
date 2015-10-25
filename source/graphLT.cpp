#include "header.h"
#include "graphLT.h"

/* .	.	 .																		. ..	graphLT	.. .																		.	 .	. */

void CFgraphLT::graphLT()
{
	int a;	

	switch( edL[edT] )
	{
		//  Lists  //	//  Lists  //	//  Lists  //	//  Lists  //
		///----------------------------------------------------------------------------------------------------------

		/* .clr List */ 
		case 0:
			anim( ah, 1 );
			Clear( xt, 0, xe, ( chLY + 2 ) * Fy,  ah * bckL[0].t );
			for (y = 0;	y < cLY;	y++)
			{
				w = pgClrL + y;
				if (w < nClrL )
				{
					a = y*( ICOsize + 1 );
					/*q*/if (y == yClrL )
					{
						Fclr = ah * bckL[0].f[1];
						Clear( xt + 5, a + 1, xe - 5, a + Fy - 1,  ah*bckL[0].q );
						scpy(s, "[" );  Write( xt + 2, a - 1 );
						scpy(s, "]" );  Write( xe - 9, a - 1 );
					}
					else
						Fclr = ah * bckL[0].f[0];
					/*na*/
					scpy(s, cle[w].na );
					/*dir*/
					if (cle[w].d )
						WriteL( xt + 10, a );
					else
					{
						Write( xt + 40, a );
						/*icon*/
						Fspr->Draw( cle[w].ico, 0, 0, &D3DXVECTOR3( xt + 12, a, 0 ), ah*ah*CLR( 1, 1, 1, 1 ) );
					}
				}
			}
			/*st*/
			Fclr = ah * bckL[0].s;
			format(s,S, "all: %d", nClrL );	Write( xt, chLY*Fy + Fy*2/3 );
			/*st%*/
			Fclr = ah * bckL[0].p;
			format(s,S, "%5.1f%%", 100.f * float( pgClrL + yClrL + 1 ) / float( nClrL ) );
			Write( xt + 100, chLY*Fy + Fy*2/3 );

			/*char/G*/
			Fclr = ah * 0.95f * CLR( 0.9f, ( curChan >= CH2 ) ? 0.75f : 1.f, 1,  1 );
			format(s,S, "%s", curChan < CH2?"Font":"Glow" );
			WriteL( xt, ( chLY - 1 )*Fy );

			break;

		/* .fnt List */
		case 1:
			anim( ah, 1 );
			Clear( xt, 0, xe, ( chLY + 2 )*Fy,  ah*bckL[1].t );
			for (y = 0;	y < cLY;	y++)
			{
				w = pgFntL + y;
				if (w < nFntL )
				{
					a = y * ( ICOsize + 1 );	
					/*q*/
					if (y == yFntL )
					{
						Fclr = ah * bckL[1].f[1];
						Clear( xt + 5, a + 1, xe - 5, a + Fy - 1,  ah*bckL[1].q );
						scpy(s, "(" );  Write( xt + 2, a - 1 );
						scpy(s, ")" );  Write( xe - 9, a - 1 );
					}
					else
						Fclr = ah * bckL[1].f[0];
					/*na*/
					scpy(s, fL[w].na );
					/*dir*/
					if (fL[w].d )
						WriteL( xt + 20, a );
					else
						Write( xt + 20, a );
				}
			}
			/*st*/
			Fclr = ah * bckL[1].s;
			format(s,S, "all: %d", nFntL );  Write( xt, chLY*Fy + Fy*2/3 );	
			/*st%*/
			Fclr = ah * bckL[1].p;
			format(s,S, "%5.1f%%", 100.f * float( pgFntL + yFntL + 1 ) / float( nFntL ) );
			Write( xt + 100, chLY*Fy + Fy*2/3 );
			
			break;
	
		 /* Chars List */
		 case 2:
			anim( ah, 1 );
			Clear( xt, 0, xe, ( chLY + 2 )*Fy,  ah*bckL[2].t );

		 	switch( ChPage )
		 	{
				/*summary info*/
				case 6:  y = 2*Ly;
					Fclr = ah * CLR( 0.35f, 0.75f, 0.65f, 1 );
					scpy(s, "summary" );	Write( xt + 5, Ly/2 );
					Fclr = ah * bckL[2].s;
					if (!bRect )
					{
						format(s,S, "chars: %d", zi );   Write( xt + 5, y );  y += Ly;
						format(s,S, "height: %d", Sy );  Write( xt + 5, y );  y += Ly;
						format(s,S, "lines: %d", lin );  Write( xt + 5, y );  y += Ly*4/3;

						Fclr = ah * CLR( 0.35f, 0.6f, 0.7f, 1 );
						scpy(s, "width:" );	Write( xt + 5, y );  y += Ly;

						Fclr = ah * bckL[2].s;
						format(s,S, "avg: %4.1f", float( sx ) / float( zi ) );
						Write( xt + 9, y );  y += Ly;
						format(s,S, "max: %d	%c", ss, h[ssn].s );
						Write( xt + 5, y );	 y += Ly;

						Fclr = ah * CLR( 0.2f, 0.8f, 0.85f, 1 );
						format(s,S, "sum: %d", psx );	Write( xt + 5, y );  y += Ly;
						format(s,S, "%%ea: %3.1f", pps );	Write( xt + 5, y );  y += Ly*4/3;	

						Fclr = ah * CLR( 0.35f, 0.6f, 0.7f, 1 );
						format(s,S, "ratio y/x:" );	Write( xt + 5, y );  y += Ly;

						Fclr = ah * bckL[2].s;
						format(s,S, "avg: %5.3f", float( Sy ) / float( sx ) * float( zi ) );
						Write( xt + 9, y );  y += Ly;	
						format(s,S, "min: %5.3f", float( Sy ) / float( ss ) );
						Write( xt + 5, y );  y += Ly*3/2;
					}
					break;

				/*groups*/
				case 5:  x = 2*Ly;
					Fclr = ah * CLR( 0.45f, 0.95f, 0.8f, 1 );
					scpy(s, "groups" );	Write( xt + 5, Ly/2 );
					for (y = 1;	y <= MaxGroups;	y++)
					{	a = x + y*Fy;
						clrHead( ah, grcur, a );
						format(s,S, "%2d", y );  Write( xt + 5, a );
						if (grw[y])	{	format(s,S, "%2d", grw[y] );	Write( xt + 40, x + y*Fy );  }
						if (grwi[y]){	format(s,S, "%2d", grwi[y] );	Write( xt + 80, x + y*Fy );  }
					}
					wrListEnd( "gr  wi", "         wi+" );	break;
				
				/*ch  wi gr */
				case 4:
					for (y = 0;	y < chLY; y++) {	w = pgChrL + y;	 a = y*Ly;	if (w <= zi)
					{	clrHead( ah, yChrL, a );
						format(s,S, "%c", h[w].s );		WriteL( xt + 5, a );
						/*wi*/format(s,S, "%2d", h[w].wi );  Write( xt + 40, a );
						/*gr*/if (h[w].gr){	format(s,S, "%2d", h[w].gr );	Write( xt + 80, a );	}
					}	}
					wrListEnd( "ch  wi", "         gr" );	break;

				/*ch  xx yy */
				case 3:
					for (y = 0;	y < chLY; y++) {	w = pgChrL + y;	 a = y*Ly;	if (w <= zi)
					{	clrHead( ah, yChrL, a );
						format(s,S, "%c", h[w].s );		WriteL( xt + 5, a );
						/*x + */if (h[w].xx){	format(s,S, "%2d", h[w].xx );	Write( xt + 40, a );	}
						/*y + */if (h[w].yy){	format(s,S, "%2d", h[w].yy );	Write( xt + 80, a );	}
					}	}
					wrListEnd( "ch", "     x+  y+" );	break;
					
				/*ch  wi ss es*/
				case 2:
					for (y = 0;	y < chLY; y++) {	w = pgChrL + y;	 a = y*Ly;	if (w <= zi)
					{	clrHead( ah, yChrL, a );
						format(s,S, "%c", h[w].s );	WriteL( xt + 5, a );
						/*wi*/
						format(s,S, "%2d", h[w].wi );	Write( xt + 40, a );
						/*wi + */if (h[w].ss){	format(s,S, "%2d", h[w].ss );	Write( xt + 85, a );	}
						/*ps - */if (h[w].pp){	format(s,S, "*" );	Write( xt + 125, a );	}
					}	}
					wrListEnd( "ch  wi", "         wi+  ea" );	break;
					
				 /*ch  nn of ea-*/
				 case 1:
					for (y = 0;	y < chLY; y++) {	w = pgChrL + y;	 a = y*Ly;	if (w <= zi)
					{	clrHead( ah, yChrL, a );
						format(s,S, "%c", h[w].s );		WriteL( xt + 5, a );
						/*fileNum*/
						clrHead( ah, yChrL, a );
						if (h[w].ch)	format(s,S, "%3d*", h[w].ch );	else	format(s,S, "%3d", w + z1 );
						Write( xt + 30, a );
						/*of*/	if (h[w].of){	format(s,S, "%2d", h[w].of );	Write( xt + 80, a );	}
						/*psi*/	if (h[w].psi){	format(s,S, "%2d", h[w].psi );	Write( xt + 120, a );	}
					}	}
					wrListEnd( "    nn   of  ea-", "ch" );	break;
					
				 /*ch  a b c*/
				 case 0:
					for (y = 0;	y < chLY; y++) {	w = pgChrL + y;	 a = y*Ly;	if (w <= zi)
					{	clrHead( ah, yChrL, a );
						format(s,S, "%c", h[w].s );		WriteL( xt + 5, a );
						/*abc*/  for (x = 0; x < 3; x++)
						{	format(s,S, "%2d", h[w].h[x] );  Write( xt + 30 + x*35, a );	}
						/*wi0*/	s[0] = h[w].wi0;  s[1] = 0;  Write( xt + 140, a );
					}	}
					wrListEnd( "ch  a   b   c  <>", "" );	break;
					
			}	// ChPage
				
			/*subpg nr*/
			Fclr = ah * CLR( 0.f, 0.9f, 0.6f, 1 );
			format(s,S, "%d", ChPage );	Write( xe - 1*Fx-1, chLY*Fy - Fy*2/9 );
			
			break;
		 
		/* Fonts List */
		case 3:
			anim( ah, 1 );
			Clear( xt, 0, xe, ( chLY + 2 )*Fy,  ah*bckL[3].t );
			for (y = 0; y < chLY; y++)
				if (( w = pfn + y ) <= iFonts)
				{
					a = y*Fy;
					/*q*/
					Fclr = ah * bckL[3].f[y == yfn ? 1 : 0];
					if (y == yfn)
						Clear( xt, a, xe, a + Fy - 1,  ah*bckL[3].q );
					scpy(s, fontNames[w] );	Write( xt, a );
				}
			/*st*/
			Fclr = ah * bckL[3].s;
			format(s,S, "all: %d", iFonts );  Write( xt, chLY*Fy + Fy*2/3 );	
			/*st%*/
			Fclr = ah * bckL[3].p;
			format(s,S, "%5.1f%%", 100.f * float( pfn + yfn + 1 ) / float( iFonts + 1 ) );
			Write( xt + 100, chLY * Fy + Fy*2/3 );
			
			break;	

	}
	

	switch( edT )
	{
		//  Tables  //	//  Tables  //	//  Tables  //	//  Tables  //
		///----------------------------------------------------------------------------------------------------------
		
		/* Color Table */
		case 0:
			anim( ac, 0 );
			Clear( xp, yp, px, py,  ac*bckT[0].t );
			Fclr = ac * CLR( 0.9f, ( curChan >= CH2 ) ? 0.75f : 1.f, 1,  1 );
			
			/*chan*/
			format(s,S, "%d %c", curChan%CH2 + 1, ( curChan >= CH2 ) ? 'G' : ' ' );
			WriteL( xp, yp );
			f = &ct[curChan][0];
			w = min( nChanTypes, Flt2Int( f[12] ) );
			float of;	

			/*off*/
			if (Flt2Int( f[10] ) == 0 )
			{
				Fclr = ac * CLR( 0.f, 1.f, 1.f,  1 );
				format(s,S, "Off" );	Write( xp + 117, yp );
				of = 0.7f;
			}
			/*typ*/
			else
			{
				Fclr = ac * CLR( 0, 1, 1,  1 );
				format(s,S, "%d %s", w, sChanTypes[w] );
				Write( xp + 100, yp );
				of = 1.f;
			}

			/*elem*/
			for (y = 0;	y < clrY; y++)
				for (x = 0;	x < clrX; x++)
				{
					cte = ctE[y][x];
					format(s,S,cte.s, f[cte.f] );	
					/*q*/
					if (clrx == x && clry == y )
					{
						Fclr = ac * ( of - 0.05f ) * bckT[0].f[0].r * ctp[w][y][x];
						Clear( xp + cte.x - Fx, yp + cte.y,  xp + cte.x + 7*Fx, yp + cte.y + Fy - 1,
							CLR( Fclr.r * 0.2f, Fclr.g * 0.2f, Fclr.b * 0.4f, 1 ) /*ac*dt_[0]*/ );
					}
					else
						Fclr = ac * of * bckT[0].f[1].r * ctp[w][y][x];
					Write( xp + cte.x, yp + cte.y );
				}
			break;

		/* Font Table */
		case 1:
			if (bRect )
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[ntabT].t );

				Fclr = ac * bckT[ntabT].f[0];	//RecT
				w = 80;
				Clear(  xp + 10 + editx*w, yp + ( edity + 2 )*Fy,
						xp + editx*w + 62, yp + ( edity + 3 )*Fy,  ac*bckT[ntabT].q );

				scpy(s, "Rect" );	 Write( xp + 5, yp + 5 );
				Fclr = ac * bckT[ntabT].f[1];
				/*x, y*/
				format(s,S, "x:%4d", rect_sx );  Write( xp + 10, yp + 2*Fy );
				format(s,S, "y:%4d", rect_sy );  Write( xp + 10, yp + 3*Fy );
			}
			else
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[1].t );	Fclr = ac * bckT[1].f[0];
				x = xp + 10;
				w = 80;
				Clear( x + fontx*w - 10, yp + ( fonty + 2 )*Fy, x + fontx*w + 62, yp + ( fonty + 3 )*Fy,  ac*bckT[1].q );
				/*fontName*/
				scpy(s, fontName );  Write( x + 60, yp + 5 );
				/*sy*/
				format(s,S, "%2d", sy );	WriteL( x + 5, yp + 5 );

				Fclr = ac * bckT[1].f[1];
				/*fix*/
				format(s,S, "%s", fix == 0?"var":"fix" );	Write( x, yp + 3*Fy );
				/*z1*/
				format(s,S, "z1:%3d", z1 );		Write( x + w, yp + 2*Fy );
				format(s,S, "z2: %3d", z2 );	Write( x + w*2, yp + 2*Fy );
				/*Ea*/
				format(s,S, "Ea: %d", Ea );		Write( x + w, yp + 3*Fy );
				/*ql*/
				char qla[5][6] = {"non", "aa", "pro", "ct", "ctn"};
				format(s,S, "qlt: %s", qla[ql] );	Write( x + 2*w, yp + 3*Fy );
				/*bold*/
				format(s,S, "bold:%d", fbold );	 Write( x, yp + 2*Fy );
				/*z2*/
				format(s,S, "%c %c", z1, z2 );	 WriteL( x + 3*w, yp + 2*Fy );
				
				Fclr = ac * CLR( 0.65f, 0.95f, 0.65f,  1 );
				/*[ + ]*/
				format(s,S, "ax:%3d", ax );	 Write( x,     yp + 4*Fy );
				format(s,S, "bx:%3d", bx );	 Write( x + w, yp + 4*Fy );
				format(s,S, "ay:%3d", ay );	 Write( x,     yp + 5*Fy );
				format(s,S, "by:%3d", by );	 Write( x + w, yp + 5*Fy );	
				/*Txy*/
				Fclr = ac * CLR( 0.7f, 0.9f, 0.7f,  1 );
				format(s,S, "xy: %s", Txy?" Pic":"Tex" );	Write( x + 2*w, yp + 4*Fy );
				/*oneLine*/
				Fclr = ac * CLR( 0.7f, 0.9f, 0.6f,  1 );
				format(s,S, "line: %s", oneLine?"1":"*" );	Write( x + 2*w, yp + 5*Fy );
			}
			break;

		/* Glow Table */
		case 2:
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[2].t );

				Fclr = ac * bckT[2].f[0];
				GTE qg = gte[glowy][glowx];
				Clear(  xp + qg.x, yp + qg.y*Fy + qg.yy,
						xp + qg.w, yp + ( qg.y + 1 )*Fy + qg.yy,  ac*bckT[2].q );
				/*glow Dist*/
				format(s,S, "D:%2d", gd );	WriteL( xp + 10, yp + 5 );
				
				if (addGlow )
					scpy(s, "add " );
				else
					scpy(s, "dist" );
				Write( xp + 210, yp + 5 );
				
				if (!addGlow )
				{
					//dist
					format(s,S, "mul: %5.2f", gmul1 );		Write( xp + 10,  yp + 2*Fy );
					format(s,S, "pow: %5.2f", gpow );		Write( xp + 160, yp + 2*Fy );
					format(s,S, "mul: %5.2f", gmul2 );		Write( xp + 10,  yp + 3*Fy );
					format(s,S, "dis: %5.2f", gpowm );		Write( xp + 171, yp + 3*Fy );

					format(s,S, "  *: %5.2f", gmulall );	Write( xp + 10,  yp + 4*Fy );
					format(s,S, "  -: %4d", gsub );			Write( xp + 167, yp + 4*Fy );

					/*  ( 0, 0 )  ( 0, d )  ( d, d )  */
					Fclr = ac * CLR( 0.7f, 0.5f, 0.7f, 1 );	
					format(s,S, "%4d %4d %4d",
						gdt[gd*mdg + gd], gdt[gd*mdg + gd2], gdt[gd2*mdg + gd2] );
					Write( xp + 10, yp + 5*Fy + Fy/2 );	
				}
				else
				{
					//add
					format(s,S, "mul: %5.2f", gamul );	Write( xp + 10, yp + 2*Fy );
					format(s,S, "max: %3d",	gamax );	Write( xp + 160, yp + 2*Fy );
				}
			}
			break;	
			
		/* Alpha Table */
		case 3:
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[3].t );

				Fclr = ac * bckT[3].f[0];
				w = 90;
				x = xp + 30 + alphx*w;
				Clear( x - 25, yp + (alphy + 1)*Fy, x + 60, yp + (alphy + 2)*Fy,  ac*bckT[3].q );

				x = xp + 10;
				Fclr = ac * CLR( 0.9f, 1.0f, 1.0f, 1 );	
				format(s,S, "bck: %1d", bckA);		Write( x + w*2, yp + 1*Fy );
				Fclr = ac * CLR( 0.8f, 0.9f, 0.96f, 1 );
				format(s,S, "min %3d", amin);		Write( x    , yp + 1*Fy );
				format(s,S, "max %3d", amax);		Write( x + w, yp + 1*Fy );
				format(s,S, "mulF %4.2f", amulF);	Write( x    , yp + 2*Fy );
				format(s,S, "mulG %4.2f", amulG);	Write( x + w, yp + 2*Fy );
				Fclr = ac * CLR( 0.6f, 0.65f, 0.7f, 1 );	
				format(s,S, "ofsF%4d", aofsF);		Write( x      , yp + 3*Fy );
				format(s,S, "ofsG%4d", aofsG);		Write( x + w  , yp + 3*Fy );
				format(s,S, "ofsC%4d", aofsC);		Write( x + w*2, yp + 3*Fy );
				Fclr = ac * CLR( 0.5f, 0.7f, 0.9f, 1 );	
				format(s,S, "r %3d", bAc[0] ); 		Write( x      , yp + 4*Fy );
				format(s,S, "g %3d", bAc[1] );	 	Write( x + w  , yp + 4*Fy );
				format(s,S, "b %3d", bAc[2] );	 	Write( x + w*2, yp + 4*Fy );
				format(s,S, "R %3d", bAd[0] );	 	Write( x      , yp + 5*Fy );
				format(s,S, "G %3d", bAd[1] );	 	Write( x + w  , yp + 5*Fy );
				format(s,S, "B %3d", bAd[2] );		Write( x + w*2, yp + 5*Fy );
			}
			break;	
			
		/* Save	Table */
		case 4:
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[4].t );
				Fclr = ac * bckT[4].f[1];
				float c0 = ( cfp > 0 ) ? 1.f : 0.8f;

				x = xp + 10;
				scpy(s, "Number:" );	Write( x, yp + 1*Fy );
				scpy(s, "Format:" );	Write( x, yp + 2*Fy );	
				x = xp + 170;
				scpy(s, "Chars:" );	Write( x, yp + 1*Fy );

				Fclr = ac * bckT[4].f[1]*c0;
				scpy(s, "Data:" );   Write( x, yp + 2*Fy );
				scpy(s, "Type:" );   Write( x, yp + 3*Fy );	
				Fclr = ac * bckT[4].f[0];
				x = xp + 90 + savex*140;

				Clear( x - 5, yp + ( savey + 1 )*Fy, x + ( savex == 0 ? 60 : 80 ), yp + ( savey + 2 )*Fy,  ac*bckT[4].q );

				x = xp + 90;
				format(s,S, "%03d", fileNum );	 Write( x, yp + 1*Fy );
				format(s,S, "%s", fmtExt[fmt] );  Write( x, yp + 2*Fy );
				x = xp + 230;
				scpy(s, Cfp[cfp] );	Write( x, yp + 1*Fy );

				Fclr = ac * bckT[4].f[0] * c0;
				scpy(s, Cfd[cfd] );	Write( x, yp + 2*Fy );
				scpy(s, Cft[cft] );	Write( x, yp + 3*Fy );
			}
			break;	

		/* Edit Table */
		case 5:
			{
				anim( ac, 0 );
				Clear( xp, yp, px, py,  ac*bckT[5].t );
				Fclr = ac * bckT[5].f[0];
				/*x bndry*/
				Fxb = px - 10;
				/*es*/
				for (y = 0;	y <= EdY; y++)
				{
					scpy(s, es[y] );
					WriteX( xp + 20, yp + ( y + 1 )*Fy );
				}
				/*cl_*/
				Fclr = ac * CLR( 1.f,  0.7f + 0.3f*sin( eqt ),  1.f,  1 );
				eqt += Ti.dt*3.f;	if (eqt > PI ) eqt -= PI;
				/*len*/
				y = min( ex[ey],  strlen( es[ey] ) );
				/*len.x*/
				a = 0;
				for (x = 0; x < y; x++)
					a += Fwi[ BYTE( es[ey][x] ) - Fz1 ];
				/*q*/
				if (edIns )
					scpy(s, "|" );
				else
					scpy(s, "_" );
				WriteX( xp + 20 + a, yp + ( ey + 1 )*Fy );
			}
			break;	

	}
	

	switch( edTL )
	{
		// others //	// others //	// others //	// others //
		
		/*svLc*/
		case 2:
			nqt += Ti.dt;	if (nqt > 0.7f )  nqt -= 0.7f;
			Clear( xt, ( chLY - 3 )*Fy - Fy/2, xe, ( chLY - 1 )*Fy - Fy/4,  CLR( 0.13f, 0.3f, 0.3f,  1 ) );

			Fclr = CLR( 0.6f, 0.95f, 1,  1 );
			scpy(s, "Save as:" );
			Write( xt + 5, ( chLY - 3 )*Fy - Fy/2 );	

			Fclr = CLR( 1, 1, 1,  1 );
			scpy(s, nedit );
			if (nqt < 0.3f)  scat( s, "_" );
			Write( xt + 15, ( chLY - 2 )*Fy - Fy/2 );
			
			break;

		/*svFn*/
		case 3:
			nqt += Ti.dt;	if (nqt > 0.7f )  nqt -= 0.7f;
			Clear( xt, ( chLY - 3 )*Fy - Fy/2, xe, ( chLY - 1 )*Fy - Fy/4,  CLR( 0.1f, 0.35f, 0.24f,  1 ) );

			Fclr = CLR( 0.9f, 1, 0.9f,  1 );
			scpy(s, "Save as:" );
			Write( xt + 5, ( chLY - 3 )*Fy - Fy/2 );

			Fclr = CLR( 1, 1, 1.f,  1 );
			scpy(s, nfe );
			if (nqt < 0.3f)  scat( s, "_" );
			Write( xt + 15, ( chLY - 2 )*Fy - Fy/2 );
			
			break;
	}


}

// util
void CFgraphLT::wrListEnd( char* s1, char* s2 )
{
	Fclr = ah * CLR( 0.25f, 0.65f, 0.45f, 1 );
	scpy(s, s1 );
	Write( xt, chLY*Fy + Fy*2/3 );

	Fclr = ah * CLR( 0.5f, 1.f, 0.8f, 1 );
	scpy(s, s2 );
	Write( xt, chLY*Fy + Fy*2/3 );
}
