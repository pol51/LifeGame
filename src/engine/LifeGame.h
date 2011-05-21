#ifndef _LIFEGAME_H
#define _LIFEGAME_H


#include "Square8.h"

class Table8;
class Object;

#include "assert.h"

class LifeGame
{
  protected:
	Table8 * _gameTable;
	Table8 * _backTable;
	Object * _lifeObject;
	int _nbLife;
	int _size;

  public:
	LifeGame(int size);
	virtual ~LifeGame();
	const int getNbLife() const;
	const int getSize() const;
	void computeNextGeneration();
	void endOfLife();
	bool isAlive(int xPos, int yPos);
	void setAlive(int xPos, int yPos, bool alive);

  protected:
	void swapTables();
};
#endif
