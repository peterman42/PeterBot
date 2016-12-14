#ifndef ROUTE_H
#define ROUTE_H
#include <string>
#include <vector>
#include "move.h"

class Route{
public:
	std::vector<float> obstaclesX;
	std::vector<float> obstaclesY;
	std::vector<float> subroutesInCentiM;
	std::vector<std::string> routeName;
	std::vector<Move> moves;
public:
	Route(){};
	~Route(){};
	void addX(float x);
	void addY(float y);
	void addSubroute(float distance);
	void setName(std::string name);
	void addMove(Move move);
};

//////////////////////////////////////////////////////////////////
void Route::addX(float x){
	X.push_back(x);
}

//////////////////////////////////////////////////////////////////
void Route::addY(float y){
	Y.push_back(y);
}

//////////////////////////////////////////////////////////////////
void Route::addSubroute(float distance){
	subroutesInCentiM.push_back(distance);

}

//////////////////////////////////////////////////////////////////
void Route::setName(std::string name){
	routeName.push_back(name);
}

//////////////////////////////////////////////////////////////////
void Route::addMove(Move move){
	moves.push_back(move);
}
#endif
