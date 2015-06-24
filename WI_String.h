#pragma once

#ifndef __WI_String__
#define __WI_String__

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// ---------------------------------------------------------
// Theory in-house string class
// This class implements variable-size strings, 
// and auto-manages its memory space, expanding the buffer 
// whenever necessary. The class supplies methods for 
// constructing a WI_String from a char pointer, 
// concatenating, copying and comparing strings, 
// indexing a specific character and finding a sub-string.
// ---------------------------------------------------------
// ---------------------------------------------------------
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////


#define NOTFOUND -1
#define INULL    -1
#define NOPREV   -1
#define NULLI    -1
#define STRBEGIN -1
#define MRANGE_HI 1
#define MRANGE_LO 0
#define NULLPOS  -1

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string classes
// ---------------------------------------------------------
////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string data location structure use w/ ( find string location )

class WI_StrDataLoc
{
public:

	WI_StrDataLoc ( );
	~WI_StrDataLoc ( );

	void create_array ( WI_Int size );

	void setstr ( char* buff );

	void setstatus ( bool x );

	void setsearchstr ( char* buff );

	/////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------
	// return pointer to the string which the array holds data for
	char* getstr ( );

	char* getsearchstr ( );

	WI_Int getarraysize ( );

	WI_Int getstringpoint ( WI_Int index );

	/////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------
	// maximum string points for search
	WI_Int getmaxpoint ( );

	/////////////////////////////////////////////////////////////////////
	//-------------------------------------------------------------------
	// get status
	bool getstatus ( );

	bool wassearchsuccesful ( );

	WI_Int*	dindex;
	WI_Int  array_size;
	char*	thestring;
	char*	searchstr;
	bool	search_status;
};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// find string location ( dumps all locations into the location data structure ( WI_StrDataLoc ) )

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// standard
bool WI_StrFindLocation ( char* buff,char* search, WI_StrDataLoc* dloc );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// forward
bool WI_StrFindLocationForward ( char* buff, char* search, WI_StrDataLoc* dloc );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// backward
bool WI_StrFindLocationBackward ( char* buff, char* search, WI_StrDataLoc* dloc );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string range class
//----------------------------------------------------------
////////////////////////////////////////////////////////////
class WI_StrRange
{
public:
	WI_Int start_x;
	WI_Int stop_y;

	WI_StrRange ( );

	void SetRange ( WI_Int x, WI_Int y );

	WI_Int GetRangeX ( );

	WI_Int GetRangeY ( );

	WI_Int GetRangeHI ( );

	WI_Int GetRangeLO ( );

	void Clear ( );
};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// range search structures for range style string manipulation
bool WI_StrSearchRange		( char*		buff,		char*	search,		WI_StrRange*	mrang );
void WI_StrCopyLeftRange	( char*		input,		char*	output,		WI_StrRange*	mrang,	WI_Int		 hi_lo );
void WI_StrCopyRightRange	( char*		input,		char*	output,		WI_StrRange*	mrang,	WI_Int		 hi_lo );
void WI_StrCopyMidRange		( char*		input,		char*	output,		WI_StrRange*	mrang,	WI_Int		 hi_lo,	WI_StrRange*	mrangx, WI_Int	hi_lox );
bool WI_StrISearchRange		( WI_Int	startx,		char*	buff,		char*			search,	WI_StrRange* mrang );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string list class string data
//----------------------------------------------------------
////////////////////////////////////////////////////////////
class WI_StrList_String
{
public:
	WI_StrList_String ( );

	~WI_StrList_String ( );

	void set ( char* buff );

	char* get ( );

private:
	char* thestring;
};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string list, list handler structure
//----------------------------------------------------------
////////////////////////////////////////////////////////////
class WI_StrList
{
public:
	~WI_StrList ( );

	WI_StrList ( WI_Int list_size );

	WI_StrList ( );

	void create ( WI_Int list_sizez );

	char* getstr ( WI_Int index );

	WI_Int getcount ( );

public:
	WI_StrList_String* strings;
	WI_Int list_size;
};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// create string list
void WI_StrCreatestrList ( char* buffer, char* list_marker,WI_StrList* list );

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// WI_Charwrap  easy to use char array,
// that automaticly removes itself from freestore
//----------------------------------------------------------
////////////////////////////////////////////////////////////
class WI_Charwrap
{
public:
	WI_Charwrap ( WI_Int size );

	WI_Charwrap ( char* buff );

