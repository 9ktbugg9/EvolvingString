#include "stdafx.h"
#include "stringManipulator.h"


string stringManipulator::mate(string mate1, string mate2, double mutationRate) {
	string offspring, holder1 = mate1;
	int length = 0, x = 0;
	if (mate1.length() > mate2.length())
		length = mate2.length();
	else
		length = mate1.length();
	for (int i = 0; i < length; i++) {
		if (rand() % 2 == 1) {
			mate1[i] = mate2[i];
			x--;
		}
		else
			x++;
		if (x >= 3) {
			mate1[i] = mate2[i];
			x = 0;
		}
	}

	// Mutating
	for (unsigned int i = 0; i < mate1.length(); i++) {
		if (rand() % 100 + 1 <= mutationRate) {
			mate1[rand() % mate1.length()] = char(rand() % (126 - 32 + 1) + 32);
		}
	}

	// Add or Subtracting
	for (unsigned int i = 0; i < mate1.length(); i++) {
		if (rand() % 100 + 1 <= mutationRate) {
			if (rand() % 2 == 1) {
				string insertString = "";
				insertString += rand() % (126 - 32 + 1) + 32;
				mate1.insert(rand() % mate1.length(), insertString);
			}
			else if (mate1.length() >= 1) {
				mate1.erase(rand() % mate1.length());
			}
		}
	}
	return mate1;
}