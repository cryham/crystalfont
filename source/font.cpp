#include "header.h"
#include "font.h"


/*::.. .. .	.	 .				.	. ..: Save :.. .	.				.	 .	. .. ..::*/
bool CFfont::SaveFont()
{
	char nf[S+1], na[S+1], nb[S+1], nc[S+1];
	
	// Get file name
	format(s,S, "%03d_", fileNum );	// s + num
	scpy( na, s );
	
	if (bRect )
	{
		scat( na, "Rect" );
		scpy( nf, na );
	} else {
		// s + fnt_name :len = 9
		scpy(s, fontName );	s[9] = 0;

		// replace space with _
		for (int i=0; i < 9; ++i)  if (s[i]==' ')  s[i]='_';
		scat( na, s );
				
		// s + size
		format(s,S, "_%2d", sy );
		scat( na, s );

		// full file name no ext
		//format(nf,S, "%03d_%s_%2d", fileNum, s, sy );
		scpy( nf, na );
		
		/*.cf > */
		sadd( nc,  pathSave, na );
		if (cfp == 2)
			scat( nc, ".fontdef" );
		else
			scat( nc, ".cf" );
	}
	// s + .ext
	scat( na, "." );	scat( na, fmtExt[fmt] );
	// path + s
	sadd( nb,  pathSave, na );
	saveTime = 2.f;

	/* progress bar */
	//
		/* Begin */
		dev->BeginScene();
		Clear( xp + 275, ye - Fy, xp + 370, ye,  RGB( 0, 20, 70 ) );

		FontBegin( 1 );
		RndSt( ALPHABLENDENABLE, TRUE );

		// write
		Fclr = CLR( 1.0f, 0.3f, 0.3f,  1 );
		scpy(s, "Saving....." );
		Write( xp + 280, ye - Fy );

		/* End */
		FontEnd();
		RndSt( ALPHABLENDENABLE, FALSE );
		dev->EndScene();	 dev->Present( 0, 0, 0, 0 );
	//

	// Save image
	if (Ux != Uy)
	{
		// diffrent dimensions
		scpy( saveInfo, "ERROR: " );
		scat( saveInfo, na );
		LPDIRECT3DSURFACE9 su;
		Warng( 
			dev->CreateOffscreenPlainSurface( Ux, Uy, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &su, 0 ) ,
			"", "save" );
		Warng(
			TexFnt->LockRect( 0, &lrect, 0, 0 ) ,
			"lock TexFnt", "save" );
			
		RECT rs = {0, 0, Ux, Uy};	
		D3DXLoadSurfaceFromMemory( su, 0, 0, lrect.pBits, D3DFMT_A8R8G8B8, lrect.Pitch, 0, &rs, D3DX_DEFAULT, 0 );
		
		if (D3DXSaveSurfaceToFileA( nb, fmtIFF[fmt], su, 0, 0 ) == D3D_OK)
		{
			scpy( saveInfo, "Saved: " );
			scat( saveInfo, na );
		}
		TexFnt->UnlockRect( 0 );
		RELEASE( su );
	}
	else
	{
		// equal dimensions
		if (D3DXSaveTextureToFileA( nb, fmtIFF[fmt], TexFnt, 0 ) == D3D_OK)
		{
			scpy( saveInfo, "Saved: " );
			scat( saveInfo, na );
		} else {
			scpy( saveInfo, "ERROR: " );
			scat( saveInfo, na );
		}
	}
	
	/* CFclr file */
	if (!bRect)
	switch (cfp)  // type
	{
		case 0:  // none
			break;

		case 1:  // .cf
		{
			ofstream f;	
			f.open( nc );
			if (f.fail())
			{
				scpy( saveInfo, "ERROR: chars file" );
				return false;
			}
			
			switch (cfd)  // detail
			{
				case 0:  // minimal
				{	f << "CrystalFont " << ver << "\n";
					f << Sy << "\n";
					f << z1 << " " << z2 << "\n";
					ForEachChar
						f << h[n].bx << " " << h[n].by << " " << h[n].wi << "\n";
				}	break;

				case 1:  // extended
				{	f << "CrystalFont " << ver << "\n";
					f << "chars_height = " << Sy << "\n";
					f << "chars_from = " << z1 << "\n";
					f << "chars_to = " << z2 << "\n";
					ForEachChar
						f << "x=" << h[n].bx << "\t y=" << h[n].by << "\t w=" << h[n].wi << "\n";
				}	break;

				case 2:  // abc
				{	f << "CrystalFont " << ver << "\n";
					f << "chars_height = " << Sy << "\n";
					f << "chars_from = " << z1 << "\n";
					f << "chars_to = " << z2 << "\n";
					ForEachChar
						f << "code=" << n+z1 << "\t x=" << h[n].bx << "\t y=" << h[n].by << "\t w=" << h[n].wi
						  << "\t a=" << h[n].h[0] << "\t b=" << h[n].h[1] << "\t c=" << h[n].h[2] << "\n";
				}	break;

				case 3:  // full
				{	f << "CrystalFont " << ver << "\n";
					f << "chars_from = " << z1 << "\n";
					f << "chars_to = " << z2 << "\n";
					ForEachChar
						f << "code=" << n+z1 << "\t posx=" << h[n].bx << "\t posy=" << h[n].by
						  << "\t width=" << h[n].wi << "\t height=" << Sy
						  << "\t a=" << h[n].h[0] << "\t b=" << h[n].h[1] << "\t c=" << h[n].h[2]
						  << "\t grp=" << int(h[n].gr) << "\n";
				}	break;
			}
			f.close();
		}	break;
			
		case 2:  // ogre
		{
			ofstream f;	
			f.open( nc );
			if (f.fail())
			{
				scpy( saveInfo, "ERROR: chars file" );
				return false;
			}
			
			f << nf << "\n";  // name same as img
			f << "{" << "\n";
			f << "	type	image" << "\n";
			f << "	source	" << nf << "." << fmtExt[fmt] << "\n\n";  // img file
			float fSy = Sy, fUx = Ux, fUy = Uy;
			ForEachChar
			{
				//format(s,S, "glyph %c %9.7f %9.7f %9.7f %9.7f",
				format(s,S, "glyph %c %f %f %f %f",
					(char)h[n].s,
					(float)(h[n].bx) / fUx,
					(float)(h[n].by) / fUy,
					(float)(h[n].bx + h[n].wi) / fUx,
					(float)(h[n].by + fSy) / fUy );
				f << "\t" << s << "\n";  // "glyph " << << x=" << h[n].bx << "\t y=" << h[n].by << "\t w=" << h[n].wi << "\n";
			}
			f << "}";

			f.close();
		}  break;
	}
	fileNum++;
	
	return true;
}


