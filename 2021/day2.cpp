#include <iostream>
#include <fstream>
#include <string>

struct pos {
	pos() : depth(0), position(0) {}
	int depth;
	int position;
};

int main(int argc, char** argv ) {
	auto filename = argv[1];
	std::ifstream infile{ filename };

	std::string line = "";
	pos position{};
	
	while(std::getline(infile,line))
	{
		std::string direc = "";
		int i = 0;

		do direc += line[i];
		while(line[++i] != ' ');
		i++;

		int amount = std::stoi(line.substr(i));
		if( direc == "forward" )
			position.position+=amount;
		else if( direc == "down" )
			position.depth+=amount;
		else if( direc == "up" )
			position.depth-=amount;

	}

	std::cout << (position.position*position.depth) << "\n";

}

