#include "LyteGlobals.h"

//////////////////////////////////////////////////
//------------------------------------------------
// This is our constructor that allows us to initialize our data upon creating an instance
WI_Vector2::WI_Vector2( WI_Float X,  WI_Float Y) 
{ 
	x = X; y = Y;
}

//WI_Vector2::~WI_Vector2(void)
//{
//}

// Here we overload the + operator so we can add vectors together 
WI_Vector2 WI_Vector2::operator+(WI_Vector2 vVector)
{
	// Return the added vectors result.
	return WI_Vector2(vVector.x + x, vVector.y + y);
}

// Here we overload the - operator so we can subtract vectors 
WI_Vector2 WI_Vector2::operator-(WI_Vector2 vVector)
{
	// Return the subtracted vectors result
	return WI_Vector2(x - vVector.x, y - vVector.y);
}

// Here we overload the * operator so we can multiply by scalars
WI_Vector2 WI_Vector2::operator*( WI_Float num)
{
	// Return the scaled vector
	return WI_Vector2(x * num, y * num);
}

// Here we overload the / operator so we can divide by a scalar 
WI_Vector2 WI_Vector2::operator/( WI_Float num)
{
	// Return the scaled vector
	return WI_Vector2(x / num, y / num);
}