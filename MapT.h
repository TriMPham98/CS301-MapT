//
// Created by Varick Erickson on 4/19/2021.
//

#ifndef MAPT_H
#define MAPT_H

#include <forward_list> // stl library for singly linked list

using namespace std;

class KeyDoesNotExist {
};

template<class K, class T>
class MapT {
public:
    MapT();

    void Add(K key, T value);

    void Remove(K key);

    bool Contains(K key);

    double LoadFactor();

    void SetMaxLoad(double maxLoad);

    void Rehash(int numBuckets);

    T operator[](K key);

    int Size() { return numKeys; }

    void ResetIterator();

    pair<K, T> GetNextPair();

private:
    forward_list<pair<K, T> > *buckets;   // Each node contains a key and value
    int numBuckets;
    int numKeys;

    double maxLoad;


    // Short Version:
    // Iterators that use templates need "typename" in front.
    //
    // Longer Version:
    // The forward_list iterator depends on the types of
    // K and T in this case. The compiler can't determine
    // if this iterator declaration is a field or a type.
    // By putting typename in front, it is telling the
    // compiler it is a type.
    typename forward_list<pair<K, T> >::iterator mapIter;
    int currBucket;


    int GetHashIndex(const K &key);
};


#include "MapT.cpp"

#endif // MAPT_H
