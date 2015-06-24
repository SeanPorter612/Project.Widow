#include "LyteGlobals.h"

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// assuming this is an HTML logging even we are going 
// to have the first row shaded
bool g_bShadeRow = true;

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// no file name as of yet
WI_String		g_szLogFileName;

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// the type of log file that is being kept
WI_Int			g_iLogType					=				0;

/////////////////////////////////////////////////////////////////////////
// ----------------------------------------------------------------------
// initialize the log file
bool WI_InitLog ( WI_String szLogName, WI_Int iLogType )
{
	if ( !szLogName.GetAsChar() )
		return false;

	g_iLogType = iLogType;

	/////////////////////////////////////////////////////////////////////////
	// ----------------------------------------------------------------------
	// file pointer
	FILE* FP;

	/////////////////////////////////////////////////////////////////////////
	// ----------------------------------------------------------------------
	// record the kind of log this is 
	if ( g_iLogType == WI_TXT_LOG_FILE )
	{

		g_szLogFileName = WI_String ( "%s.txt", szLogName.GetAsChar ( ) );

		/////////////////////////////////////////////////////////////////////////
		// ----------------------------------------------------------------------
		// open the file for writing
		FP = fopen ( g_szLogFileName.GetAsChar ( ) , "w" );

		if ( !FP )
			return false;

		/////////////////////////////////////////////////////////////////////////
		// ----------------------------------------------------------------------
		// the first line is data about these handful of function
		fprintf ( FP , "Widow's event logging system v2.9 text file output\n" );

		/////////////////////////////////////////////////////////////////////////
		// ----------------------------------------------------------------------
		// close the file
		fclose ( FP );

		/////////////////////////////////////////////////////////////////////////
		// ----------------------------------------------------------------------
		// yes we do have a log file
		return true;
	}
	else if ( g_iLogType == WI_HTML_LOG_FILE )
	{
		g_szLogFileName = WI_String ( "%s.html", szLogName.GetAsChar ( ) );

		FP = fopen ( g_szLogFileName.GetAsChar ( ) , "w" );

		if ( !FP )
			return false;

			fprintf ( FP , "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" );
			fprintf ( FP , "<html xmlns=\"http://www.w3.org/1999/xhtml\">" );
			fprintf ( FP , "<head>" );
			fprintf ( FP , "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />" );
			fprintf ( FP , "<title>Widow HTML Log file</title>" );
			fprintf ( FP , "<body bgcolor=\"#000000\" text=\"#FFFFFF\">" );
			fprintf ( FP , "<center>" );
			fprintf ( FP , "<table width=\"800\" border=\"0\" cellspacing=\"1\" cellpadding=\"1\">" );
			fprintf ( FP , "  <tr>" );
			fprintf ( FP , "    <th colspan=\"2\" bgcolor=\"#999999\" scope=\"col\"><h1>Widow's event logging system v2.5 HTML file version</h1></th>" );
			fprintf ( FP , "    </tr>" );
			fprintf ( FP , "  <tr>" );
			fprintf ( FP , "    <th width=\"20%\" align=\"center\" valign=\"top\" bgcolor=\"#999999\" scope=\"row\">event</th>" );
			fprintf ( FP , "    <th width=\"80%\" align=\"center\" valign=\"top\" bgcolor=\"#999999\">Log</th>" );
			fprintf ( FP , "  </tr>" );

			fclose ( FP );

			return true;
	}
	else if ( g_iLogType == WI_XML_LOG_FILE )
	{
		g_szLogFileName = WI_String ( "%s.xml", szLogName.GetAsChar ( ) );

		FP = fopen ( g_szLogFileName.GetAsChar ( ) , "w" );

		if ( !FP )
			return false;


		fclose ( FP );
	}
	else
	{
		return false;
	}

	return false;
}

