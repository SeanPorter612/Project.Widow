#include "Globals.h"	

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// TiniXml globals for out used here bec they are non public
TiXmlDocument		g_docOut;
TiXmlDeclaration*	g_declOut				=	NULL;

TiXmlElement*		g_rootOut				=	NULL;
TiXmlElement*		g_childOut				=	NULL;
TiXmlElement*		g_siblingOut			=	NULL;
TiXmlElement*		g_childSiblingOut		=	NULL;

///////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
// constructor with file name
WI_MarkupOut::WI_MarkupOut ( WI_String szFileName, WI_String szRootNodeName )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// create a new markup object and init the root node
	CreateNew ( szFileName, szRootNodeName );
}


WI_MarkupOut::~WI_MarkupOut ( void )
{
	if ( g_declOut )
		delete g_declOut;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is a root element
	if ( g_rootOut )
		delete g_rootOut;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is a child element
	if ( g_childOut )
		delete g_childOut;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is a sybling element
	if ( g_siblingOut )
		delete g_siblingOut;

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is a child sybling element
	if ( g_childSiblingOut )
		delete g_childSiblingOut;
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// makes a new markup object and sets the root node
void WI_MarkupOut::CreateNew ( WI_String szFileName, WI_String szRootNodeName )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the file name so it can be saved later
	m_szFileName = szFileName;

	g_docOut.Clear ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// start a new xml document
	g_declOut = new TiXmlDeclaration ( "1.0", "", "" );
	g_docOut.LinkEndChild ( g_declOut );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// create the root node of the document
	g_rootOut = new TiXmlElement ( szRootNodeName.GetAsChar ( ) );  
	g_docOut.LinkEndChild ( g_rootOut ); 
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// saves the markup document to disk
void WI_MarkupOut::Save ( )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// save the current XML ducument to disk
	g_docOut.SaveFile ( m_szFileName.GetAsChar ( ) );
}

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// child node functions
	//--------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a child node to the current root node
