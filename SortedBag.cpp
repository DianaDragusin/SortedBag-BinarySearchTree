#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {

    cap = 5;
    len = 0;
    tree = new std::tuple<TElem,int,int>[cap];
    root = nullpt;
    rel = r;
    next_empty = 0;

    for (int i=0; i<cap; i++) {
        tree[i] = std::make_tuple(NULL_TCOMP,i+1,nullpt);
    }

    tree[cap-1] = std::make_tuple(NULL_TCOMP,nullpt,nullpt);
}

void SortedBag::resize() {

    int old_cap = cap;
    cap *= 2;
    auto temp = new std::tuple<TElem,int,int>[cap];

    for (int i=0; i<old_cap; i++)
        temp[i] = tree[i];

    for (int i=old_cap; i<cap; i++)
        temp[i] = std::make_tuple(NULL_TCOMP,i+1,nullpt);

    temp[cap-1] = std::make_tuple(NULL_TCOMP,nullpt,nullpt);

    next_empty = old_cap;

    //delete[] tree;
    tree = temp;

}

bool SortedBag::emptyLeft(int pos) const {
    if (std::get<1>(tree[pos]) == nullpt)
        return true;
    else
        return false;
}

bool SortedBag::emptyRight(int pos) const {

    if (std::get<right>(tree[pos]) == nullpt)
        return true;
    else
        return false;
}

bool SortedBag::Leaf(int pos) const{

    if (emptyRight(pos) && emptyLeft(pos) )
        return true;
    else
        return false;
}

void SortedBag::add(TComp e) {

    if(len == cap) resize();
	int current = root;

    if (root == nullpt) {
        root = next_empty;
        next_empty = std::get<left>(tree[root]);
        tree[root] = std::make_tuple(e,nullpt,nullpt);
        len++;
    } else {
        while (true) {
            if (rel(std::get<info>(tree[current]),e)) {
                if (!emptyLeft(current)) {
                    current = std::get<left>(tree[current]);
                }
                else if (emptyLeft(current)) {
                    int new_node = next_empty;
                    next_empty = std::get<left>(tree[new_node]);
                    tree[new_node] = std::make_tuple(e, nullpt, nullpt);
                    std::get<left>(tree[current]) = new_node;
                    len++;
                    break;
                }
            } else {
                if (!emptyRight(current)) {
                    current = std::get<right>(tree[current]);
                } else if(emptyRight(current)) {
                    int new_node = next_empty;
                    next_empty = std::get<left>(tree[new_node]);
                    tree[new_node] = std::make_tuple(e,nullpt,nullpt);
                    std::get<right>(tree[current]) = new_node;
                    len++;
                    break;
                }
            }
        }
    }
    /*
     * Best Case: Θ(1)
     * Worst case: Θ(n)
     * Average Case: O(log n)
     */
}

std::pair<int,int> SortedBag::nextMin(int pos) const {
    int father = pos;
    while (!emptyLeft(pos)) {
        father = pos;
        pos = std::get<left>(tree[pos]);
    }
    return std::make_pair(pos,father);

}


