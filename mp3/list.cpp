#include <iostream>
using namespace std;

/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1clear
    ListNode * Temp = head;
    head = NULL;
    while (Temp != NULL){
        Temp = Temp->next;
        if (Temp != NULL){
            delete Temp->prev;
            Temp->prev = NULL;
        }
        else {
            delete tail;
            tail = NULL;
        }

    }
    length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata)
{
    /// @todo Graded in MP3.1
    ListNode * Front = new ListNode(ndata);
    if (length == 0){
        head = Front;
        tail = Front;
        head->next = NULL;
        head->prev = NULL;
        Front = NULL;
    }
    else{
        Front->next = head;
        head = Front;
        Front = NULL;
        (head->next) -> prev = head;
        head -> prev = NULL;
    }
    length = length + 1;
}


/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata)
{
    /// @todo Graded in MP3.1
    ListNode * Back = new ListNode(ndata);
    if (length == 0){
        head = Back;
        tail = Back;
        head->next = NULL;
        head->prev = NULL;
        Back = NULL;
    }
    else{
        Back->prev = tail;
        tail->next = Back;
        tail = Back;
        Back = NULL;
        tail->next = NULL;
    }
    length = length + 1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint)
{
    /// @todo Graded in MP3.1

    if(startPoint == endPoint ||startPoint == NULL || endPoint == NULL) 
        return;

    else{
        ListNode * curr;
        ListNode * end_next;
        ListNode * start_prev;
        ListNode * start_next;

        curr = startPoint;
        end_next = endPoint->next; 
        start_prev = startPoint->prev;
        while (curr != endPoint){
            ListNode * P;
            P = curr->prev;
            curr->prev = curr->next;
            curr->next = P;
            curr = curr->prev;
        }  //This loop is right.

        ListNode * N = curr->prev;

        curr->prev = start_prev;
        curr->next = N;

        endPoint = startPoint;  //why switch at last part does not work?
        startPoint = curr;

        endPoint->next = end_next;

        if (start_prev == NULL){
            head = startPoint;
        }
        else{
            start_prev->next = startPoint;
        }
        if (end_next == NULL){
            tail = endPoint;
        }
        else{
            end_next->prev = endPoint;
        }

    }


/*
        S2->next = endPoint;
        endPoint->prev = S2;
        startPoint->next = G;
        
        if(G == NULL){
            tail = startPoint;
        }
        else{
            G->prev = startPoint;
        }
        if(S2 == NULL){
            head = endPoint;
        }
        else{
            S2->next = endPoint;
        }
        
    }
*/
    
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n)
{
    /// @todo Graded in MP3.1
    
    if (n <= 1)
        return;
    if (length <= n){
        reverse();
        return;
    }

    int count = 1;
    ListNode * S = head;
    ListNode * end = head;     

    while (S != NULL && S->next != NULL){ 
        //curr = S; 
        while (end->next != NULL && count< n){
            end = end->next;
            count ++;
        }

        reverse(S, end);
        S = end->next;
        end = S;    
        count = 1;       
    }

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
    if (head == NULL || head->next == NULL) return;
    ListNode * curr;
    ListNode * theNext;
    curr = head->next; // The first thing to be removed
    while (curr != tail && curr != NULL){
        theNext = curr->next;
        (curr->prev)->next = curr->next;
        (curr->next)->prev = curr->prev;
        tail->next = curr;
        curr->prev = tail;
        curr->next = NULL;
        tail = curr;
        curr = theNext->next;
    }
}  // Done!!!And well done!!!!

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head) {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    } else {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL) {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint)
{
    /// @todo Graded in MP3.2
    if (head == NULL) return NULL;
    if (start == NULL || splitPoint <= 0) 
        return start;

    ListNode * secondhead = start;
    ListNode * secondtail;
    int i = 0;
    while(i < splitPoint && secondhead != NULL){
        secondhead = secondhead->next;
        i++;
    }
    if (secondhead == NULL){
        return secondhead;
    }
    else{
        secondtail = tail;
        tail = secondhead->prev;
        secondhead->prev->next = NULL;
        secondhead->prev = NULL;
        return secondhead;
    }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if (tail != NULL) {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second)
{
    /// @todo Graded in MP3.2
    
    ListNode * curr1, * curr2, * track, * merged;
    
    if (first == NULL && second == NULL) return NULL;
    else if (first == NULL) return second;
    else if (second == NULL) return first;
    else if (second == first) return first;
    else{
           
        curr1 = first; //curr1 is the track on list1
        curr2 = second;  //curr2 is the track on list2
    
        if (first->data < second->data){
            curr1 = first->next;
            merged = first;
        }
        else{
            curr2 = curr2->next;
            merged = second;
        }
        
        track = merged; // start with the smallest value
  
            while(curr1 != NULL && curr2 != NULL){
                if(curr2->data < curr1->data){ 
                //curr2 is smaller

                    track ->next = curr2;
                    curr2->prev = track;
                    track = curr2;
                    curr2 = curr2->next;
                    //track->next = curr1;
                    //curr1->prev = track;
                }

                else{ 
                    //curr1 is smaller, put curr1 on the list
                    track ->next = curr1;
                    curr1 ->prev = track;
                    track = curr1;
                    curr1 = curr1->next;
                }
            }
            if (curr2 != NULL){
                track->next = curr2;
                curr2->prev = track;
            }
            else{
                track->next = curr1;
                curr1->prev = track;
            }

            first = NULL;
            second = NULL;
            return merged;       
        }           
    
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength)
{
    /// @todo Graded in MP3.2
    
    if (start == NULL || chainLength == 0) return NULL;

    ListNode * secondhead, * h1, * h2, * sorted;
    if (chainLength == 1){
        return start;
    }

    secondhead = split(start,chainLength/2);
    h1 = mergesort(start, chainLength/2);
    h2 = mergesort(secondhead, chainLength-chainLength/2);
    sorted = merge(h1, h2);

    return sorted; // change me!
    
    
}
