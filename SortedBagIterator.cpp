#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

void SortedBagIterator::inorder(int nod) {

    if (bag.Leaf(nod)) {
        arr[current_pos] = std::get<info>(bag.tree[nod]);
        current_pos++;
        return;
    }
    if (current_pos==bag.len) return;

    if(!bag.emptyLeft(nod))
    inorder(std::get<left>(bag.tree[nod]));

    arr[current_pos] = std::get<info>(bag.tree[nod]);
    current_pos++;

    if(!bag.emptyRight(nod))
    inorder(std::get<right>(bag.tree[nod]));


}

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	arr = new TElem[b.len];
    current_pos = 0;
    if (b.root != -1) {
        inorder(b.root);
        current_pos--;
    }
    else
        current_pos = -1;
    /*
     * Best Case: Θ(1)
     * Worst case: Θ(n)
     * Average Case: Θ(n)
     */
}

TComp SortedBagIterator::getCurrent() {
	if (valid())
        return arr[current_pos];
    else
        throw exception();
    /*
    * Θ(1)
    */

}

bool SortedBagIterator::valid() {
	if (current_pos >= 0)
        return true;
	return false;
    /*
    * Θ(1)
    */

}

void SortedBagIterator::next() {
	if (valid())
        current_pos--;
    else
        throw exception();
    /*
    * Θ(1)
    */

}

void SortedBagIterator::first() {
    current_pos = bag.len-1;
    /*
    * Θ(1)
    */

}