/*.	 .	 .	 .	 .	 .	 .	 .	 .	 .	 .	 .	 .	Colorize .	 .	 .	 .	 .	 .	 .	 .	 .	 .	 .	 .	.*/
bool CFfont::Colorize()
{
	if (!isFont && !isGlow)
		return true;		//fast +
	
	UINT k, kk, l, al;
	int  mi = 0;
	int  a, xx,  rr, gg, bb;
	BYTE *c, *o;
	UINT *o_, yO;
	
	if (!TexFnt)  return false;
	Warng(
		TexFnt->LockRect( 0, &lrect, 0, 0 ) ,
		"lock TexFnt", "Colorize" );
	o_ = (UINT*) lrect.pBits;
	yO = lrect.Pitch >> 2;

	if (bRect)
	{
		for (y = 0;	y < Uy;	y++)
		{
			a = y * yO;
			b = y * MaxSY * 3;	
			for (x = 0;	x < Ux;	x++)
			{
				c = &tClrF[b];
				o_[a] = RGB( c[2], c[1], c[0] ) + 0xFF000000;
				b += 3;
				++a;
			}
		}
	}
	else
	switch( isFont )
	{
		case 1:
			switch( isGlow )
			{
				/* FG */
				case 1:
					ForEachChar
					for (y = 0; y < Sy; ++y )
					{
						a = w = y + h[n].by;
						a *= yO;		w *= MaxTex;
						w += h[n].bx;	a += h[n].bx;
						xx = h[n].wi;	mi = ( ss - xx ) / 2;
						b = ( y * MaxSY + mi ) * 3;
						for (x = 0;	x < xx;	++x )
						{
							k = tFont[w];	kk = 255 - k;
							l = tGlow[w];
							al = tAlpha[w] * 0x01000000;

							c = &tClrF[b];
							o = &tClrG[b];	
							
							bb = c[2] * k >> 8;  bb += o[2] * kk * l >> 16;
							gg = c[1] * k >> 8;  gg += o[1] * kk * l >> 16;
							rr = c[0] * k >> 8;  rr += o[0] * kk * l >> 16;
							
							o_[a] = RGB( bb, gg, rr ) + al;
							b += 3;  ++a;  ++w;
						}
					}
					break;

				/* F_ */
				case 0:
					ForEachChar
					for (y = 0; y < Sy; ++y )
					{
						a = w = y + h[n].by;
						a *= yO;		w *= MaxTex;
						w += h[n].bx;	a += h[n].bx;
						xx = h[n].wi;	mi = ( ss - xx ) / 2;
						b = ( y * MaxSY + mi ) * 3;
						for (x = 0;	x < xx;	++x )
						{
							k = tFont[w];
							al = tAlpha[w] * 0x01000000;
							c = &tClrF[b];

							bb =  c[2] * k >> 8;
							gg =  c[1] * k >> 8;
							rr =  c[0] * k >> 8;
							
							o_[a] = RGB( bb, gg, rr ) + al;
							b += 3;  ++a;  ++w;
						}
					}
					break;
			}
			break;	

		case 0:
			switch( isGlow )
			{
				/* _G */
				case 1:
					ForEachChar
					for (y = 0; y < Sy; ++y )
					{
						a = w = y + h[n].by;
						a *= yO;		w *= MaxTex;
						w += h[n].bx;	a += h[n].bx;
						xx = h[n].wi;	mi = ( ss - xx ) / 2;
						b = ( y * MaxSY + mi ) * 3;
						for (x = 0;	x < xx;	++x )
						{
							kk = 255 - tFont[w];
							l = tGlow[w];
							al = tAlpha[w] * 0x01000000;
							c = &tClrG[b];

							bb =  c[2] * kk * l >> 16;
							gg =  c[1] * kk * l >> 16;
							rr =  c[0] * kk * l >> 16;
							
							o_[a] = RGB( bb, gg, rr ) + al;
							b += 3;  ++a;  ++w;
						}
					}
					break;

				/* __ */
				case 0:
					break;
			}
	}

	TexFnt->UnlockRect( 0 );
	return true;
}


