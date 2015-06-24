#include "LyteGlobals.h"


//
//bool tWiLessCompare::operator ( )  ( WI_String s1, WI_String s2) const
//{
//		const WI_UInt length = WI_MIN ( s1.GetStringLength ( ), s2.GetStringLength ( ) );
//
//		s1.LowerCase();
//		s2.LowerCase();
//
//		for ( WI_UInt i = 0; i < length;  ++i)
//		{
//			if ( s1.GetAsChar ( )[ i ] > s2.GetAsChar ( )[i] )
//				return false;
//
//			else if ( s1.GetAsChar ( )[ i ] < s2.GetAsChar()[ i ] )
//				return true;
//		}
//
//		return s1.GetStringLength ( ) < s2.GetStringLength ( );
//}
//
//WI_Inline void WI_CleanupCharEscapes ( WI_String& szS )
//{
//	string s = szS.GetAsChar();
//
//	std::string::iterator itr1	= s.begin();
//	std::string::iterator itr2	= s.begin();
//	std::string::iterator end	= s.end();
//
//	std::size_t removal_count	= 0;
//
//	while ( end != itr1 )
//	{
//		bool bypass = false;
//
//		if ('\\' == (*itr1))
//		{
//			bypass = true;
//			++removal_count;
//
//			if (end == ++itr1)
//				break;
//
//			else if ('\\' != (*itr1))
//			{
//				switch (*itr1)
//				{
//				case 'n' : (*itr1) = '\n'; break;
//				case 'r' : (*itr1) = '\r'; break;
//				case 't' : (*itr1) = '\t'; break;
//				}
//				continue;
//			}
//			else
//			{
//				bypass = false;
//			}
//		}
//
//		if (!bypass)
//		{
//			if (itr1 != itr2)
//			{
//				(*itr2) = (*itr1);
//			}
//			++itr1;
//			++itr2;
//		}
//	}
//
//	s.resize ( s.size() - removal_count );
//	szS = WI_String ( s.c_str ( ) );
//}