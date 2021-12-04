#include <iostream>
#include <fstream>
#include <string>
#include "utils/input_parser.h"

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
}
