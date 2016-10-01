#include "stdafx.h"
#include "randomString.h"


int randomString::maxPopulation = 0;

randomString::randomString() {
	maxPopulation++;
	setRandomString();
}

randomString::~randomString() {
}

void randomString::setRandomString() {
	//mt19937 rg(time(NULL) + randomizer);
	//uniform_real_distribution<float> singleSeed(32, 126);
	//uniform_real_distribution<float> singleSize(1, 11);
	
	int size = rand() % 21 + 1;//singleSize(rg);
	char seed = 0;
	for (int i = 0; i < size; i++) {
		seed = char(rand() % (126 - 32 + 1) + 32);//singleSeed(rg));
		myString += seed;
	}
}

void randomString::setString(string set) {
	myString = set;
}

void randomString::setMatching(int matching) {
	myMatching = matching;
}

int randomString::getMatching() {
	return myMatching;
}

string randomString::getString() {
	return myString;
}