bool SortedBag::remove(TComp e) {
    if (!search(e)) return false;
    else {
        int father = nullpt;
        bool fromLeft;
        int current = root;
        while (current!=nullpt && std::get<info>(tree[current]) != e && std::get<info>(tree[current])!=NULL_TCOMP) {
            if (rel(std::get<info>(tree[current]),e)) {
                father = current;
                fromLeft = true;
                current = std::get<left>(tree[current]);
            }
            else {
                father = current;
                fromLeft = false;
                current = std::get<right>(tree[current]);
            }
        }

        if (Leaf(current)) {
            std::get<info>(tree[current]) = NULL_TCOMP;
            std::get<left>(tree[current]) = next_empty;
            next_empty = current;
            std::get<right>(tree[current]) = nullpt;
            if (fromLeft)
                std::get<left>(tree[father]) = nullpt;
            else
                std::get<right>(tree[father]) = nullpt;
            return true;
        } else if (!emptyLeft(current) && emptyRight(current)) {

            std::get<info>(tree[current]) = std::get<info>(tree[std::get<left>(tree[current])]);
            std::get<right>(tree[current]) = std::get<right>(tree[std::get<left>(tree[current])]);
            int to_del = std::get<left>(tree[current]);
            std::get<left>(tree[current]) = std::get<left>(tree[std::get<left>(tree[current])]);
            std::get<info>(tree[to_del]) = NULL_TCOMP;
            std::get<right>(tree[to_del]) = nullpt;
            std::get<left>(tree[to_del]) = next_empty;
            next_empty = to_del;
            len--;
            return true;
        } else if (emptyLeft(current) && !emptyRight(current)) {
            std::get<info>(tree[current]) = std::get<info>(tree[std::get<right>(tree[current])]);
            std::get<left>(tree[current]) = std::get<left>(tree[std::get<right>(tree[current])]);
            int to_del = std::get<right>(tree[current]);
            std::get<right>(tree[current]) = std::get<right>(tree[std::get<right>(tree[current])]);
            std::get<info>(tree[to_del]) = NULL_TCOMP;
            std::get<right>(tree[to_del]) = nullpt;
            std::get<left>(tree[to_del]) = next_empty;
            next_empty = to_del;
            len--;
            return true;
        } else if (!emptyLeft(current) && !emptyRight(current)) {
            int pos_of_min = nextMin(std::get<right>(tree[current])).first;
            int father_of_min = nextMin(std::get<right>(tree[current])).second;

            std::get<info>(tree[current]) = std::get<info>(tree[pos_of_min]);
            std::get<left>(tree[father_of_min]) = std::get<right>(tree[pos_of_min]);

            std::get<info>(tree[pos_of_min]) = NULL_TCOMP;
            std::get<right>(tree[pos_of_min]) = nullpt;
            std::get<left>(tree[pos_of_min]) = next_empty;
            next_empty = pos_of_min;

            len--;
            return true;
        }

    }
    /*
     * Best Case: Θ(1)
     * Worst case: Θ(n)
     * Average Case: O(log n)
     */
}


bool SortedBag::search(TComp elem) const {
    int current = root;
    while (current!=nullpt && std::get<info>(tree[current]) != elem && std::get<info>(tree[current])!=NULL_TCOMP) {
        if (rel(std::get<info>(tree[current]),elem))
            current = std::get<left>(tree[current]);
        else
            current = std::get<right>(tree[current]);
    }
    if (current == nullpt || std::get<info>(tree[current]) == NULL_TCOMP)
	    return false;
    else
        return true;
    /*
     * Best Case: Θ(1)
     * Worst case: Θ(n)
     * Average Case: O(log n)
     */
}

void SortedBag::inorder(int nod, int to_search, int &nrOcc) const {

    if (Leaf(nod)) {
        if (std::get<info>(tree[nod]) == to_search)
            nrOcc++;
        return;
    }

    if (nod<0 || nod>=cap)
        return;

    if(!emptyLeft(nod))
        inorder(std::get<left>(tree[nod]),to_search,nrOcc);

    if (std::get<info>(tree[nod]) == to_search)
        nrOcc++;

    if(!emptyRight(nod))
        inorder(std::get<right>(tree[nod]),to_search,nrOcc);

}

int SortedBag::nrOccurrences(TComp elem) const {
    if (!search(elem)) return 0;
	int cnt = 0;
    int current = root;
    inorder(root, elem, (int &) cnt);
//    while (true) {
//        if (std::get<info>(tree[current]) == elem)
//            cnt++;
//        if (rel(std::get<info>(tree[current]),elem)) {
//            if (!emptyLeft(current)) {
//                current = std::get<left>(tree[current]);
//            }
//            else if (emptyLeft(current)) {
//                break;
//            }
//        } else {
//            if (!emptyRight(current)) {
//                current = std::get<right>(tree[current]);
//            } else if(emptyRight(current)) {
//                break;
//            }
//        }
//    }

     /*
     * Best Case: Θ(1)
     * Worst case: Θ(n)
     * Average Case: O(log n)
     */
	return cnt;
}



int SortedBag::size() const {

	return len;

    /*
    * Θ(1)
    */

}


