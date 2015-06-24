#pragma once

#if ( _MSC_VER >= 1400 )

	////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------
	// annoying warnings
//	#define _CRT_SECURE_NO_DEPRECATE
	#pragma warning ( disable: 4996 )
	#pragma warning ( disable: 4244 )

#else

	#pragma warning ( disable: 4505 )
	#pragma warning ( disable: 4514 )

#endif

/////////////////////////////////////////////////////////
//------------------------------------------------------
// encryption/decryption class
#include "Lane.h"

/////////////////////////////////////////////////////////
//------------------------------------------------------
// Paradox Systems very own encryption and decryption system
extern LaneV2		g_Crypt;

//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// include and link to TinyXML is used in the game file
// that Essence makes and the console reads
#pragma comment(lib, "tinyxml2.lib")
#include "tinyxml2.h"

//#pragma comment(lib, "LinearMath.lib")
/////Math library & Utils
//#include "LinearMath/btQuaternion.h"
//#include "LinearMath/btTransform.h"
//#include "LinearMath/btDefaultMotionState.h"
//#include "LinearMath/btQuickprof.h"
//#include "LinearMath/btIDebugDraw.h"
//#include "LinearMath/btSerializer.h"

// Include the WidowLyte main header in every page as to not include it in every page
#include "WI_Config.h"
#include "WidowLyte.h"