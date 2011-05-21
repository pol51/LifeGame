
#include "Table.h"
#include "Square.h"

Table::Table()
{
}
Table::Table(int width, int length)
{
	if (width > 0 && length > 0)
	{
		_width = width;
		_length = length;
		
		//création des cases
		_squares = (Square***)malloc(_width * sizeof(void*));
		for (int i = 0; i < _width; i++)
		{
			_squares[i] = (Square**)malloc(_length * sizeof(void*));
			for (int j = 0; j < _length; j++)
			{
				_squares[i][j] = new Square();
				_squares[i][j]->setObject(NULL);
			}
		}
		
		//liaison des cases
		for (int i = 0; i < _width; i++)
			for (int j = 0; j < _length; j++)
			{
				if (j > 0)
					_squares[i][j]->setUpSquare(_squares[i][j-1]);
				if (i < _width-1)
					_squares[i][j]->setRightSquare(_squares[i+1][j]);
				if (j < _length-1)
					_squares[i][j]->setDownSquare(_squares[i][j+1]);
				if (i > 0)
					_squares[i][j]->setLeftSquare(_squares[i-1][j]);
			}
	}
	else
	{
		_width = 0;
		_length = 0;
		_squares = NULL;
	}
}
Table::~Table()
{
	clear();
}
void Table::clear()
{
	if (_width <= 0 || _length <= 0)
		return;
	
	//suppression des cases
	for (int i = 0; i < _width; i++)
		for (int j = 0; j < _length; j++)
			delete _squares[i][j];
}
const int Table::getWidth() const
{
	return _width;
}
const int Table::getLength() const
{
	return _length;
}
Square* Table::getSquare(int xPos, int yPos)
{
	if (xPos >= 0 && xPos < _width && yPos >= 0 && yPos < _length)
		return _squares[xPos][yPos];
	else
		return NULL;
}
