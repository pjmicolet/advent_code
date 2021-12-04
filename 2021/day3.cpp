#include <iostream>
#include <string>
#include "utils/input_parser.h"

int main(int argc, char** argv ) {
	std::string filename = argv[1];
	InputParser parser{filename};
	std::string binary = "";
	bool nextLine = false;

	int zeroC = 0;
	int oneC = 0;
	std::string gamma = "";
	std::string epsilonR = "";
	while( parser.readLineAsCol(binary,nextLine) )
	{
		if( nextLine )
		{
			if( zeroC < oneC ){
				gamma += "1";
				epsilonR += "0";
			}
			else
			{
				gamma += "0";
				epsilonR += "1";
			}
			zeroC =0;
			oneC = 0;
		}
		if( binary == "0" )
			zeroC++;
		else if( binary == "1" )
			oneC++;
		binary = "";
	}
	// We'll have hit next line but then it's done reading, should really fix this in the API
	if( nextLine )
	{
		if( zeroC < oneC ){
			gamma += "1";
			epsilonR += "0";
		}
		else
		{
			gamma += "0";
			epsilonR += "1";
		}
	}
	int gCount = std::stoi(gamma,nullptr,2);
	int eCount = std::stoi(epsilonR,nullptr,2);
	std::cout << (gCount*eCount) << "\n";
}

