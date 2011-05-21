
#include "Square.h"
#include "Object.h"

//Constructeur.
Square::Square()
{
	_upSquare = NULL;
	_rightSquare = NULL;
	_downSquare = NULL;
	_leftSquare = NULL;
	_object = NULL;
}
//Destructeur.
Square::~Square()
{
}
void Square::setUpSquare(Square* value)
{
	_upSquare = value;
}
void Square::setRightSquare(Square* value)
{
	_rightSquare = value;
}
void Square::setDownSquare(Square* value)
{
	_downSquare = value;
}
void Square::setLeftSquare(Square* value)
{
	_leftSquare = value;
}
void Square::setObject(Object* value)
{
	_object = value;
}
const Square* Square::getUpSquare() const
{
	return _upSquare;
}
const Square* Square::getRightSquare() const
{
	return _rightSquare;
}
const Square* Square::getDownSquare() const
{
	return _downSquare;
}
const Square* Square::getLeftSquare() const
{
	return _leftSquare;
}
const Object* Square::getObject() const
{
	return _object;
}
