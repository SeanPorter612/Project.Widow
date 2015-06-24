#pragma once

#ifndef __WI_Date__
#define __WI_Date__

#ifndef __WI_CommonDef__
	#include "WI_Config.h"
#endif

class WIDOWLYTE_API WI_Date
{

private:
	WI_Int m_nYear;
	WI_Int m_nMonth;
	WI_Int m_nDay; 

	WI_Int m_nOldYear;
	WI_Int m_nOldMonth;
	WI_Int m_nOldDay;

public:
		// constrcutors
		WI_Date ( );
		WI_Date ( WI_String date );
		WI_Date ( WI_Int d, WI_Int m, WI_Int y );

		// set value functions
		void setDate ( WI_String date );
		void setYear ( WI_Int y );
		void setMonth ( WI_Int m );
		void setDay ( WI_Int d );

		// get functions
		WI_Int getYear ( );
		WI_Int getMonth ( );
		WI_Int getDay ( );    
		WI_String getShortMonth ( );
		WI_String getFullMonth ( WI_String ret );		
		WI_String getDate ( );
		WI_String getDate ( WI_String format );

		// arithmetic functions
		void addDays	( WI_Int d );
		void addMonths	( WI_Int m );
		void addYears	( WI_Int y );		
		void lessDays	( WI_Int d );
		void lessMonths ( WI_Int m );
		void lessYears	( WI_Int y );

		string differenceInDays		( WI_Date DateFrom, WI_Date DateTo );
		WI_Int differenceInMonths	( WI_Date d );
		WI_Int differenceInYears	( WI_Date d );
		
		// operators
		bool operator >		 ( WI_Date d );
		bool operator < 	 ( WI_Date d );
		bool operator ==	 ( WI_Date d );
		bool operator !=	 ( WI_Date d );
		void operator =		 ( WI_Date d );
		void operator =		 ( char* c );
		
		// utilities		
		bool isLeapYear ( );

private:
		void validate ( );
		WI_Int getDaysInMonth ( );
		void correctDays ( );
		void restore ( );	
};

class WIDOWLYTE_API WI_DateException
{
private:
		WI_String m_strErr;
	
public:
		WI_DateException ( ) 
		{ m_strErr = ""; }
		
		WI_DateException ( WI_String s )
		{ m_strErr = WI_String ( s.GetAsChar ( ) ); }		
		
		WI_String getMessage ( )
		{ return m_strErr; }
	
protected:

		void setMessage ( WI_String s )
		{ m_strErr = WI_String ( s.GetAsChar ( ) ); }
};

#pragma message ( "		Widow date class complete..." )
#endif

