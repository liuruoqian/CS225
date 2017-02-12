/**
 * @file quadtree.cpp
 * Quadtree class implementation.
 * @date Spring 2008
 */
#include "quadtree.h"
#include <iostream>
#include <cmath>

using namespace std;

/** 1. check if all function are named correctly.
    2. check if the ideas are correctly represented.
    3. other possible solution?
 */


/**
 * A buildTree helper function, which takes four auguments: PNG source, length of 
 * root square d, x coordinate of upper left corner upleftX, y coordinate of upper 
 * left corner upleftY. This function will return a pointer to a quadtree root which
 * is recursively built as instructed and representing a dxd square whose upper left corner is at 
 * (upleftX, upleftY) of source PNG image.
 */
Quadtree::QuadtreeNode * Quadtree::buildTree_helper(PNG const & source, int d, int upleftX, int upleftY){
	QuadtreeNode * root = new QuadtreeNode;

	if (d == 0) root = NULL;

	if (d == 1){
		root->nwChild = NULL;
		root->neChild = NULL;
		root->swChild = NULL;
		root->seChild = NULL;
		root->element = *(source(upleftX, upleftY));
	}
	else{
		d = d/2;
		root->nwChild = buildTree_helper(source, d, upleftX, upleftY);
		root->neChild = buildTree_helper(source, d, upleftX+d, upleftY);
		root->swChild = buildTree_helper(source, d, upleftX, upleftY+d);
		root->seChild = buildTree_helper(source, d, upleftX+d, upleftY+d);

		RGBAPixel nwColor = root->nwChild->element;
		RGBAPixel neColor = root->neChild->element;
		RGBAPixel swColor = root->swChild->element;
		RGBAPixel seColor = root->seChild->element;
		
		(root->element).red = (nwColor.red + neColor.red + swColor.red + seColor.red)/4;
		(root->element).blue = (nwColor.blue + neColor.blue + swColor.blue + seColor.blue)/4;
		(root->element).green = (nwColor.green + neColor.green + swColor.green + seColor.green)/4;
	}

	return root;
	//build the Quadtree itself

}

/**
 * A buildTree function takes two arguments: source PNG image, int resolution. 
 * This function will be implemented by buildTree helper function, in which, d is 
 * corresponding is int resolution, and the upper left corner is at (0,0).
 */

void Quadtree::buildTree(PNG const & source, int resolution){
	if (root != NULL)
		clear();
	//resol = 0;

	root = buildTree_helper(source, resolution, 0, 0);
	resol = resolution;
}

/**
 * QuadTree Constructors
 */

Quadtree::Quadtree(){
	// initialize two private member variables
	root = NULL;
	resol = 0;
}

Quadtree::Quadtree(PNG const & source, int resolution){
	//buildTree(source, resolution);
	// buildTree will set up the root and resol.
	root = buildTree_helper(source, resolution, 0, 0);
	resol = resolution;
}

/**
 * The Big Three: Destructor
 */
Quadtree::~Quadtree(){
	clear();
}

/** helper function of destructor */

void Quadtree::clear(){
	clearSub(root);
	resol = 0;
}

/** A function which clears Quadtree and treeNodes */

void Quadtree::clearSub(QuadtreeNode * &subRoot){
    if (subRoot == NULL) return;

    clearSub(subRoot->nwChild);
    clearSub(subRoot->neChild);
    clearSub(subRoot->swChild);
    clearSub(subRoot->seChild);
    delete subRoot;
    subRoot = NULL;
}

/**
 * The Big Three: Copy Constructor
 */

Quadtree::Quadtree(Quadtree const & other){
	root = copy(other.root);
	resol = other.resol;

}	