//\\   program Options   \\//
//--------------------------------------------------------------------------------------------------
void CFfont::optLoad()
{
	ifstream f;
	f.open( setFile );

	if (!f.fail() )
	{
		int i = 0, j;

		//default options
		edTL = 1;	edT = 3;
		edL[0] = 0;	edL[1] = 2;
		edL[2] = 2;	edL[3] = 1;
		edL[4] = 3;
		ChPage = 4;  HelpPage = 0;  showChar = 1;

		#define gNewLine		f.getline( co[i++], CommLen );	
		#define fin( n, a, b )	f.getline( s,9, ' ');	\
								gNewLine;	\
								n = range( a, b, atoi( s ) );
		
		gNewLine;
			fin( fileNum, 0, 999 );
			fin( fmt, 0, nFormats );

			fin( cfp, 0, CFp );
			fin( cfd, 0, CFd );
		gNewLine;
			fin( edTL, 0, 1 );
			fin( edT, 0, ntabT - 1 );

			fin( ChPage, 0, ChSubPgs );
			fin( HelpPage, 0, HelpPages );
			fin( showChar, 0, 1 );
		gNewLine;
			fin( Txy, 0, 1 );
			fin( oneLine, 0, 1 );
			fin( bRect, 0, 1 );  bRect = 0;//!
			fin( rect_sx, 8, MaxSY );
			fin( rect_sy, 8, MaxSY );
		
		gNewLine;
			fin( bckA, 0, 4 );
			fin(bAc[0],0,255);  fin(bAc[1],0,255);  fin(bAc[2],0,255);
			fin(bAd[0],0,255);  fin(bAd[1],0,255);  fin(bAd[2],0,255);

		gNewLine;
			for (j = 0; j < ntabT; j++)
			{	fin( edL[j], 0, ntabL - 1 );	}

		f.close();
	}
}

