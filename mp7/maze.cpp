/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <queue>
#include <stack>
SquareMaze::SquareMaze(){

}

void SquareMaze::makeMaze(int width, int height){
	// declare the height/width and size
	wid = width;
	hgt = height;

	int size = wid * height;
	// If this object already represents a maze it will clear all the existing data before doing so
	// initialize the right wall and down wall to be true
	for (int i = 0; i < size; i++){
		downWall.push_back(true);
		rightWall.push_back(true);
	}
    // declare disjoint set for maze
	DisjointSets mazeSets; // private?
	mazeSets.addelements(size);
	int removed = 0;
	//srand (time(NULL)); set seed?
	//drop walls on right/down which will not cause cycle
	//walls on the right and down edge should not be removed
	while(removed < size - 1){
		//random select a square in the maze
		int random = rand() % size; //(0, size-1)
		int colNum = random % wid + 1; // 1 to wid
		int rowNum = random / wid + 1; // 1 to hgt
		int dir = rand() % 2; // dir = (0,1). Either 0 (right) or 1 (down)
		// go right and right wall is not the rightmost edge
		if (dir == 0 && colNum != wid){
			if (mazeSets.find(random) != mazeSets.find(random+1)){ // check for cycle
				rightWall[random] = false;
				mazeSets.setunion(random, random+1);
				removed ++;
			}
            
		}
		else if(dir == 1 && rowNum != hgt){
			if (mazeSets.find(random) != mazeSets.find(random+wid)){ // check for cycle
				downWall[random] = false;
				mazeSets.setunion(random, random+wid);
				removed ++;
			}
		}
	}
}

// independent of my maze class
bool SquareMaze::canTravel(int x, int y, int dir) const{
    //check right
	if (dir == 0 && x >= 0 && x < wid -1){ // x is valid, x not right edge
        return (!rightWall[y*wid + x]);
	}
	// check down
	if (dir == 1 && y >= 0 && y < hgt -1){
		return (!downWall[y*wid + x]);
	}
	// check left (check x-1 right)
	if (dir == 2 && x >0 && x < wid){
		return (!rightWall[y*wid + x -1]);
	}
	// check up (check y-1 down)
	if (dir == 3 && y >0 && y < hgt){
		return (!downWall[(y-1)*wid + x]);
	}
	return false;
}

// independent of my maze class
void SquareMaze::setWall(int x, int y, int dir, bool exists){
	int index = y * wid + x;
	if (dir == 0) rightWall[index] = exists;
	if (dir == 1) downWall[index] = exists;
}

vector<int> SquareMaze::solveMaze(){
	vector<int> solve; //target vector

	int size = wid * hgt;
	//construct a vector store distance from origin(0, 0) for each square
	vector<int> length(size, -1);
	// vector store the prev square of current square
	vector<int> prev(size, -1);
	// vector stores the direction which from prev to curr
	vector<int> direction(size, -1);
	// vector stores if current square has been visited
	vector<bool> visited(size, 0);

	queue<int> track;
	track.push(0); //origin
	visited[0] = 1;
	length[0] = 0;

	// go over every path possible from origin(start)
	while(track.empty() == false){
		int currSq = track.front();
		int x = currSq % wid;
		int y = currSq / wid;

		if(canTravel(x, y, 0)){ // can go right
			if(visited[currSq+1] == 0){ //unvisited
				length[currSq + 1] = length[currSq] + 1;
				visited[currSq+1] = 1; //visited
				direction[currSq + 1] = 0;
				prev[currSq+1] = currSq;
				track.push(currSq+1);
			}
		}
		if(canTravel(x, y, 1)){
			if(visited[currSq + wid] == 0){
				length[currSq +wid] = length[currSq]+1;
				visited[currSq + wid] = 1; //visited
				direction[currSq + wid] = 1;
				prev[currSq + wid] = currSq;
				track.push(currSq+wid);
			}
		}
		if(canTravel(x, y, 2)){
			if (visited[currSq -1] == 0){
				length[currSq - 1] = length[currSq]+1;
				visited[currSq -1] = 1; // visited
				direction[currSq -1] = 2;
				prev[currSq -1] = currSq;
				track.push(currSq-1);
			}
		}
		if(canTravel(x, y, 3)){
			if(visited[currSq - wid] == 0){
				length[currSq - wid] = length[currSq] + 1;
				visited[currSq - wid] = 1; //visited
				direction[currSq - wid] = 3;
				prev[currSq - wid] = currSq;
				track.push(currSq - wid);
			}
		}

		track.pop();
	}

	//calculate distance on the bottom row, pick the longest path
	// and find the exit
	int maxdist = 0;
	int exit;
	for (int i = wid * (hgt - 1); i < size; i++){
		if (length[i] > maxdist){
			maxdist = length[i];
			exit = i;
		}
	}

	int back = exit;
	stack<int> backPath;
	while(back != 0){ // not to origin
		backPath.push(direction[back]);
		back = prev[back];
	}

	while(backPath.empty() == false){
		int elem = backPath.top();
		solve.push_back(elem);
		backPath.pop();
	}

	return solve;	
}


