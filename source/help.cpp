#include "header.h"
#include "help.h"


//*		_	 _	_ _ __ ___... .. . help . .. ...___ __ _ _	_	 _		*//

void CFhelp::Help()
{
	if (updHelp > 0 )
	{
		updHelp--;
		
		int y, yy = yf + fp,
			x = 20, x0 = 70+x, x1 = 100+x, x2 = 400+x;
		float c;

		for (y = 0;	y < yy;	y++)
		{
			c = float( yy - y ) / float( yy );
			Clear( 0, y, xf2 + fp, y + 1,  RGB( 40 + c*60, 30 + c*40, 20 + c*30 ) );
		}

		Fclr = CLR( 1, 0.9f, 1,  1 );  y = 5;
			format(s,S, "CrystaL Font  %s", ver );  Write( 20, y );
		Fclr = CLR( 1, 0.8f, 1,  1 );
			scpy(s, "Keyboard help" );	Write( xf2 - 120, y );
		Fclr = CLR( 1, 0.8f, 0.7f,  1 );
			scpy(s, "Page:" );		Write( xf2/2 - 40, y );
		
		Fclr = CLR( 1, 0.6f, 0.7f,  1 );
			format(s,S, "%c %d %c",
				(HelpPage > 0) ? '<' : ' ',
				 HelpPage + 1,
				(HelpPage < HelpPages) ? '>' : ' ' );
			WriteL( xf2/2 + 30, y );	y += 2*Ly;	

		static const char ht[HelpPages + 1][20] = {
			" -  Main  - ", "   [Table]", "   List[]"  };

		Fclr = CLR( 1.f, 0.8f, 0.7f,  1 );
			scpy(s, ht[HelpPage] );
			WriteL( xf2/2 - 30, y );

		y += 2*Ly;	 yy = y;
		
		switch( HelpPage )
		{
		/*  Main  */
			case 0:
				y = yy;		Fclr = CLR( 1, 1, 1,  1 );	
				
				scpy(s, "Tab" );	Write(x, y);		y += Ly*3/2;
				scpy(s, "H" );		WriteL(x, y);		y += Ly;
				scpy(s, "F" );		WriteL(x, y);		y += Ly;
				scpy(s, "G" );		WriteL(x, y);		y += Ly;
				scpy(s, "C" );		WriteL(x, y);		y += Ly;
				scpy(s, "Space" );	Write(x, y);		y += Ly*3/2;
				scpy(s, "Q" );		WriteL(x, y);		y += Ly;
				scpy(s, "W" );		WriteL(x, y);		y += Ly;
				scpy(s, "I" );		WriteL(x, y);		y += Ly*3/2;
				scpy(s, "F9" );	WriteL(x, y);		y += Ly;
				scpy(s, "F11" );	WriteL(x, y);		y += Ly*3/2;
				scpy(s, "Alt Arrows" );	Write(x, y);	y += Ly;
				scpy(s, "Alt Num -,+" );	Write(x, y);	y += Ly;
				scpy(s, "Alt Num /,*" );	Write(x, y);	y += Ly;

			/**/y = yy;  Fclr = CLR( 0.6f, 1, 1,  1 );	

				scpy(s, "switch Table - List" );				Write( x0, y );  y += Ly*3/2;
				scpy(s, "view char / maximize tex display" );	Write( x0, y );  y += Ly;
				scpy(s, "toggle Font draw" );				Write( x0, y );  y += Ly;
				scpy(s, "toggle Glow draw" );				Write( x0, y );  y += Ly;
				scpy(s, "toggle All draw (F+G)" );			Write( x0, y );  y += Ly;
				scpy(s, "switch Font / Glow color set" );	Write( x0, y );  y += Ly*3/2;
				scpy(s, "color-rect filtering" );			Write( x0, y );  y += Ly;
				scpy(s, "char/font filtering" );			Write( x0, y );  y += Ly;
				scpy(s, "show showfps / texture size" );	Write( x0, y );  y += Ly*3/2;
				scpy(s, "save texture" );					Write( x0, y );  y += Ly;
				scpy(s, "display help" );					Write( x0, y );  y += Ly*3/2;
				scpy(s, "move font texture" );				Write( x0+70, y );  y += Ly;
				scpy(s, "zoom - - ,  (H off)" );			Write( x0+70, y );  y += Ly;
				scpy(s, "integer zoom" );					Write( x0+70, y );  y += Ly;
				
				break;	

		/*  Table  */
			case 1:
				y = yy;		Fclr = CLR( 1, 1, 1,  1 );
				
				scpy(s, "F1..F5" );		WriteL(x, y); y += Ly*3/2;
				scpy(s, "Page Up, Dn" );	Write(x, y);  y += Ly;
				scpy(s, "Home, End" );		Write(x, y);  y += Ly*4/2;

				/*Clr*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "Color" );			WriteL( x+10, y );	 y += Ly;	Fclr = CLR( 1, 1, 1,  1 );
				scpy(s, "Num /,*" );		Write(x, y);	 y += Ly;
				scpy(s, "Num -,+ or a,s" );Write(x, y);	 y += Ly;	
				scpy(s, "Enter" );			Write(x, y);	 y += Ly;
				scpy(s, "1,2,3" );			Write(x, y);	 y += Ly;
				scpy(s, " -,= " );			Write(x, y);	 y += Ly*4/2;

				/*Font*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "Font" );			WriteL( x+10, y );	 y += Ly;	Fclr = CLR( 1, 1, 1,  1 );
				scpy(s, "Num /,*" );		Write(x, y);	 y += Ly;
				scpy(s, "Enter" );			Write(x, y);	 y += Ly;
				scpy(s, "Num +" );			Write(x, y);	 y += Ly*4/2;

				/*Glow*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "Glow" );			WriteL( x+10, y );	y += Ly;	Fclr = CLR( 1, 1, 1,  1 );
				scpy(s, "Num /,*" );		Write(x, y);	 y += Ly;
				scpy(s, "Num +" );			Write(x, y);	 y += Ly;
			 
			/**/y = yy + 2*Ly;
				
				/*edit*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "edit" );				WriteL( x2 + 10, y );	y += Ly;	Fclr = CLR( 1, 1, 1,  1 );
				scpy(s, "Ctrl Enter" );		Write( x2, y );	 y += Ly;
				scpy(s, "Ctrl Backspace" );	Write( x2, y );	 y += Ly;	
				
				y = yy;		Fclr = CLR( 0.6f, 1, 1,  1 );
				scpy(s, "change page" );	Write( x+100, y );	
				/**/
				Fclr = CLR( 0.9f, 0.9f, 1,  1 );
				scpy(s, "Color Font Glow Save edit" );	Write( x1+120, y );	y += Ly*3/2;	Fclr = CLR( 0.6f, 1, 1,  1 );	
				scpy(s, "inc, dec table value" );		Write( x1+20, y );	 y += Ly;
				scpy(s, "inc, dec - -  (small)" );		Write( x1+20, y );	y += Ly*6/2;
				/*Clr*/
				scpy(s, "prev, next channel" );		Write( x1, y );	y += Ly;
				scpy(s, "prev, next channel type" );	Write( x1+50, y );	y += Ly;	
				scpy(s, "turn on/off channel" );		Write( x1, y );	y += Ly;
				scpy(s, "toggle R,G,B display" );	Write( x1, y );	y += Ly;	
				scpy(s, "zoom color-rect" );			Write( x1, y );	y += Ly*6/2;
				/*Font*/
				scpy(s, "dec, inc font size (height)" );Write( x1, y );	y += Ly;
				scpy(s, "go to fonts list" );			Write( x1, y );	y += Ly;
				scpy(s, "switch Font/Rect" );			Write( x1, y );	y += Ly*6/2;
				/*Glow*/
				scpy(s, "dec, inc glow array size" );	Write( x1, y );	y += Ly;
				scpy(s, "toggle additive glow" );		Write( x1, y );	 y += Ly;
			 /*2*/y = yy + 3*Ly;
				/*edit*/
				scpy(s, "enter string" );				Write( x2 + 140, y );	y += Ly;
				scpy(s, "leave string" );				Write( x2 + 140, y );	y += Ly;
				
				break;	

		/*  List  */
			case 2:
				y = yy;		Fclr = CLR( 1, 1, 1,  1 );	
				scpy(s, "F1..F4" );		WriteL(x, y);		y += Ly*3/2;
				scpy(s, "Page Up, Dn" );	Write(x, y);	 y += Ly;
				scpy(s, "Home, End" );		Write(x, y);	 y += Ly*4/2;	
				/*.clr*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, ".clr  .fnt" );		WriteL( x+10, y );	 y += Ly;	Fclr = CLR( 1, 1, 1,  1 );	
				scpy(s, "Enter" );			Write(x, y);	 y += Ly;
				scpy(s, "Backspace" );		Write(x, y);	 y += Ly;
				scpy(s, "S" );				Write(x, y);	 y += Ly*6/2;	
				/*Fonts*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "Fonts" );			WriteL( x+10, y );	 y += Ly;	Fclr = CLR( 1, 1, 1,  1 );	
				scpy(s, "Enter" );			Write(x, y);	 y += Ly;
				scpy(s, "A..Z" );			Write(x, y);	 y += Ly*4/2;	

			/**/y = yy + 2*Ly;

				/*Chars*/
				Fclr = CLR( 0.9f, 0.8f, 1,  1 );
				scpy(s, "Chars" );					WriteL( x2+10, y );	y += Ly;	Fclr = CLR( 1, 1, 1,  1 );	
				scpy(s, "Num /,*" );				Write( x2, y );	y += Ly;
				scpy(s, "shift Arrows" );			Write( x2, y );	y += Ly;

				y = yy;

				Fclr = CLR( 0.6f, 1, 1,  1 );
				scpy(s, "change page" );			Write( x1, y );

				Fclr = CLR( 0.9f, 0.9f, 1,  1 );
				scpy(s, ".clr .fnt Chars Fonts" ); Write( x1+120, y );	y += Ly*3/2;

				Fclr = CLR( 0.6f, 1, 1,  1 );
				scpy(s, "up, dn list x4" );		Write( x1+20, y );	y += Ly;
				scpy(s, "prev, next list page" );	Write( x1+20, y );	y += Ly*6/2;	
				/*.clr*/
				scpy(s, "load set / enter dir" );	Write( x1, y );  y += Ly;
				scpy(s, "one directory up" );		Write( x1, y );	 y += Ly;	
				scpy(s, "save current set as" );	Write( x1, y );	 y += Ly;

				Fclr = CLR( 0.6f, 0.8f, 0.9f,  1 );	
				scpy(s, "Enter accept  Del cancel" );		Write( x+20, y );

				y += Ly*6/2;		Fclr = CLR( 0.6f, 1, 1,  1 );	
				/*Fonts*/
				scpy(s, "pick font name" );		Write( x1, y );	 y += Ly;
				scpy(s, "seek letter" );			Write( x1, y );	 y += Ly*6/2;
			 /*2*/y = yy + 3*Ly;
				/*Chars*/
				scpy(s, "prev, next subpage" );			Write( x2 + 140, y );	 y += Ly;
				scpy(s, "change highlighted value(s)" );	Write( x2 + 140, y );	 y += Ly;

				break;
		}
	}
		
	FontEnd();
	RndSt( ALPHABLENDENABLE, FALSE );
}
