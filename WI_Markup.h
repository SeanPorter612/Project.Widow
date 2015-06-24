#pragma once

#ifndef __WI_Markup__
#define __WI_Markup__

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// a set of structures that	can make up any markup document
//---------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// node element number name value
struct tNumElement
{
	WI_Double					m_val;
	WI_String					m_szName;
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// node element boolean name value
struct tBoolElement
{
	bool						m_bVal;
	WI_String					m_szName;
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// node element string name value
struct tStrElement
{
	WI_String					m_szVal;
	WI_String					m_szName;
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// node and elements
struct tNode
{
	WI_String					m_szName;			// the name of the node
	WI_String					m_szText;			// the text inside the node

	WI_Array< tNumElement >		m_arrNumElement;	// an array of number elements
	WI_Array< tBoolElement >	m_arrBoolElement;	// an array of boolean elements
	WI_Array< tStrElement >		m_arrStrElement;	// an array of string elements
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// a root node
struct tRoot
{
	WI_String					m_szName;			// the name of the node
	WI_Array< tNode >			m_arrNodes;			// an array of child nodes
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// a markup document structure
struct tMarkupDoc
{
	WI_Array< tRoot >			m_arrRootNodes;			// an array of root nodes
};

////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------
// the markup document class used for both reading and writing markup
// files can also be used for parsing different kinds of markup systems (IE: HTML ) 
class WI_Markup
{
public:
	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// constructor / deconstructor
	WI_Markup ( const char* XmlData );				// with XML data in a const char*
	WI_Markup ( WI_String szFileName );				// open a markup file by its name
	WI_Markup ( void );
	~WI_Markup (void);

public:
	
	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// get node and element data
	//---------------------------------------------------------------------
	////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// loads a markup file in to memory returns error message
	WI_Int LoadMarkupFile ( WI_String szFileName );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// get the number value in a child node by its element name 
	// returns the value of the element
	// pram ( WI_String szChild = child node with the element, 
	//        WI_String szElement = name of the element to get the value from )
	WI_Double GetElementNumVal ( WI_String szRoot, WI_String szChild, WI_String szElement );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// get the number value in a child node by its element name 
	// returns the value of the element
	// pram ( WI_String szRoot = name of the root node,
	//        WI_String szChild = child node with the element, 
	//        WI_String szElement = name of the element to get the value from )
	WI_String GetElementStrVal ( WI_String szRoot, WI_String szChild, WI_String szElement );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// gets the text inside the child node returns WI_String value of the text
	// pram	( WI_String szRoot = name of the root node, 
	//        WI_String szChild = the name of child node to get the text value from  )
	WI_String GetChildNodeText ( WI_String szRoot, WI_String szChild );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// get the number value in a child node by its element name 
	// returns the value of the element
	// pram ( WI_String szRoot = name of the root node,
	//        WI_String szChild = child node with the element, 
	//		  WI_String szInnerChild = the name of the inner child node to get the element value from
	//        WI_String szElement = name of the element to get the value from )
	WI_Double GetElementNumVal ( WI_String szRoot, WI_String szChild, WI_String szInnerChild, WI_String szElement );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// get the number value in a child node by its element name 
	// returns the value of the element
	// pram ( WI_String szRoot = name of the root node,
	//        WI_String szChild = child node with the element,
	//        WI_String szInnerChild = child node with the element,
	//        WI_String szElement = name of the element to get the value from )
	WI_String GetElementStrVal ( WI_String szRoot, WI_String szChild, WI_String szInnerChild, WI_String szElement );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// gets the text inside the child node returns WI_String value of the text
	// pram	( WI_String szRoot = name of the root node, 
	//        WI_String szChild = the name of child node to get the text value from  
	//        WI_String szInnerChild = the name of the inner child node to get the text from )
	WI_String GetInnerChildNodeText ( WI_String szRoot, WI_String szChild,  WI_String szInnerChild );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// set delete and save node and element data
	//---------------------------------------------------------------------
	////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds a new root node to the markup document returns an error ID
	// pram	( WI_String szRootName = root node name )
	WI_Int	AddRootNode ( WI_String szRootName );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds a child node to the a root node returns an error ID
	// pram	( WI_String szRootName = root name, WI_String szChildName = new node name )
	WI_Int AddChildNode ( WI_String szRootName, WI_String szChildName );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// removes a child node by it's name returns an error ID
	// pram	( WI_String szRootName = root name, WI_String szChildName = name of the node to remove )
	WI_Int DeleteChildNode ( WI_String szRootName, WI_String szChildName );
	
	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds a child node to a child node returns an error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szInnerChild = new node name )
	WI_Int AddInnerChildNode ( WI_String szRootName, WI_String szChildName, WI_String szInnerChild );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// removes an inner child node by its name
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szInnerChild = name of inner child node to remove )
	WI_Int DeleteInnerChildNode ( WI_String szRootName, WI_String szChildName, WI_String szInnerChild );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child,
	//		  WI_String szAttribName = the name of the attribute
	//        WI_Double iAttribute = attribute value )
	WI_Int AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_Double iAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        bool bAttribute = attribute value )
	WI_Int AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, bool bAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szAttribute = attribute value )
	WI_Int AddChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_String szAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds some text inside a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szText = the text to add inside the child node )
	WI_Int AddChildText	( WI_String szRootName, WI_String szChildName, WI_String szAttribName, WI_String szText );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// removes an attribute from a child node by its name returns an error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szAttribute = attribute value )
	WI_Int DeleteChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szAttribName );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child,
	//        WI_String szInnerChildName = name of inner child, 
	//		  WI_String szAttribName = the name of the attribute
	//        WI_Double iAttribute = attribute value )
	WI_Int AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, WI_Double iAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child,
	//        WI_String szInnerChildName = name of inner child, 
	//        bool bAttribute = attribute value )
	WI_Int AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, bool bAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// add a numerical attribute element to a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child,
	//        WI_String szInnerChildName = name of inner child, 
	//        WI_String szAttribute = attribute value )
	WI_Int AddInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName, WI_String szAttribute );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds some text inside a child node returns error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child,
	//        WI_String szInnerChildName = name of inner child, 
	//        WI_String szText = inner child node text value )
	WI_Int AddInnerChildText ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szText );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// removes an attribute from a child node by its name returns an error ID
	// pram	( WI_String szRootName = root name, 
	//        WI_String szChildName = name of child, 
	//        WI_String szInnerChildName = name of inner child,
	//        WI_String szAttribute = attribute value )
	WI_Int DeleteInnerChildAttribute ( WI_String szRootName, WI_String szChildName, WI_String szInnerChildName, WI_String szAttribName );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// adds a comment to the end of the last child node	returns an error ID
	// pram ( WI_String strComment = what the comment is going to be )
	WI_Int AddComment ( WI_String strComment );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// saves the tMarkupDoc data to a markup file and returns an error ID
	WI_Int SaveMarkupDocData ( WI_String szFileName, tMarkupDoc doc, bool bCompact = false );

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// saves the markup data in memory to file and returns an error ID
	WI_Int SaveMarkupData ( WI_String szFileName, bool bCompact = false );

private:

	////////////////////////////////////////////////////////////////////////
	//---------------------------------------------------------------------
	// private member variables

	WI_String			m_szMarkupData;				// the markup data

};



#pragma message ( "		Widow Lyte's markup system defined..." )
#endif