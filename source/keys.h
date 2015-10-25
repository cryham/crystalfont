#pragma once

#include "font.h"


class CFkeys : public CFfont
{
	public:
		CFkeys();

		WPARAM key;
		bool KeyPress( WPARAM );

		bool showfps, //option
			kAlt, Alt, Shift, Ctrl;  // is pressed

		float sp;  // animation speed
};


// check list cursor range
#define LcurRng( y, p, L, m)	if (p + y > m) {	p = ( m )/L*L;	y = m - p;	}


// Common
#define ListKeys( y, p, L, m, e )	\
	case VK_PRIOR:	if (y >= 4) y -= 4;  else y = 0;	 e\
	case VK_NEXT:	if (y <= L - 5)  y += 4;\
					else  y = L - 1;  LcurRng( y, p, L, m )	e\
	case VK_UP:		if (y > 0)	 y--;\
					else  if (p > 0) {	p -= L;  y = L - 1;  }	e\
	case VK_DOWN:	if (y < L - 1)  y++;\
					else {	p += L;  y = 0;  }\
					LcurRng( y, p, L, m )	e\
	case VK_HOME:	if (p > 0)	p -= L;  else y = 0;	e\
	case VK_END:	p += L;  LcurRng( y, p, L, m )	e
