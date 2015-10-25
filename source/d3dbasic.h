#pragma once

//#include "defs.h"
#include "header.h"


class Timer
{
	private:
		double cc, fq,  t, st,  dt1, st1,  iFR;
		LARGE_INTEGER CC;

	public:
		double dt, FR, iv, iv1;
		// delta time, Frame Rate, interval, intervalFR
		
		Timer();
		bool update();
};	


// temp string max size
#define S  300


class D3Dbasic
{
	public:
		// basic
		Timer Ti;
		
		HINSTANCE hi;
		HWND hw;

		int xe, ye;		//screen size

		/* common fuctions */
		bool createWnd();
		bool Init( bool Real );
		void Destroy();
		
		virtual void OnLost();
		virtual bool OnReset();
		
		/* draw & clear rect */
		void Clear( int x1, int y1, int x2, int y2, CLR c );
		void drawRect(
			int i, int j,
			int sx, int sy,

			int xp, int yp,
			int xr, int yr,
			int YY, LPDIRECT3DTEXTURE9 tx );
			
		D3DLOCKED_RECT lrect;
		
		/* CFont */
		void Write( int x, int y );
		void WriteL( int x, int y );
		void WriteX( int x, int y );

		// font chars data
		int Fbx[256], Fby[256], Fwi[256],  //begin x,y, width
			Fy, Fx,  Fz1, Fz2, Fzi;   // size x,y,  range zi = z1 - z2
		int Lbx[256], Lby[256], Lwi[256],
			Ly, Lx,  Lz1, Lz2, Lzi;
		
		// F - Tahoma, L - Lucida
		LPD3DXSPRITE Fspr;
		LPDIRECT3DTEXTURE9 Ftex, Ltex;
			
		void FontBegin( int a ), FontEnd();

		CLR Fclr;  // font color
		int Fxb;  // x boundary

		char s[S+1];	// temp string

		/* D3D */
		LPDIRECT3D9 d3d;
		LPDIRECT3DDEVICE9 dev;

		D3DPRESENT_PARAMETERS params;
		D3DDISPLAYMODE mode;
		D3DCAPS9 caps;
};


LRESULT CALLBACK  WinMsg( HWND, UINT, WPARAM, LPARAM );


// key to char tables
const BYTE kz[2][223 - 32] = 
	{  {
		' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
		0, 0, 0, 0, 0, 0, 0, 
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
		'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		';	', ' = ', ', ', ' - ', '.', '/', '`', 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		'[', '\\', ']', '\''
	}, {
		' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		' )', '!', '@', '#', '$', '%', '^', '&', '*', '( ', 
		0, 0, 0, 0, 0, 0, 0, 
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
		'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		':', ' + ', ' < ', '_', ' > ', '?', '~', 
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		'{', '|' , '}', '\"'
	}  };	

//  with alt (pgClrL)
const BYTE pz[2][26]  = 
	{  {
		'π', 'b', 'Ê', 'd', 'Í', 'f', 'g', 'h', 'i', 'j', 'k', '≥', 'm', 
		'Ò', 'Û', 'p', 'q', 'r', 'ú', 't', 'u', 'v', 'w', 'ü', 'y', 'ø'
	}, {
		'•', 'B', '∆', 'D', ' ', 'F', 'G', 'H', 'I', 'J', 'K', '£', 'M', 
		'—', '”', 'P', 'Q', 'R', 'å', 'T', 'U', 'V', 'W', 'è', 'Y', 'Ø'
	}  };	

const char Fname[]   = "..\\data\\Tah21c.png";	
const char FnameCf[] = "..\\data\\Tah21c.cf";	
const char Lname[]   = "..\\data\\Luc21.png";	
const char LnameCf[] = "..\\data\\Luc21.cf";	
