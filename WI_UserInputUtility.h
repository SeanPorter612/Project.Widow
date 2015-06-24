#pragma once

#ifndef __User_Input_Utilitys__
#define __User_Input_Utilitys__

enum eWiAsciiKeyCode
{
	Key_UNKNOWN		= 0,

	Key_L_MOUSE_BUTTON = VK_LBUTTON,
	Key_R_MOUSE_BUTTON = VK_RBUTTON,
	Key_M_MOUSE_BUTTON = VK_MBUTTON,

	Key_F1	= VK_F1,
	Key_F2,
	Key_F3,
	Key_F4,
	Key_F5,
	Key_F6,
	Key_F7,
	Key_F8,
	Key_F9,
	Key_F10,
	Key_F11,
	Key_F12,
	Key_lastSpecialKey,

	Key_ESCAPE	= VK_ESCAPE ,
	Key_SPACE	= VK_SPACE ,
	Key_PLUS	= VK_ADD,
	Key_MINUS	= VK_SUBTRACT,

	// L-Case Keyboard
	Key_a = 'a',
	Key_b,
	Key_c,
	Key_d,
	Key_e,
	Key_f,
	Key_g,
	Key_h,
	Key_i,
	Key_j,
	Key_k,
	Key_l,
	Key_m,
	Key_n,
	Key_o,
	Key_p,
	Key_q,
	Key_r,
	Key_s,
	Key_t,
	Key_u,
	Key_v,
	Key_w,
	Key_x,
	Key_y,
	Key_z,

	// U-Case Keyboard
	Key_A = 'A',
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
} ;

///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// a basic structure to set the mouses X, Y position neatly inside of
struct tWiMousePos
{
	// the X position
	WI_Int x;

	// the Y position
	WI_Int y;
};

///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// WI_IsKeyDown returns not 0 if the eWiAsciiKeyCode enum
// Key_xx is being pressed good for handling generic keyboard
// and mouse click
//
// example:
// if ( IsKeyDown ( Key_L_MOUSE_BUTTON ) )
// {
//      tWiMousePos pos =  WI_GetMousePosition ( );
// }
WI_Int WI_IsKeyDown ( WI_Int keycode );

///////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------
// returns a basic structure with the X, Y position of the mouse
// in the window
tWiMousePos WI_GetMousePosition ( );

#pragma message("  ( WI_UserInputUtility: Generic user input utilities are defined and ready for use... )" )
#endif // __User_Input_Utilitys__
