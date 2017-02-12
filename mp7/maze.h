/* Your code here! */
#include <vector>
#include "png.h"
using namespace std;

#ifndef _MAZE_H
#define _MAZE_H

class SquareMaze{
public:
	SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	vector<int> solveMaze();
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();

private:
	int wid;
	int hgt;
	vector<bool> downWall;
	vector<bool> rightWall;

};

#endif