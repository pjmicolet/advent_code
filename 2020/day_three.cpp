#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <array>

template< int x_size, int y_size >
struct field {
	
	field() : x_( 0 ), y_( 0 ) { field_.reserve(y_size); };
	
	auto fill( std::string& line, int lineNum ) -> void {
		int yy = 0;
		field_[ lineNum ].reserve( x_size );
		for( auto& character : line ) {
			field_[ lineNum ][ yy++ ] = character == '.' ? 0 : 1;
		}
	};


	auto move( int x, int y ) -> void {
		x_ += x;
		y_ += y;
		x_ = x_ % x_size;
	}
	
	auto reset() -> void {
		x_ = 0;
		y_ = 0;
	}

	auto hit() -> bool {
		return field_[ y_ ][ x_ ] == 1;
	}

private:
	int x_;
	int y_;

	std::vector< std::vector<int> > field_;
};

typedef field< 31, 323 > partOne;

auto main( int argc, char** argv ) -> int {
	partOne fieldOne;

	std::ifstream file;
	file.open("day_three.txt");
	std::string data;
	int lineNum = 0;
	if( file.is_open() ) {
		while( std::getline( file, data ) ) {
			fieldOne.fill( data, lineNum );
			lineNum++;
		}
	}
	int down_moves = 1;
	int right_moves = 3;
	int y = 0;
	int trees = 0;
	while( y < 322 ) {
		fieldOne.move( right_moves, down_moves );
		y += down_moves;
		trees += fieldOne.hit();
	}

	std::cout << "Hit " << trees << "\n";
	fieldOne.reset();
	// { right, down }
	std::vector< std::pair< int, int > > moveSelection = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };
	trees = 0;
	long long int totalTrees = 1;
	for( auto& input : moveSelection )
	{
		int y = 0;
		right_moves = input.first;
		down_moves = input.second;
		trees = 0;
		while( y < 322 ) {
			fieldOne.move( right_moves, down_moves );
			y += down_moves;
			trees += fieldOne.hit();
		}
		totalTrees *= trees;
		fieldOne.reset();
	}
	std::cout << "Hit " << totalTrees << "\n";
	return 0;	
}
