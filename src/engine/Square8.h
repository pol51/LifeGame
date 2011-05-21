#ifndef _SQUARE8_H
#define _SQUARE8_H


#include "Square.h"

class Square8 : public Square
{
  public:
	Square8();
	virtual ~Square8();

  protected:
	//Case au dessus à gauche.
	Square* _upLeftSquare;
	//Case au dessus à droite.
	Square* _upRightSquare;
	//Case au dessous à gauche.
	Square* _downLeftSquare;
	//Case au dessous à droite.
	Square* _downRightSquare;

  public:
	const Square* getUpLeftSquare() const;
	const Square* getUpRightSquare() const;
	const Square* getDownLeftSquare() const;
	const Square* getDownRightSquare() const;
	void setUpLeftSquare(Square* value);
	void setUpRightSquare(Square* value);
	void setDownLeftSquare(Square* value);
	void setDownRightSquare(Square* value);
};
#endif