void CFfont::optSave()
{
	ofstream f;
	f.open( setFile );
	
	if (!f.fail() )
	{
		int i = 0, j;
		#define fNewLine	f << co[i++] << "\n";
		#define fout( a )	f <<  a << ' ' << co[i++] << "\n";

		fNewLine;
			fout( fileNum );
			fout( fmt );
			
			fout( cfp );
			fout( cfd );
		fNewLine;
			fout( edTL );
			fout( edT );

			fout( ChPage );
			fout( HelpPage );
			fout( showChar );
		fNewLine;
			fout( Txy );
			fout( oneLine );
			fout( bRect );
			fout( rect_sx );
			fout( rect_sy );

		fNewLine;
			fout( bckA );
			fout(bAc[0]);  fout(bAc[1]);  fout(bAc[2]);
			fout(bAd[0]);  fout(bAd[1]);  fout(bAd[2]);

		fNewLine;
			for (j = 0; j < ntabT; j++)
			{	fout( edL[j] );		}
				
		f.close();
	}
}


CFfont::CFfont() :
	isHelp(0/**/), HelpPage(0), updHelp(0),
	str(0), Txy(0), oneLine(0),
	rect_sx(128), rect_sy(128),
	
	dc(0), hb(0), hf(0),
	lin(1), psx(0), pps(0.f), ssn(0),

	clearAll(2), upRct(1), upChr(1),
	ar(0.f),  ah(0.f), ac(0.f),  at(0.f), nqt(0.5f),

	texFilR(1), texFilH(0), atexFilR(1.f), atexFilH(1.f),

	fileNum(0), fmt(0), cfp(0), cfd(0),
	saveTime(2.f),

	ey(0), edIns(0), eqt(0.f),
	yfn(0), pfn(0),
	yFntL(0), pgFntL(0), nFntL(0),  nfx(0)

	//FLE fL[MaxList];
{
	ZeroMemory( &saveInfo[0], sizeof(saveInfo));
	ZeroMemory( &co[0], sizeof(co));

	ZeroMemory( &es[0][0], sizeof(es));
	for (int i=0;i < EdY+1; ++i)  ex[i] = 0;

	ZeroMemory( &nfe[0], sizeof(nfe));
	ZeroMemory( &phf[0], sizeof(phf));
}


bool CFfont::settings()
{
	str = bRect = oneLine = false;	/*main*/
	
	// first values
	clearAll = 2;
	texFilR = 1;  texFilH = 0;
	upRct = 1;    upChr = 1;
	isHelp = 0;   updHelp = 0;
	optLoad();
	oneLine = false;

	CFclr::settings();

	/*fontNames*/
	scpy( phf, pathFnt0 );
	fntList();

	return true;
}

							// .fnt routines
