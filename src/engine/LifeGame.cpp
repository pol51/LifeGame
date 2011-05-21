
#include "LifeGame.h"
#include "Table8.h"
#include "Object.h"

LifeGame::LifeGame(int size)
{
	assert(size);
	
	_size = size;
	_gameTable = new Table8(_size, _size);
	_backTable = new Table8(_size, _size);
	_lifeObject = new Object();
	_lifeObject->setName("Vie");
	_nbLife = 0;
}
LifeGame::~LifeGame()
{
	delete _gameTable;
	delete _backTable;
	delete _lifeObject;
}
const int LifeGame::getNbLife() const
{
	return _nbLife;
}
const int LifeGame::getSize() const
{
	return _size;
}
void LifeGame::computeNextGeneration()
{
	int nbr, nbLife = 0;
	
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
		{
			nbr = 0;
			
			if (_gameTable->getSquare8(i, j)->getUpSquare())
				if (_gameTable->getSquare8(i, j)->getUpSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getRightSquare())
				if (_gameTable->getSquare8(i, j)->getRightSquare()
						->getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getDownSquare())
				if (_gameTable->getSquare8(i, j)->getDownSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getLeftSquare())
				if (_gameTable->getSquare8(i, j)->getLeftSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getUpLeftSquare())
				if (_gameTable->getSquare8(i, j)->getUpLeftSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getUpRightSquare())
				if (_gameTable->getSquare8(i, j)->getUpRightSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getDownLeftSquare())
				if (_gameTable->getSquare8(i, j)->getDownLeftSquare()->
						getObject() == _lifeObject)
					nbr++;
			if (_gameTable->getSquare8(i, j)->getDownRightSquare())
				if (_gameTable->getSquare8(i, j)->getDownRightSquare()->
						getObject() == _lifeObject)
					nbr++;
			
			if (nbr == 3)
				_backTable->getSquare8(i, j)->setObject(_lifeObject);
			else if (nbr == 2)
				_backTable->getSquare8(i, j)->setObject((Object*)_gameTable->
					getSquare8(i, j)->getObject());
			else
				_backTable->getSquare8(i, j)->setObject(NULL);
			
			if (_backTable->getSquare8(i, j)->getObject())
				nbLife++;
		}
	
	_nbLife = nbLife;
	swapTables();
}
void LifeGame::endOfLife()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++)
			_backTable->getSquare8(i, j)->setObject(NULL);
			
	_nbLife = 0;
	swapTables();
}
bool LifeGame::isAlive(int xPos, int yPos)
{
	if (_gameTable->getSquare8(xPos, yPos))
		return (_gameTable->getSquare8(xPos, yPos)->getObject());
	return false;
}
void LifeGame::setAlive(int xPos, int yPos, bool alive)
{
	if (_gameTable->getSquare8(xPos, yPos))
		if (alive)
		{
			if (!_gameTable->getSquare8(xPos, yPos)->getObject())
			{
				_gameTable->getSquare8(xPos, yPos)->setObject(_lifeObject);
				_nbLife++;
			}
		}
		else
		{
			if (_gameTable->getSquare8(xPos, yPos)->getObject())
			{
				_gameTable->getSquare8(xPos, yPos)->setObject(NULL);
				_nbLife--;
			}
		}
}
void LifeGame::swapTables()
{
	Table8* tmpTable = _gameTable;
	_gameTable = _backTable;
	_backTable = tmpTable;
}
