#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include "bst.h"

template<typename Key, typename Value>
class SplayTree : public BinarySearchTree<Key, Value>
{
 public:
  SplayTree();
  ~SplayTree();
  
  // All of the basic operations that one would perform on a map. 
  // Do not change these function definitions, but you may add others
  void insert(const std::pair<Key, Value>& keyValuePair);
  void clear();


public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    * TODO: You must implement this!
    */
    class iterator
    {
    public:
        // Constructors - must be implemented below!
        iterator();
        iterator(Node<Key,Value>* ptr);

        // Various operators - some must be implemented below!
        std::pair<Key,Value>& operator*(); // Already implemented for you.
        std::pair<Key,Value>* operator->(); // Already implemented for you.
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        iterator& operator=(const iterator& rhs);
        iterator& operator++();
        Node<Key, Value>* mCurrent;

    protected:
        // A pointer to the current node.
        // Node<Key, Value>* mCurrent;

        /* Feel free to add additional data members and/or helper functions! */

    };

public:
    // Access to data through iterators, just like you are used to with std::map, std::set,
    // std::vector, etc.
    iterator begin();
    iterator end();
    Node<Key, Value>* internalFind(const Key& key) const;
    // iterator find(const Key& key) const; //iterator find

public:
  iterator find(const Key& k); // remember a find
                               // also requires splaying
  Value get(const Key& k);
  Value operator[](const Key& k);
  
 private:
  // Add any private data members and member functions as needed. 
 	void rotateLeft(Node<Key, Value>* x);
 	void rotateRight(Node<Key, Value>* x);
 	void splay(Node<Key, Value>* x);

};

//*******ITERATORS*******
//*******ITERATORS*******
//*******ITERATORS*******
//*******ITERATORS*******
//*******ITERATORS*******

/**
* Initialize the internal members of the iterator.
* You can choose what kind of iterator the default constructor should create.
*/
template<typename Key, typename Value>
SplayTree<Key, Value>::iterator::iterator()
{
    // TODO
    mCurrent = NULL; 
}

