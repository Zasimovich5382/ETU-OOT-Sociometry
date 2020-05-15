#pragma once
#include "Entity.h"
using namespace std;

#include <list>
#include <string>

enum Type
{
	TYPE_VAN,
	TYPE_TWO,
};

class Relation
{
private:
	string name; //ыозможно не нужно
	Type type;
	Entity firstEntity;
	Entity secondEntity;
public:
	Relation(Type tipe, Entity f, Entity t);
	bool equals(Relation r);
	Entity getFirstEntity();
	Entity getSecondEntity();
	void setFirstEntity(Entity entity);
	void setSecondEntity(Entity entity);
	void setType(Type type);

};
