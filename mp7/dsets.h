/* Your code here! */
/* the structure itself is a vector of ints, union by size is applied*/

#ifndef _DSETS_H_
#define _DSETS_H_

#include <vector>

class DisjointSets{
public:
	void addelements(int num);
	int find(int elem);
	void setunion(int a, int b);

private:
	// the only member data is vector of ints, which should be initialized to be empty
	std::vector<int> disSet;

};


//#include "dsets.cpp"

#endif