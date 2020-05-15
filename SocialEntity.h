#pragma once
#include "Entity.h"

enum Gender {

	MALE,
	FEMALE,

};

class SocialEntity : Entity{
private:
	Gender gender;
	int age;
public:
	Gender getGender();
	int getAge();
	void setGender(Gender gender);
	void setAge(int age);
};

