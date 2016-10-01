#include "stdafx.h"
#include <conio.h>
#include <fstream>
#include "randomString.h"
#include "stringManipulator.h"

int main() {
	srand((signed)time(NULL));
	int gatherLoopInc = 0, gatherLoop = 50;
	bool fastRun = false, first = false;
	while (true) {
		int population = 0, dividedPopulation = 0, moreDividedPopulation = 0;
		int matchChecker = 0, matchHighest = 0;
		int loopAmount = 0, loopTimes = 0;
		double mutationRate = 0.0;
		string userString = "", generatedString = "";

		if (!fastRun) {
			cout << "Enter Population Number: ";
			cin >> population;
			cout << "Enter Mutation Rate (0 - 100): ";
			cin >> mutationRate;
			cout << "Enter Targed String: ";
			cin.ignore();
			getline(cin, userString);
			cout << "Max Generation (0 to run until target found): ";
			cin >> loopAmount;
			cout << "\nRunning..." << endl;
		}
		else if (first) {
			population = 500;
			mutationRate = 35;
			userString = "Bugg";
			loopAmount = 0;
		}
		else if(!first) {
			cout << "Enter Population Number: ";
			population = 250;
			cout << population << endl;
			cout << "Enter Mutation Rate (0 - 100): ";
			mutationRate = 35;
			cout << mutationRate << endl;
			cout << "Enter Targed String: ";
			userString = "Buggs!";
			cout << userString << endl;
			cout << "Max Generation (0 to run until target found): ";
			loopAmount = 0;
			cout << loopAmount << endl;
			cout << "\nRunning..." << endl;

			first = true;
		}

		dividedPopulation = population / 4 * 3;
		moreDividedPopulation = population / 4;
		randomString *randomStrings = new randomString[population];
		stringManipulator stringManip(userString);

		char comparingUser, comparingGenerated;
		double fitness = 0.0;
		int matchingNumbers = 0, savedIteration = 0, savedMost = 0;
		bool foundMatch = false;
		while (!foundMatch) {
			for (int i = 0; i < population; i++)
				randomStrings[i].setMatching(0);
			for (int i = 0; i < population; i++) {
				generatedString = randomStrings[i].getString();
				for (unsigned int k = 0; k < userString.length(); k++) {
					comparingUser = userString[k];
					if (generatedString.length() < k)
						break;
					comparingGenerated = generatedString[k];
					//cout << "Comparing User: " << comparingUser << ", Comparing Generated: " << comparingGenerated << "." << endl;
					if (comparingUser == comparingGenerated)
						matchingNumbers += 10;
				}
				if (matchingNumbers > 0) {
					int charsOver = 0, charsUnder = 0;
					if (randomStrings[i].getString().length() > userString.length())
						charsOver = randomStrings[i].getString().length() - userString.length();
					if (randomStrings[i].getString().length() < userString.length()) {
						charsUnder = userString.length() - randomStrings[i].getString().length();
					}
					//cout << randomStrings[i].getString() << " ~~ Over: " << charsOver << " Under: " << charsUnder << " Both " << (matchingNumbers - (charsOver + charsUnder)) << endl << endl; system("pause");
					randomStrings[i].setMatching(matchingNumbers - (charsOver + charsUnder));
					if (savedMost < matchingNumbers) {
						savedMost = matchingNumbers;
					}
				}
				matchingNumbers = 0;
			}

			int *deadStrings = new int[dividedPopulation];
			deadStrings[0] = -1;
			int lowestString = 0, highestString = 0, dyingString = 0;
			for (int i = 0; i < dividedPopulation; i++) {
				for (int l = 0; l < population; l++)
					if (randomStrings[l].getMatching() > lowestString)
						lowestString = randomStrings[l].getMatching();
				for (int k = 0; k < population; k++) {
					bool doneBefore = false;
					for (int j = 0; j < dividedPopulation; j++) {
						if (deadStrings[j] == k)
							doneBefore = true;
					}
					if (randomStrings[k].getMatching() < lowestString && !doneBefore && k != savedIteration) {
						lowestString = randomStrings[k].getMatching();
						dyingString = k;
					}
				}

				deadStrings[i] = dyingString;

			}

			int *usedMate1 = new int[moreDividedPopulation];
			int *usedMate2 = new int[moreDividedPopulation];
			for (int i = 0; i < moreDividedPopulation; i++) {
				usedMate1[i] = -1;
				usedMate2[i] = -1;
			}

			for (int i = 0, dead = 0; i < moreDividedPopulation / 2; i++) {
				int mate1 = 0, mate2 = 0, mate1Matching = -1, mate2Matching = -1;
				for (int x = 0; x < population; x++) {
					bool isDead = false;
					for (int k = 0; k < moreDividedPopulation; k++) {
						if (usedMate1[k] == x)
							isDead = true;
						if (usedMate2[k] == x)
							isDead = true;
					}
					for (int k = 0; k < dividedPopulation; k++)
						if (deadStrings[k] == x)
							isDead = true;
					if (isDead)
						continue;

					if (mate1Matching <= randomStrings[x].getMatching()) {
						mate1Matching = randomStrings[x].getMatching();
						mate1 = x;
						usedMate1[i] = x;
					}
				}
				for (int x = 0; x < population; x++) {
					bool isDead = false;
					for (int k = 0; k < moreDividedPopulation; k++) {
						if (usedMate1[k] == x)
							isDead = true;
						if (usedMate2[k] == x)
							isDead = true;
					}
					for (int k = 0; k < dividedPopulation; k++)
						if (deadStrings[k] == x)
							isDead = true;
					if (isDead)
						continue;

					if (mate2Matching <= randomStrings[x].getMatching()) {
						mate2Matching = randomStrings[x].getMatching();
						mate2 = x;
						usedMate2[i] = x;
					}
				}


				for (int x = 0; x < 6; x++)
					if (dead <= dividedPopulation - 1) {
						randomStrings[deadStrings[dead++]].setString(stringManip.mate(randomStrings[mate1].getString(), randomStrings[mate2].getString(), mutationRate));
					}
					else {
						randomStrings[deadStrings[dead]].setString(stringManip.mate(randomStrings[mate1].getString(), randomStrings[mate2].getString(), mutationRate));
					}
			}
			delete[] usedMate1;
			delete[] usedMate2;
			delete[] deadStrings;

			matchChecker = -100;
			matchHighest = 0;
			for (int a = 0; a < population; a++) {
				if (randomStrings[a].getMatching() > matchChecker) {
					matchChecker = randomStrings[a].getMatching();
					matchHighest = a;
					if (randomStrings[a].getString() == userString) {
						foundMatch = true;
						matchChecker = randomStrings[a].getMatching();
						matchHighest = a;
					}
				}
			}
			string evoString = "Evolving String: ", gen = "Generation: ", fit = "Fitness: ", uStr = "UserString: ";
			system("cls");
			cout << evoString << randomStrings[matchHighest].getString() << endl;
			cout << uStr << "\t " << userString << endl;
			cout << gen << ++loopTimes << endl;
			cout << fit << static_cast<double>((matchChecker * 100) / stringManip.getMaxFitness()) << "%" << endl;
			cout << endl << endl;
			if (loopTimes == loopAmount)
				break;
		}


		delete[] randomStrings;
		char x;
		cout << "\nEnter X to quit (anything else to go again): ";
		x = _getch();
		if (x == 'x' || x == 'X' || gatherLoop < gatherLoopInc) {
			break;
		}
		else {
			system("cls");
			gatherLoopInc++;
		}
	}
}
