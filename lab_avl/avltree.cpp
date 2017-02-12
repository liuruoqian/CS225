/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node * newroot = t->right;
    t->right = newroot->left;
    newroot->left = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = newroot;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    //updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    Node * newroot = t->left;
    t->left = newroot->right;
    newroot->right = t;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    t = newroot;
    t->height = max(heightOrNeg1(t->left),heightOrNeg1(t->right))+1;
    //updateHeight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

/*
template <class K, class V>
void AVLTree<K, V>::updateHeight(Node *& t){
    if (t == NULL){
        return;
    }
    else{
        updateHeight(t->left);
        updateHeight(t->right);
        t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right))+1;
    }
}
*/

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
/*
    if(subtree == NULL){
        return;
    }
    */
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    int leftBalance = 0;
    int rightBalance = 0;
    if(subtree->left != NULL)
        leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
    if(subtree->right != NULL)
        rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);

    if (balance == -2){
        if(leftBalance == -1)
            rotateRight(subtree);
        else
            rotateLeftRight(subtree);
    }

    else if (balance == 2){
        if(rightBalance == 1)
            rotateLeft(subtree);
        else 
            rotateRightLeft(subtree);
    }
    subtree->height = max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right))+1;
    //The node’s height should always be updated, even if no rotations are required.
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
        subtree = new Node(key, value);
        
    }
    else if (key < subtree->key){
        insert(subtree->left, key, value);
        
    }
    
    else if (key > subtree->key){
        insert(subtree->right, key, value);
        
    }
    
    rebalance(subtree);
    //subtree->height = max(heightOrNeg1(subtree->left),heightOrNeg1(subtree->right))+1;       
    
    
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node * temp = subtree;
            subtree = NULL;
            delete temp;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * & iop = rightMostChild(subtree->left);
            swap(subtree, iop);
            if (iop->left == NULL){
                delete iop;
                iop = NULL;
            }
            else{
                Node * temp = iop;
                iop = iop->left;
                delete temp;
            }

        } else {
            /* one-child remove */
            // your code here
            Node * temp = subtree;
            if (subtree->left == NULL) subtree = subtree->right;
            else subtree = subtree->left;
            delete temp;
        }
        // your code here
        //rebalance(subtree);
    }
}

template <class K, class V>
typename AVLTree<K, V>::Node *& AVLTree<K, V>::rightMostChild(Node *& subtree){
    if (subtree->right == NULL)
        return subtree;
    else
        return rightMostChild(subtree->right);
}


