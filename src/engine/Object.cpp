
#include "Object.h"
#include "Type.h"

Object::Object()
{
	_type = NULL;
	_name = NULL;
}
Object::~Object()
{
	if (_name) free(_name);
}
void Object::setType(Type * value)
{
	_type = value;
}
void Object::setName(char* value)
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
const Type * Object::getType() const
{
	return _type;
}
const char* Object::getName() const
{
	return _name;
}
