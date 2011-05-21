
#include "Type.h"

Type::Type()
{
	_id = 0;
	_name = NULL;
}
Type::~Type()
{
	if (_name) free(_name);
}
void Type::setId(int value)
{
	_id = value;
}
void Type::setName(char* value)
{
	if (!value)
		return;
	
	//suppression de l'ancien nom
	if (_name)
	{
		free(_name);
		_name = NULL;
	}
	
	//copie du nouveau nom et allocation
	_name = (char*)malloc((strlen(value)+1) * sizeof(char));
	strcpy(_name, value);
}
const int Type::getId() const
{
	return _id;
}
const char* Type::getName() const
{
	return _name;
}
