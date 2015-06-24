#include "LyteGlobals.h"	

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// ---------------------------------------------------------
////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find string location algorithms
bool WI_StrFindLocation ( char* buff,char* search,WI_StrDataLoc* dloc )
{
	WI_Int len = strlen ( buff );
	WI_Int len2 = strlen ( search );
	WI_Int* f;
	WI_Int  f_i = 0;
	f = new WI_Int[ len+1 ];// big just in case

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
				f[ f_i ] = i;
				f_i++;
			}
		}
	}

	dloc->create_array ( f_i );
	dloc->setstr ( buff );
	dloc->setsearchstr ( search );
	for ( WI_Int p = 0; p < f_i; p++ )
	{
		dloc->dindex[ p ] = f[ p ];
	}
	// WI_DELETE_PTR ( f );

	if ( f_i != 0 )
	{
		dloc->setstatus ( true );
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus ( false ); 
		return false; // not found
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find string location forward search
bool WI_StrFindLocationForward ( char* buff,char* search,WI_StrDataLoc* dloc )
{
	return WI_StrFindLocation ( buff,search,dloc );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// find string location backwards search
bool WI_StrFindLocationBackward ( char* buff,char* search,WI_StrDataLoc* dloc )
{
	WI_Int len = strlen ( buff );
	WI_Int len2 = strlen ( search );
	WI_Int* f;
	WI_Int  f_i = 0;
	f = new WI_Int[ len+1 ];// big just in case

	for ( WI_Int i = len; i > 0; i-- )
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
				f[ f_i ] = i;
				f_i++;
			}
		}
	}

	dloc->create_array ( f_i );
	dloc->setstr ( buff );
	dloc->setsearchstr ( search );
	for ( WI_Int p = 0; p < f_i; p++ )
	{
		dloc->dindex[ p ] = f[ p ];
	}

	// WI_DELETE_PTR ( f );

	if ( f_i != 0 )
	{
		dloc->setstatus ( true );
		return true; // we got some locations
	}
	else
	{
		dloc->setstatus ( false );
		return false; // not found
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string ( range based ) manipulation algorithims
bool WI_StrSearchRange ( char* buff,char* search,WI_StrRange* mrang )
{
	WI_Int len;
	WI_Int len2;
	len = strlen ( buff );
	len2 = strlen ( search );

	for ( WI_Int i = 0; i < len; i++ )
	{
		if ( buff[ i ] == search[ 0 ] )
		{
			bool ik = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( buff[ i+z ] == search[ z ] )
				{
				}
				else
				{
					ik = false;
				}
			}

			if ( ik == true )
			{
				mrang->SetRange ( i,i+len2 );
				return true;
			}
		}
	}

	mrang->SetRange ( 0,0 );
	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string range manipulation ex ( i )
bool WI_StrISearchRange ( WI_Int startx, char* buff,char* search,WI_StrRange* mrang )
{
	WI_Int len;
	WI_Int len2;
	len = strlen ( buff );
	len2 = strlen ( search );

	for ( WI_Int i = startx+1; i < len; i++ )
	{
		if ( buff[ i ] == search[ 0 ] )
		{
			bool ik = true;

			for ( WI_Int z = 0; z < len2; z++ )
			{
				if ( buff[ i+z ] != search[ z ] )
				{
					ik = false;
				}
			}

			if ( ik == true )
			{
				mrang->SetRange ( i,i+len2 );
				return true;
			}
		}
	}
	mrang->SetRange ( 0,0 );
	return false;
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string range manipulation copy left range
void WI_StrCopyLeftRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo )
{
	if ( hi_lo == MRANGE_HI )
	{
		WI_StrLeftCopy ( input,output,mrang->GetRangeHI ( ) );
	}
	else
	{
		WI_StrLeftCopy ( input,output,mrang->GetRangeLO ( ) );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string range manipulation copy right range
void WI_StrCopyRightRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo )
{
	if ( hi_lo == MRANGE_HI )
	{
		WI_StrRightCopy ( input,output,mrang->GetRangeHI ( ) );
	}
	else
	{
		WI_StrRightCopy ( input,output,mrang->GetRangeLO ( ) );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// string range manipulation mid copy
void WI_StrCopyMidRange ( char* input,char* output,WI_StrRange* mrang, WI_Int hi_lo,WI_StrRange* mrangx, WI_Int hi_lox )
{
	WI_Int cx;
	WI_Int cy;

	if ( hi_lo == MRANGE_HI )
	{
		cx = mrang->GetRangeHI ( );
	}
	else
	{
		cx = mrang->GetRangeLO ( );
	}

	if ( hi_lox == MRANGE_HI )
	{
		cy = mrangx->GetRangeHI ( );
	}
	else
	{
		cy =mrangx->GetRangeLO ( );
	}

	WI_StrMidCopy ( input,output,cx,cy );
}



////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// create a list from string data
void WI_StrCreatestrList ( char* buff,char* search,WI_StrList* list )
{
	WI_Int occ;
	occ = WI_StrFindOccurance ( buff,search );

	if ( occ == -1 )
	{
		return; // failure
	}
	list->create ( occ );

	WI_Int occ_i = 0;

	WI_StrDataLoc dloc;

	if ( WI_StrFindLocation ( buff,search,&dloc ) )
	{
		WI_Int pre_pos = 0;

		for ( WI_Int z = 0; z < dloc.getmaxpoint ( ); z++ )
		{
			WI_Int cur = 0;
			cur = dloc.dindex[ z ];
			WI_Charwrap cwrap ( buff );
			cwrap.strclearn ( );
			WI_StrMidCopy ( buff, cwrap.get ( ), pre_pos, cur );
			list->strings[ occ_i ].set ( cwrap.get ( ) );
			occ_i++;
			pre_pos = cur;
		}

		WI_Charwrap cwrapx ( buff,true );
		WI_StrRightCopy ( buff,cwrapx.get ( ),pre_pos );
		list->strings[ occ_i ].set ( cwrapx.get ( ) );
		occ_i++;
	}

	return;
}

WI_StrDataLoc::WI_StrDataLoc ( )
{
	search_status = false;
	dindex = 0;
	array_size = 0;
	searchstr = 0;
}

WI_StrDataLoc::~WI_StrDataLoc ( )
{
	if ( dindex != 0 )
	{
		// WI_DELETE_PTR ( dindex );
	}

	if ( thestring != 0 )
	{
		// WI_DELETE_PTR ( thestring );
	}

	if ( searchstr != 0 )
	{
		// WI_DELETE_PTR ( searchstr );
	}
}

void WI_StrDataLoc::create_array ( WI_Int size )
{
	dindex = new WI_Int[ size ];
	array_size = size;
}

void WI_StrDataLoc::setstr ( char* buff )
{
	WI_Int len;
	len = strlen ( buff );
	thestring = new char[ len+1 ];
	WI_StrCopy ( thestring,buff );
}

void WI_StrDataLoc::setstatus ( bool x )
{
	search_status = x;
}

void WI_StrDataLoc::setsearchstr ( char* buff )
{
	WI_Int len;
	len = strlen ( buff );
	searchstr = new char[ len+1 ];
	WI_StrCopy ( searchstr,buff );
}

/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// return pointer to the string which the array holds data for
char* WI_StrDataLoc::getstr ( )
{
	return thestring;
}

char* WI_StrDataLoc::getsearchstr ( )
{
	return searchstr;
}

WI_Int WI_StrDataLoc::getarraysize ( )
{
	return array_size;
}

WI_Int WI_StrDataLoc::getstringpoint ( WI_Int index )
{
	if ( index <= array_size )
	{
		return dindex[ index ];
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// maximum string points for search
WI_Int WI_StrDataLoc::getmaxpoint ( )
{
	return array_size;
}

/////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------
// get status
bool WI_StrDataLoc::getstatus ( )
{
	return search_status;
}

bool WI_StrDataLoc::wassearchsuccesful ( )
{
	return getstatus ( );// was it successful?
}


////////////////////////////////////////////////////////////
//----------------------------------------------------------
// master string range structure
//----------------------------------------------------------
////////////////////////////////////////////////////////////
WI_StrRange::WI_StrRange ( )
{
	start_x = 0;
	stop_y = 0;
}

void WI_StrRange::SetRange ( WI_Int x, WI_Int y )
{
	start_x = x;
	stop_y = y;
}

WI_Int WI_StrRange::GetRangeX ( )
{
	return start_x;
}

WI_Int WI_StrRange::GetRangeY ( )
{
	return stop_y;
}

WI_Int WI_StrRange::GetRangeHI ( )
{
	return start_x;
}

WI_Int WI_StrRange::GetRangeLO ( )
{
	return stop_y;
}

void WI_StrRange::Clear ( )
{
	start_x = 0;
	stop_y = 0;
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string list
//----------------------------------------------------------
////////////////////////////////////////////////////////////
WI_StrList_String::WI_StrList_String ( )
{

}

WI_StrList_String::~WI_StrList_String ( )
{
	// WI_DELETE_PTR ( thestring );
}

void WI_StrList_String::set ( char* buff )
{
	WI_Int len;
	len = strlen ( buff ) + 1;
	thestring = new char[ len ];
	WI_StrCopy ( thestring,buff );
}

char* WI_StrList_String::get ( )
{
	return thestring;
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// string list , list handler structure
//----------------------------------------------------------
////////////////////////////////////////////////////////////
WI_StrList::~WI_StrList ( )
{
	// WI_DELETE_PTR ( strings );
}

WI_StrList::WI_StrList ( WI_Int list_size )
{
	create ( list_size );
}

WI_StrList::WI_StrList ( )
{
	list_size = 0;
	strings = NULL;
}

void WI_StrList::create ( WI_Int list_sizez )
{
	list_size = list_sizez;
	strings = new WI_StrList_String[ list_size ];
}

char* WI_StrList::getstr ( WI_Int index )
{
	return strings[ index ].get ( );
}

WI_Int WI_StrList::getcount ( )
{
	return list_size;
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// WI_Charwrap  easy to use char array,
// that automatically removes itself from freestore
//----------------------------------------------------------
////////////////////////////////////////////////////////////
WI_Charwrap::WI_Charwrap ( WI_Int size )
{
	str = new char[ size ];
}

WI_Charwrap::WI_Charwrap ( char* buff )
{
	set ( buff );
}

WI_Charwrap::WI_Charwrap ( char* buff,bool x )
{
	set ( buff );
	strclearn ( );
}

WI_Charwrap::~WI_Charwrap ( )
{
	// WI_DELETE_PTR ( str ); // delete that shit
}

void WI_Charwrap::set ( char* buff )
{
	WI_Int len;
	len = strlen ( buff ) + 1;
	str = new char[ len ];
	WI_StrCopy ( str,buff );
}

void WI_Charwrap::snew ( WI_Int size )
{
	str = new char[ size ];
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// clear off freestore
void WI_Charwrap::clear ( )
{
	// WI_DELETE_PTR ( str );

}

void WI_Charwrap::strclear ( )
{
	WI_Int len;
	len = WI_StrGetLength ( str );

	for ( WI_Int i = 0; i < len; i++ )
	{
		str[ i ] = 0;
	}
}

void WI_Charwrap::strclearn ( )
{
	WI_StrCopy ( str,"" );
}

char* WI_Charwrap::get ( )
{
	return str;
}

WI_Int WI_Charwrap::len ( )
{
	return WI_StrGetLength ( str );
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// structure of string manipulation algorithims to use
// for objects to inherit
//----------------------------------------------------------
////////////////////////////////////////////////////////////
void WI_StrObj::Copy ( char* input,char* output )
{
	WI_StrCopy ( input,output );
}

void WI_StrObj::Attach ( char* input,char* output )
{
	WI_StrAttach ( input,output );
}

void WI_StrObj::LeftCopy ( char* input,char* output,WI_Int pos )
{
	WI_StrLeftCopy ( input,output,pos );
}

void WI_StrObj::RightCopy ( char* input,char* output,WI_Int pos )
{
	WI_StrRightCopy ( input,output,pos );
}

void WI_StrObj::MidCopy ( char* input,char* output,WI_Int start_pos,WI_Int stop_pos )
{
	WI_StrMidCopy ( input,output,start_pos,stop_pos );
}

void WI_StrObj::Trim ( char* buff )
{
	WI_StrTrimSpace ( buff );
}

WI_Int WI_StrObj::Find ( char* buffer,char* search )
{
	return WI_StrFind ( buffer,search );
}

WI_Int WI_StrObj::Find ( WI_Int i, char* buffer,char* search )
{
	return WI_StrFindInside ( i,buffer,search );
}

WI_Int WI_StrObj::FindBody ( char* body, char* search )
{
	return WI_StrFindBackwards ( body,search );
}

WI_Int WI_StrObj::BackwardFindBody ( WI_Int startx,char* body,char* search )
{
	return WI_StrInsideFindBackwards ( startx,body,search );
}

WI_Int WI_StrObj::Search ( WI_Int start,WI_Int stop,char* buff,char* search )
{
	return WI_StrFind ( start,stop,buff,search );
}

WI_Int WI_StrObj::BackwardSearch ( WI_Int start, WI_Int stop,char* buff,char* search )
{
	return WI_StrBackwardRangeSearch ( start,stop,buff,search );
}

WI_Int WI_StrObj::GetLen ( char* buff )
{
	WI_Int len = 0;
	len = strlen ( buff );
	return len;
}

void WI_StrObj::ToLcase ( char* buffer )
{
	WI_StrToLowerCase ( buffer );
}

void WI_StrObj::ToUcase ( char* buffer )
{
	WI_StrToUpperCase ( buffer );
}

WI_Int WI_StrObj::ToUcaseLetter ( char c )
{
	return WI_StrToUpperCase ( c );
}

WI_Int WI_StrObj::ToLcaseLetter ( char c )
{
	return WI_StrToLowerCase ( c );
}

bool WI_StrObj::FindLocation ( char* buff,char* search,WI_StrDataLoc* dloc )
{
	return WI_StrFindLocation ( buff,search,dloc );
}

bool WI_StrObj::FindLocationForward ( char* buff, char* search, WI_StrDataLoc* dloc )
{
	return WI_StrFindLocationForward ( buff,search,dloc );
}

bool WI_StrObj::FindLocationBackwards ( char* buff,char* search,WI_StrDataLoc* dloc )
{
	return WI_StrFindLocationBackward ( buff,search,dloc );
}

bool WI_StrObj::SearchRange ( char* buff,char* search,WI_StrRange* mrang )
{
	return WI_StrSearchRange ( buff,search,mrang );
}

bool WI_StrObj::SearchRange ( WI_Int startx, char* buff,char* search,WI_StrRange* mrang )
{
	return WI_StrISearchRange ( startx,buff,search,mrang );
}

void WI_StrObj::CopyLeftRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo )
{
	WI_StrCopyLeftRange ( input,output,mrang,hi_lo );
}

void WI_StrObj::CopyRightRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo )
{
	WI_StrCopyRightRange ( input,output,mrang,hi_lo );
}

void WI_StrObj::CopyMidRange ( char* input,char* output,WI_StrRange* mrang,WI_Int hi_lo,WI_StrRange* mrangx,WI_Int hi_lox )
{
	WI_StrCopyMidRange ( input,output,mrang,hi_lo,mrangx,hi_lox );
}

WI_Int WI_StrObj::FindOccourance ( char* buffer,char* searchx )
{
	return WI_StrFindOccurance ( buffer,searchx );
}

void WI_StrObj::ConverToInteger ( WI_Int integer,char* buff,WI_Int base )
{
	WI_StrConvertIntToString ( integer,buff,base );
}

WI_Int WI_StrObj::ConverToInteger ( char* buff )
{
	return WI_StrConvertStringToInt ( buff );
}

bool WI_StrObj::IsHexc ( char c )
{
	return WI_StrIsHex ( c );
}

bool WI_StrObj::IsHex ( char* buff )
{
	return WI_StrIsHex ( buff );
}

WI_Int WI_StrObj::HexToInteger ( char c )
{
	return WI_StrIntToHex ( c );
}

WI_Int WI_StrObj::HexToInteger ( char* buff )
{
	return WI_StrHexToInt ( buff );
}

void WI_StrObj::TripDown ( char* buff,WI_Int by )
{
	WI_StrTripDown ( buff,by );
}

void WI_StrObj::TripUp ( char* buff, WI_Int by )
{
	WI_StrTripUp ( buff,by );
}

void WI_StrObj::Replace ( char* buff, char findchr, char replace )
{
	WI_StrReplaceChar ( buff,findchr,replace );
}

void WI_StrObj::Replace ( char* buff,char* findstr,char* replacex,char* output )
{
	WI_StrReplaceInside ( buff,findstr,replacex,output );
}

void WI_StrObj::RemoveSingleInstanceOf ( char* buff,char* findchr,char* re,char* out )
{
	WI_StrRemoveInstance ( buff,findchr,re,out );
}

char WI_StrObj::Random ( WI_Int max )
{
	return WI_StrRandom ( max );
}

char WI_StrObj::Random ( WI_Int max, WI_Int up )
{
	return WI_StrRandom ( max,up );
}

void WI_StrObj::Random ( char* buff,WI_Int max, WI_Int size )
{
	WI_StrRandom ( buff,max,size );
}

void WI_StrObj::Remove ( char* input,char* output,char c )
{
	WI_StrRemoveChar ( input,output,c );
}

char WI_StrObj::Find ( char* str,char c )
{
	return WI_StrFindCharForward ( str,c );
}

char WI_StrObj::FindInside ( WI_Int start,char* str,char c )
{
	return WI_StrFindCharForwardInside ( start,str,c );
}

char WI_StrObj::FindBackward ( char* str,char c )
{
	return WI_StrFindStrBackward ( str,c );
}

char WI_StrObj::FindBackward ( WI_Int start,char* str,char c )
{
	return WI_StrFindStrBackward ( start,str,c );
}

char WI_StrObj::FindForward ( char* str,WI_Int start,WI_Int stop,char c )
{
	return WI_StrFindChar ( str,start,stop,c );
}

char WI_StrObj::FindBackward ( char* str,WI_Int start,WI_Int stop,char c )
{
	return WI_StrFindCharBackward ( str, start, stop, c );
}

void WI_StrObj::Remove ( char* str,char* output,char* strsearch )
{
	WI_StrRremove ( str,output,strsearch );
}

void WI_StrObj::RemoveInstanceOf ( char* str,char* output,char* strx )
{
	WI_StrRremoveSingleInstance ( str,output,strx );
}

void WI_StrObj::SavestoFile ( char* filename,char* string )
{
	WI_StrSaveStringToFile ( filename,string );
}

bool WI_StrObj::LoadFomeFile ( char* filename,char* output )
{
	return WI_StrLoadFromFile ( filename,output );
}

WI_Int WI_StrObj::SetFileStrLength ( char* filename )
{
	return WI_StrGetFileStringLength ( filename );
}

void WI_StrObj::Reverse ( char* str_input,char* str_output )
{
	WI_StrReverses ( str_input,str_output );
}

bool WI_StrObj::IsValid ( char* str )
{
	return WI_StrIsValid ( str );
}

bool WI_StrObj::Compare ( char* buff1,char* buff2 )
{
	return WI_StrCompare ( buff1,buff2 );
}

bool WI_StrObj::CompareNoCase ( char* buff1,char* buff2 )
{
	return WI_StrCompareNoCase ( buff1,buff2 );
}

bool WI_StrObj::IsInside ( char* buff1,char* buff2 )
{
	return WI_StrIsInside ( buff1,buff2 );
}

bool WI_StrObj::IsInsideNoCase ( char* buff1,char* buff2 )
{
	return WI_StrIsInsideLowerCase ( buff1,buff2 );
}

void WI_StrObj::Separate ( char* str,char* lstr,WI_Int lpos,char* rstr,WI_Int rpos )
{
	WI_StrSeparate ( str,lstr,lpos,rstr,rpos );
}

WI_Int WI_StrObj::GetNullPos ( char* str )
{
	return WI_StrGetNullPos ( str );
}

void WI_StrObj::RemoveNull ( char* str )
{
	WI_StrRmvNull ( str );
}

void WI_StrObj::SetNullPos ( char* str, WI_Int pos )
{
	WI_StrSetNullPos ( str, pos );
}

void WI_StrObj::TrimComments ( char* input, char* output, char start_c, char stop_c )
{
	WI_StrTrimComments ( input, output, start_c, stop_c );
}
void WI_StrObj::TrimCommentsToAssembly ( char* input, char* output )
{
	WI_StrTrimCommentsToAssembly ( input, output );
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// the WI_String Object
//----------------------------------------------------------
////////////////////////////////////////////////////////////
WI_String::~WI_String()
{
	if ( str_on )
	{
		str_on = false;
	}

	str = NULL;

	array_size = 0;
}
////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// generic init string
WI_String::WI_String ( )
{
	str_on = false;
	array_size = 0;
	str = NULL;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// init a string in a %s %i %s... format
WI_String::WI_String ( const char *fmt, ... )
{
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// If There's No Text
	if( fmt == NULL )									
	{
		////////////////////////////////////////////////////////////
		// ---------------------------------------------------------
		// Do Nothing
		return;
	}

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// Holds Our CString
	char		text[ WI_MAX_SIZE ];
	
	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// Pointer To List Of Arguments
	va_list		ap;

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// Parses The char For Variables
	va_start ( ap, fmt);
		
		////////////////////////////////////////////////////////////
		// ---------------------------------------------------------
		// And Converts Symbols To Actual Numbers
		vsprintf ( text, fmt, ap );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// End parsing
	va_end ( ap );

	////////////////////////////////////////////////////////////
	// ---------------------------------------------------------
	// set the parsed text as this string
	set ( text );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// just allocate size for the string
WI_String::WI_String ( WI_Int size )
{
	set ( size, "" );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// set the internal string as a char*
WI_String::WI_String ( char* buff )
{
	WI_Int size = strlen ( buff ) + 2;
	set ( size, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// constructor set size of the string as int 
// and internal string as char cutting off at int
WI_String::WI_String ( WI_Int size, char* buff )
{
	set ( size, buff );
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// internal functions
//----------------------------------------------------------
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// sets the internal string as a char*
void WI_String::set ( char* buff )
{
	WI_Int size = strlen ( buff ) + 1;

	if ( str_on == false )
	{
		str = new char[ size ];
		str_on = true;
	}
	else
	{
		str = new char[ size ];
	}

	WI_StrCopy ( str, buff );
	array_size = size;
}

void WI_String::set ( WI_Int size, char* buff )
{
	if ( str_on == false )
	{
		str = new char[ size ];
		str_on = true;
	}
	else
	{
		str = new char[ size ];
	}

	WI_StrCopy ( str, buff );
	array_size = size;
}

void WI_String::SetChar ( WI_Int iPos, char c )
{
	str[ iPos ] = c;
}

void WI_String::add ( char* buff )
{

	char* strThis = new char[ WI_MAX_SIZE ];
	sprintf ( strThis, "%s%s", str, buff );
	set ( strThis );

/*
	WI_Int total_length = GetStringLength ( ) + strlen ( buff ) + 2;

	if ( total_length > GetStringLength ( ) )
	{
		char* ptemp;
		ptemp = new char[ GetStringLength ( ) +1 ];
		strcpy ( ptemp, str );

		str = new char[ total_length + 2 ];
		strcpy ( str, ptemp );
		strcpy ( str, buff );
	}
	else
	{
		strcat ( str, buff );
	}
*/
}

void WI_String::unset ( )
{
	if ( str_on == true )
	{
		// WI_DELETE_PTR ( str );
		str_on = false;
	}
}

char* WI_String::GetAsChar ( )
{
	return str;
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// gets the hex value of the internal string
WI_Int WI_String::GetHexValue ( )
{
	if ( WI_StrIsHex ( str ) )
	{
		return WI_StrIsHex ( str );
	}

	return -1;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// gets the double val of internal string
double WI_String::GetAsDouble ( )
{
	return atof ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// gets the decimal val of internal string
WI_Int WI_String::GetAsDesmal ( )
{
	return atof ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// converts string to int
WI_Int WI_String::GetAsInt ( )
{
	return atoi ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the string as a LPCSTR
LPCSTR WI_String::GetAsLPCSTR ( )
{
	char *strWord = new char[ array_size ];

	sprintf ( strWord, "%s", str );
	wchar_t *wText = new wchar_t[ array_size ];
	
	memset ( wText, 0, array_size );
	::MultiByteToWideChar ( CP_ACP, NULL, strWord, -1, wText, array_size );

	// WI_DELETE_PTR ( wText );

	return strWord;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the string as a LPWSTR
LPWSTR WI_String::GetAsLPWSTR ( )
{
	wchar_t* szWideArray = new wchar_t[ WI_MAX_SIZE ];
	
	mbstowcs ( szWideArray, str, GetStringLength ( ) );

	return szWideArray;
}
/*
////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// split string by a delimiter and returns an array
vector< char* > WI_String::SplitStringBy ( char* strDelm )
{
	vector< char* > szReturnVal;

	char* pch;
	
	pch = strtok ( str, strDelm );
	
	while (pch != NULL) 
	{
		szReturnVal.push_back ( pch );
		pch = strtok ( NULL, strDelm );
	}

	return szReturnVal;
}
*/
////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// encrypts/decrypts a string
void WI_String::EncryptDencrypt ( char* strKey )
{

	////////////////////////////////////////////////////////////
	//----------------------------------------------------------
	// this function encrypts twice, the first time with a hard 
	// coded key, the second with the user key so this encrypts
	// different than using WI_EncryprtDecryptString alone

	char* strNewText = new char[ strlen ( str ) + 1 ];
	sprintf (  strNewText, "%s", str );
	WI_EncryprtDecryptString ( "C@S3Y_IS_L3V3N_&_L3V3N_1S_G0D_H3R3", strNewText );

	char* strNewText2 = new char[ strlen ( strNewText ) + 1 ];
	sprintf (  strNewText2, "%s", str );
	WI_EncryprtDecryptString ( strKey, strNewText2 );
	set ( strNewText2 );
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// begin operators
//----------------------------------------------------------
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// operator =
WI_String WI_String::operator = ( char* buffer )
{
	// set
	WI_Int len;
	len = strlen ( buffer ) + 2;
	set ( len, buffer );
	return *this;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// operator += char*
WI_String WI_String::operator += ( char* buffer )
{
	add ( buffer );
	return *this;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// operator += int
WI_String WI_String::operator += ( WI_Int x )
{
	char buffer[ 30 ];

	_itoa ( x , buffer, 31 );

	add ( buffer );
	return *this;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// operator += long
WI_String WI_String::operator += ( WI_Long x )
{
	char buffer[ 30 ];
	_itoa ( x, buffer, 31 );
	add ( buffer );
	return *this;
}

////////////////////////////////////////////////////////////
//----------------------------------------------------------
// misc but useful functions

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the number of chars in the string
WI_Int WI_String::GetStringLength ( )
{
	return ( strlen ( str ) + 1 );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// gets the char pointer
char* WI_String::GetCharPointer ( )
{
	return str;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the char WI_Int pos of c
WI_Int WI_String::FindChar ( char c )
{
	return WI_StrFindCharForward ( str, c );
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the char WI_Int pos of c starting at WI_Int pre_pos
WI_Int WI_String::FindCharEx ( WI_Int pre_pos, char c )
{
	return WI_StrFindCharForwardInside ( pre_pos, str, c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the WI_Int pos of c from the end of the string
WI_Int WI_String::FindCharBackward ( char c )
{
	return WI_StrFindStrBackward ( str, c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the char WI_Int pos of c starting from the end WI_Int pre_pos
WI_Int WI_String::FindCharBackwardEx ( WI_Int pre_pos, char c )
{
	return WI_StrFindStrBackward ( pre_pos, str, c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_String::FindCharControledForward ( WI_Int start, WI_Int stop, char c )
{
	return WI_StrFindChar ( str, start, stop, c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_String::FindCharControledBackward ( WI_Int start, WI_Int stop, char c )
{
	return WI_StrFindCharBackward ( str, start, stop, c );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the WI_Int position of the char* if found
WI_Int WI_String::FindString ( char* search )
{
	return WI_StrFind ( str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the WI_Int position of the char* 
// if found starting from index
WI_Int WI_String::FindStringEx ( WI_Int index, char* search )
{
	return Find ( index, str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the int position of char* where search is starting
// at the end of the string
WI_Int WI_String::FindStringBackward ( char* search )
{
	return WI_StrFindBackwards ( str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the int pos in the string where char* is from the
// end of the internal string
WI_Int WI_String::FindStringBackwardEx ( WI_Int index, char* search )
{
	return WI_StrInsideFindBackwards ( index, str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// returns the int position in the string where char* is from the
// beginning of the internal string
WI_Int WI_String::FindOccourance ( char* search )
{
	return WI_StrFindOccurance ( str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// copies a char* to the end of a string
void WI_String::StringCopy ( char* buff )
{
	WI_StrCopy ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// attaches a char* to the end of the interal string
void WI_String::StringAttach ( char* buff )
{
	WI_StrAttach ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// resizes the internal string and cuts off the end
void WI_String::StringResize ( WI_Int newSize )
{
	char* ptemp;
	ptemp = new char [ strlen ( str ) + 1 ];
	strcpy ( ptemp, str );

	// WI_DELETE_PTR ( str );

	strcpy ( str, ptemp );

	// WI_DELETE_PTR ( ptemp );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::StringLeft ( char* output, WI_Int pos )
{
	WI_StrLeftCopy ( str, output, pos );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::StringRight ( char* output, WI_Int pos )
{
	WI_StrRightCopy ( str, output, pos );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::StringMid ( char* output, WI_Int x, WI_Int y )
{
	WI_StrMidCopy ( str, output, x, y );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// trim the white spaces off of the internal string
void WI_String::TrimSpace ( )
{
	WI_StrTrimSpace ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// converts the internal string to uppercase
void WI_String::UpperCase ( )
{
	WI_StrToUpperCase ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// converts the internal string to lowercase
void WI_String::LowerCase ( )
{
	WI_StrToLowerCase ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// extracts a char at index
char WI_String::ExtractChar ( WI_Int index )
{
	if ( index <= GetStringLength ( ) )
	{
		return str[ index ];
	}

	return 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_String::ForwardStringSearch ( WI_Int start, WI_Int stop, char* search )
{
	return WI_StrFind ( start, stop, str, search );
}


////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_String::BackwardStringSearch ( WI_Int start, WI_Int stop, char* search )
{
	return WI_StrBackwardRangeSearch ( start, stop, str, search );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::FindStringLocation ( char* search, WI_StrDataLoc* dloc )
{
	return WI_StrFindLocation ( str, search, dloc );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::FindStringLocationF ( char* search, WI_StrDataLoc* dloc )
{
	return WI_StrFindLocationForward ( str, search, dloc );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::FindStringLocationB ( char* search, WI_StrDataLoc* dloc )
{
	return WI_StrFindLocationBackward ( str, search, dloc );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::SearchRange ( char* search, WI_StrRange* mrang )
{
	WI_StrSearchRange ( str, search, mrang );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::SearchRangeEx ( WI_Int startx, char* search, WI_StrRange* mrang )
{
	WI_StrISearchRange ( startx, str, search, mrang );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::CopyLeftRange ( char* output, WI_StrRange* mrang, WI_Int hi )
{
	WI_StrCopyLeftRange ( str, output, mrang, hi );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::CopyRightRange ( char* output, WI_StrRange* mrang, WI_Int hi )
{
	WI_StrCopyRightRange ( str, output, mrang, hi );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::CopyMidRange ( char* output, WI_StrRange* mrang, WI_Int hi, WI_StrRange* mrangx, WI_Int hix )
{
	WI_StrCopyMidRange ( str, output, mrang, hi, mrangx, hix );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// is hex or not
bool WI_String::IsHex ( )
{
	return WI_StrIsHex ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// clears the current string
void WI_String::ClearString ( )
{
	for ( WI_Int z = 0; z < GetStringLength ( ); z++ )
	{
		str[ z ] = 0;
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// clears the string within a starting and an ending range
void WI_String::ClearStringRange ( WI_Int iStart, WI_Int iEnd )
{
	 for ( WI_Int i = iStart; i < iEnd; i++ )
	 {
		 str[ i ] = 0;
	 }
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// replaces a find char with replace in the string
void WI_String::ReplaceCharacter ( char findchr, char replace )
{
	WI_StrReplaceChar ( str, findchr, replace );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// generates a random string from 0 to 255
void WI_String::RandomizeString ( )
{
	WI_StrRandom ( str, 255, strlen ( str ) );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// generates a random string from 0 to iMaxChars
void WI_String::RandomizeString ( WI_Int iMaxChars )
{
	WI_StrRandom ( str, iMaxChars, strlen ( str ) );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// replaces search with replace string in the string
void WI_String::ReplaceString ( char* search, char* replacestr )
{
	if ( WI_StrFind ( str, search ) != -1 )
	{ 
		char* output = new char[ strlen ( str )+1 ];

		Replace ( str, search, replacestr, output );

		set ( output );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Removes the Character c from the string
void WI_String::RemoveCharacters ( char c )
{
	char* output;
	output = new char[ strlen ( str ) + 10 ];

	Remove ( str, output, c );
	set ( strlen ( output )+10,output );

	// WI_DELETE_PTR ( output );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// removes a char* from this string
void WI_String::RemoveString ( char* search )
{
	if ( Find ( str, search ) != -1 )
	{
		char* output;
		output = new char [ strlen ( str ) + 1 ];

		Remove ( str, output, search );

		set ( output );

		// WI_DELETE_PTR ( output );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// Remove a single instance of char*
void WI_String::RemoveSingleInstanceOfString ( char* search )
{
	if ( WI_StrFind ( str, search ) != -1 )
	{
		char* output;
		output = new char[ strlen ( str )+10 ];

		WI_StrRremoveSingleInstance ( str,output,search );
		set ( output );

		// WI_DELETE_PTR ( output );
	}
}

//////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------
// Compare with a char pointer
bool WI_String::Compare ( const char *strIn ) const
{ 
	if ( strcmp ( strIn, str ) )
	{ 
		// if it is then
		return false;
	}
	
	// if we got here then
	return true;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// saves the internal string as a file
void WI_String::SaveToFile ( char* filename )
{
	WI_StrSaveStringToFile ( filename, str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// loads a text file as a string
void WI_String::LoadStringFromFile ( char* filename )
{
	if ( WI_StrGetFileStringLength ( filename ) == -1 )
	{
		return; // failure file not found
	}

	char* temp;
	temp = new char[ WI_StrGetFileStringLength ( filename ) + 20 ];
	
	WI_StrLoadFromFile ( filename,temp );
	
	set ( strlen ( temp ) + 20, temp );
	
	// WI_DELETE_PTR ( temp );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::IsStringValid ( )
{
	return WI_StrIsValid ( str );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// reverse the string
void WI_String::ReverseString ( ) 
{
	char* temp;
	temp = new char[ GetStringLength ( )+10 ];

	WI_StrReverses ( str,temp );
	set ( strlen ( temp ) + 10, temp );

	// WI_DELETE_PTR ( temp );;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::StringCompare ( char* buff )
{
	return WI_StrCompare ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::StringCompare_NOCASE ( char* buff )
{
	return WI_StrCompareNoCase ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::IsInsideString ( char* buff )
{
	return WI_StrIsInside ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_String::IsInsideString_NOCASE ( char* buff )
{
	return WI_StrIsInsideLowerCase ( str, buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::SeperateString ( char* lbuff,WI_Int lpos,char* rbuff,WI_Int rpos )
{
	WI_StrSeparate ( str, lbuff, lpos, rbuff, rpos );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// trim string as tho it were assembly language source
void WI_String::AsmTrim ( )
{
	char* output;
	output = new char[ GetStringLength ( ) + 10 ];

	WI_StrTrimCommentsToAssembly ( str, output );
	set ( strlen ( output ) + 10, output );

	// WI_DELETE_PTR ( output );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_String::TrimComments ( char start_c,char stop_c )
{
	char* output = new char[ GetStringLength ( ) + 10 ];

	WI_StrTrimComments ( str, output, start_c, stop_c );

	set ( strlen ( output ) + 10, output );

	// WI_DELETE_PTR ( output );
}

WI_StringList::WI_StringList ( )
{
	ion = false;
	off = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_StringList::WI_StringList ( WI_Int size )
{
	createList ( size );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StringList::createList ( WI_Int size )
{
	item = new WI_StringItem[ size ];
	ion = true;
	array_size = size;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int  WI_StringList::GetArraySize ( )
{
	return array_size;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
char* WI_StringList::GetListStringPointerByIndex ( WI_Int index )
{
	return item[ index ].GetAsChar ( );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StringList::AddString ( char* buffer )
{
	item[ off ].set ( strlen ( buffer )+10,buffer );
	WI_Int xoff = off;
	off++;
	return xoff;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_StringList::GetListLength ( )
{
	return off;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StringList::GetString ( WI_Int index, char* output )
{
	strcpy ( output, item[ index ].GetAsChar ( ) );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_StringList::Clear ( )
{
	for ( WI_Int i = 0; i < off; i++ )
	{
		item[ i ].ClearString ( );
	}

	off = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Entry::WI_Entry ( )
{
	name = "";
	value = "";
	on_switch = false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_Entry::amion ( )
{
	return on_switch;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
// constructors/deconstructors
WI_INI::WI_INI ( )
{
	masEntry = 0;
	mas_on = false;
	off_count = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_INI::WI_INI ( WI_Int size )
{
	set ( size );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_INI::~WI_INI ( )
{
	if ( mas_on )
	{
		// WI_DELETE_PTR ( masEntry );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_INI::set ( WI_Int size )
{
	if ( mas_on == true )
	{
		// WI_DELETE_PTR ( masEntry );
	}

	masEntry = new WI_Entry[ size ];
	mas_on = true;
	array_size = size;
	off_count = 0;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_INI::getsize ( )
{
	return array_size;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_INI::Create ( WI_Int size )
{
	set ( size );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_INI::AddEntry ( char* name,char* value )
{
	if ( off_count < getsize ( ) )
	{
		masEntry[ off_count ].name = name;
		masEntry[ off_count ].value = value;
		masEntry[ off_count ].list_index = off_count;

		off_count++;
		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
bool WI_INI::GetEntry ( char* name,char* output_value )
{
	for ( WI_Int i = 0; i < getsize ( ); i++ )
	{
		if ( WI_StrFind ( masEntry[ i ].name.GetAsChar ( ), name ) != -1 )
		{
			WI_StrCopy ( output_value, masEntry[ i ].value.GetAsChar ( ) );
			return true;
		}
	}

	strcpy_s ( output_value,8, "*NULL*" );
	return false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_CharList::WI_CharList ( )
{
	list = 0;
	list_on = false;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_CharList::WI_CharList ( char* buff )
{
	BuildList ( buff );
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_CharList::~WI_CharList ( )
{
	if ( list_on == true )
	{
		// WI_DELETE_PTR ( list );
	}
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
void WI_CharList::BuildList ( char* buff )
{
	WI_Int size;
	size = WI_StrCountLines ( buff ) + 1;
	list = new WI_String[ size ];
	list_on = true;
	array_size = size;

	////////////////////////////////////////////////////////////
	// format the characters into this array
	WI_Int pre_pos = 0;
	WI_Int acount = 0;

	while ( 1 )
	{
		WI_Int find_x;
		find_x = WI_StrFindInside ( pre_pos,buff,"\n" );
		
		if ( find_x == -1 )
		{
			break;// all done !
		}

		
		char* temp;
		temp = new char[ strlen ( buff ) + 1 ];

		WI_StrMidCopy ( buff, temp, pre_pos, find_x );
		pre_pos = find_x;
	
		// add
		list[ acount ] = temp;
		acount++;

		// WI_DELETE_PTR ( temp );
		temp = 0;
	}
	list_len = acount;

}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_Int WI_CharList::GetLength ( )
{
	return list_len;
}

////////////////////////////////////////////////////////////
// ---------------------------------------------------------
WI_String* WI_CharList::GetWI_String ( WI_Int index )
{
	return ( WI_String* )&list[ index ];
}