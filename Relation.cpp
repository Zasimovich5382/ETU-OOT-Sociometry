#include "Relation.h"

Relation::Relation(Type type, Entity f, Entity s) {
	this->type = type;
	this->firstEntity = f;
	this->secondEntity = s;
}

bool Relation::equals(Relation r) {
	return this->name == r.name && this->firstEntity.equals(r.firstEntity) && this->secondEntity.equals(r.secondEntity);
}

Entity Relation::getFirstEntity() {

	return this->firstEntity;
}

Entity Relation::getSecondEntity() {

	return this->secondEntity;
}

void Relation::setFirstEntity(Entity e) {
	
	this->firstEntity = e;
}

void Relation::setSecondEntity(Entity e) {

	this->secondEntity = e;
}

void Relation::setType(Type type) {

	this->type = type;
}