	WI_Charwrap ( char* buff,bool x );

	~WI_Charwrap ( );

	void set ( char* buff );

	void snew ( WI_Int size );

	////////////////////////////////////////////////////////////
	//----------------------------------------------------------
	// clear off freestore
	void clear ( );

	void strclear ( );

	void strclearn ( );

	char* get ( );

	WI_Int len ( );

private:
	char* str;

};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// structure of string manipulation algorithms to use
// for objects to inherit
//----------------------------------------------------------
////////////////////////////////////////////////////////////
struct WI_StrObj
{
	void Copy ( char* input,char* output );

	void Attach ( char* input,char* output );

	void LeftCopy ( char* input,char* output,WI_Int pos );

	void RightCopy ( char* input,char* output,WI_Int pos );

	void MidCopy ( char* input,char* output,WI_Int start_pos,WI_Int stop_pos );

	void Trim ( char* buff );

	WI_Int Find ( char* buffer,char* search );

	char Find ( char* str, char c );

	WI_Int Find ( WI_Int i,char* buffer,char* search );

	WI_Int FindBody ( char* body, char* search );

	WI_Int BackwardFindBody ( WI_Int startx, char* body, char* search );

	WI_Int Search ( WI_Int start ,WI_Int stop, char* buff, char* search );

	WI_Int BackwardSearch ( WI_Int start, WI_Int stop, char* buff, char* search );

	WI_Int GetLen ( char* buff );

	void ToLcase ( char* buffer );

	void ToUcase ( char* buffer );

	WI_Int ToUcaseLetter ( char Letter );

	WI_Int ToLcaseLetter ( char Letter );

	bool FindLocation ( char* buff, char* search, WI_StrDataLoc* dloc );

	bool FindLocationForward ( char* buff,char* search, WI_StrDataLoc* dloc );

	bool FindLocationBackwards ( char* buff,char* search,WI_StrDataLoc* dloc );

	bool SearchRange ( char* buff, char* search, WI_StrRange* mrang );

	bool SearchRange ( WI_Int startx, char* buff, char* search, WI_StrRange* mrang );

	void CopyLeftRange ( char* input, char* output, WI_StrRange* mrang, WI_Int hi_lo );

	void CopyRightRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo );

	void CopyMidRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo,WI_StrRange* mrangx,WI_Int hi_lox );

	WI_Int FindOccourance ( char* buffer,char* searchx );

	void ConverToInteger ( WI_Int integer, char* buff, WI_Int base );

	WI_Int ConverToInteger ( char* buff );

	bool IsHexc ( char c );

	bool IsHex ( char* buff );

	WI_Int HexToInteger ( char c );

	WI_Int HexToInteger ( char* buff );

	void TripDown ( char* buff,WI_Int by );

	void TripUp ( char* buff, WI_Int by );

	void Replace ( char* buff,char findchr,char replace );

	void Replace ( char* buff,char* findstr, char* replacex, char* output );

	void RemoveSingleInstanceOf ( char* buff,char* findchr,char* re,char* out );

	char Random ( WI_Int max );

	char Random ( WI_Int max, WI_Int up );

	void Random ( char* buff, WI_Int max, WI_Int size );

	void Remove ( char* input, char* output, char c );

	char FindBackward ( char* str,char c );

	char FindInside ( WI_Int start,char* str,char c );

	char FindInsideBackward ( char* str,char c );

	char FindBackward ( WI_Int start, char* str,char c );

	char FindForward ( char* str, WI_Int start,WI_Int stop, char c );

	char FindBackward ( char* str, WI_Int start, WI_Int stop, char c );

	void Remove ( char* str, char* output, char* strsearch );

	void RemoveInstanceOf ( char* str, char* output, char* strx );

	void SavestoFile ( char* filename, char* string );

	bool LoadFomeFile ( char* filename, char* output );

	WI_Int  SetFileStrLength ( char* filename );

	void Reverse ( char* str_input,char* str_output );

	bool IsValid ( char* str );

	bool Compare ( char* buff1,char* buff2 );

	bool CompareNoCase ( char* buff1,char* buff2 );

	bool IsInside ( char* buff1,char* buff2 );

	bool IsInsideNoCase ( char* buff1,char* buff2 );

	void Separate ( char* str,char* lstr,WI_Int lpos,char* rstr,WI_Int rpos );

	WI_Int GetNullPos ( char* str );

	void RemoveNull ( char* str );

	void SetNullPos ( char* str, WI_Int pos );

	void TrimComments ( char* input, char* output, char start_c, char stop_c );

	void TrimCommentsToAssembly ( char* input, char* output );
};

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// the WI_String Object
//----------------------------------------------------------
////////////////////////////////////////////////////////////
class WI_String :  WI_StrObj
{
private:

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// char* buffer
	char*		str;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// size of the char*
	WI_Int		array_size;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// is the string on or off
	bool		str_on;

public:
	~WI_String ( );
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// constructors

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// generic init string
	WI_String ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// init a string in a %s %i %s... format
	WI_String ( const char *fmt, ... );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// just allocate size for the string
	WI_String ( WI_Int size );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// set the internal string as a char*
	WI_String ( char* buff );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// constructor set size of the string as int 
	// and internal string as char cutting off at int
	WI_String ( WI_Int size, char* buff );