/**
* Initialize the internal members of the iterator.
*/
template<typename Key, typename Value>
SplayTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
{
    // TODO
    mCurrent = ptr;
}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>& SplayTree<Key, Value>::iterator::operator*()
{
    return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<Key, Value>* SplayTree<Key, Value>::iterator::operator->()
{
    return &(mCurrent->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool SplayTree<Key, Value>::iterator::operator==(const SplayTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->mCurrent == rhs.mCurrent; 
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool SplayTree<Key, Value>::iterator::operator!=(const SplayTree<Key, Value>::iterator& rhs) const
{
    // TODO
    return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator& SplayTree<Key, Value>::iterator::operator=(const SplayTree<Key, Value>::iterator& rhs)
{
    // TODO
    this->mCurrent = rhs.mCurrent;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator& SplayTree<Key, Value>::iterator::operator++()
{
    // TODO
    //let's play the game: FIND the successor

    Node<Key, Value>* mCurrentP = NULL; //makes sure we capture the successor

    if (mCurrent->getRight() != NULL) //right child exists
    {
        mCurrent = mCurrent->getRight(); //we can now explore the right subtree left children
        mCurrentP = mCurrent->getParent(); //keep track of the actual successor
        while(mCurrent->getLeft() != NULL) //walk as far left as possible
        { 
            mCurrent = mCurrent->getLeft();
            mCurrentP = mCurrent->getParent();
        }
        mCurrent = mCurrentP;
        return this;
    }
    else //walk up ancestor chian until you find that particular parent/child relationship
    {
        bool found = false;
        while (!found)
        {
            if (mCurrent->getKey() == this->mRoot->getKey()) //if we ever get to the root, there is no successor
            {
                return *mCurrent;
            }

            Node<Key, Value>* temp = mCurrent->getParent();
            if (temp->getLeft() == mCurrent) //found first left child pointer 
            {
                found = true;
                mCurrent = mCurrent->getParent();
            }
            else //walking up ancestor chain 
            {
                mCurrent = mCurrent->getParent();
            }
        }
    }
    return this;
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::begin()
{
    // TODO
    //walk all the way to the left

    SplayTree<Key, Value>::iterator it;
    while (it.mCurrent->getLeft() != NULL)
    {
        it.mCurrent = it.mCurrent->getLeft();
    } 
    return it; 
}

template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::end()
{
    // TODO
    SplayTree<Key, Value>::iterator it;
    return it; // A dummy return value until you provide your implementation.
}

//****SPLAYTREE****
//****SPLAYTREE****
//****SPLAYTREE****
//****SPLAYTREE****
//****SPLAYTREE****


template<typename Key, typename Value>
SplayTree<Key,Value>::SplayTree()
{
	//do nothing
}

template<typename Key, typename Value>
SplayTree<Key,Value>::~SplayTree()
{
	clear();
}

template<typename Key, typename Value>
typename SplayTree<Key,Value>::iterator SplayTree<Key,Value>::find(const Key& k)
{
	Node<Key, Value>* curr = this->mRoot;
	Node<Key, Value>* currP;

	SplayTree<Key, Value>::iterator it;

	while (curr != NULL)
	{
		if (curr->getKey() == k)
		{
			splay(curr);
			it.mCurrent = curr;
			return it;
		}
		else if (k < curr->getKey())
		{
			curr = curr->getLeft();
			currP = curr->getParent();
		}
		else
		{
			curr = curr->getRight();
			currP = curr->getParent();
		}
	}
	//if we get here, we didn't find the key
	if (curr->getParent() != NULL)
	{
		splay(currP);
		it.mCurrent = currP;
		return it;
	}
	else
	{
		return it.end();
	}
}

template<typename Key, typename Value>
void SplayTree<Key,Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
	if (this->mRoot == NULL) //empty tree condition, i think
	{
	    //create new node
	    Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
	    this->mRoot = newNode;
	}
	else
	{
		Node<Key, Value>* newNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
		Node<Key, Value>* tempN = this->mRoot;
		Node<Key, Value>* tempP;
		bool override = false;;

		while (tempN != NULL)
		{
			if (tempN->getKey() < newNode->getKey())
			{
				tempP = tempN;
				tempN = tempN->getRight(); 
			}
			else if (tempN->getKey() > newNode->getKey())
			{
				tempP = tempN;
				tempN = tempN->getLeft();
			} 
			else
			{
				tempP = tempN;
				tempN->setValue(keyValuePair.second);
				splay(tempN);
				override = true;
				break;
			}
		}		
		//we now know who will be our parent. now which side
		if (!override)
		{
			if (tempP->getKey() < newNode->getKey())
			{
				tempP->setRight(newNode);
				newNode->setParent(tempP);
				splay(newNode);

			}
			else if (tempP->getKey() > newNode->getKey())
			{
				tempP->setLeft(newNode);
				newNode->setParent(tempP);
				splay(newNode);
			}
		}
	}
}

template<typename Key, typename Value>
void SplayTree<Key,Value>::clear()
{
	this->deleteAll(this->mRoot);
	this->mRoot = NULL;
}

template<typename Key, typename Value>
Value SplayTree<Key,Value>::get(const Key& k)
{
	Node<Key, Value>* curr = this->mRoot;
	Node<Key, Value>* currP;

	while (curr != NULL)
	{
		if (curr->getKey() == k)
		{
			return curr->getValue();
		}
		else if (k < curr->getKey())
		{
			curr = curr->getLeft();
			currP = curr->getParent();
		}
		else
		{
			curr = curr->getRight();
			currP = curr->getParent();
		}
	}
	Node<Key, Value>* dummy = this->mRoot;
	return dummy->getValue();
}

template<typename Key, typename Value>
Value SplayTree<Key,Value>::operator[](const Key& k)
{
	Node<Key, Value>* curr = this->mRoot;
	Node<Key, Value>* currP;

	while (curr != NULL)
	{
		if (curr->getKey() == k)
		{
			return curr->getValue();
		}
		else if (k < curr->getKey())
		{
			curr = curr->getLeft();
			currP = curr->getParent();
		}
		else
		{
			curr = curr->getRight();
			currP = curr->getParent();
		}
	}	
	Node<Key, Value>* dummy = this->mRoot;
	return dummy->getValue();
}

//******SPLAY******
//******SPLAY******
//******SPLAY******
//******SPLAY******
//******SPLAY******

template<typename Key, typename Value>
void SplayTree<Key,Value>::splay(Node<Key, Value>* x)
{
	//Base Case
	if (x == this->mRoot) return;

	//Set Up
	Node<Key, Value>* parent = x->getParent();

	//Intial relationship is x is left of parent
	if (parent->getLeft() == x) //x is left child of parent
	{
		if (parent->getParent() != NULL)
		{
			Node<Key, Value>* grandpa = parent->getParent();
			if (grandpa->getLeft() == parent) //parent is left child of grandpa (zig-zig left confirmed)
			{
				rotateRight(grandpa);
				rotateRight(parent);
				splay(x);
			}
			else //parent is rigth child of grandpa (zig-zag left right confirmed)
			{ 
				rotateRight(parent);
				rotateLeft(grandpa);
				splay(x);
			}
		}
		else
		{
			rotateRight(parent); //what's required if there is no grandpa in left child relationship
			splay(x);
		}
	}
	else if (parent->getRight() == x)//x is right child of parent
	{
		if (parent->getParent() != NULL)
		{
			Node<Key, Value>* grandpa = parent->getParent();
			if (grandpa->getRight() == parent) //parent is left child of grandpa (zig-zig right confirmed)
			{
				rotateLeft(grandpa);
				rotateLeft(parent);
				splay(x);
			}
			else //parent is left child of grandpa (zig-zag right left confirmed)
			{ 
				rotateLeft(parent);
				rotateRight(grandpa);
				splay(x);
			}
		}
		else
		{
			rotateLeft(parent); //what's required if there is no grandpa in right child relationship,
			splay(x);
		}
	}
}

//**********ROTATIONS************
//**********ROTATIONS************
//**********ROTATIONS************
//**********ROTATIONS************
//**********ROTATIONS************


template<typename Key, typename Value>
void SplayTree<Key,Value>::rotateLeft(Node<Key, Value>* x)
{
    // TODO
    //REMEMBER: X is the ogParent

    //important set up to fix all the breaks we're about to commit
    Node<Key, Value>* ogRightChild = x->getRight(); //take right child

    Node<Key, Value>* rightChildsLeft = ogRightChild->getLeft();
    x->setRight(rightChildsLeft);
    if (ogRightChild->getLeft() != NULL)
    {
    	rightChildsLeft->setParent(x);
    }
    if (x->getParent() == NULL) //the ogParent was the root 
    {
        ogRightChild->setParent(NULL);
        this->mRoot = ogRightChild;
    }
    else
    {
        Node<Key, Value>* grandpaOfX = x->getParent();
        if (grandpaOfX->getLeft() == x) //see if the ogParent was the right or left child of the grandpa
        {
            grandpaOfX->setLeft(ogRightChild);
            ogRightChild->setParent(grandpaOfX);
        } 
        else if (grandpaOfX->getRight() == x)
        {
            grandpaOfX->setRight(ogRightChild); 
            ogRightChild->setParent(grandpaOfX);
        }
    }
    x->setParent(ogRightChild);
    ogRightChild->setLeft(x);
}

template<typename Key, typename Value>
void SplayTree<Key,Value>::rotateRight(Node<Key, Value>* x)
{
	 // TODO
	 //REMEMBER: X is the ogParent

	 //important set up to fix all the breaks we're about to commit
	 Node<Key, Value>* ogLeftChild = x->getLeft(); //take right child

	 Node<Key, Value>* leftChildsRight = ogLeftChild->getRight();
	 x->setLeft(leftChildsRight);
	 if (ogLeftChild->getRight() != NULL)
	 {
	 	leftChildsRight->setParent(x);
	 }
	 if (x->getParent() == NULL) //the ogParent was the root 
	 {
	     ogLeftChild->setParent(NULL);
	     this->mRoot = ogLeftChild;
	 }
	 else
	 {
	     Node<Key, Value>* grandpaOfX = x->getParent();
	     if (grandpaOfX->getLeft() == x) //see if the ogParent was the right or left child of the grandpa
	     {
	         grandpaOfX->setLeft(ogLeftChild);
	         ogLeftChild->setParent(grandpaOfX);
	     } 
	     else if (grandpaOfX->getRight() == x)
	     {
	         grandpaOfX->setRight(ogLeftChild); 
	         ogLeftChild->setParent(grandpaOfX);
	     }
	 }
	 x->setParent(ogLeftChild);
	 ogLeftChild->setRight(x);
}
#endif
