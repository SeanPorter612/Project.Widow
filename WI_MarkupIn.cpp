#include "Globals.h"	

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// TiniXml globals for out used here bec they are non public
TiXmlDocument		g_docIn;
TiXmlDeclaration*	g_declIn;

TiXmlElement*		g_pElem;
TiXmlHandle			g_hRoot ( 0 );

WI_MarkupIn::WI_MarkupIn( WI_String szFileName, WI_String szRootNode )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// cheak to see if the file is really there or not
	if ( WI_FileExists ( szFileName ) == true )
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// save the file name
		m_szFileName = szFileName;

		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// if we could not load the document
		if ( g_docIn.LoadFile ( m_szFileName.GetAsChar ( ) ) == false )
		{
			///////////////////////////////////////////////////////////////////////////
			//------------------------------------------------------------------------
			// display the error
			WI_MsgBox ( "Invalid markup document" );

			///////////////////////////////////////////////////////////////////////////
			//------------------------------------------------------------------------
			// delete this object
			delete this;
		}
		else
		{
			///////////////////////////////////////////////////////////////////////////
			//------------------------------------------------------------------------
			// get the name of the root node
			GetRootNodeName ( szRootNode );
		}
	}
	else
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// display the error
		WI_MsgBox ( "could not load markup document" );
		
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// remove this object
		delete this;
	}
}

WI_MarkupIn::~WI_MarkupIn ( void )
{
	if ( g_pElem )
		delete g_pElem;
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// gets the name of the root node
void WI_MarkupIn::GetRootNodeName ( WI_String szRootNode )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the first element in the document
	g_pElem = g_docIn.FirstChildElement ( szRootNode.GetAsChar ( ) );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// should always have a valid root but handle gracefully if it does
	if ( !g_pElem )
	{
		delete this;
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// save the name of the root node
	m_szRootNodeName = WI_String ( g_pElem->Value ( ) );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// save this for later
	g_hRoot = TiXmlHandle ( g_pElem );
}

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// gets a string attribute from a node
WI_String WI_MarkupIn::GetStringAttribute ( WI_String szNodeName, WI_String szAttributeName )
{
	WI_String szRetunThis;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node we want to look at
	TiXmlElement* pNode = g_hRoot.FirstChild ( szNodeName.GetAsChar ( ) ).Element ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the return value as the value of the string attribute
	szRetunThis = WI_String ( pNode->Attribute ( szAttributeName.GetAsChar ( ) ) );

	return szRetunThis;
}

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// gets a WI_Int attribute from a node
WI_Int WI_MarkupIn::GetIntAttribute ( WI_String szNodeName, WI_String szAttributeName )
{
	WI_Int iReturnThis;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node we want to look at
	TiXmlElement* pNode = g_hRoot.FirstChild ( szNodeName.GetAsChar ( ) ).Element ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node attribute value by name
	pNode->QueryIntAttribute ( szAttributeName.GetAsChar ( ), &iReturnThis );

	return iReturnThis;
}

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// gets a WI_Double attribute from a node
WI_Double WI_MarkupIn::GetDoubleAttribute ( WI_String szNodeName, WI_String szAttributeName )
{
	WI_Double nReturnthis;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node we want to look at
	TiXmlElement* pNode = g_hRoot.FirstChild ( szNodeName.GetAsChar ( ) ).Element ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node attribute value by name
	pNode->QueryDoubleAttribute ( szAttributeName.GetAsChar ( ), &nReturnthis );

	return nReturnthis;
}


///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// gets a WI_Double attribute from a node
WI_Float WI_MarkupIn::GetFloatAttribute ( WI_String szNodeName, WI_String szAttributeName )
{
	WI_Float fReturnthis;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node we want to look at
	TiXmlElement* pNode = g_hRoot.FirstChild ( szNodeName.GetAsChar ( ) ).Element ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node attribute value by name
	pNode->QueryFloatAttribute ( szAttributeName.GetAsChar ( ), &fReturnthis );

	return fReturnthis;
}

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// get the text inside a node
WI_String WI_MarkupIn::GetNodeText ( WI_String szNode )
{
	WI_String szRetunThis;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// get the node we want to look at
	TiXmlElement* pNode = g_hRoot.FirstChild ( szNode.GetAsChar ( ) ).Element ( );

	szRetunThis = WI_String ( pNode->GetText ( ) );

	return szRetunThis;
}