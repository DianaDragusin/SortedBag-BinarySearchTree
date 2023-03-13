#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testFunc() {
    SortedBag sb1(relation1);
    SortedBag sb2(relation1);
    sb1.add(5);
    sb1.add(6);
    sb1.add(0);
    sb1.add(5);
    sb1.add(10);
    sb1.add(8);
    sb2.add(5);
    sb2.add(6);
    sb2.add(0);
    sb2.add(5);
    sb2.add(10);
    sb2.add(8);
    SortedBag sb3 = sb1.reun(sb1,sb2);
    assert(sb3.nrOccurrences(5)==4);
    assert(sb3.nrOccurrences(8)==2);
    assert(sb3.nrOccurrences(11)==0);
    assert(sb3.search(6));
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

