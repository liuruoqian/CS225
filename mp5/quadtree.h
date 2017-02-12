/**
 * @file quadtree.h
 * Quadtree class definition.
 * @date Spring 2008
 */

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

/**
 * A tree structure that is used to compress PNG images.
 */
class Quadtree
{
  public:
    Quadtree(); /**< The Quadtree default constructor */
    
    /**<The Quadtree constructor given source image, and resolution */
    Quadtree(PNG const & source, int resolution);

    ~Quadtree();  

    Quadtree const & operator=(Quadtree const & other);

    Quadtree(Quadtree const & other);

    void buildTree(PNG const & source, int resolution); /**< A function to build QuadTree*/

    RGBAPixel getPixel(int x, int y) const;

    PNG decompress() const;

    // mp5.2 functions:
    void clockwiseRotate();

    void prune(int tolerance);

    int pruneSize(int tolerance)const;

    int idealPrune(int numLeaves)const;

  private:
    /**
     * A simple class representing a single node of a Quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class QuadtreeNode
    {
      public:
        QuadtreeNode* nwChild; /**< pointer to northwest child */
        QuadtreeNode* neChild; /**< pointer to northeast child */
        QuadtreeNode* swChild; /**< pointer to southwest child */
        QuadtreeNode* seChild; /**< pointer to southeast child */

        RGBAPixel element; /**< the pixel stored as this node's "data" */
    };

    QuadtreeNode* root; /**< pointer to root of quadtree */

    int resol; /**< remember the resolution */


    /**
     * A helper function of buildTree.
     */
    QuadtreeNode * buildTree_helper(PNG const & source, int d, int upleftX, int upleftY);

    void clearSub(QuadtreeNode * &subRoot); /**< clear subtree given a pointer to the subroot */

    void clear(); /**< helper function for destructor */
    
    QuadtreeNode * copy(QuadtreeNode * const & subRoot);

    //RGBAPixel getpixel(QuadtreeNode* temp, int x, int y, int i) const;

    QuadtreeNode * help_getPixel(int x, int y, int d, QuadtreeNode * subRoot) const;
    
    void Rotate_helper(QuadtreeNode * subRoot);

    void prune_helper(int tolerance, QuadtreeNode * subRoot);

    bool Prunable(QuadtreeNode * rootN, QuadtreeNode * leaf, int tolerance) const;

    int pruneSize_helper(QuadtreeNode * subRoot, int tolerance, int count) const;

    int idealPrune_helper(int numLeaves, int maxTol, int minTol) const;

/**** Functions for testing/grading                      ****/
/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};

#endif