/** Cctor helper function */
Quadtree::QuadtreeNode * Quadtree::copy(QuadtreeNode * const & subRoot){
	QuadtreeNode * copyRoot;

	if (subRoot == NULL)
		copyRoot = NULL;
	else if (subRoot->nwChild == NULL){ // leaf node
		copyRoot = new QuadtreeNode;
		copyRoot->element = subRoot->element;
		copyRoot->nwChild = NULL;
		copyRoot->neChild = NULL;
		copyRoot->swChild = NULL;
		copyRoot->seChild = NULL;
	}
	else{
		copyRoot = new QuadtreeNode;
		copyRoot->element = subRoot->element;
		copyRoot->nwChild = copy(subRoot->nwChild);
		copyRoot->neChild = copy(subRoot->neChild);
		copyRoot->swChild = copy(subRoot->swChild);
		copyRoot->seChild = copy(subRoot->seChild);
	}
	return copyRoot;
}

/**
 * The Big Three: operator = 
 */

Quadtree const & Quadtree::operator=(Quadtree const & other){
	if (this != &other){
		clear();
		root = copy(other.root);
		resol = other.resol;
	}
	return (*this);
}

/**
 * Gets the RGBAPixel corresponding to the pixel at coordinates (x, y) 
 * in the bitmap image which the Quadtree represents.
 */
 

RGBAPixel Quadtree::getPixel(int x, int y) const{
	RGBAPixel pixel = RGBAPixel(); // created by RGBAPixel default ctor 
	if ((x > (resol-1)) || (y > (resol-1))|| (x < 0 )|| (y < 0 )|| root == NULL)
		return pixel;
	else{
        return help_getPixel(x,y,resol,root)->element;
	}
}

/**
 * getPixel helper function. When (x,y) falls in the bounds, and Quadtree is not 
 * empty, return the pointer which points to the QuadtreeNode that contains the target
 * RGBAPixel. We assume subRoot is not NULL, and x, y are less than d, because this
 * helper function is only called under these conditions. 
 */

Quadtree::QuadtreeNode * Quadtree::help_getPixel(int x, int y, int d, QuadtreeNode * subRoot) const{
	QuadtreeNode * target;

	if (d == 1)
		target = subRoot;

	else{
		if (subRoot->nwChild != NULL){ //subRoot is not leaf node
			int newx = x - d/2;
			int newy = y - d/2;
			if (x < d/2 && y < d/2) 
				target = help_getPixel(x,y,d/2,subRoot->nwChild);
			else if (x >= d/2 && y < d/2)
				//int newx = x - d/2;
				target = help_getPixel(newx,y,d/2,subRoot->neChild);
			else if (x < d/2 && y >= d/2)
				//int newy = y - d/2;
				target = help_getPixel(x,newy,d/2,subRoot->swChild);
			else
				target = help_getPixel(newx,newy,d/2,subRoot->seChild);
		}

		else{
			target = subRoot;
		}
	}

	return target;

}



PNG Quadtree::decompress() const{
	if (root == NULL){
		return PNG();
	}
	else{
		PNG img = PNG(resol, resol);
		for (int i = 0; i < resol; i++){
			for (int j = 0; j < resol; j++){
				*(img(i, j)) = getPixel(i,j);
			}
		}
	return img;
	}
}



/**
 * MP 5.2
 */

void Quadtree::clockwiseRotate(){
    Rotate_helper(root);
 	return;
 }

void Quadtree::Rotate_helper(QuadtreeNode * subRoot){
	if (subRoot == NULL)
		return;
	else{
		Rotate_helper(subRoot->nwChild);
		Rotate_helper(subRoot->neChild);
		Rotate_helper(subRoot->seChild);
		Rotate_helper(subRoot->swChild);
		QuadtreeNode * tempNW = subRoot->nwChild;
		subRoot->nwChild = subRoot->swChild;
		subRoot->swChild = subRoot->seChild;
		subRoot->seChild = subRoot->neChild;
		subRoot->neChild = tempNW;
	}
}

void Quadtree::prune(int tolerance){
    prune_helper(tolerance, root);
 	return;
}