	////////////////////////////////////////////////////////////
	//----------------------------------------------------------
	// internal functions

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// sets the initial string as a char*
	void set ( char* buff );

	void set ( WI_Int size, char* buff );

	void SetChar ( WI_Int iPos, char c );

	void add ( char* buff );

	void unset ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// gets the widow string as a char*
	char* GetAsChar ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// gets the hex value of the internal string
	WI_Int GetHexValue ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// gets the double val of internal string
	double GetAsDouble ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// gets the decimal val of internal string
	WI_Int GetAsDesmal ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// covers string to int
	WI_Int GetAsInt ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the string as a LPCSTR
	LPCSTR GetAsLPCSTR ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the string as a LPWSTR
	LPWSTR GetAsLPWSTR ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// splits string by a delimiter and returns an array
	//vector< char* > SplitStringBy(char* strDelm);

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// encrypts/decrypts this string
	void EncryptDencrypt ( char* strKey );

	////////////////////////////////////////////////////////////
	//----------------------------------------------------------
	// begin operators
	//----------------------------------------------------------
	////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// operator =
	WI_String operator = ( char* buffer );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// operator += char*
	WI_String operator += ( char* buffer );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// operator += int
	WI_String operator += ( WI_Int x );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// operator += long
	WI_String operator += ( WI_Long x );

	////////////////////////////////////////////////////////////
	//----------------------------------------------------------
	// misc but useful functions

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the number of chars in the string
	WI_Int GetStringLength ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// gets the char pointer
	char* GetCharPointer ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the char WI_Int pos of c
	WI_Int FindChar ( char c );

	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the char WI_Int pos of c starting at WI_Int pre_pos
	WI_Int FindCharEx ( WI_Int pre_pos, char c );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the WI_Int pos of c from the end of the string
	WI_Int FindCharBackward ( char c );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the char WI_Int pos of c starting from the end WI_Int pre_pos
	WI_Int FindCharBackwardEx ( WI_Int pre_pos, char c );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int FindCharControledForward ( WI_Int start, WI_Int stop, char c );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int FindCharControledBackward ( WI_Int start, WI_Int stop, char c );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the WI_Int position of the char* if found
	WI_Int FindString ( char* search );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the WI_Int position of the char* 
	// if found starting from index
	WI_Int FindStringEx ( WI_Int index, char* search );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the int position of char* where search is starting
	// at the end of the string
	WI_Int FindStringBackward ( char* search );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the int pos in the string where char* is from the
	// end of the internal string
	WI_Int FindStringBackwardEx ( WI_Int index, char* search );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// returns the int position in the string where char* is from the
	// beginning of the internal string
	WI_Int FindOccourance ( char* search );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// copies a char* to the end of a string
	void StringCopy ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// attaches a char* to the end of the internal string
	void StringAttach ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// resizes the internal string and cuts off the end
	void StringResize ( WI_Int newSize );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void StringLeft ( char* output, WI_Int pos );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void StringRight ( char* output, WI_Int pos );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void StringMid ( char* output, WI_Int x, WI_Int y );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// trim the white spaces off of the internal string
	void TrimSpace ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// converts the internal string to uppercase
	void UpperCase ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// converts the internal string to lowercase
	void LowerCase ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// extracts a char at index
	char ExtractChar ( WI_Int index );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int ForwardStringSearch ( WI_Int start, WI_Int stop, char* search );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int BackwardStringSearch ( WI_Int start, WI_Int stop, char* search );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool FindStringLocation ( char* search, WI_StrDataLoc* dloc );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool FindStringLocationF ( char* search, WI_StrDataLoc* dloc );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool FindStringLocationB ( char* search, WI_StrDataLoc* dloc );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void SearchRange ( char* search, WI_StrRange* mrang );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void SearchRangeEx ( WI_Int startx, char* search, WI_StrRange* mrang );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void CopyLeftRange ( char* output, WI_StrRange* mrang, WI_Int hi );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void CopyRightRange ( char* output, WI_StrRange* mrang, WI_Int hi );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void CopyMidRange ( char* output, WI_StrRange* mrang, WI_Int hi, WI_StrRange* mrangx, WI_Int hix );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// is hex or not
	bool IsHex ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// clears the current string
	void ClearString ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// clears the string within a starting and an ending range
	void ClearStringRange ( WI_Int iStart, WI_Int iEnd );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// replaces a find char with replace in the string
	void ReplaceCharacter ( char findchr, char replace );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// generates a random string from 0 to 255 characters long
	void RandomizeString ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// generates a random string from 0 to iMaxChars number of characters
	void RandomizeString ( WI_Int iMaxChars );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// replaces search with replacestr in the string
	void ReplaceString ( char* search, char* replacestr );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// Removes the Character c from the string
	void RemoveCharacters ( char c );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// removes a char* from this string
	void RemoveString ( char* search );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// Remove a single instance of char*
	void RemoveSingleInstanceOfString ( char* search );

