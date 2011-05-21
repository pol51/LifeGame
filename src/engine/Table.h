#ifndef _TABLE_H
#define _TABLE_H


class Square;

#include <stdlib.h>
#include <stdio.h>

class Table
{
  protected:
	int _width;
	int _length;
	Square*** _squares;

  public:
	Table();
	Table(int width, int length);
	virtual ~Table();
	void clear();
	const int getWidth() const;
	const int getLength() const;
	Square* getSquare(int xPos, int yPos);
};
#endif
