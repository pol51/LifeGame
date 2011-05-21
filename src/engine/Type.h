#ifndef _TYPE_H
#define _TYPE_H


#include <string.h>
#include <stdlib.h>

class Type
{
  protected:
	int _id;
	char* _name;

  public:
	Type();
	virtual ~Type();
	void setId(int value);
	void setName(char* value);
	const int getId() const;
	const char* getName() const;
};
#endif
