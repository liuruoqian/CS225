/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) return true;
    else if (first[curDim] == second[curDim]) 
        return (first < second);
    else return false;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int disCurr = 0;
    int disPot = 0;
    for (int i = 0; i < Dim; i ++){
        disCurr = disCurr + pow(target[i] - currentBest[i], 2);
        disPot = disPot + pow(target[i] - potential[i], 2);
    }
    if(disPot < disCurr)
        return true;
    else if (disCurr == disPot)
        return (potential < currentBest);
    else return false;
}





template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    points = newPoints;
    KDTree_helper(0, points.size()-1, 0);

}


template <int Dim>
void KDTree<Dim>::KDTree_helper(int left, int right, int dim){
    
    if (left >= right)
        return;
    int n = (left + right)/2;
    select (left, right, n, dim);

    if (n - left <= 1 && right - n <= 1)
            return;
    else{

        if (right - n > 1)
            KDTree_helper(n+1, right, (dim+1)%Dim);
    
        if (n - left > 1)
            KDTree_helper(left, n-1, (dim + 1)%Dim);
    }

    // the previous one only deal with part of the vector (left or right)
    
    /*
    int mindex;
    mindex = (left + right)/2;
    select(left, right, mindex, dim);
    if(left < mindex - 1)
        KDTree_helper(left, mindex - 1, (dim + 1) % Dim);
    if(right > mindex + 1)
        KDTree_helper(mindex + 1, right, (dim + 1) % Dim);
    */
}


/*

template <int Dim>
void KDTree<Dim>::swap(Point<Dim> & first, Point<Dim> & second){
    Point<Dim> t = first;
    first = second;
    second = t;
}

*/
template <int Dim>
int KDTree<Dim>::partition(int left, int right, int index, int dim){
    Point<Dim> pivotValue = points[index];
    std::swap(points[index], points[right]);
    int storeIndex = left;
    for (int i = left; i < right; i++){
        if (smallerDimVal(points[i], pivotValue, dim)){
            std::swap(points[storeIndex], points[i]);
            storeIndex ++;

        }
    }
    std::swap(points[right], points[storeIndex]);
    return storeIndex;
}


// sort the vector from left to right, and let the median in the middle,
// the elemetn on the left is lower than median, and element on the right 
// is larger than median
template <int Dim>
void KDTree<Dim>::select(int left, int right, int n, int dim){
    if (left >= right)
        return ;
    int pivotIndex = (left + right)/2;
    pivotIndex = partition(left, right, pivotIndex, dim);
    if(n == pivotIndex)
        return ;
    else if (n < pivotIndex)
        select(left, pivotIndex-1, n, dim);
    else
        select(pivotIndex+1, right, n, dim);
}

/*
template<int Dim>
int KDTree<Dim>::getDistance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
    int distance = 0;
    for(int i = 0; i < Dim; i++)
        distance += (point1[i]-point2[i])*(point1[i]-point2[i]);
    return distance;
}
*/

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //return Point<Dim>();

    return findNN(query, 0, points.size()-1, 0);
    
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNN(const Point<Dim>& query, int left, int right, int dim) const{
    
    Point<Dim> child;
    bool Left = false;
    int mid;

    if (left == right) 
        return points[left]; // if vector points has only one element, return

    else{

        mid = (left + right)/2; // parent node index!!

        if(smallerDimVal(query, points[mid], dim)){
            if (mid - left < 1)
                return points[left];
            else{
                child = findNN(query, left, mid-1, (dim+1)%Dim);
                // parentIndex = mid;
            }
            Left = true;
        }
        else{
            if (right - mid < 1) 
                return points[right];
            else{
                child = findNN(query, mid+1, right, (dim+1)%Dim);
                // parentIndex = mid;
            }
            Left = false;
        }

        int distToPlane = pow(query[dim]-points[mid][dim],2);
        int distChild = 0;
        int distParent = 0;
        Point<Dim> bestNode;
        Point<Dim> opposite;
        int currRadius;

        for (int i = 0; i < Dim; i++){
            distChild = distChild + pow(child[i]-query[i],2);
            distParent = distParent + pow(points[mid][i] - query[i], 2);
        }

        if(distParent < distChild){
            bestNode = points[mid];
            currRadius = distParent;
        }
        else if (distParent == distChild){
            if (points[mid] < child){
                bestNode = points[mid];
                currRadius = distParent;
            }
            else{
                bestNode = child;
                currRadius = distChild;
            }
        }
        else{
            bestNode = child;
            currRadius = distChild;
        }

        if(distToPlane <= currRadius){
            if (Left == true){
                if (right - mid < 1)
                    opposite = points[mid];
                else
                    opposite = findNN(query, mid+1, right, (dim+1)%Dim);      
            }
            else{
                if (mid - left < 1)
                    opposite = points[mid];
                else
                    opposite = findNN(query, left, mid-1, (dim+1)%Dim);
            }
            if(shouldReplace(query, bestNode, opposite))
                return opposite;
            else 
                return bestNode;
        }
        else 
            return bestNode;
        
    }

    
}