//--------------------------------------------------------------------------------------------------
bool CFfont::fntSave()
{
	sadd(s, phf, nfe );
	scat( s, ".fnt" );
	int i, c;
	
	ofstream f;
	f.open( s );
	if (f.fail() )
		return false;					 // save
		
	f << "CrystalFont " << ver << "\n";	
	/*main*/
	f << bRect << " " << str << "	bRect, str\n";
	f <<  Txy << " " <<  oneLine << "	Txy, oneLine\n";
	f <<  rect_sx << " " <<  rect_sy << "	r.xy\n";

	f <<  "	Font\n" <<  fontName << "\n";
	f <<  sy << " sy\n";
	f <<  fbold << " " << fix << "	bold, fix\n";
	f <<  Ea << " " << ql << "	Ea, ql\n";
	f <<  z1 << " " <<  z2 << " " <<  zi << "	z1, z2, zi\n";
	f <<  ax << " " <<  bx << " " <<  ay << " " <<  by << "	ax, bx, ay, by\n";

	f <<  "	Glow\n" <<  gd << "	gd\n";
	f <<  isGlow << " " << isFont << " " <<  addGlow << "	isGlow, isFont, addGlow\n";
	f <<  gmul1 << " " << gmul2 << " " << gmulall << "	gmul1, gmul2, gmulall\n";
	f <<  gpow << " " << gpowm << " " << gsub << "	gpow, gpowm, gsub\n";	
	f << gamul << " " << gamax << "	gamul, gamax\n";	

	f <<  "	[Alpha]\n";
	f <<  amin << " " << amax << "	amin,amax" << "\n";
	f <<  amulF << " " << amulG << "	amulF,G" << "\n";
	f <<  aofsF << " " << aofsF << " " << aofsC << "	aofsF,G,C" << "\n";

	f <<  "	[Groups]\n";
	f <<  "	grw, grwi\n";
	for (i = 1;	i <= MaxGroups;	i++)
		f <<  grw[i] << " " << grwi[i] << "	#" << i << "\n";

	f <<  "	[Chars]\n";
	f <<  "	ch, gr,  ss, pp,  xx, yy\n";
	for (i = 0; i < 256; i++)
	{
		f <<  int( h[i].ch ) << " " << int( h[i].gr ) << "	";
		f <<  h[i].ss << " " << h[i].pp << "	" << h[i].xx << " " << h[i].yy;
		f <<  "	#" << i << "\n";
	}

	f <<  "	[clrFont]\n";
	for (c = 0;	c < CH2; c++)
	{
		for (i = 0;	i < 32;	i++)
			if (i != 12 )
				f <<  ct[c][i] << " ";
			else
				f <<  Flt2Int( ct[c][i] ) << " ";
			f << "\n";
	}

	f <<  "	[clrGlow]\n";
	for (c = CH2; c < CH; c++)
	{
		for (i = 0;	i < 32;	i++)
			if (i != 12 )
				f <<  ct[c][i] << " ";
			else
				f <<  Flt2Int( ct[c][i] ) << " ";
			f << "\n";
	}

	f <<  "	Edit - str\n";
	for (c = 0; c <= EdY; c++)
		f << es[c] << "\n";

	f.close();

	return true;
}


