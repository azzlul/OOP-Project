#include "VectorTemplate.h"
#include "iostream"


void testVector()
{
    Vector<int> vect;
    int val = 7;
    vect.add(3);
    vect.add(2);
    vect.add(1);
    assert(vect.get(0) == 3);
    assert(vect.get(1) == 2);
    vect.set(2, val);
    assert(vect.get(2) == 7);
    Vector<int> vect2 = vect;
    assert(vect2.size() == 3);
    int sum = 0;
    for(const auto& el : vect)
    {
        sum += el;
    }
    assert(sum == 12);
    int index = 0;
    for(auto i = vect.begin();i.valid();++i)
    {
        assert(*i == vect.get(index));
        index++;
    }
    vect.sort([&](int a, int b){return a <= b;});
    assert(vect.get(0) == 2);
    assert(vect.get(1) == 3);
    assert(vect.get(2) == 7);
    vect.del(1);
    assert(vect.get(1) == 7);
}