bool SortedBag::isEmpty() const {

    if (len == 0) return true;
    else
        return false;

    /*
    * Θ(1)
    */
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);

    /*
    * Θ(1)
    */
}

SortedBag SortedBag::reun(SortedBag b1, SortedBag b2) {
    SortedBag b3(b1.rel);
    for (int i=0; i< b1.cap; i++) {

        if (std::get<info>(b1.tree[i])!=NULL_TCOMP) {
            if(b3.len == b3.cap) b3.resize();
            int current = b3.root;

            if (b3.root == nullpt) {
                b3.root = b3.next_empty;
                b3.next_empty = std::get<left>(b3.tree[b3.root]);
                b3.tree[b3.root] = std::make_tuple(std::get<info>(b1.tree[i]),nullpt,nullpt);
                b3.len++;
            } else {
                while (true) {
                    if (b3.rel(std::get<info>(b3.tree[current]),std::get<info>(b1.tree[i]))) {
                        if (!b3.emptyLeft(current)) {
                            current = std::get<left>(b3.tree[current]);
                        }
                        else if (b3.emptyLeft(current)) {
                            int new_node = b3.next_empty;
                            b3.next_empty = std::get<left>(b3.tree[new_node]);
                            b3.tree[new_node] = std::make_tuple(std::get<info>(b1.tree[i]), nullpt, nullpt);
                            std::get<left>(b3.tree[current]) = new_node;
                            b3.len++;
                            break;
                        }
                    } else {
                        if (!b3.emptyRight(current)) {
                            current = std::get<right>(b3.tree[current]);
                        } else if(b3.emptyRight(current)) {
                            int new_node = b3.next_empty;
                            b3.next_empty = std::get<left>(b3.tree[new_node]);
                            b3.tree[new_node] = std::make_tuple(std::get<info>(b1.tree[i]),nullpt,nullpt);
                            std::get<right>(b3.tree[current]) = new_node;
                            b3.len++;
                            break;
                        }
                    }
                }
            }
        }

    }

    for (int i=0; i< b2.cap; i++) {

        if (std::get<info>(b2.tree[i])!=NULL_TCOMP) {
            if(b3.len == b3.cap) b3.resize();
            int current = b3.root;

            if (b3.root == nullpt) {
                b3.root = b3.next_empty;
                b3.next_empty = std::get<left>(b3.tree[b3.root]);
                b3.tree[b3.root] = std::make_tuple(std::get<info>(b2.tree[i]),nullpt,nullpt);
                b3.len++;
            } else {
                while (true) {
                    if (b3.rel(std::get<info>(b3.tree[current]),std::get<info>(b2.tree[i]))) {
                        if (!b3.emptyLeft(current)) {
                            current = std::get<left>(b3.tree[current]);
                        }
                        else if (b3.emptyLeft(current)) {
                            int new_node = b3.next_empty;
                            b3.next_empty = std::get<left>(b3.tree[new_node]);
                            b3.tree[new_node] = std::make_tuple(std::get<info>(b2.tree[i]), nullpt, nullpt);
                            std::get<left>(b3.tree[current]) = new_node;
                            b3.len++;
                            break;
                        }
                    } else {
                        if (!b3.emptyRight(current)) {
                            current = std::get<right>(b3.tree[current]);
                        } else if(b3.emptyRight(current)) {
                            int new_node = b3.next_empty;
                            b3.next_empty = std::get<left>(b3.tree[new_node]);
                            b3.tree[new_node] = std::make_tuple(std::get<info>(b2.tree[i]),nullpt,nullpt);
                            std::get<right>(b3.tree[current]) = new_node;
                            b3.len++;
                            break;
                        }
                    }
                }
            }
        }

    }

    return b3;
}

SortedBag::SortedBag(const SortedBag& b) {

    cap = b.cap;
    len = b.len;
    root = b.root;
    next_empty = b.next_empty;
    rel = b.rel;
    tree = new std::tuple<TElem,int,int>[cap];
    for (int i=0; i<cap; i++)
        tree[i] = b.tree[i];

}

SortedBag::~SortedBag() {
	//delete[] tree;

    /*
    * Θ(1)
    */
}

