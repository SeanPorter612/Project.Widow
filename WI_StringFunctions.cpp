#include "LyteGlobals.h"	

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string functions
// ---------------------------------------------------------
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string copy
void WI_StrCopy ( char* input,char* output )
{
	strcpy ( input,output );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string attach
void WI_StrAttach ( char* input,char* output )
{
	strcat ( input,output );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// left copy
void WI_StrLeftCopy ( char* input,char* output,WI_Int pos )
{
	WI_Int index = 0;
	for ( WI_Int i = 0; i < pos; i++ )
	{
		output[ index ] = input[ i ];
		index++;
	}
	output[ index ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// right copy
void WI_StrRightCopy ( char* input,char* output,WI_Int pos )
{
	WI_Int index = 0;
	WI_Int len = strlen ( input );
	for ( WI_Int i = pos; i < len; i++ )
	{
		output[ index ] = input[ i ];
		index++;
	}
	output[ index ] = 0;

}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// mid copy
void WI_StrMidCopy ( char* input,char* output,WI_Int start_pos, WI_Int stop_pos )
{
	WI_Int index = 0;
	for ( WI_Int i = start_pos; i < stop_pos; i++ )
	{
		output[ index ] = input[ i ];
		index++;
	}

	output[ index ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// trim the space
void WI_StrTrimSpace ( char* buffer )
{
	WI_Int len;
	len = strlen ( buffer );
	char* ptemp;
	ptemp = new char[ len+1 ];
	strcpy ( ptemp,buffer );

	WI_Int index = 0;
	for ( WI_Int z = 0; z < len; z++ )
	{
		if ( ptemp[ z ] != ' ' )
		{
			buffer[ index ] = ptemp[ z ];
			index++;
		}
	}
	buffer[ index ] = 0;

	// WI_DELETE_PTR ( ptemp );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrFind ( char* body,char* search )
{
	WI_Int len = strlen ( body );
	WI_Int len2 = strlen ( search ); // search len

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( body[ i ] == search[ 0 ] )
		{
			bool ichk = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( body[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
				return i;
			}
		}
	}

	return -1; // failure
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrFindInside ( WI_Int startx,char* body,char* search )
{
	WI_Int len = strlen ( body );
	WI_Int len2 = strlen ( search ); // search len

	for ( WI_Int i = startx+1; i < len; i++ )
	{
		if ( body[ i ] == search[ 0 ] )
		{
			bool ichk = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( body[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
				return i;
			}
		}
	}

	return -1; // failure
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrFindBackwards ( char* body,char* search )
{
	WI_Int len = strlen ( body );
	WI_Int len2 = strlen ( search );

	for ( WI_Int i = len; i > 0; i-- )
	{
		if ( body[ i ] == search[ 0 ] )
		{
			bool ichk = true;
			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( body[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find inside backwards string loop
WI_Int WI_StrInsideFindBackwards ( WI_Int startx, char* body,char* search )
{
	WI_Int len2 = strlen ( search );

	for ( WI_Int i = startx-1; i > 0; i-- )
	{
		if ( body[ i ] == search[ 0 ] )
		{
			bool ichk = true;
			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( body[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
				return i; // found it
			}
		}

	}
	return -1; // failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// forward search string ( controlled range ) 
WI_Int WI_StrFind ( WI_Int start,WI_Int stop,char* buff,char* search )
{
	WI_Int len2 = strlen ( search );

	for ( WI_Int i = start; i < stop; i++ )
	{
		if ( buff[ i ] == search[ 0 ] )
		{
			bool ichk = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( buff[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
			  return i; // found it
			}
		}
	}

	return -1; // failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// backward search string ( controlled range )
WI_Int WI_StrBackwardRangeSearch ( WI_Int start,WI_Int stop,char* buff,char* search )
{
	WI_Int len2 = strlen ( search );

	for ( WI_Int i = start; i > stop; i-- )
	{
		if ( buff[ i ] == search[ 0 ] )
		{
			bool ichk = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( buff[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ichk = false;
				}
			}

			if ( ichk == true )
			{
				return i; // found it;
			}
		}
	}

	return -1;// failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// getting length
WI_Int WI_StrGetLength ( char* buff )
{
	return strlen ( buff );// use strlen : )
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// lower case
void WI_StrToLowerCase ( char* buffer )
{
	WI_Int len = WI_StrGetLength ( buffer );

	for ( WI_Int i = 0; i < len; i++ )
	{
		buffer[ i ] = tolower ( buffer[ i ] );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// uppercase
void WI_StrToUpperCase ( char* buffer )
{
	WI_Int len = WI_StrGetLength ( buffer );

	for ( WI_Int i = 0; i < len; i++ )
	{
		buffer[ i ] = toupper ( buffer[ i ] );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// uppercase letter
WI_Int WI_StrToUpperCase ( char c )
{
	return tolower ( c );
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// lowercase letter
WI_Int WI_StrToLowerCase ( char c )
{
	return tolower ( c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find the number of times a specific string occurs
WI_Int WI_StrFindOccurance ( char* buff,char* search )
{
	WI_Int len;
	WI_Int len2;
	len = strlen ( buff );
	len2 = strlen ( search );

	WI_Int occ = 0;

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff[ i ] == search[ 0 ] )
		{
			bool ic = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( buff[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ic = false;
				}
			}

			if ( ic == true )
			{
				occ++;
			}

		}
	}

	if ( occ == 0 )
	{
		return -1; // failure
	}
	else
	{
		return occ;
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// conversion of integers
void WI_StrConvertIntToString ( WI_Int integer,char* buff,WI_Int base )
{
	itoa ( integer, buff, base );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// conversion of strings
WI_Int WI_StrConvertStringToInt ( char* buff )
{
	return atoi ( buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// could this be a hexadecimal digit?
bool WI_StrIsHex ( char c )
{
	c = WI_StrToLowerCase ( c );

	switch ( c )
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
			return true;
		break;
	}
	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// does this string contain a non-hexadecimal digit?
bool WI_StrIsHex ( char* buff )
{
	WI_Int len = strlen ( buff );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( WI_StrIsHex ( buff[ i ] ) == false )
		{
			return false;
		}
	}
	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// hexadecimal digit to integer value
WI_Int WI_StrIntToHex ( char c )
{
	if ( WI_StrIsHex ( c ) == false )
	{
		return -1; // failure, not a hex digit
	}

	c = WI_StrToLowerCase ( c );

	switch ( c )
	{
		case '0':
			return 0;
		break;
		
		case '1':
			return 1;
		break;
		
		case '2':
			return 2;
		break;
		
		case '3':
			return 3;
		break;
		
		case '4':
			return 4;
		break;
		
		case '5':
			return 5;
		break;
		
		case '6':
			return 6;
		break;
		
		case '7':
			return 7;
		break;
		
		case '8':
			return 8;
		break;
		
		case '9':
			return 9;
		break;
		
		case 'a':
			return 10;
		break;
		
		case 'b':
			return 11;
		
		case 'c':
			return 12;
		
		case 'd':
			return 13;
		
		case 'e':
			return 14;
		
		case 'f':
			return 15;
	}

	return -1; // failure ? never would get here
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// convert hex value into a integer
WI_Int WI_StrHexToInt ( char* buff )
{
	WI_Int rt = 0;

	if ( buff[ 1 ] == 0 )
	{
		return WI_StrIntToHex ( buff[ 0 ] );
	}

	WI_Int len = strlen ( buff );
	WI_Int* hexval;
	hexval = new WI_Int[ len+1 ];
	WI_Int  hexvali = 0;

	for ( WI_Int i = 0; i < len; i++ )
	{
		hexval[ hexvali ] = WI_StrIntToHex ( buff[ i ] );
		hexvali++;
	}

    WI_Int index = 0;

	for ( WI_Int z = hexvali-1; z >= 0; z-- )
	{
		WI_Int cur;
		if ( index == 0 )
		{
			cur = hexval[ z ];
			index = 16;
		}
		else
		{

		cur = hexval[ z ] * index;
		index = index * 16;
		}
		
		rt = rt + cur;
	}

	// WI_DELETE_PTR ( hexval );

	return rt;
} 


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrTripUp ( char* buff, WI_Int up )
{
	WI_Int len;
	len = strlen ( buff );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff[ i ] != 0 )
		{
			buff[ i ] = buff[ i ] + up;
		}
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrTripDown ( char* buff,WI_Int up )
{
	WI_Int len;
	len = strlen ( buff );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff[ i ] != 0 )
		{
			buff[ i ] = buff[ i ] - up;
		}
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// replace single instance of a character
void WI_StrReplaceChar ( char* buff,char findchr,char replace )
{
	WI_Int len;
	len = strlen ( buff );

	for ( WI_Int z = 0; z < len; z++ )
	{
		if ( buff[ z ] == findchr )
		{
			buff[ z ] = replace;
		}
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrRemoveInstance ( char* buff,char* findstr,char* replacex,char* output )
{

	WI_Int xt = WI_StrFindInside ( NOPREV,buff,findstr );


	char* temp;
	temp = new char[ strlen ( buff )+1 ];
	WI_StrCopy ( temp,buff );

	char* ltemp;
	char* rtemp;

	ltemp = new char[ strlen ( buff )+1 ];
	rtemp = new char[ strlen ( buff )+1 ];

	WI_StrLeftCopy ( buff,ltemp,xt );
	WI_StrRightCopy ( buff,rtemp,xt+strlen ( findstr ) );


	cout << "\n#: " << ltemp << replacex << rtemp << endl;

	
	strcpy ( output,ltemp );
	strcat ( output,replacex );
	strcat ( output,rtemp );

	// WI_DELETE_PTR ( temp );
	// WI_DELETE_PTR ( ltemp );
	// WI_DELETE_PTR ( rtemp );
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// replace string
void WI_StrReplaceInside ( char* buff,char* findstr,char* replacex,char* output )
{
	WI_Int xt;
	xt = WI_StrFindInside ( 0,buff,findstr );

	if ( xt == -1 )
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[ strlen ( buff ) + 500 ];
	outtemp = new char[ strlen ( buff ) + 500 ];
	WI_StrCopy ( ptemp,buff );

	while ( 1 )
	{
		WI_Int xr;
		xr = WI_StrFindInside ( 0,ptemp,findstr );
		if ( xr == -1 )
		{
			break;
		}
		else
		{
			WI_StrRemoveInstance ( ptemp,findstr,replacex,outtemp );
			WI_StrCopy ( ptemp,outtemp );
		}
	}

	WI_StrCopy ( output,ptemp );

	// WI_DELETE_PTR ( ptemp );
	// WI_DELETE_PTR ( outtemp );

}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// random char
char WI_StrRandom ( WI_Int max )
{
	WI_Int x;
	x = rand ( )%max;
	char c;
	c = x;
	return c;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// random char + up
char WI_StrRandom ( WI_Int max,WI_Int up )
{
	WI_Int x;
	x = rand ( )%max+up;
	char c;
	c = x;
	return c;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// random string
void WI_StrRandom ( char* buff, WI_Int max, WI_Int size )
{
	for ( WI_Int i = 0; i < size; i++ )
	{
		if ( rand ( )%2 )
		{
			buff[ i ] = WI_StrRandom ( max );
		}
		else
		{
			buff[ i ] = WI_StrRandom ( max,rand ( )%10 );
		}
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// remove char
void WI_StrRemoveChar ( char* in,char* out,char c )
{
	WI_Int len;
	len = strlen ( in );
	WI_Int ic = 0;

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( in[ i ] != c )
		{
			out[ ic ] = in[ i ];
			ic++;
		}
	}

	out[ ic ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find single character in string
WI_Int WI_StrFindCharForward ( char* str,char c )
{
	WI_Int len = strlen ( str );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}

	return -1; // failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find char ex ( inside )
WI_Int WI_StrFindCharForwardInside ( WI_Int start, char* str, char c )
{
	WI_Int len = strlen ( str );

	for ( WI_Int i = start + 1; i < len; i++ )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}

	return -1;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find single char backward
WI_Int WI_StrFindStrBackward ( char* str, char c )
{
	WI_Int len;
	len = strlen ( str );

	for ( WI_Int i = len; i > 0; i-- )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}

	return -1;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find single char backward
WI_Int WI_StrFindStrBackward ( WI_Int start, char* str, char c )
{
	WI_Int len;
	len = strlen ( str );
	for ( WI_Int i = start-1; i > 0; i-- )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}
	return -1;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int  WI_StrFindChar ( char* str, WI_Int start, WI_Int stop, char c )
{
	for ( WI_Int i = start; i < stop; i++ )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}

	return -1; // failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrFindCharBackward ( char* str, WI_Int start, WI_Int stop, char c )
{
	for ( WI_Int i = stop; i > start; i-- )
	{
		if ( str[ i ] == c )
		{
			return i;
		}
	}
	return -1;// failure
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// remove instances of string
void WI_StrRremove ( char* input, char* output, char* string )
{
	char* buff = input;
	char* findstr = string;

	WI_Int xt;
	xt = WI_StrFindInside ( NULLPOS,buff,findstr );

	if ( xt == -1 )
	{
		return; // failure no string to replace
	}

	char* ptemp;
	char* outtemp;
	ptemp = new char[ strlen ( buff ) + 500 ];
	outtemp = new char[ strlen ( buff ) + 500 ];
	WI_StrCopy ( ptemp,buff );

	while ( 1 )
	{
		WI_Int xr;
		xr = WI_StrFindInside ( 0,ptemp,findstr );
		if ( xr == -1 )
		{
			break;
		}
		else
		{
			WI_StrRremoveSingleInstance ( ptemp,findstr,outtemp );
			WI_StrCopy ( ptemp,outtemp );
		}
	}

	WI_StrCopy ( output,ptemp );

	// WI_DELETE_PTR ( ptemp );
	// WI_DELETE_PTR ( outtemp );

}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrRremoveSingleInstance ( char* buff, char* output, char* string )
{
	WI_Int xt = WI_StrFindInside ( NOPREV,buff,string );

	char* temp;
	temp = new char[ strlen ( buff )+1 ];

	WI_StrCopy ( temp,buff );

	char* ltemp;
	char* rtemp;

	ltemp = new char[ strlen ( buff )+1 ];
	rtemp = new char[ strlen ( buff )+1 ];

	WI_StrLeftCopy ( buff,ltemp,xt );
	WI_StrRightCopy ( buff,rtemp,xt+strlen ( string ) );
	
	strcpy ( output,ltemp );
	strcat ( output,rtemp );

	// WI_DELETE_PTR ( temp );
	// WI_DELETE_PTR ( ltemp );
	// WI_DELETE_PTR ( rtemp );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrSaveStringToFile ( char* filename, char* buff )
{
	ofstream fout ( filename );

	fout << buff;

	fout.close ( );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrGetFileStringLength ( char* filename )
{
	WI_Int count = 0;
	ifstream fin ( filename );

	if ( fin )
	{
		char ch;
		while ( fin.get ( ch ) )
		{
			count++;
		}

		fin.close ( );
		return count;

	} 
	else 
	{ 
		return -1; // failure
	}

	return -1;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_StrLoadFromFile ( char* file, char* output )
{
	ifstream fin ( file );

	if ( fin )
	{
		char ch;
		WI_Int str_i = 0;

		while ( fin.get ( ch ) )
		{
			output[ str_i ] = ch;
			str_i++;
		}

		output[ str_i ] = 0;
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrReverses ( char* input,char* output )
{
	WI_Int len;
	len = strlen ( input );
	WI_Int fcount = 0;

	for ( WI_Int i = len; i > 0; i-- )
	{
		output[ fcount ] = input[ i ];
		fcount++;
	}
	
	output[ fcount ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_StrIsValid ( char* string )
{
	WI_Int len = strlen ( string );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( string[ i ] == 0 )
		{
			return true; // true it is a null terminated string!
		}
	}

	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Save Master INI
bool wi_SaveMasterINI ( char* filename,WI_INI* mini )
{
	ofstream fout ( filename,ios::binary );

	if ( fout )
	{
		fout.write ( ( char* )&mini,sizeof ( mini ) );
		fout.close ( );

		return true;

	}

	fout.close ( );
	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Load master INI
bool wi_LoadMasterINI ( char* filename,WI_INI* mini )
{
	ifstream fin ( filename,ios::binary );

	if ( fin )
	{
		fin.read ( ( char* )&mini,sizeof ( mini ) );
	}
	
	fin.close ( );
	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string compare ( case sensitive )
bool WI_StrCompare ( char* buff1,char* buff2 )
{
	WI_Int len;
	WI_Int len2;
	len = strlen ( buff1 );
	len2 = strlen ( buff2 );

	if ( len != len2 )
	{
		return false; // not equal length
	}

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff1[ i ] != buff2[ i ] )
		{
			return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string compare ( not case sensitive )
bool WI_StrCompareNoCase ( char* buff1,char* buff2 )
{
	WI_Int len;
	WI_Int len2;
	len = strlen ( buff1 );
	len2 = strlen ( buff2 );

	if ( len != len2 )
	{
		return false; // not equal length
	}

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( tolower ( buff1[ i ] ) != tolower ( buff2[ i ] ) )
		{
			return false;
		}
	}

	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_StrIsInside ( char* buff1,char* buff2 )
{
	WI_Int chk;
	chk = WI_StrFind ( buff1,buff2 );

	if ( chk == -1 )
	{
		return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_StrIsInsideLowerCase ( char* buff1,char* buff2 )
{
	char* pbuff1;
	char* pbuff2;

	pbuff1 = new char[ strlen ( buff1 )+1 ];
	pbuff2 = new char[ strlen ( buff2 )+1 ];

	WI_StrCopy ( pbuff1,buff1 );
	WI_StrCopy ( pbuff2,buff2 );

	WI_StrToLowerCase ( pbuff1 );
	WI_StrToLowerCase ( pbuff2 );

	WI_Int chk;
	chk = WI_StrFind ( pbuff1,buff2 );

	// WI_DELETE_PTR ( pbuff1 );
	// WI_DELETE_PTR ( pbuff2 );

	if ( chk == -1 )
	{
		return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string separation from 2 points
void WI_StrSeparate ( char* str, char* sleft, WI_Int go_left, char* sright, WI_Int go_right )
{
	WI_StrLeftCopy ( str,sleft,go_left );
	WI_StrRightCopy ( str,sright,go_right );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrSetNullPos ( char* str,WI_Int pos )
{
	str[ pos ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StrRmvNull ( char* str )
{
	WI_Int len;
	len = strlen ( str );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( str[ i ] == 0 )
		{
			str[ i ] = ' ';
		}
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StrGetNullPos ( char* str )
{
	WI_Int len = strlen ( str );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( str[ i ] == 0 )
		{
			return i;
		}
	}

	return -1; // failure to find 0
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// trim commented characters ( ) 
void WI_StrTrimComments ( char* str, char* output,char start_c,char stop_c )
{
	WI_Int len = strlen ( str );
	WI_Int index = 0;

	bool iadd = true;

	for ( WI_Int z = 0; z < len; z++ )
	{
		if ( str[ z ] == start_c )
		{
			iadd = false; 
		}

		if ( str[ z ] == stop_c )
		{
			iadd = true;
		}

		if ( iadd == true )
		{
			output[ index ] = str[ z ];
			index++;
		}
	}
	
	output[ index ] = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// trim comments to an assembly language source file
void WI_StrTrimCommentsToAssembly ( char* input,char* output )
{
	WI_StrTrimComments ( input,output,';','\n' );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// count the number of lines existing within the source
WI_Int WI_StrCountLines ( char* buffer )
{
	return WI_StrFindOccurance ( buffer,"\n" );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// get the first letter that's not a space
WI_Int WI_StrGetFirstLetter ( char* buff )
{
	WI_Int len = strlen ( buff );
	
	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff[ i ] != ' ' )
		{
			return i;
		}
	}
	return -1; // failure! no letters
}

void WI_EncryprtDecryptString ( char* strKey, char* buffer )
{
	LaneV2		g_Crypt;
	g_Crypt.TransformString ( strKey, buffer );
}
