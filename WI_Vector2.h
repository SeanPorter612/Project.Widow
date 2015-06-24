#pragma once
#ifndef __WI_VECTOR2__
#define __WI_VECTOR2__

class WI_Vector2
{
public:

	//////////////////////////////////////////////////
	//------------------------------------------------
	// the X value of this vector
	WI_Float x;

	//////////////////////////////////////////////////
	//------------------------------------------------
	// the Y value of this vector
	WI_Float y;

public:

	//////////////////////////////////////////////////
	//------------------------------------------------
	// This is our constructor that allows us to initialize our data upon creating an instance
	WI_Vector2( WI_Float X,  WI_Float Y);

	//////////////////////////////////////////////////
	//------------------------------------------------
	// A default constructor
	WI_Vector2() {}

	void Set ( WI_Float X, WI_Float Y )
	{ x = X; y = y; }

	// Here we overload the + operator so we can add vectors together 
	WI_Vector2 operator+(WI_Vector2 vVector);

	// Here we overload the - operator so we can subtract vectors 
	WI_Vector2 operator-(WI_Vector2 vVector);

	// Here we overload the * operator so we can multiply by scalars
	WI_Vector2 operator*( WI_Float num);

	// Here we overload the / operator so we can divide by a scalar
	WI_Vector2 operator/( WI_Float num);

};


#endif
