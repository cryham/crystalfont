#include "header.h"
#include "d3dbasic.h"


// Draw Rect

struct QV
{
	D3DXVECTOR3 p;
	float u, v;
};

const DWORD Qvf = D3DFVF_XYZ|D3DFVF_TEX1;			


void D3Dbasic::drawRect(
	int i, int j,
	int sx, int sy,

	int xp, int yp,
	int xr, int yr,
	int YY, LPDIRECT3DTEXTURE9 tx )
{
	LPDIRECT3DVERTEXBUFFER9 vb;
	QV *q;
	
	dev->CreateVertexBuffer( 4*sizeof( QV ), 0, Qvf, D3DPOOL_DEFAULT, &vb, 0 );

	vb->Lock( 0, 0, ( void** )&q, 0 );

	float x = i * 2 / float( xe ) - 1,
		y = - j * 2 / float( ye ) + 1,
		xx = x + float( 2 * sx ) / float( xe ),
		yy = y - float( 2 * sy ) / float( ye ),
		FY = float( YY ),
		rect_sx = float( xp ) / FY,
		rect_sy = float( yp ) / FY,
		vx = rect_sx + float( xr ) / FY,
		vy = rect_sy + float( yr ) / FY;
	
	q[0].p = D3DXVECTOR3( x,  y , 0 );	q[0].u = rect_sx;  q[0].v = rect_sy;
	q[1].p = D3DXVECTOR3( xx, y , 0 );	q[1].u = vx;  q[1].v = rect_sy;
	q[2].p = D3DXVECTOR3( xx, yy, 0 );	q[2].u = vx;  q[2].v = vy;
	q[3].p = D3DXVECTOR3( x,  yy, 0 );	q[3].u = rect_sx;  q[3].v = vy;

	vb->Unlock();
	
	dev->SetFVF( Qvf );
	dev->SetStreamSource( 0, vb, 0, sizeof( QV ) );
	dev->SetTexture( 0, tx );

	dev->DrawPrimitive( D3DPT_TRIANGLEFAN, 0, 2 );
	vb->Release();
}

// Clear with color c
void D3Dbasic::Clear( int x1, int y1, int x2, int y2, CLR c )
{
	D3DRECT zR = {x1, y1, x2, y2};
	dev->Clear( 1, &zR, D3DCLEAR_TARGET, DWORD( c ), 1.f, 0 );
}


// font functions

void D3Dbasic::FontBegin( int a )
{
	Fspr->Begin( a != 0 ? D3DXSPRITE_ALPHABLEND : D3DXSPRITE_SORT_TEXTURE );
}

void D3Dbasic::FontEnd()
{
	Fspr->End();
}

void D3Dbasic::Write( int x, int y )
// font F
{
	int i = 0;
	int fc, z;
	D3DXVECTOR3 p = D3DXVECTOR3( x, y, 0 );
	
	while( ( fc = BYTE( s[i++] ) - Fz1 ) >= 0 )
		if (fc <= Fzi )
		{
			z = Fwi[fc];	
			RECT r = { Fbx[fc], Fby[fc], Fbx[fc] + z, Fby[fc] + Fy };
			Fspr->Draw( Ftex, &r, 0, &p,  Fclr );
			p.x += z;
		}
}

void D3Dbasic::WriteL( int x, int y )
// font L
{
	int i = 0;
	int fc, z;
	D3DXVECTOR3 p = D3DXVECTOR3( x, y, 0 );

	while( ( fc = BYTE( s[i++] ) - Lz1 ) >= 0 )
		if (fc <= Lzi )
		{
			z = Lwi[fc];
			RECT r = { Lbx[fc], Lby[fc], Lbx[fc] + z, Lby[fc] + Ly };
			Fspr->Draw( Ltex, &r, 0, &p,  Fclr );
			p.x += z;
		}
}

void D3Dbasic::WriteX( int x, int y )
// with x boundary
{
	int i = 0;
	int fc, z;
	D3DXVECTOR3 p = D3DXVECTOR3( x, y, 0 );

	while( ( fc = BYTE( s[i++] ) - Fz1 ) >= 0 )
		if (fc <= Fzi )
		{
			z = Fwi[fc];
			RECT r = {Fbx[fc], Fby[fc], Fbx[fc] + z, Fby[fc] + Fy};
			if (p.x + z > Fxb )
				break;
			Fspr->Draw( Ftex, &r, 0, &p,  Fclr );
			p.x += z;
		}
}


