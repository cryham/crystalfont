#include "header.h"
#include "graphLT.h"


class CFmainApp : public CFgraphLT
{
public:

	UINT ti;

	bool Begin();
	void End();

	bool Check();

};
CFmainApp *app = 0;


// time event
void CALLBACK Tev( UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR )
{
	if (app->Check() )
		app->graph();
}


/*  -   - 	 - 	  - 		- 	 -  -- begin --  - 	 - 			- 	 - 	 -   -  */
bool CFmainApp::Begin()
{
	/*d3d*/
	if (!Init( 0 ))
		return false;

	CreateDC();
	settings();

	/*graph*/
	if (!initGraph())
		return false;

	/*event*/
	ti = timeSetEvent(  int( 0.6f * 1000.f / float( mode.RefreshRate ) ) - 1,
		0, Tev, 0, TIME_PERIODIC | TIME_CALLBACK_FUNCTION | TIME_KILL_SYNCHRONOUS );

	return true;
}


/* End */
void CFmainApp::End()
{
	timeKillEvent( ti );
	optSave();
	DestroyDC();
	destroyGraph();
	Destroy();
}


/* Check */
bool CFmainApp::Check()
{
	switch( dev->TestCooperativeLevel() )
	{
		case D3D_OK:	return true;
		case D3DERR_DEVICELOST:		return false;
		case D3DERR_DEVICENOTRESET:
		{
			D3Dbasic::OnLost();
			if (FAILED( dev->Reset(&params) ))
			{
				MsgInf( "reset", "Check" )
				PostQuitMessage( 0 );
				End();
				DELETE( app );
				return false;
			}
			D3Dbasic::OnReset();
		}	return true;
	}

	return false;
}


///  Win Main  ///
int WINAPI WinMain( HINSTANCE h, HINSTANCE, LPSTR, int )
{
	MSG m;	

	app = new CFmainApp;
	app->hi = h;
	
	if (app->Begin())
		while (GetMessage(&m, 0, 0, 0))
		{
			TranslateMessage( &m );
			DispatchMessage( &m );
		}
		
	app->End();

	DELETE(app);
	return 0;
}


///  Win Messages  ///
LRESULT CALLBACK WinMsg( HWND hi, UINT msg, WPARAM wp, LPARAM lp )
{
	switch (msg)
	{
		case WM_KEYDOWN:
			if (wp != VK_ESCAPE)
			{
				app->key = wp;
				break;
			}

		case WM_DESTROY:
			PostQuitMessage( 0 );
			return 0;
		
		case WM_ACTIVATE:
			ShowCursor( 0 );
			return 0;

	}
	return DefWindowProc( hi, msg, wp, lp );
}


//	header -> d3dbasic ->
//		colour -> font ->
//		keys -> help ->
//		graph -> graphLT -> main
