#pragma once
#include <fstream>
#include <string>
#include <vector>

struct InputParser {
	InputParser( std::string& filename ) {
		infile_ = std::ifstream( filename );
		line_size_=-1;
		pos_=0;
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

	bool readColumn( std::string &line )
	{
		std::string tmp="";
		if( std::getline( infile_, tmp) )
		{
			if(line_size_==-1)
				line_size_=tmp.size();
			line+=tmp[pos_];
		}
		while(std::getline(infile_,tmp))
		{
			line+=tmp[pos_];
		}
		pos_++;
		infile_.seekg(0, std::ios::beg);
		return pos_<line_size_;
	}

	bool readLineAsCol( std::string &line, bool&nextLine )
	{
		std::string tmp = "";
		if( std::getline( infile_, tmp) )
		{
			if(line_size_==-1)
			{
				line_size_=tmp.size();
			}
			line+=tmp[pos_];
			nextLine=false;
			return true;
		}
		else
		{
			nextLine=true;
			pos_++;
			if( pos_ < line_size_ )
			{
				infile_.clear();
				infile_.seekg(0, std::ios::beg);
				std::getline(infile_, tmp );
				line += tmp[pos_];
				return true;
			}
			return false;
		}
		return false;
	}

	private:
		std::ifstream infile_;
		size_t line_size_;
		int pos_;
};