	//////////////////////////////////////////////////////////////////////
	// ------------------------------------------------------------------
	// Compare with a char pointer
	bool Compare ( const char *strIn ) const;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// saves the internal string as a file
	void SaveToFile ( char* filename );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// loads a text file as a string
	void LoadStringFromFile ( char* filename );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool IsStringValid ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// reverse the string
	void ReverseString ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool StringCompare ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool StringCompare_NOCASE ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool IsInsideString ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool IsInsideString_NOCASE ( char* buff );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void SeperateString ( char* lbuff,WI_Int lpos,char* rbuff,WI_Int rpos );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// trim string as tho it were assembly language source
	void AsmTrim ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void TrimComments ( char start_c,char stop_c );
};

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// WI_String Item Structure 
struct ListItem
{
	WI_Int list_index;

	void setindex ( WI_Int i )
	{
		list_index = i;
	}

	WI_Int getindex ( )
	{
		return list_index;
	}
};

struct WI_StringItem : 
	WI_String,
	ListItem
{
	bool on;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_StringItem ( )
	{
		on = false;
	}

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void seton ( bool x )
	{
		on = x;
	}

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool geton ( )
	{
		return on;
	}
};

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// example of a list using WI_Strings
struct WI_StringList 
{
private:
	WI_StringItem* item;
	bool ion;
	WI_Int array_size;
	WI_Int off;

public:
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_StringList ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_StringList ( WI_Int size );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void createList ( WI_Int size );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int  GetArraySize ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	char* GetListStringPointerByIndex ( WI_Int index );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int AddString ( char* buffer );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int GetListLength ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void GetString ( WI_Int index, char* output );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void Clear ( );
};

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
struct WI_Entry : ListItem
{
	WI_String name;
	WI_String value;
	bool on_switch;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Entry ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool amion ( );

};

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// easy to use INI object, using WI_Strings
struct WI_INI
{
	WI_Entry* masEntry;
	bool mas_on;
	WI_Int array_size;
	WI_Int off_count;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// constructors/deconstructors
	WI_INI ( );
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_INI ( WI_Int size );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	~WI_INI ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void set ( WI_Int size );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int getsize ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void Create ( WI_Int size );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool AddEntry ( char* name,char* value );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	bool GetEntry ( char* name,char* output_value );
};

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Save INI
bool SaveMasterINI ( char* filename,WI_INI* mini ); 

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Load INI
bool LoadMasterINI ( char* filename,WI_INI* mini ); 

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// char list based on the \n ( breaks strings into lines )
// ( for use with WI_Asm )
struct WI_CharList 
{
private:
	WI_String* list;
	bool list_on;
	WI_Int array_size;
	WI_Int list_len;

public:
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_CharList ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_CharList ( char* buff );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	~WI_CharList ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	void BuildList ( char* buff );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_Int GetLength ( );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	WI_String* GetWI_String ( WI_Int index );
};

#pragma message ( "		Widow string system created..." )

#endif