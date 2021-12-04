#pragma once
#include <fstream>
#include <string>
#include <vector>

struct InputParser {
	InputParser( std::string& filename ) {
		infile_ = std::ifstream( filename );
	}

	bool readLine( std::vector< std::string >& buffer, char split )
	{
		std::string line = "";
		if( std::getline( infile_, line ) )
		{
			int i =0;
			std::string temp = "";
			while( i < line.size() )
			{
				do temp += line[i];
				while(line[++i] != split && i < line.size() );
				i++;
				buffer.push_back(temp);
				temp="";
			}
			return true;
		}
		return false;
	}

	bool readLine( std::string &line )
	{
		if( std::getline(infile_, line) )	
			return true;
		return false;
	}

	private:
		std::ifstream infile_;
};
