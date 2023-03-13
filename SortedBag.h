#pragma once
#include <tuple>
//DO NOT INCLUDE SORTEDBAGITERATOR

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP (-11111)
const int nullpt = -1;
const int info = 0;
const int left = 1;
const int right = 2;

class SortedBagIterator;

class SortedBag {
	friend class SortedBagIterator;

private:
	std::tuple<TElem, int, int> *tree;
    int cap;
    int len;
    int root;
    int next_empty;
    Relation rel;
    void resize();
    bool Leaf(int pos) const;
    bool emptyLeft(int pos) const;
    bool emptyRight(int pos) const;
    void inorder(int root, int to_search, int &nrOcc) const;
    std::pair<int,int> nextMin(int pos) const;

    //reununia a 2 containere

public:
	//constructor
    SortedBag reun(SortedBag b1, SortedBag b2);

	SortedBag(Relation r);

    SortedBag(const SortedBag &b);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears in the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//destructor
	~SortedBag();
};