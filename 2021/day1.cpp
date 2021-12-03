#include <iostream>
#include <fstream>
#include <string>

int main( int argc, char** argv)
{
	auto filename = argv[1];
	std::ifstream infile{ filename };

	std::string line = "";
	int level = 0;
	int next_level = -1;

	if(std::getline(infile, line))
		level = stoi(line);

	int increases = 0;
	while(std::getline(infile,line))
	{
		next_level = std::stoi(line);
		if( next_level > level )
			increases++;
		level=next_level;

	}

	std::cout << increases << "\n";
}
