/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    /// @todo Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the left child.
    return 2*currentIdx;
    //return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the right child.
    //return 0;
    return (2*currentIdx+1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    /// @todo Update to return the index of the parent.
    //return 0;
    return currentIdx/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    /// @todo Update to return whether the given node has a child
    
    if (2*currentIdx < _elems.size()) //???? ....
        return true;
    else return false;
    
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //return 0;
    
    if (rightChild(currentIdx) < _elems.size())
        if(higherPriority(_elems[leftChild(currentIdx)], _elems[rightChild(currentIdx)]))
            return leftChild(currentIdx);
        else return rightChild(currentIdx);
    else 
        return leftChild(currentIdx);
    
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    /// @todo Implement the heapifyDown algorithm.
    
    if (hasAChild(currentIdx)){
        size_t minIdx = maxPriorityChild(currentIdx);
        if(higherPriority(_elems[minIdx], _elems[currentIdx])){
            std::swap(_elems[currentIdx], _elems[minIdx]);
            heapifyDown(minIdx);
        }
    }
    
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying

    // empty heap should start at index 1, then push T() at index 0
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    /// @todo Construct a heap using the buildHeap algorithm
    
    _elems.push_back(T()); //push T() at index 0

    // start pushing elements at index 1
    for(size_t i = 0; i < elems.size(); i++)
        _elems.push_back(elems[i]);

    int size = _elems.size() - 1; //always 
    for (int i = parent(size); i > 0; i--) 
        heapifyDown(i);
    
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    /// @todo Remove, and return, the element with highest priority
    //return T();
    if ((*this).empty())
        return T();
    T minVal = _elems[1];
    _elems[1] = _elems.back();
    _elems.pop_back();
    heapifyDown(1);
    return minVal; 

}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    /// @todo Return, but do not remove, the element with highest priority
    //return T();
    if ((*this).empty())
        return T();
    T minVal = _elems[1];
    return minVal;
    
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    /// @todo Add elem to the heap
    
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
    
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    //return true;
    return (_elems.size() == 1);
}
