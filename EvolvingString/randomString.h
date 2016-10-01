#pragma once

#include <string>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

class randomString {
	private:
	string myString = "";
	int myMatching = 0;
	static int maxPopulation;

	public:
	string getString();
	void setRandomString();
	void setString(string set);
	void setMatching(int matching);
	int getMatching();

	randomString();
	~randomString();
};

