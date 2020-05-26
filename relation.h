#ifndef RELATION_H
#define RELATION_H

#include <string>

template<class T>
class SocialEntity;

enum Type{
    NEGATIVE,
    POSITIVE
};

template<class T>
class Relation{

public:
    Relation(SocialEntity<T>* first, SocialEntity<T>* second, Type type);
    SocialEntity<T>* getFirstEntity();
    SocialEntity<T>* getSecondEntity();

    void setDescription(const std::string& descr);
    std::string getDescription() const;

    void setType(Type type);
    Type getType();

    bool operator==(const Relation& other);

private:
    std::string description; //not necessary
    Type type;
    SocialEntity<T>* firstEntity;
    SocialEntity<T>* secondEntity;
};

template<class T>
Relation<T>::Relation(SocialEntity<T>* first, SocialEntity<T>* second, Type type) {
    this->type = type;
    firstEntity = first;
    secondEntity = second;
}

template<class T>
bool Relation<T>::operator==(const Relation<T>& other) {
    return this->type == other.type
           && *this->firstEntity == *other.firstEntity
           && *this->secondEntity == *other.secondEntity;
}

template<class T>
SocialEntity<T>* Relation<T>::getFirstEntity() {
    return firstEntity;
}

template<class T>
SocialEntity<T>* Relation<T>::getSecondEntity() {
    return secondEntity;
}

template<class T>
void Relation<T>::setDescription(const std::string &descr)
{
    this->description = descr;
}

template<class T>
std::string Relation<T>::getDescription() const
{
   return this->description;
}

template<class T>
void Relation<T>::setType(Type newType) {
    if (this->type == newType) return;

    this->type = newType;
    if(this->type == POSITIVE){
        secondEntity->setRating(secondEntity->getRating() + 1);
    } else {
        int newRating = secondEntity->getRating() - 1;
        secondEntity->setRating(newRating > 0 ? newRating : 0);
    }
}

template<class T>
Type Relation<T>::getType() {
    return this->type;
}

#endif // RELATION_H
