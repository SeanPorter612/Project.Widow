#pragma once

#ifndef __WI_MarkupOut__
#define __WI_MarkupOut__

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// basicly XML this is widow's markup writing out to a file this class
// requires a root node defined in the constructor and supports
// child node, sybling node and child sybling so a markup document cal look like so

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------------------
// <?xml version="1.0" ?>
// <Root>
//     <!-- child comment -->
//     <child1 strAttr = "some string" intAttr = 1.0 >child node text</child1>
//
//     <child2>
//
//         <!-- sybling comment -->
//         <sybling strAttr = "some string" intAttr = 1.0 >
//				sybling text
//		   </sybling>
//
//         <sybling2>
//
//              <!-- child sybling comment -->
//				<childSybling1 strAttr = "some string" intAttr = 1.0 ></childSybling2>
//
//				<childSybling2>child sybling text</childSybling2>
//
//		   </sybling2>
//
//     </child2>
//
// </Root>
//--------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////

class WI_MarkupOut
{
public:
	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// constructor / deconstructor
	WI_MarkupOut ( WI_String szFileName, WI_String szRootNodeName );
	~WI_MarkupOut ( void );

public:
	
	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// saves the markup document to disk
	void Save ( );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// makes a new markup object and sets the root node
	void CreateNew ( WI_String szFileName, WI_String szRootNodeName );

		/////////////////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------------------
		// child node functions
		//--------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a child node to the current root node
	void AddChildNode ( WI_String szNodeName );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a string attribute name value pair to the current child node
	void SetChildAttribute ( WI_String szName, WI_String szAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetChildAttribute ( WI_String szName, WI_Int iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetChildDoubleAttribute ( WI_String szName, WI_Double iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// sets the text of the child node
	void SetChildText ( WI_String szText );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a comment to the document just above the child node
	void AddChildComment ( WI_String szComment );

		/////////////////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------------------
		// Sybling node functions
		//--------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a sibling node to the current child node
	void AddSybling ( WI_String szNodeName );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a string attribute name value pair to the current child node
	void SetSyblingAttribute ( WI_String szName, WI_String szAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetSyblingAttribute ( WI_String szName, WI_Int iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetSyblingDoubleAttribute ( WI_String szName, WI_Double iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// sets the text of the child node
	void SetSyblingText ( WI_String szText );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a comment to the document just above the sybling node
	void AddSyblingComment ( WI_String szComment );

		/////////////////////////////////////////////////////////////////////////////
		//--------------------------------------------------------------------------
		// Child sybling node functions
		//--------------------------------------------------------------------------
		/////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a sibling node to the current child node
	void AddChildSybling ( WI_String szNodeName );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a string attribute name value pair to the current child node
	void SetChildSyblingAttribute ( WI_String szName, WI_String szAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetChildSyblingAttribute ( WI_String szName, WI_Int iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// set a number attribute name value pair to the current child node
	void SetChildSyblingDoubleAttribute ( WI_String szName, WI_Double iAttribute );

	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// sets the text of the child node
	void SetChildSyblingText ( WI_String szText );
	
	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// adds a comment to the document just above the sybling node
	void AddChildSyblingComment ( WI_String szComment );

private:
	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// private attributes
	//--------------------------------------------------------------------------
	/////////////////////////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////////////////////////
	//--------------------------------------------------------------------------
	// the document's file name
	WI_String					m_szFileName;
};

#pragma message ( "		Widow Lyte markup writing out system complete..." )
#endif