void Quadtree::prune_helper(int tolerance, QuadtreeNode * subRoot){
	if (subRoot == NULL) return;
	else if (subRoot->nwChild == NULL){
		return;
	}
	else{
		if(Prunable(subRoot, subRoot, tolerance)){
			clearSub(subRoot->nwChild);
			clearSub(subRoot->neChild);
			clearSub(subRoot->swChild);
			clearSub(subRoot->seChild);
		}
		else{
			prune_helper(tolerance, subRoot->nwChild);
			prune_helper(tolerance, subRoot->neChild);
			prune_helper(tolerance, subRoot->swChild);
			prune_helper(tolerance, subRoot->seChild);
		}
	}
}

/**
 * Helper function to check prunable for a subtree root node. 
 * Compare root element with every leaf node element. 
 * Return true if the conditions are met.
 */
bool Quadtree::Prunable(QuadtreeNode * rootN, QuadtreeNode * leaf, int tolerance) const{
    // if (rootN == NULL)
    bool prunable;
    if (leaf == NULL) prunable = true;
    else if (leaf->nwChild == NULL){ 
    	int diffRed = pow((rootN->element.red - leaf->element.red),2);
        int diffBlue = pow((rootN->element.blue - leaf->element.blue),2);
        int diffGreen = pow((rootN->element.green - leaf->element.green),2);
        int diff = diffRed + diffBlue + diffGreen;
        if (diff <= tolerance) 
        	prunable = true;
        else 
        	prunable = false;
    }
    // can be revised to check one pair each time, and probably can save time..
    // !!!!!
    else{
    	prunable = (Prunable(rootN, leaf->nwChild, tolerance) && Prunable(rootN, leaf->neChild, tolerance) && Prunable(rootN, leaf->swChild, tolerance) && Prunable(rootN, leaf->seChild, tolerance));

    }
    return prunable;
}

int Quadtree::pruneSize(int tolerance)const{
    
	return pruneSize_helper(root, tolerance, 0);
}

/*
int Quadtree::countLeaves(QuadtreeNode * subRoot){
	int numLeaves;
	if(subRoot == NULL){
		numLeaves = 0;
	}
	else if(subRoot->nwChild == NULL){
		numLeaves = 1;
	}
	else{
        return (countLeaves(subRoot->nwChild)+countLeaves(subRoot->neChild)+countLeaves(subRoot->swChild)+countLeaves(subRoot->seChild));
	}
}
*/

int Quadtree::pruneSize_helper(QuadtreeNode * subRoot, int tolerance, int count) const{
	if(subRoot == NULL){
		count = count + 0;
		return count;
	}

	else if(Prunable(subRoot, subRoot, tolerance)) {
		count = count + 1;
		return count; 
	}

	else{
		int count1 = pruneSize_helper(subRoot->nwChild, tolerance, count);
		int count2 = pruneSize_helper(subRoot->neChild, tolerance, count1);
		int count3 = pruneSize_helper(subRoot->swChild, tolerance, count2);
		int count4 = pruneSize_helper(subRoot->seChild, tolerance, count3);
		return count4;
	}
	//return count;
}





int Quadtree::idealPrune(int numLeaves)const{
	int maxTol = 255*255*3;
	int minTol = 0;
	return idealPrune_helper(numLeaves, maxTol, minTol);
}

int Quadtree::idealPrune_helper(int numLeaves, int maxTol, int minTol) const{
	if(maxTol - minTol <= 1){
		if (pruneSize(minTol) <= numLeaves)
			return minTol;
		else return maxTol;
		//return maxTol;
	}
	//else if (maxTol - minTol == 1)

	int midTol = (maxTol + minTol)/2;
	if (pruneSize(midTol) <= numLeaves){
		return idealPrune_helper(numLeaves, midTol, minTol);

	}
	else
		return idealPrune_helper(numLeaves, maxTol, midTol);
}








