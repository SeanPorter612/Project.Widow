#pragma once

#ifndef __WidowLyte__
#define __WidowLyte__

//////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// link to Widow's Lyte library and include the main include
#pragma comment(lib, "Lyte.lib")

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// the main header file for the Widow.Lyte
// this file includes all classes and functions Widow.Lyte
// library and contains all the core files needed to start 
// the whole widow system
// ----------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////

#if ( defined _MSC_VER )

	#pragma message(" ")
	#pragma message("/////////////////////////////////////////////////////////////////////////////////////////////////")
	#pragma message("//---------------------------------------------------------------------------------------------//")
	#pragma message("// Paradox Systems: Widow.Lyte.lib: Build version 3.8.25                                       //")
	#pragma message("// This free API is the core system that all of Paradox Systems API and front end software is  //")
	#pragma message("// This defines a lot of useful data, math, and systems that are a valuable asset to           //")
	#pragma message("// develop with. Any programmer could use this library in their toolbox or take a look at the  //")
	#pragma message("// features of the other Paradox Systems development tools for ideas on way that your software //")
	#pragma message("// can add on top of this API to handle all your programming data management needs.            //")
	#pragma message("//---------------------------------------------------------------------------------------------//")
	#pragma message("/////////////////////////////////////////////////////////////////////////////////////////////////")
	#pragma message(" ")

#endif

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// Widow.Lyte's defines all data that is used in every program
// that is made by paradox systems
#include "WI_Config.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// all of the template-based data containers that are used in any paradox
// systems program is here from a smart memory allocator to a dynamic
// list and link list and even a bunch of stuff to let you do most anything 
// you would want with text or binary data
// -----------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// a class to handle allocation of memory and will free the data from memory
// memory as soon as it loses scope
#include "WI_Allocator.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// an array or list that allocates memory as items are added and freed
// when removed
#include "WI_Array.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// a whole lot of C like functions to handle string data
#include "WI_StringFunctions.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// Paradox Systems in-house string class. I lost count of how many
// functions it had after about 390. This will do most anything you will
// ever want with a letter, string, or text file
#include "WI_String.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// a lexer class to let you collect data from a string in a predefined
// format that was built with the tokenizer
#include "WI_Lexer.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// use to add personalized logging and debugging to your applications
#include "WI_LogUtility.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// some generic utilities to handle user input
#include "WI_UserInputUtility.h"

//////////////////////////////////////////////////////////////////////////
// -----------------------------------------------------------------------
// Widow's Lyte library 2D & 3D math system that is used in all of Paradox Systems software
#include "WI_Vector2.h"
#include "WI_Vector4.h"

#include "WI_Matrix.h"

#include "WI_MathDef.h"
#include "WI_MathUtility.h"

#include "WI_Quaternion.h"

#pragma message("  (WidowLyte: The Widow Lyte library is ready for use! )" )

#endif