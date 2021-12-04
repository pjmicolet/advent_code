#include <iostream>
#include <string>
#include "utils/input_parser.h"

struct pos {
	pos() : depth(0), position(0), aim(0) {}
	int depth;
	int position;
	int aim;
};

int main(int argc, char** argv ) {
	std::string filename = argv[1];
	InputParser parser{filename};

	std::string line = "";
	pos position{};
	std::vector<std::string> splitLine;
	
	while(parser.readLine(splitLine, ' '))
	{
		auto direc = splitLine[0];
		int amount = std::stoi(splitLine[1]);
		if( direc == "forward" )
			position.position+=amount;
		else if( direc == "down" )
			position.depth+=amount;
		else if( direc == "up" )
			position.depth-=amount;
		splitLine.clear();
	}

	std::cout << (position.position*position.depth) << "\n";

	std::string filename2 = argv[2];
	InputParser parser2{filename};
	position.depth=0;
	position.position=0;
	
	while(parser2.readLine(splitLine, ' '))
	{
		auto direc = splitLine[0];
		int amount = std::stoi(splitLine[1]);
		if( direc == "forward" )
		{
			position.position+=amount;
			position.depth+= (position.aim*amount);
		}
		else if( direc == "down" )
			position.aim+=amount;
		else if( direc == "up" )
			position.aim-=amount;
		splitLine.clear();
	}

	std::cout << (position.position*position.depth) << "\n";
}

