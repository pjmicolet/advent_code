#include <iostream>
#include <numeric>
#include <set>
#include <unordered_map>
#include <string>
#include "utils/input_parser.h"
#include <tuple>
#include <list>

using numberPos = std::tuple< int, int, int>;

struct ColRow {
	ColRow(size_t size ) {
		line_ = std::vector<bool>(size, false);
		size_ = size;
		set_ = 0;
	}
	bool set(size_t index){
		line_[index]=true;
		set_++;
		if(set_ == size_)
			return true;//we're done
		return false;
	}
	private:
		std::vector<bool> line_;
		size_t size_;
		size_t set_;
};

struct BingoCard {

	BingoCard( size_t x, size_t y, std::vector< numberPos > numbers  )
	{
		for(int i = 0; i < x; i++ )
			cols_.push_back( ColRow( x ) );
		for(int i = 0; i < y; i++ )
			rows_.push_back( ColRow( y ) );
		for(auto& number : numbers )
		{
			auto [bingoNumber,colIndex,rowIndex] = number;
			pos_[bingoNumber] = std::make_pair(colIndex,rowIndex);
			remaining_numbers_.insert(bingoNumber);
		}
	}

	int setNumber( int number )
	{
		if( pos_.contains(number) )
		{
			auto [col, row] = pos_[number];
			bool done = false;
			done |= cols_[col].set(row);
			done |= rows_[row].set(col);
			remaining_numbers_.erase(number);
			if( done )
			{
				auto acc = std::accumulate(remaining_numbers_.begin(),remaining_numbers_.end(),0);
				return acc*number;
			}

		}
		return 0;
	}
	std::vector<ColRow> cols_;
	std::vector<ColRow> rows_;
	std::unordered_map<int, std::pair<int,int> > pos_;
	std::set<int> remaining_numbers_;
};

int main(int argc, char** argv ) {
	std::string filename = argv[1];
	InputParser parser{filename};
	std::vector<std::string> plays;
        parser.readLine( plays, ',');

	// There's an empty line to split things
	std::string line;
	parser.readLine( line );
	
	std::vector< numberPos > numbers;
	std::vector< std::string > splitLine;
	std::vector<int> nums;
	std::list<BingoCard> cards;
	std::unordered_map<int, std::vector<BingoCard*> > numToBing;
	int row = 0;
	int col = 0;
	while(parser.readLine( splitLine, ' ' ) )
	{
		if(splitLine.empty())
		{
			cards.emplace_back(col,row,numbers);
			for(auto& num: nums )
				numToBing[num].push_back(&cards.back());
			row=0;
			nums.clear();
			numbers.clear();
		}
		else
		{
			col = 0;
			for(auto& number : splitLine )
			{
				nums.push_back(std::stoi(number));
				numbers.emplace_back(std::stoi(number),col,row);
				col++;
			}
			row++;
		}
		splitLine.clear();
	}
	for( auto& bingoNum : plays )
	{
		for( auto& card : numToBing[ std::stoi(bingoNum) ] )
		{
			auto winningNumber = card->setNumber(std::stoi(bingoNum));
			if( winningNumber != 0 )
			{
				std::cout << winningNumber << "\n";
				return 0;
			}
			
		}
	}
}