PNG * SquareMaze::drawMaze()const{
	PNG * ret = new PNG(wid*10 + 1, hgt * 10 + 1);
	//blacken the topmost and leftmost walls
	for (int i = 10; i < wid*10 + 1; i ++){
		(*ret)(i,0)->red = 0;
		(*ret)(i,0)->green = 0;
		(*ret)(i,0)->blue = 0;
	}
	for (int i = 0; i < hgt*10 + 1; i++){
		(*ret)(0,i)->red = 0;
		(*ret)(0,i)->green = 0;
		(*ret)(0,i)->blue = 0;
	}

	int size = wid*hgt;
	for(int i = 0; i < size; i++){
		int x = i % wid;
		int y = i / wid;
		if(rightWall[i]){
			for(int k = 0; k <= 10; k++){
				(*ret)((x+1)*10,y*10+k) -> red = 0;
				(*ret)((x+1)*10,y*10+k) -> green = 0;
				(*ret)((x+1)*10,y*10+k) -> blue = 0;
			}
		}
		if(downWall[i]){
			for(int k = 0; k <= 10; k++){
				(*ret)(x*10+k, (y+1)*10) -> red = 0;
				(*ret)(x*10+k, (y+1)*10) -> green = 0;
				(*ret)(x*10+k, (y+1)*10) -> blue = 0;
			}
		}

	}
	return ret;
    
}

PNG * SquareMaze::drawMazeWithSolution(){
	PNG * ret = drawMaze();
	vector<int> solve = solveMaze();
	int x = 5;
	int y = 5;
	for(size_t i = 0; i < solve.size(); i++){
		if(solve[i] == 0){ // go right
			for(int k = 0; k <= 10; k++){
				(*ret)(x+k,y) -> red = 255;
				(*ret)(x+k,y) -> green = 0;
				(*ret)(x+k,y) -> blue = 0;
			}
			x = x+10;
		}
		if(solve[i] == 1){
			for(int k = 0; k <= 10; k++){
				(*ret)(x,y+k)->red = 255;
				(*ret)(x,y+k)->green = 0;
				(*ret)(x,y+k)->blue = 0;
			}
			y = y+10;
		}
		if(solve[i] == 2){
			for(int k = 0; k <= 10; k++){
				(*ret)(x-k,y)->red = 255;
				(*ret)(x-k,y)->green = 0;
				(*ret)(x-k,y)->blue = 0;
 			}
 			x = x-10;
		}
		if(solve[i] == 3){
			for(int k = 0; k <= 10; k++){
				(*ret)(x,y-k)->red = 255;
				(*ret)(x,y-k)->green = 0;
				(*ret)(x,y-k)->blue = 0;
			}
			y = y-10;
		}

	}
	// deal with the exit
	int endX = x/10;
	int endY = hgt - 1;
	for(int k = 1; k < 10; k++){
		(*ret)(endX*10+k, (endY+1)*10)->red = 255;
		(*ret)(endX*10+k, (endY+1)*10)->green = 255;
		(*ret)(endX*10+k, (endY+1)*10)->blue = 255;
	}

	return ret;

}