bool WI_AppendToLog ( WI_String szEvent , WI_String szText )
{
	if ( !g_szLogFileName.GetAsChar ( ) )
	return false;

	/////////////////////////////////////////////////////////////
	// local file pointer
	FILE *FP = fopen ( g_szLogFileName.GetAsChar ( ) , "a+" );

	if ( !FP )
		return false;

	if ( g_iLogType == WI_TXT_LOG_FILE )
	{
		fprintf ( FP ,
				  "Event type: %s\nEvent description: %s\n\n\n" ,
				  szEvent.GetAsChar ( ) ,
				  szText.GetAsChar ( ) );

		fclose ( FP );
		return true;
	}
	else if ( g_iLogType == WI_HTML_LOG_FILE )
	{
		/////////////////////////////////////////////////////////////
		// start a new table row
		fprintf ( FP , "<tr>" );

		/////////////////////////////////////////////////////////////
		// to have or not to have a bg color
		if ( g_bShadeRow == true )
		{
			g_bShadeRow = false;
			fprintf ( FP , "<td align=\"left\" valign=\"top\" bgcolor=\"#000099\" scope=\"row\">%s</td>" , szEvent.GetAsChar ( ) );
			fprintf ( FP , "<td align=\"left\" valign=\"top\" bgcolor=\"#000099\">%s</td>" , szText.GetAsChar ( ) );
			//fprintf ( FP, "<td bgcolor='#00CCFF'>%s</td>\n", szText.GetAsChar ( ) );
		}
		else
		{
			g_bShadeRow = true;
			fprintf ( FP , "<td align=\"left\" valign=\"top\" bgcolor=\"#000066\" scope=\"row\">%s</td>" , szEvent.GetAsChar ( ) );
			fprintf ( FP , "<td align=\"left\" valign=\"top\" bgcolor=\"#000066\">%s</td>" , szText.GetAsChar ( ) );
			//fprintf_s ( FP, "<td bgcolor='#CCCCCC'>%s</td>\n", szText.GetAsChar ( ) );
		}

		/////////////////////////////////////////////////////////////
		// end this row
		fprintf ( FP , "</tr>\n" );	

		fclose ( FP );
		return true;
	}
	else if ( g_iLogType == WI_HTML_LOG_FILE )
	{	
		fclose ( FP );
		return true;
	}
	else
	{
		fclose ( FP );
		return false;
	}

	return false;
}

WI_String WI_GetLogFileName ( )
{
	return WI_String ( g_szLogFileName );
}

WI_String	WI_GetLog ( )
{
	/////////////////////////////////////////////////////////////
	// a temp buffer to process before inserting into the final string
	string strBuffer; 

	WI_String szReturnThis = WI_String ( "Widow Log v3.2" );

	/////////////////////////////////////////////////////////////
	// the file stream
	fstream  FS;

	/////////////////////////////////////////////////////////////
	// open this file for reading
	FS.open ( g_szLogFileName.GetAsChar ( ) );		// file stream for what we are reading in

	/////////////////////////////////////////////////////////////
	// Check to make sure we have a valid file
	if ( FS.is_open ( ) == false ) 
	{

		/////////////////////////////////////////////////////////////
		// close the file, we can't go on 
		FS.close ( );

		/////////////////////////////////////////////////////////////
		// return false. We are done
		return "Something is wrong with the Widow Log file";
	}

	/////////////////////////////////////////////////////////////
	// while not End Of File
	while ( !FS.eof ( ) )
	{

		/////////////////////////////////////////////////////////////
		// read in this line
		getline ( FS , strBuffer );
	}

	szReturnThis += ( ( char* ) strBuffer.c_str ( ) );

	FS.close ( );

	return szReturnThis;
}

/////////////////////////////////////////////////////////////////////////
// -------------------------------------------------------------------
// closes the data
void WI_KillLog ( )
{
	WI_String szEvent = "Kill log";
	WI_String szMsg		= "Shutting down widow's logging system";

	if ( g_iLogType == WI_TXT_LOG_FILE )
	{
		WI_AppendToLog ( szEvent, szMsg );
	}
	if ( g_iLogType == WI_HTML_LOG_FILE )
	{
		WI_AppendToLog ( szEvent, szMsg );

		FILE* FP;
		FP = fopen ( g_szLogFileName.GetAsChar ( ) , "a" );

		fprintf ( FP , "</table></center></body></html>" );

		fclose ( FP );
	}
	else if ( g_iLogType == WI_XML_LOG_FILE )
	{
		WI_AppendToLog ( szEvent, szMsg );

		FILE* FP;
		FP = fopen ( g_szLogFileName.GetAsChar ( ) , "a" );

		fprintf ( FP , "</LOG_ROOT>" );

		fclose ( FP );
	}
}