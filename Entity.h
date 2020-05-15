#pragma once

#include "Relation.h"

#include <list>
#include <string>

using namespace std;

class Entity
{
private: 
	list<Relation> relations;
	string name;
	
public:
	Entity();
	Entity(string name);
	void setName(string name);
	string getName();
	void addRelation(Relation relation);
	void removeRelation(Relation relations);
	void removeAllRelations();
	bool isRelatedTo(Entity entity);
	bool equals(Entity entity);


};

