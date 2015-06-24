#include "stdafx.h"

struct tXmlData
{
	tinyxml2::XMLDocument*	m_pDoc;
	tinyxml2::XMLElement*	m_pRoot;
	tinyxml2::XMLElement*	m_pElement;
	tinyxml2::XMLElement*	m_pItemElement;
	tinyxml2::XMLText*		m_pText;
	tinyxml2::XMLNode*		m_pNode;
};


tXmlData g_XmlData;

WI_Markup::WI_Markup( const char* XmlData )
{
	m_szMarkupData = XmlData;

	g_XmlData.m_pDoc = new tinyxml2::XMLDocument ( m_szMarkupData.GetAsChar ( ) );
	g_XmlData.m_pDoc->Parse ( m_szMarkupData.GetAsChar ( ) );
}

WI_Markup::WI_Markup ( WI_String szFileName )
{
	LoadMarkupFile ( szFileName );
}

WI_Markup::WI_Markup ( void )
{
	g_XmlData.m_pDoc = new tinyxml2::XMLDocument ( );
}

WI_Markup::~WI_Markup(void)
{
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// loads a markup file in to memory returns error message
WI_Int WI_Markup::LoadMarkupFile ( WI_String szFileName )
{
	m_szMarkupData.LoadStringFromFile ( szFileName.GetAsChar ( ) );

	g_XmlData.m_pDoc = new tinyxml2::XMLDocument ( m_szMarkupData.GetAsChar ( ) );
	g_XmlData.m_pDoc->Parse ( m_szMarkupData.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}	 

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// get node and element data
//---------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// get the number value in a child node by its element name 
// returns the value of the element
// pram ( WI_String szRoot = name of the root node,
//        WI_String szChild = child node with the element, 
//        WI_String szElement = name of the element to get the value from )
WI_Double WI_Markup::GetElementNumVal ( WI_String szRoot, WI_String szChild, WI_String szElement )
{
	if (!g_XmlData.m_pDoc)
		return -1;

	WI_Double v0 = 0;

	tinyxml2::XMLElement* attributeElement = g_XmlData.m_pDoc->FirstChildElement ( szRoot.GetAsChar ( ) )->FirstChildElement( szChild.GetAsChar ( ) );
	attributeElement->QueryAttribute ( szElement.GetAsChar ( ), &v0 );

	return v0;
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// get the number value in a child node by its element name 
// returns the value of the element
// pram ( WI_String szRoot = name of the root node,
//        WI_String szChild = child node with the element, 
//        WI_String szElement = name of the element to get the value from )
WI_String WI_Markup::GetElementStrVal ( WI_String szRoot, WI_String szChild, WI_String szElement )
{
	if (!g_XmlData.m_pDoc)
		return -1;

	tinyxml2::XMLElement* attributeElement = g_XmlData.m_pDoc->FirstChildElement ( szRoot.GetAsChar ( ) )->FirstChildElement( szChild.GetAsChar ( ) )->FirstChildElement ( szElement.GetAsChar ( ) );
	const char* v0 = attributeElement->GetText ( );

	return WI_String ( v0 );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// gets the text inside the child node returns WI_String value of the text
// pram	( WI_String szRoot = name of the root node, 
//        WI_String szChild = the name of child node to get the text value from  )
WI_String WI_Markup::GetChildNodeText ( WI_String szRoot, WI_String szChild )
{
	
	tinyxml2::XMLElement* text = g_XmlData.m_pDoc->FirstChildElement( szRoot.GetAsChar ( ) );//->FirstChildElement( "textApproach" );
	
	const char* strValue = text->FirstChildElement( szChild.GetAsChar ( ) )->GetText  ( );
	
	return WI_String ( strValue );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// gets the text inside the child node returns WI_String value of the text
// pram	( WI_String szRoot = name of the root node, 
//        WI_String szChild = the name of child node to get the text value from  
//        WI_String szInnerChild = the name of the inner child node to get the text from )
WI_String WI_Markup::GetInnerChildNodeText ( WI_String szRoot, WI_String szChild,  WI_String szInnerChild )
{
	
	tinyxml2::XMLElement* text = g_XmlData.m_pDoc->FirstChildElement( szRoot.GetAsChar ( ) )->FirstChildElement( szChild.GetAsChar ( ) );
	
	const char* strValue = text->FirstChildElement( szInnerChild.GetAsChar ( ) )->GetText  ( );
	
	return WI_String ( strValue );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// get the number value in a child node by its element name 
// returns the value of the element
// pram ( WI_String szRoot = name of the root node,
//        WI_String szChild = child node with the element, 
//		  WI_String szInnerChild = the name of the inner child node to get the element value from
//        WI_String szElement = name of the element to get the value from )
WI_Double WI_Markup::GetElementNumVal ( WI_String szRoot, WI_String szChild, WI_String szInnerChild, WI_String szElement )
{
	if (!g_XmlData.m_pDoc)
		return -1;

	WI_Double v0 = 0;

	tinyxml2::XMLElement* attributeElement = g_XmlData.m_pDoc->FirstChildElement ( szRoot.GetAsChar ( ) )->FirstChildElement( szChild.GetAsChar ( ) )->FirstChildElement ( szInnerChild.GetAsChar ( ) );
	attributeElement->QueryAttribute ( szElement.GetAsChar ( ), &v0 );

	return v0;
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// get the number value in a child node by its element name 
// returns the value of the element
// pram ( WI_String szRoot = name of the root node,
//        WI_String szChild = child node with the element,
//        WI_String szInnerChild = child node with the element,
//        WI_String szElement = name of the element to get the value from )
WI_String WI_Markup::GetElementStrVal ( WI_String szRoot, WI_String szChild, WI_String szInnerChild, WI_String szElement )
{
	if (!g_XmlData.m_pDoc)
		return -1;

	tinyxml2::XMLElement* attributeElement = g_XmlData.m_pDoc->FirstChildElement ( szRoot.GetAsChar ( ) )->FirstChildElement( szChild.GetAsChar ( ) )->FirstChildElement ( szInnerChild.GetAsChar ( ) )->FirstChildElement ( szElement.GetAsChar ( ) );
	const char* v0 = attributeElement->GetText ( );

	return WI_String ( v0 );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// saves the markup data in memory to file and returns an error ID
WI_Int WI_Markup::SaveMarkupData ( WI_String szFileName, bool bCompact )
{
	if ( !g_XmlData.m_pDoc )
		return -1;

	g_XmlData.m_pDoc->SaveFile (  szFileName.GetAsChar ( ), bCompact );
	
	return g_XmlData.m_pDoc->ErrorID ( );
}  

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// saves the tMarkupDoc data to a markup file and returns an error ID
WI_Int WI_Markup::SaveMarkupDocData ( WI_String szFileName, tMarkupDoc doc, bool bCompact )
{
	if ( !g_XmlData.m_pDoc )
		return -1;

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// loop through all the root nodes
	for ( WI_Int i = 0; i < doc.m_arrRootNodes.size ( ); i++ )
	{
		////////////////////////////////////////////////////////////////////////
		//---------------------------------------------------------------------
		// add the root node name as the end child node
		g_XmlData.m_pDoc->InsertEndChild ( g_XmlData.m_pDoc->NewElement ( doc.m_arrRootNodes[ i ].m_szName.GetAsChar ( ) ) );

		////////////////////////////////////////////////////////////////////////
		//---------------------------------------------------------------------
		// loop through all of the children nodes
		for ( WI_Int j = 0; j < doc.m_arrRootNodes[ i ].m_arrNodes.size ( ); j++ )
		{
			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// add the node to the current child node
			g_XmlData.m_pDoc->NewElement ( doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_szName.GetAsChar ( ) );

			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// start a basic counter to set all the attributes this child may have
			WI_Int k = 0;

			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// add all the boolean elements to this child
			for ( k = 0; k < doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrBoolElement.size ( ); k++ )
			{
				WI_String szName = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrBoolElement[ k ].m_szName;
				bool bVal = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrBoolElement[ k ].m_bVal;
				g_XmlData.m_pDoc->FirstChildElement ( doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_szName.GetAsChar ( ) )->SetAttribute ( szName.GetAsChar( ), bVal );
			}

			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// add all the number elements to this child
			for ( k = 0; k < doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrNumElement.size ( ); k++ )
			{
				WI_String szName = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrNumElement[ k ].m_szName;
				WI_Double iVal = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrNumElement[ k ].m_val;
				g_XmlData.m_pDoc->FirstChildElement ( doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_szName.GetAsChar ( ) )->SetAttribute ( szName.GetAsChar( ), iVal );
			}

			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// add all the string elements to this child
			for ( k = 0; k < doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrStrElement.size ( ); k++ )
			{
				WI_String szName = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrStrElement[ k ].m_szName;
				WI_String szVal = doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_arrStrElement[ k ].m_szVal;
				g_XmlData.m_pDoc->FirstChildElement ( doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_szName.GetAsChar ( ) )->SetAttribute ( szName.GetAsChar( ), szVal.GetAsChar ( ) );
			}

			////////////////////////////////////////////////////////////////////////
			//---------------------------------------------------------------------
			// set the text inside the node
			g_XmlData.m_pDoc->SetValue ( doc.m_arrRootNodes[ i ].m_arrNodes[ j ].m_szText.GetAsChar ( ) );
		}
	}

	g_XmlData.m_pDoc->SaveFile (  szFileName.GetAsChar ( ), bCompact );
	
	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds a new root node to the markup document returns an error ID
WI_Int WI_Markup::AddRootNode ( WI_String szRootName )
{
	if ( !g_XmlData.m_pDoc )
		return -1;

	tinyxml2::XMLElement*  pElement = 	g_XmlData.m_pDoc->NewElement ( szRootName.GetAsChar ( ) );

	g_XmlData.m_pDoc->InsertEndChild (  pElement );

	return g_XmlData.m_pDoc->ErrorID ( );
}  

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds a child node to the current root node returns an error ID
WI_Int WI_Markup::AddChildNode ( WI_String szRootName, WI_String szChildName )
{
 	if ( !g_XmlData.m_pDoc )
		return -1;

	tinyxml2::XMLNode* pNode = g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) );
	
	g_XmlData.m_pDoc->InsertEndChild (  pNode );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds a child node to the current root node returns an error ID
WI_Int WI_Markup::DeleteChildNode ( WI_String szRootName, WI_String szChildName )
{
 	if ( !g_XmlData.m_pDoc )
		return -1;

	tinyxml2::XMLNode* pNode = g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) );
	
	g_XmlData.m_pDoc->DeleteChild ( pNode );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds a child node to the current root node returns an error ID
WI_Int WI_Markup::AddInnerChildNode ( WI_String szRootName, WI_String szChildName, WI_String szInnerChild )
{
 	if ( !g_XmlData.m_pDoc )
		return -1;

	tinyxml2::XMLNode* pNode = g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChild.GetAsChar ( ) );
	
	g_XmlData.m_pDoc->InsertEndChild ( pNode );

	return g_XmlData.m_pDoc->ErrorID ( );
}

WI_Int WI_Markup::DeleteInnerChildNode ( WI_String szRootName, WI_String szChildName, WI_String szInnerChild )
{
 	if ( !g_XmlData.m_pDoc )
		return -1;

	tinyxml2::XMLNode* pNode = g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChild.GetAsChar ( ) );
	
	g_XmlData.m_pDoc->DeleteChild ( pNode );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child, 
//        WI_Double iAttribute = attribute value )
WI_Int WI_Markup::AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_Double iAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  iAttribute );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child, 
//        bool bAttribute = attribute value )
WI_Int WI_Markup::AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, bool bAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  bAttribute );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child, 
//        WI_String szAttribute = attribute value )
WI_Int WI_Markup::AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_String szAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  szAttribute.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds some text inside a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child, 
//        WI_String szText = the text to add inside the child node )
WI_Int WI_Markup::AddChildText	( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_String szText )
{

	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->SetText ( szText.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );

}

WI_Int WI_Markup::DeleteChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->DeleteAttribute ( szAttribName.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child,
//        WI_String szInnerChildName = name of child,
//		  WI_String szAttribName = the name of the attribute
//        WI_Double iAttribute = attribute value )
WI_Int WI_Markup::AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, WI_Double iAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  iAttribute );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child,
//        WI_String szInnerChildName = name of child, 
//        bool bAttribute = attribute value )
WI_Int WI_Markup::AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, bool bAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  bAttribute );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// add a numerical attribute element to a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child,
//        WI_String szInnerChildName = name of child, 
//        WI_String szAttribute = attribute value )
WI_Int WI_Markup::AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, WI_String szAttribute )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChildName.GetAsChar ( ) )->SetAttribute ( szAttribName.GetAsChar ( ),  szAttribute.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds some text inside a child node returns error ID
// pram	( WI_String szRootName = root name, 
//        WI_String szChildName = name of child,
//        WI_String szInnerChildName = name of inner child, 
//        WI_String szText = inner child node text value )
WI_Int WI_Markup::AddInnerChildText ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szText )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChildName.GetAsChar ( ) )->SetText ( szText.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}

WI_Int WI_Markup::DeleteInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName )
{
	g_XmlData.m_pDoc->FirstChildElement ( szRootName.GetAsChar ( ) )->FirstChildElement ( szChildName.GetAsChar ( ) )->FirstChildElement ( szInnerChildName.GetAsChar ( ) )->DeleteAttribute ( szAttribName.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}
	
////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// adds a comment to the end of the last child node
// pram ( WI_String strComment = what the comment is going to be )
WI_Int WI_Markup::AddComment ( WI_String strComment )
{
 	if ( !g_XmlData.m_pDoc )
		return -1;

	g_XmlData.m_pDoc->NewComment ( strComment.GetAsChar ( ) );

	return g_XmlData.m_pDoc->ErrorID ( );
}