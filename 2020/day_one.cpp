#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>


int maxGlobal = 0;

auto recursiveSearch( int currentSum, int currentIndex, int currentCount, std::vector< int >& search, std::vector< int >& threeNums ) -> void
{
	currentCount++;
	for( int i = currentIndex; i < search.size(); i++ ) 
	{
		int tempSum = currentSum + search[ i ];
		if( tempSum == 2020 && currentCount == 2 )
		{
			auto res = 1;
			threeNums[ currentCount ] = search[i];
			for( auto & val : threeNums ) res *= val;
			maxGlobal = maxGlobal < res ? res : maxGlobal;
		}
		else if( currentCount > 2 )
		{
			return;
		}
		threeNums[ currentCount ] = search[ i ];
		recursiveSearch( tempSum, i+1, currentCount, search, threeNums );
	}
} 

auto main( int argc, char** argv ) -> int
{
	std::ifstream file;
	file.open("day_one.txt");
	std::string data;
	std::unordered_map< int, int > nums;
	std::vector< int > search;
	if( file.is_open() )
	{
		while( std::getline( file, data ) )
		{
			nums[ std::stoi( data ) ] = 0;
			search.push_back( std::stoi( data ) );
		}
		file.close();
	}
	int max = 0;
	for( auto& data : nums )
	{
		if( data.second == 0 )
		{
			int other = 2020-data.first;
			if( other < 0 )
				continue;
			if( nums.find( other ) != nums.end() )
			{
				if( max < other * data.first )
					max = other * data.first;
				nums[other] = 1;
			}
		}
	}

	auto index = 0;
	std::vector< int > threeNums;
	threeNums.resize( 3 );
	for( auto & data : search )
	{
		index++;
		threeNums[ 0 ] = data;
		recursiveSearch( data, index, 0, search, threeNums );
	}
	std::cout << max << std::endl;
	std::cout << maxGlobal << std::endl;
	return 0;
}
