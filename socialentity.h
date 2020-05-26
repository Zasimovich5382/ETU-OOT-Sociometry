#ifndef SOCIALENTITY_H
#define SOCIALENTITY_H

#include <list>

#include "entity.h"
#include "relation.h"
#include "allocator.h"

enum Gender {
    MALE,
    FEMALE,
    DEFAULT
};

template<class T>
class SocialEntity: public Entity<T>{
public:
    SocialEntity();
    SocialEntity(const T& name, Gender gender);
    SocialEntity(const T& name, int age, Gender gender);

    void addRelation(Relation<T> relation);
    // void addRelation(SocialEntity<T>* other, Type type);
    void removeRelation(const T& name);
    Relation<T>* getRelationWith(const T& name);
//    virtual void removeAllRelations() = 0;

    bool isRelatedTo(const T& name);

    void setName(const T& name);
    const T& getName();
    std::list<Relation<T>, Alloc::Allocator <Relation<T>>>& getRelations();
    bool operator==(const SocialEntity<T>& other);

    void setGender(Gender gender);
    Gender getGender();

    void setAge(int age);
    int getAge();

    void setRating(int new_rating);
    int getRating();

    int getId() const;
    int setId(int new_id);

private:
    int rating;

    int id;
    T name;
    Gender gender;
    int age;
    std::list<Relation<T>, Alloc::Allocator <Relation<T>>> relations;
};

template<class T>
SocialEntity<T>::SocialEntity():
    name(""),
    gender(DEFAULT),
    age(-1),
    rating(0),
    id(++Entity<T>::id_counter)
{}

template<class T>
SocialEntity<T>::SocialEntity(const T& name, Gender gender):
    name(name),
    gender(gender),
    age(-1),
    rating(0),
    id(++Entity<T>::id_counter)
{}

template<class T>
SocialEntity<T>::SocialEntity(const T& name, int age, Gender gender):
    SocialEntity<T>(name, gender)
{
    this->age = age;
}

template<class T>
bool SocialEntity<T>::operator==(const SocialEntity<T> &other)
{
    return this->name == other.name
           && this->age == other.age
           && this->gender == other.gender;
}

template<class T>
void SocialEntity<T>::addRelation(Relation<T> relation) {
    if (!isRelatedTo(relation.getSecondEntity()->getName())){
        if (relation.getType() == POSITIVE){
            SocialEntity<T>* to = relation.getSecondEntity();
            to->setRating(to->getRating() + 1);
        }
        relations.push_back(relation);
    }
}

template<class T>
void SocialEntity<T>::setName(const T& name){
    this->name = name;
}

template<class T>
const T& SocialEntity<T>::getName() {
    return this->name;
}

template<class T>
void SocialEntity<T>::removeRelation(const T& name) {
    for (Relation<T> r : relations){
        if (r.getSecondEntity()->getName() == name) {
            relations.remove(r);
            break;
        }
    }
}

template<class T>
bool SocialEntity<T>::isRelatedTo(const T& name) {
    for (Relation<T>& r : relations){
        if (r.getSecondEntity()->getName() == name) return true;
    }
    return false;
}

template<class T>
Relation<T>* SocialEntity<T>::getRelationWith(const T& name) {
    for (auto it = relations.begin(); it != relations.end(); it++){
        if ((*it).getSecondEntity()->getName() == name) {
            return &(*it);
        }
    }
    return nullptr;
}

template<class T>
std::list<Relation<T>, Alloc::Allocator <Relation<T>>>& SocialEntity<T>::getRelations(){
    return this->relations;
}

template<class T>
Gender SocialEntity<T>::getGender() {
    return this->gender;
}

template<class T>
int SocialEntity<T>::getAge() {
    return this->age;
}

template<class T>
void SocialEntity<T>::setRating(int new_rating)
{
    this->rating = new_rating;
}

template<class T>
int SocialEntity<T>::getRating()
{
    return this->rating;
}

template<class T>
void SocialEntity<T>::setGender(Gender gender) {
    this->gender = gender;
}

template<class T>
void SocialEntity<T>::setAge(int age) {
    this->age = age;
}

template<class T>
int SocialEntity<T>::getId() const
{
    return this->id;
}

template<class T>
int SocialEntity<T>::setId(int new_id)
{
    this->id = new_id;
    Entity<T>::id_counter = new_id;
}

#endif // SOCIALENTITY_H
