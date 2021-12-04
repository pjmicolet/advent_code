#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include "utils/input_parser.h"

struct Levels {
	Levels( int numberOfLevels ) : numberOfLevels_(numberOfLevels) {}
	bool pushBack( int level ) {
		levels_.push_back(level);
		return levels_.size() < numberOfLevels_;
	}
	Levels check( int& increaseCounter, int& previous )
	{
		int sum = std::accumulate(levels_.begin(), levels_.end(), 0);
		if( previous != -1 && previous < sum )
			increaseCounter++;
		previous = sum;
		Levels nextP{numberOfLevels_};

		for( int i = 1; i < numberOfLevels_; i++ )
			nextP.pushBack( levels_[i] );
		return nextP;
	}
	private:
		int numberOfLevels_;
		std::vector<int> levels_;
};

int main( int argc, char** argv)
{
	std::string filename = argv[1];
	InputParser parser{filename};

	std::string line = "";
	int level = 0;
	int next_level = -1;

	if(parser.readLine(line))
		level = stoi(line);

	int increases = 0;
	while(parser.readLine(line))
	{
		next_level = std::stoi(line);
		if( next_level > level )
			increases++;
		level=next_level;

	}

	std::cout << increases << "\n";

	std::string secondInput = argv[2];
	InputParser parser2{secondInput};

	int previous = -1;
	int increaseCounter=0;
	Levels threeWind{3};
	line ="";
	while(parser2.readLine(line))
	{
		auto number = std::stoi(line);
		if(!threeWind.pushBack(number))
			threeWind = threeWind.check(increaseCounter,previous);
	}

	std::cout << "Sliding " << increaseCounter << "\n";
}
