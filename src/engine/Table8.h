#ifndef _TABLE8_H
#define _TABLE8_H


#include "Table.h"

class Square8;

class Table8 : public Table
{
  public:
	Table8(int width, int length);
	virtual ~Table8();
	Square8* getSquare8(int xPos, int yPos);
};
#endif
