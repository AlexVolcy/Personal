#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
template <
         typename T,
         typename KComparator = std::equal_to<T>,
         typename PComparator = std::less<T>,
         typename Hasher = std::hash<T> >
class Heap
{
public:
    /// Constructs an m-ary heap. M should be >= 2
    Heap(int m = 2,
         const PComparator& c = PComparator(),
         const Hasher& hash = Hasher(),
         const KComparator& kcomp = KComparator()  );

    /// Destructor as needed
    ~Heap();

    /// Adds an item
    void push(const T& item);

    /// returns the element at the top of the heap
    ///  max (if max-heap) or min (if min-heap)
    T const & top() const;

    /// Removes the top element
    void pop();

    /// returns true if the heap is empty
    bool empty() const;

    /// decreaseKey - Finds key matching old object &
    /// updates its location in the heap based on the new value
    void decreaseKey(const T& old, const T& newVal);

 private:
    /// Add whatever helper functions and data members you need below
    void trickleUp(int loc);
    void trickleDown(int loc);

 private:
   /// Data members - These should be sufficient
    std::vector< T > store_;
    int m_;
    PComparator c_;
    std::unordered_map<T, size_t, Hasher, KComparator> keyToLocation_;

};

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::Heap(
    int m,
    const PComparator& c,
    const Hasher& hash,
    const KComparator& kcomp ) :

    store_(),
    m_(m),
    c_(c),
    keyToLocation_(100, hash, kcomp)

{

}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
Heap<T,KComparator,PComparator,Hasher>::~Heap()
{

}

template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleUp(int loc)
{
  //new item added, needs to "trickle up" to its correct position
  int parent = (loc-1)/m_; 
  while (parent >= 0 && c_(store_[loc], store_[parent]))
  {
    keyToLocation_[store_[loc]] = parent;
    keyToLocation_[store_[parent]] = loc;
    std::swap(store_[parent], store_[loc]);

    loc = parent;
    parent = (loc-1)/m_;
  }
}

//Complete, push propety should be the same
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::push(const T& item)
{
    store_.push_back(item);
    keyToLocation_.insert(std::make_pair(item, store_.size()-1));
    trickleUp(store_.size()-1);
}

//Complete
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::decreaseKey(const T& old, const T& newVal)
{
    typename std::unordered_map<T, size_t, Hasher, KComparator>::iterator it = keyToLocation_.find(old); //finds the location of the old key on the heap
    keyToLocation_[old];
    if (it != keyToLocation_.end()) //makes sure it exists
    {
        if (c_(newVal, old))
        {
            store_[keyToLocation_[old]] = newVal; //assuming it->second is the index
            //add new to keyToLocation
            keyToLocation_.insert(std::make_pair(newVal, it->second));
            //erase
            keyToLocation_.erase(old);
            //then call trickleUp
            trickleUp(it->second);
        }      
    }
}

// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
T const & Heap<T,KComparator,PComparator,Hasher>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()) {
        throw std::logic_error("can't top an empty heap");
    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return store_[0];
}

//Complete 
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::trickleDown(int loc)
{
  //because of popping method, the node that was initially swapped
  //needs to "trickle down" to its correct spot

  if ((unsigned int)loc*m_+1 >= store_.size()) return;

  //formula for finding children of a parent is iterated through
  //allowing for the comparison of all the children
  //eventually finding the smallest/biggest one
  int smallerChild = loc*m_+1;
  for (unsigned int i = loc*m_+1; i < (unsigned int)(loc*m_+1)+m_; i++)
  {
    unsigned int nextChild = i; 
    if (nextChild < store_.size() && c_(store_[nextChild], store_[smallerChild]))
    {
      smallerChild = nextChild;
    }
  }

  if (c_(store_[smallerChild],store_[loc]))
  {
    //if smallest/biggest child is smaller/bigger than its parent
    //then we should swap those and continue trickle down.

    std::swap(store_[loc], store_[smallerChild]);
    //Only new additions
    keyToLocation_[store_[smallerChild]] = loc;
    keyToLocation_[store_[loc]] = smallerChild;

    trickleDown(smallerChild);
  }

}

// Complete
template <typename T, typename KComparator, typename PComparator, typename Hasher >
void Heap<T,KComparator,PComparator,Hasher>::pop()
{
    if(empty()) {
        throw std::logic_error("can't pop an empty heap");
    }

    if (store_.size() > 1)
    {
      store_[0] = store_.back();
      store_.pop_back();

      //Only additions
      keyToLocation_.erase(store_[0]);
      keyToLocation_.insert(std::make_pair(store_.back(), 0));

      trickleDown(0);
    }
    else if (store_.size() == 1)
    {
      store_[0] = store_.back();
      keyToLocation_.erase(store_[0]);
      store_.pop_back();
    }
}

/// Complete!
template <typename T, typename KComparator, typename PComparator, typename Hasher >
bool Heap<T,KComparator,PComparator,Hasher>::empty() const
{
    return store_.empty();
}


#endif