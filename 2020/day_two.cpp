#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>

enum phase{ LOOKING_FOR_MIN, LOOKING_FOR_MAX, LOOKING_FOR_REPEAT, PARSING_PASSWORD };
auto partOne() -> void
{
	std::ifstream file;
	file.open("day_two.txt");
	std::string data;
	const char split = ':';
	const char countSplit = '-';
	if( file.is_open() )
	{
		int correctPwd = 0;
		while( std::getline( file, data ) )
		{
			char repeatedChar = ' ';
			int minCount = -1;
			int maxCount = -1;
			int count = 0;
			std::string countStack = "";
			int pass = 0;
			
			for( auto& character : data )
			{
				switch( pass )
				{
					case LOOKING_FOR_MIN: {
						if( character == countSplit )
						{
							minCount = std::stoi( countStack );
							countStack = "";
							pass++;
						}
						else
							countStack += character;
						break;
					}
					case LOOKING_FOR_MAX: {
						if( character == ' ' )
						{
							maxCount = std::stoi( countStack );
							countStack = "";
							pass++;
						}
						else
							countStack += character;
						break;
					}
				    case LOOKING_FOR_REPEAT: {
						if( character != ' ' )
						{
							repeatedChar = character;
							pass++;
						}
						break;
					}
					case PARSING_PASSWORD: {
						if( character != ' ' && character != split )
							count += character == repeatedChar;
						break;
					}
				}
			}
			correctPwd += ( count >= minCount && count <= maxCount );
		}
		file.close();
		std::cout << correctPwd << "\n";
	}
}

enum phasePartTwo{ LOOKING_FOR_FIRST, LOOKING_FOR_LAST, LOOKING_FOR_CHAR, REMOVING_CRUFT, INDEXING_PASSWORD };
auto partTwo() -> void
{
	std::ifstream file;
	file.open("day_two.txt");
	std::string data;
	const char split = ':';
	const char countSplit = '-';
	if( file.is_open() )
	{
		int correctPwd = 0;
		while( std::getline( file, data ) )
		{
			char repeatedChar = ' ';
			int firstIndex = -1;
			int secondIndex = -1;
			int count = 0;
			std::string countStack = "";
			int pass = 0;
			int currIndex = 1;
			bool alreadySeen = false;
			bool valid = false;
			
			for( auto& character : data )
			{
				switch( pass ) {
					case LOOKING_FOR_FIRST: {
						if( character == countSplit ) {
							firstIndex = std::stoi( countStack );
							countStack = "";
							pass++;
						}
						else countStack += character;
						break;
					}
					case LOOKING_FOR_LAST: {
						if( character == ' ' ) {
							secondIndex = std::stoi( countStack );
							countStack = "";
							pass++;
						}
						else countStack += character;
						break;
					}
				    case LOOKING_FOR_CHAR: {
						if( character != ' ' ) {
							repeatedChar = character;
							
							pass++;
						}
						break;
					}
					case REMOVING_CRUFT: {
						if( character != ' ' && character != split )
							pass++;
						else break;
					}
					case INDEXING_PASSWORD: {
						if( currIndex != firstIndex && currIndex != secondIndex ) {
							currIndex++;
							continue;
						}
						bool goodToGo = ( character == repeatedChar );
						if( goodToGo )
							valid = !alreadySeen;
						alreadySeen = goodToGo;
						currIndex++;
						break;
					}
				}
			}
			correctPwd += valid;
		}
		file.close();
		std::cout << correctPwd << "\n";
	}
}
auto main( int argc, char** argv ) -> int
{
	partOne();
	partTwo();
	return 0;
}
