
#include "Square8.h"

Square8::Square8() : Square()
{
	_upLeftSquare = NULL;
	_upRightSquare = NULL;
	_downLeftSquare = NULL;
	_downRightSquare = NULL;
}
Square8::~Square8()
{
}
const Square* Square8::getUpLeftSquare() const
{
	return _upLeftSquare;
}
const Square* Square8::getUpRightSquare() const
{
	return _upRightSquare;
}
const Square* Square8::getDownLeftSquare() const
{
	return _downLeftSquare;
}
const Square* Square8::getDownRightSquare() const
{
	return _downRightSquare;
}
void Square8::setUpLeftSquare(Square* value)
{
	_upLeftSquare = value;
}
void Square8::setUpRightSquare(Square* value)
{
	_upRightSquare = value;
}
void Square8::setDownLeftSquare(Square* value)
{
	_downLeftSquare = value;
}
void Square8::setDownRightSquare(Square* value)
{
	_downRightSquare = value;
}
