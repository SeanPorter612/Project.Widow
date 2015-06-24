#include "LyteGlobals.h"

///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------

WI_Int WI_IsKeyDown ( WI_Int keycode )
{
	WI_Int code = GetAsyncKeyState ( keycode );

	if (code & 0x8000)
	{
		code *= 1;
	}

	return ( code & 0x8000 ) ? 1 : 0;
}

///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// returns a basic structure that with the X, Y position of the mouse
// in the window
tWiMousePos WI_GetMousePosition ( )
{
	 tWiMousePos pos;

	 POINT mousePos;
	 GetCursorPos(&mousePos);

	 pos.x = mousePos.x;
	 pos.y = mousePos.y;

	 return pos;
}