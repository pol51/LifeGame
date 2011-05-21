#ifndef _OBJECT_H
#define _OBJECT_H


class Type;

#include <string.h>
#include <stdlib.h>

class Object
{
  protected:
	Type * _type;
	char* _name;

  public:
	Object();
	virtual ~Object();
	void setType(Type * value);
	void setName(char* value);
	const Type * getType() const;
	const char* getName() const;
};
#endif
