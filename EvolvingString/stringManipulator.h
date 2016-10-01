#pragma once
#include <string>

using namespace std;

class stringManipulator {
	private:
	unsigned int maxFitness;

	public:
	string mate(string mate1, string mate2, double mutationRate);
	void setMaxFitness(string &src) { maxFitness = src.length() * 10; }
	int getMaxFitness() { return maxFitness; }

	stringManipulator(string &src) { setMaxFitness(src); }
	stringManipulator() {}
	~stringManipulator() {}
};

