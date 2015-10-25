#pragma once

#include "help.h"


class CFgraph : public CFhelp
{
	public:

		bool graph();
		virtual void graphLT() = 0;
		
		bool initGraph();
		void destroyGraph();
		
		bool newRect( LPDIRECT3DTEXTURE9& tx );
		
		// util
		void clrHead( float val, int yChrL, int yy );
		void wrRGB( int onR, char ch );
		void wrTex( float& atexFil, int texFil, int xx );
		void anim( float& a, int w );
};