//--------------------------------------------------------------------------------------------------
bool CFfont::fntLoad( char*na )
{
	sadd(s, phf, na);  scat(s, ".fnt");
	int i, x, c;

	ifstream f;
	f.open( s );
	if (f.fail())
		return false;					 // load
		
	/*cf*/
	f.getline( s, 50 );
	int vm = 0, vb = 0;
	int res = sscanf_s(s, "CrystalFont %d.%d", &vm, &vb);

	/*main*/
	f >>  bRect >> str;   f.getline( s, 50 );
	f >>  Txy >> oneLine;	f.getline( s, 50 );
	f >>  rect_sx >> rect_sy;   f.getline( s, 50 );

	/*font*/
	f.getline( s, 50 );
	f.getline( fontName, 80 );
	f >>  sy;	f.getline( s, 50 );
	f >>  fbold >> fix;	f.getline( s, 50 );

	//f >>  Ea;	f.getline( s, 50 );
	Ea=0; ql=1;  f.getline( s, 50 );
	res = sscanf_s(s, "%d %d", &Ea, &ql);

	f >>  z1 >> z2 >> zi;	f.getline( s, 50 );
	f >>  ax >> bx >> ay >> by;  f.getline( s, 50 );

	/*glow*/
	f.getline( s, 50 );
	f >>  gd;	f.getline( s, 50 );
	f >>  isGlow >> isFont >> addGlow;	f.getline( s, 50 );
	f >>  gmul1 >> gmul2 >> gmulall;	f.getline( s, 50 );
	f >>  gpow >> gpowm >> gsub;	f.getline( s, 50 );
	f >>  gamul >> gamax;	f.getline( s, 50 );

	/*[Alpha]*/
	amin=0;  amax=255;
	amulF=1.f;  amulG=1.f;
	aofsF=0;  aofsG=0;  aofsC=0;
	if (vb >= 45)
	{
		f.getline( s, 50 );
		f >>  amin >> amax;		f.getline( s, 50 );
		f >>  amulF >> amulG;	f.getline( s, 50 );
		f >>  aofsF >> aofsF >> aofsC;	f.getline( s, 50 );
	}
	
	/*[Groups]*/
	f.getline( s, 50 );
	f.getline( s, 50 );
	for (i = 1;	i <= MaxGroups;	i++)
	{
		f >>  grw[i] >> grwi[i];
		f.getline( s, 50 );
	}

	/*[Chars]*/
	f.getline( s, 50 );
	f.getline( s, 50 );
	for (i = 0;	i < 256; i++)
	{	// - 
		f >>  c >> x;
		h[i].ch = c;
		h[i].gr = x;
		//f >>  h[i].ch >> h[i].gr;	
		f >>  h[i].ss >> h[i].pp >> h[i].xx >> h[i].yy;
		f.getline( s, 50 );
	}

	/*[clrFont*/
	f.getline( s, 50 );
	for (c = 0;	c < CH2; c++)
	{
		for (i = 0;	i < 32;	i++)
			if (i != 12 )
				f >>  ct[c][i];
			else
			{
				f >> x;
				ct[c][i] = Int2Flt( x );
			}
	}

	/*clrGlow*/
	f.getline( s, 50 );
	f.getline( s, 50 );
	for (c = CH2; c < CH; c++)
	{
		for (i = 0;	i < 32;	i++)
		if (i != 12 )
			f >>  ct[c][i];
		else
		{
			f >> x;
			ct[c][i] = Int2Flt( x );
		}
	}

	/*Edit - str*/
	f.getline( s, 50 );
	f.getline( s, 50 );

	for (c = 0; c <= EdY; c++)
		f.getline( es[c], EdX + 1 );

	f.close();

	return true;
}


bool CFfont::fntList()
{
	WIN32_FIND_DATAA fd;
	int dn = 1;
	ifstream fin;
	nFntL = 0;
	UINT w;//, x, y, a;
	//BYTE *c;		//updL

	sadd(s, phf, "*.*" );
	
	HANDLE hs = FindFirstFileA( s, &fd );
	if (hs == INVALID_HANDLE_VALUE )
		return false;

	while( dn )
	{
		if (nFntL < MaxList  &&  fd.cFileName[0] != '.' )
		{
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				/*file name*/
				scpy( fL[nFntL].na, fd.cFileName );
				fL[nFntL].d = 1;
				nFntL++;
			} else {
				/*file extension*/
				char*pe = strrchr( fd.cFileName, '.' );
				if (pe )
				{
					scpy(s, pe + 1 );
					if (_strnicmp( s, "fnt", 3 ) == 0 )
					{
						/*na*/
						pe[0] = 0;
						scpy( fL[nFntL].na, fd.cFileName );
						/*clr*/
						fin.read( ( char* ) &w, sizeof( int ) );
						/*ico*/
						fin.read( ( char* ) ico, sizeof( ico ) );
						fin.close();
						
						fL[nFntL].d = 0;
						nFntL++;
					}
				}
			}
		}

		if (!FindNextFileA( hs, &fd ) ) dn = 0;
	}

	FindClose( hs );	

	//dirs 1st	qsort...
	int i, j;
	FLE e;
	for (j = 0;	j < nFntL; j++)
		for (i = 0;	i < nFntL - j; i++)
			if (fL[i].d < fL[j].d )
			{
				e = fL[i];
				fL[i] = fL[j];
				fL[j] = e;
			}

	return true;
}

									// utility //
//--------------------------------------------------------------------------------------------------
void CFfont::UVadr( bool b )
{
	if (b)
	{
		dev->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER );	
		dev->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER );	
	} else {
		dev->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP );	
		dev->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP );
	}
}

