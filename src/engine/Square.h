#ifndef _SQUARE_H
#define _SQUARE_H


class Object;

#include <stdlib.h>

class Square
{
  protected:
	//Case au dessus.
	Square* _upSquare;
	//Case à droite.
	Square* _rightSquare;
	//Case au dessous.
	Square* _downSquare;
	//Case à gauche.
	Square* _leftSquare;
	//Objet contenue par la case.
	Object* _object;

  public:
	//Constructeur.
	Square();
	//Destructeur.
	virtual ~Square();
	void setUpSquare(Square* value);
	void setRightSquare(Square* value);
	void setDownSquare(Square* value);
	void setLeftSquare(Square* value);
	void setObject(Object* value);
	const Square* getUpSquare() const;
	const Square* getRightSquare() const;
	const Square* getDownSquare() const;
	const Square* getLeftSquare() const;
	const Object* getObject() const;
};
#endif
