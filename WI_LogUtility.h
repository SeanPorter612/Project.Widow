#pragma once

#ifndef __WI_LOG__
#define __WI_LOG__

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// the kinds of files the log can be saved as
#define		WI_HTML_LOG_FILE		10800
#define		WI_XML_LOG_FILE			10801
#define		WI_TXT_LOG_FILE			10802

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// initialize the log file
bool WI_InitLog ( WI_String szLogName = WI_String ( "Wi_Log" ), WI_Int iLogType = WI_TXT_LOG_FILE );


/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// will append a log file
bool			WI_AppendToLog ( WI_String szEvent, WI_String szText );

/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// will GetAsChar the current log and return it as a string
WI_String		WI_GetLog ( );

/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// GetAsChars the name of the log file
WI_String		WI_GetLogFileName ( );


/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// quick macros for common log entries


/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// fatal error

//#if defined _MSC_VER
//
//	#define _WI_ERR_MSG_DE			sprintf();
//
//#elif
//	#define _WI_ERR_MSG_DE
//
//#endif

#pragma message ( "		Widow logging system complete..." )
#endif