/* Your code here! */

#include "dsets.h"

/*Creates n unconnected root nodes at the end of the vector.*/

void DisjointSets::addelements(int num){
	for (int i = 0; i < num; i++){
		disSet.push_back(-1);
	}
}

/* This function should compress paths 
 * and works as described in lecture. */
int DisjointSets::find(int elem){
	if (disSet[elem] < 0) return elem;
	else
		return disSet[elem] = find(disSet[elem]);

}

/* This function should be implemented as union-by-size.
 * That is, when you setunion two disjoint sets, 
 * the smaller (in terms of number of nodes) should point at the larger. 
 * This function works as described in lecture, except that you should 
 * not assume that the arguments to setunion are roots of existing uptrees.
 * Your setunion function SHOULD find the roots of its arguments before combining 
 * the trees. If the two sets are the same size, make the tree containing the second 
 * argument point to the tree containing the first. 
 */

void DisjointSets::setunion	(int a, int b){
    int root1 = find(a);
    int root2 = find(b);
    //if a and b share the same root, a and b in the same set.
    if(root1 == root2)
    	return;

    int newsize = disSet[root1]+disSet[root2];
    // root2 representing a smaller tree, root2 should points to root1
    if (disSet[root2] >= disSet[root1]){
    	disSet[root2] = root1;
    	disSet[root1] = newsize;
    }
    else {
    	disSet[root1] = root2;
    	disSet[root2] = newsize;
    }

}



