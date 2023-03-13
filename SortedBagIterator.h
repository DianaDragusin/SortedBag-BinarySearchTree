#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

    TElem *arr;
    int current_pos;
    void inorder(int nod);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