bool CFfont::uTexFil( int n ){
	switch (n)
	{
		case 0:
			dev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_POINT );	
			dev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_POINT );	
			dev->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );	
			dev->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, 0 );	
			return true;	
		case 1:
			dev->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC );	
			dev->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC );	
			dev->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );	
			dev->SetSamplerState( 0, D3DSAMP_MAXANISOTROPY, 0 );	
			return true;
	}
	return false;
}


/* DC routines */
bool CFfont::CreateDC()
{
	dc = CreateCompatibleDC( 0 );

	BITMAPINFO bi;	ZeroMem( bi );
	BITMAPINFOHEADER *he = &bi.bmiHeader;
	he->biSize = sizeof( BITMAPINFOHEADER );

	he->biWidth = MaxSY;	he->biHeight = MaxSY;
	he->biBitCount = 32;	he->biSizeImage = MaxSY * MaxSY * 4;
	he->biPlanes = 1;		he->biCompression = BI_RGB;
	
	hb = CreateDIBSection( dc, &bi, DIB_RGB_COLORS, ( void** ) &oo, 0, 0 );

	SelectObject( dc, hb );
	SetTextColor( dc, RGB( 255, 255, 255 ) );
	SetBkColor( dc, RGB( 0, 0, 0 ) );

	/* new fnt tables */
	ob = (BYTE*)oo;

	tFont = new BYTE[ MaxTex * MaxTex ];
	if (!tFont)
		WrnMsg( "new Font Array", "Begin" )

	tGlow = new BYTE[ MaxTex * MaxTex ];
	if (!tGlow)
		WrnMsg( "new Glow Array", "Begin" )

	tAlpha = new BYTE[ MaxTex * MaxTex ];
	if (!tAlpha)
		WrnMsg( "new Alpha Array", "Begin" )

	/* new clr tables */
	int size = MaxSY * MaxSY * 3;
	tPrv = new BYTE[ size ];
	tChan = new BYTE[ size ];
	tClrF = new BYTE[ size ];
	tClrG = new BYTE[ size ];

	if (!tPrv || !tChan || !tClrF || !tClrG)
		WrnMsg( "new big arraytPrv tClrF tClrG tChan", "Begin" )

	// clear
	for (x = 0;	x < size; x++)
	{
		tPrv[x] = 0;
		tChan[x] = 0;
		tClrF[x] = 0;
		tClrG[x] = 0;
	}

	/*glw*/
	gdt = new int[mdg*mdg];
	if (!gdt )
		WrnMsg( "new gdt", "Begin" )

	for (x = 0;	x < mdg*mdg; x++)
		gdt[x] = 0;
	
	EnumFonts();
	
	return true;
}

void CFfont::DestroyDC()
{
	DELETEA( gdt );
	DELETEA( tPrv );
	DELETEA( tChan );
	DELETEA( tClrF );
	DELETEA( tClrG );
	DELETEA( tAlpha );
	DELETEA( tGlow );
	DELETEA( tFont );
	DeleteObject( hb );
	DeleteObject( hf );
	DeleteDC( dc );
}


// Enum System Fonts

char* CFfont::fontNames[MaxList];
int  CFfont::iFonts = 0;

bool CALLBACK EnumFunc( LPLOGFONTA f, LPNEWTEXTMETRICA tm, DWORD t, LPVOID )
{
	if (/* t & RASTER_FONTTYPE || */ t & TRUETYPE_FONTTYPE )
	{
		CFfont:: fontNames[ CFfont:: iFonts ] = new char[40];
		StringCbCopyA( &( CFfont:: fontNames[ CFfont:: iFonts++ ][0] ), 40, f->lfFaceName );
	}
	return true;
}

int cmpstr( const void* a, const void* b )
{
	return _stricmp( *( char** )a, *( char** )b );
}

void CFfont::EnumFonts()
{
	EnumFontFamiliesA( GetDC(hw), 0, (FONTENUMPROCA) EnumFunc, 0 );

	qsort( (void*) &fontNames[0], iFonts, sizeof(char*), cmpstr );

	iFonts--;
}
