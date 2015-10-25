#pragma once

#define WIN32_LEAN_AND_MEAN
#define  _WIN32_WINNT  _WIN32_WINNT_WINXP
//#define WINVER, _WIN32_WINDOWS 
#include <windows.h>

#include <d3dx9.h>
#include <strsafe.h>
#include <fstream>
#include <MMSystem.h>

using namespace std;	


// strings
#define format			StringCbPrintfA
#define scpy(a, b)		StringCbCopyA(a, sizeof(a)-1, b)
#define scat(a, b)		 StringCbCatA(a, sizeof(a)-1, b)
#define sadd(a, b, c)		scpy(a, b);  scat(a, c)


// messages
#define Error( a, b, c )	if (FAILED(a) ) {	MessageBoxA( hw, b, c, MB_OK | MB_ICONSTOP );	return false;	}
#define Warng( a, b, c )	if (FAILED(a) ) {	MessageBoxA( hw, b, c, MB_OK | MB_ICONWARNING );	return false;	}
#define WrnMsg( b, c )						{	MessageBoxA( hw, b, c, MB_OK | MB_ICONWARNING );	return false;	}
#define   Msg0( b, c )							MessageBoxA(  0, b, c, MB_OK | MB_ICONWARNING );
#define MsgInf( b, c )							MessageBoxA( hw, b, c, MB_OK | MB_ICONINFORMATION|MB_RIGHT );


// common
#undef DELETE
#define RELEASE( p )	if (p) {	p->Release();	p = NULL;	}
#define DELETE( p )		if (p) {	delete p;	p = NULL;	}
#define DELETEA( p )	if (p) {	delete[]p;	p = NULL;	}

#define ZeroMem( w )	ZeroMemory( &w, sizeof( w ) );


// d3d

typedef  D3DXCOLOR  CLR;

#define RndSt(a, b)		dev->SetRenderState( D3DRS_##a, b );

#define Flt2Int( f )		*( (int*) &f )
#define Int2Flt( i )		*( (float*) &i )


// files
#define fileIn		ios_base::out | ios_base::binary
#define fileOut		fileIn | ios_base::trunc


// math
#define PI	3.1415926535898f

#define range( a, b, x )	max( a, min( b, x ) )


// isKeyDown
#define isKey( x )		( ( GetAsyncKeyState( x ) & 0x8000 ) > 0 )