/*___ ==  = -- -  --	--		--			init			--		--	-- -- -  ==  = ___*/
bool D3Dbasic::Init( bool Real )
{
	if (!createWnd() )
		Msg0( "", "createWnd" );
	
	/*DWORD w;*/
	int i;
	ifstream f;	
	
	/* CFont - F*/
	f.open( FnameCf );
	if (f.fail() )
		Msg0( FnameCf, "can't open font file" );
	
	f.getline( s, 40 );
	if (strncmp( s, "CrystalFont", 11 ) != 0 )
		Msg0( FnameCf, "cf header wrong" );
	
	f >>  Fy >> Fz1 >> Fz2;		Fzi = Fz2 - Fz1;
	for (i = 0;	i <= Fzi; i++)
		f >>  Fbx[i] >> Fby[i] >> Fwi[i];
	Fx = Fwi[0];

	f.close();
	
	/* CFont - L*/
	f.open( LnameCf );
	if (f.fail() )
		Msg0( LnameCf, "can't open font file" );
	
	f.getline( s, 40 );
	if (strncmp( s, "CrystalFont", 11 ) != 0 )
		Msg0( LnameCf, "cf header wrong" );

	f >>  Ly >> Lz1 >> Lz2;		Lzi = Lz2 - Lz1;
	for (i = 0;	i <= Lzi; i++)
		f >>  Lbx[i] >> Lby[i] >> Lwi[i];
	Lx = Fwi[0];
	
	f.close();


	/*  D3D init  */
	
	Error(
		d3d = Direct3DCreate9( D3D_SDK_VERSION ) ,
		"Direct3DCreate9", "Init" )

	d3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &mode );

	/*params*/
	D3DPRESENT_PARAMETERS p = {
		xe,  ye,  mode.Format,  1, 	D3DMULTISAMPLE_NONE,  0,
		D3DSWAPEFFECT_DISCARD,  hw,  true/*windowed*/,
		false/*true*/,  D3DFMT_UNKNOWN,  0,
		/*mode.RefreshRate*/0,
		Real ? D3DPRESENT_INTERVAL_IMMEDIATE : D3DPRESENT_INTERVAL_ONE
	};
	params = p;	

	/*vertproc option*/
	d3d->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );

	DWORD vp = 0;

	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		
	Error(
		d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hw, vp, &params, &dev ) ,
		"CreateDevice", "Init" );

	/* Font Sprite */
	Warng(
		D3DXCreateSprite( dev, &Fspr ) ,
		"sprite", "create font" );
		
	Fclr = CLR( 1, 1, 1, 1 );	

	/* font F texture */
	Warng(
		D3DXCreateTextureFromFileExA( dev,  Fname, 0, 0, 1,
			0,  D3DFMT_UNKNOWN,  D3DPOOL_MANAGED,  D3DX_FILTER_NONE,  D3DX_DEFAULT,
			/*alpha*/CLR( 0, 0, 0, 1 ) , 0, 0, &Ftex ) ,
		Fname, "load font tex" );

	/* font L texture */
	Warng(
		D3DXCreateTextureFromFileExA( dev,  Lname, 0, 0, 1, 
			0,  D3DFMT_UNKNOWN,  D3DPOOL_MANAGED,  D3DX_FILTER_NONE,  D3DX_DEFAULT,
			/*alpha*/CLR( 0, 0, 0, 1 ) , 0, 0, &Ltex ) ,
		Lname, "load font tex" );
		
	return true;
}


void D3Dbasic::OnLost()
{
	Fspr->OnLostDevice();
}

bool D3Dbasic::OnReset()
{
	Fspr->OnResetDevice();
	return true;
}


void D3Dbasic::Destroy()
{
	RELEASE( Ltex );
	RELEASE( Ftex );
	RELEASE( Fspr );
	
	RELEASE( dev );
	RELEASE( d3d );
}


// create window
bool D3Dbasic::createWnd()
{
	WNDCLASSEX wc = {
		sizeof( wc ), CS_VREDRAW | CS_HREDRAW, WinMsg,
		0, 0,  hi,  LoadIcon( 0, IDI_INFORMATION ),
		/*LoadCursor( 0, IDC_ARROW )*/ 0,
		CreateSolidBrush( RGB( 0, 0, 0 ) ),
		0, L"CFont_WC",  LoadIcon( 0, IDI_INFORMATION )};	
		
	if (!RegisterClassEx( &wc ))
		return false;
	
	xe = GetSystemMetrics( SM_CXSCREEN );
	ye = GetSystemMetrics( SM_CYSCREEN );
	
	hw = CreateWindow(L"CFont_WC", L"CrystaL Font", WS_POPUP, 0,0,xe,ye, 0,0,hi,0);
	if (!hw)
		return false;
	
	SetFocus( hw );
	ShowWindow( hw, SW_SHOWNORMAL );
	UpdateWindow( hw );

	return true;
}


// --- timer class ---
Timer::Timer()
{
	iv = 0.;
	iv1 = 0.5;
	
	LARGE_INTEGER FQ;
	if (QueryPerformanceFrequency( &FQ ) )
		fq = double( FQ.QuadPart );
}

bool Timer::update()
{
	QueryPerformanceCounter( &CC );
	cc = double( CC.QuadPart );

	t = cc / fq;
	
	if (t - st < iv )
		return false;
	
	dt = t - st;
	
	st = t;
	iFR++;

	dt1 = t - st1;
	if (dt1 >= iv1 )
	{
		FR = iFR / dt1;
		if (FR < 1. )	FR = 0.;
		iFR = 0.;
		st1 = t;
	}
	
	return true;
}
