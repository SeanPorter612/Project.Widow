#pragma once
#ifndef __WI_StringFunctions__
#define __WI_StringFunctions__


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// basic string C like functions
// ---------------------------------------------------------
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string copy
void WI_StrCopy ( char* dest, char* from );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string attach
void WI_StrAttach ( char* dest, char* from ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// left copy ( leftstr )
void WI_StrLeftCopy ( char* from, char* dest, WI_Int pos );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// right copy ( rightstr )
void WI_StrRightCopy ( char* from, char* dest, WI_Int pos );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// middle copy ( midstr )
void WI_StrMidCopy ( char* from, char* dest, WI_Int start_pos, WI_Int stop_pos );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// trim space characters
void WI_StrTrimSpace ( char* buff );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find string search
WI_Int WI_StrFind ( char* buffer, char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find string search from position
WI_Int WI_StrFindInside ( WI_Int i, char* buffer, char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// backwards search
WI_Int WI_StrFindBackwards ( char* buffer, char* search ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// inside backwards search
WI_Int WI_StrInsideFindBackwards ( WI_Int i, char* buffer, char* search ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// fully controlled range search ( forward )
WI_Int WI_StrFind ( WI_Int start, WI_Int stop,char* buff,char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// fully controlled range search ( backward )
WI_Int WI_StrBackwardRangeSearch ( WI_Int start, WI_Int stop, char* buff, char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove instances of string in buffer
void WI_StrRremove ( char* buff, char* str );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// get length of the string
WI_Int WI_StrGetLength ( char* buff );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// char* to lower case string
void WI_StrToLowerCase ( char* buff );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// char* to upper case string
void WI_StrToUpperCase ( char* buff );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// lower case letter
WI_Int WI_StrToLowerCase ( char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// upper case letter
WI_Int WI_StrToUpperCase ( char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find occurances of a specific string
WI_Int WI_StrFindOccurance ( char* buff, char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// convert integer to string
void WI_StrConvertIntToString ( WI_Int integer, char* buff, WI_Int base ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// convert string to integer
WI_Int WI_StrConvertStringToInt ( char* buff ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// is this character a hexadecimal digit?
bool WI_StrIsHex ( char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// is this string a hexadecimal value?
bool WI_StrIsHex ( char* buff );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// hexadecimal digit to integer value
WI_Int WI_StrIntToHex ( char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// hexadecimal digits to integer value
WI_Int WI_StrHexToInt ( char* buff ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find the numeric of times a string occurs
WI_Int WI_StrFindOccurance ( char* buff, char* search );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// bump the digits up X times
void WI_StrTripUp ( char* buff, WI_Int upby );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// dump the digits down X times
void WI_StrTripDown ( char* buff, WI_Int downby );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// replace all instances of a single character
void WI_StrReplaceChar ( char* string, char findchr, char replace );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// replace string inside string
void WI_StrReplaceInside ( char* string, char* findstr, char* rep, char* output );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove single instance of string
void WI_StrRemoveInstance ( char* buff, char* findstr, char* replace, char* output );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// produce a random character
char WI_StrRandom ( WI_Int max );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// produce a random character, and then make it + up
char WI_StrRandom ( WI_Int max, WI_Int up );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// produce a random string
void WI_StrRandom ( char* buff, WI_Int char_max, WI_Int char_size );// random string

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove characters from buffer
void WI_StrRemoveChar ( char* input, char* output, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find single char ( forward )
WI_Int WI_StrFindCharForward ( char* str, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// inside find single char ( forward )
WI_Int WI_StrFindCharForwardInside ( WI_Int start, char* str, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find single char ( backward )
WI_Int WI_StrFindStrBackward ( char* str, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find single char backward ex
WI_Int WI_StrFindStrBackward ( WI_Int start, char* str, char c ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find single char controlled forward
WI_Int WI_StrFindChar ( char* str, WI_Int start, WI_Int stop, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find single char controlled backward
WI_Int WI_StrFindCharBackward ( char* str, WI_Int start, WI_Int stop, char c );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove instance of string
void WI_StrRremove ( char* input, char* output, char* string );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove single instance of string
void WI_StrRremoveSingleInstance ( char* buff,char* output, char* string ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// save the string as a text file
void WI_StrSaveStringToFile ( char* filename, char* string );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// load a string from a text file
bool WI_StrLoadFromFile ( char* filename, char* output );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// get the string length of a text file
WI_Int WI_StrGetFileStringLength ( char* filename );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// reverse string
void WI_StrReverses ( char* input, char* output ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// checks to see if the string is valid or not ( is null terminated )
bool WI_StrIsValid ( char* string ); 

/////////////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string comparing

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// case sensitive compare
bool WI_StrCompare ( char* buff1, char* buff2 ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// not case sensitive compare
bool WI_StrCompareNoCase ( char* buff1, char* buff2 );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// am i inside this string?
bool WI_StrIsInside ( char* buff1, char* buff2 ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// am i inside this string lowercased ?
bool WI_StrIsInsideLowerCase ( char* buff1, char* buff2 );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// separate into 2 separate strings from 2 separate points
void WI_StrSeparate ( char* str, char* sleft, WI_Int go_left, char* sright, WI_Int go_right );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// reset the 0's position
void WI_StrSetNullPos ( char* str, WI_Int pos ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// remove the 0 to end the string
void WI_StrRmvNull ( char* str ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// get the position of the null
WI_Int WI_StrGetNullPos ( char* str );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// trim commented characters ( )
void WI_StrTrimComments ( char* buff, char* output, char startstr, char stopstr ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// trim comments to an assembly language source file
void WI_StrTrimCommentsToAssembly ( char* input,char* output );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// counts how many \n characters exist
WI_Int WI_StrCountLines ( char* buffer ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// get first letter that's not a space
WI_Int WI_StrGetFirstLetter ( char* buffer ); 

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// returns an encrypted string by input and key
void WI_EncryprtDecryptString ( char* strKey, char* buffer );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// compare 
#define	 WI_Compare_pChar( str1, str2 )			strcmp( str1, str2 )

#pragma message ( "		Widow Lyte's String API functions complete..." )
#endif