void WI_MarkupOut::AddChildNode ( WI_String szNodeName )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_rootOut )
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// display error message and exit function
		WI_MsgBox ( "No root node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set a new child element and name it name
	g_childOut = new TiXmlElement ( szNodeName.GetAsChar ( ) );  
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// link the child elemt to the root element
	g_rootOut->LinkEndChild ( g_childOut );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a string attribute name value pair
void WI_MarkupOut::SetChildAttribute ( WI_String szName, WI_String szAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_childOut )
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// display error message and exit function
		WI_MsgBox ( "No child node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// Set string attribute to the child node
	g_childOut->SetAttribute ( szName.GetAsChar ( ), szAttribute.GetAsChar ( ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair
void WI_MarkupOut::SetChildAttribute ( WI_String szName, WI_Int iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_childOut )
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// display error message and exit function
		WI_MsgBox ( "No child node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// Set string attribute to the child node
	g_childOut->SetAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair
void WI_MarkupOut::SetChildDoubleAttribute ( WI_String szName, WI_Double iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_childOut )
	{
		///////////////////////////////////////////////////////////////////////////
		//------------------------------------------------------------------------
		// display error message and exit function
		WI_MsgBox ( "No child node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// Set string attribute to the child node
	g_childOut->SetDoubleAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// sets the text of the child node
void WI_MarkupOut::SetChildText ( WI_String szText )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no child node
	if ( !g_childOut )
	{
		WI_MsgBox ( "No child node" );
		return;
	}
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the element text to this node
	g_childOut->LinkEndChild ( new TiXmlText( szText.GetAsChar ( ) ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a comment to the document
void WI_MarkupOut::AddChildComment ( WI_String szComment )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_rootOut )
	{
		WI_MsgBox ( "No root node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make a new comment object
	TiXmlComment* comment = new TiXmlComment ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the value of the comment
	comment->SetValue ( szComment.GetAsChar ( ) );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	g_rootOut->LinkEndChild( comment ); 
}

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// sibling node functions
	//--------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a sibling node to the current child node
void WI_MarkupOut::AddSybling ( WI_String szNodeName )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no child node to set attributes to
	if ( !g_childOut )
	{
		WI_MsgBox ( "No child node to add a sybling to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set a new child element and name it name
	g_siblingOut = new TiXmlElement ( szNodeName.GetAsChar ( ) );  
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// link the child elemt to the root element
	g_childOut->LinkEndChild ( g_siblingOut );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a string attribute name value pair to the current sybling node
void WI_MarkupOut::SetSyblingAttribute ( WI_String szName, WI_String szAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_siblingOut->SetAttribute ( szName.GetAsChar ( ), szAttribute.GetAsChar ( ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair to the current sybling node
void WI_MarkupOut::SetSyblingAttribute ( WI_String szName, WI_Int iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_siblingOut->SetAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair to the current sybling node
void WI_MarkupOut::SetSyblingDoubleAttribute ( WI_String szName, WI_Double iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_siblingOut->SetDoubleAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// sets the text of the child node
void WI_MarkupOut::SetSyblingText ( WI_String szText )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no child node
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No child node" );
		return;
	}
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the element text to this node
	g_siblingOut->LinkEndChild ( new TiXmlText( szText.GetAsChar ( ) ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a comment to the document
void WI_MarkupOut::AddSyblingComment ( WI_String szComment )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_childOut )
	{
		WI_MsgBox ( "No child node cant add comment" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make a new comment object
	TiXmlComment* comment = new TiXmlComment ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the value of the comment
	comment->SetValue ( szComment.GetAsChar ( ) );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	g_childOut->LinkEndChild( comment ); 
}

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// child sibling node functions
	//--------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a sibling node to the current child node
void WI_MarkupOut::AddChildSybling ( WI_String szNodeName )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no child node to set attributes to
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No child node to add a sybling to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set a new child element and name it name
	g_childSiblingOut = new TiXmlElement ( szNodeName.GetAsChar ( ) );  
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// link the child elemt to the root element
	g_siblingOut->LinkEndChild ( g_childSiblingOut );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a string attribute name value pair to the current child node
void WI_MarkupOut::SetChildSyblingAttribute ( WI_String szName, WI_String szAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_childSiblingOut )
	{
		WI_MsgBox ( "No child sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_childSiblingOut->SetAttribute ( szName.GetAsChar ( ), szAttribute.GetAsChar ( ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair to the current child node
void WI_MarkupOut::SetChildSyblingAttribute ( WI_String szName, WI_Int iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_childSiblingOut )
	{
		WI_MsgBox ( "No child sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_childSiblingOut->SetAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// set a number attribute name value pair to the current child node
void WI_MarkupOut::SetChildSyblingDoubleAttribute ( WI_String szName, WI_Double iAttribute )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make shore there is a sybling node if not display error and exit function
	if ( !g_childSiblingOut )
	{
		WI_MsgBox ( "No child sybling node to add attribute to" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set attribute to the node
	g_childSiblingOut->SetDoubleAttribute ( szName.GetAsChar ( ), iAttribute );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// sets the text of the child node
void WI_MarkupOut::SetChildSyblingText ( WI_String szText )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no child node
	if ( !g_childSiblingOut )
	{
		WI_MsgBox ( "No child node" );
		return;
	}
	
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the element text to this node
	g_childSiblingOut->LinkEndChild ( new TiXmlText( szText.GetAsChar ( ) ) );
}

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// adds a comment to the document
void WI_MarkupOut::AddChildSyblingComment ( WI_String szComment )
{
	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// if there is no root node
	if ( !g_siblingOut )
	{
		WI_MsgBox ( "No root node" );
		return;
	}

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// make a new comment object
	TiXmlComment* comment = new TiXmlComment ( );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	// set the value of the comment
	comment->SetValue ( szComment.GetAsChar ( ) );

	///////////////////////////////////////////////////////////////////////////
	//------------------------------------------------------------------------
	g_siblingOut->LinkEndChild( comment ); 
}
