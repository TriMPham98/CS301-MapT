//
// Created by we7289 on 4/19/2021.
//

#include "MapT.h"
#include <unordered_map>
//using namespace std;

const int DEFAULT_BUCKETS = 10;
const double DEFAULT_LOAD = 1.0;

template<class K, class T>
MapT<K, T>::MapT() {
    numBuckets = DEFAULT_BUCKETS;
    buckets = new forward_list<pair<K, T> >[numBuckets];
    numKeys = 0;
    maxLoad = DEFAULT_LOAD;
    currBucket = 0;
}

template<class K, class T>
MapT<K, T>::MapT(int numBuckets) {
    this->numBuckets = numBuckets;
    buckets = new forward_list<pair<K, T> >[numBuckets];
    numKeys = 0;
    maxLoad = DEFAULT_LOAD;
    currBucket = 0;
}

template<class K, class T>
void MapT<K, T>::Add(K key, T value) {

    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    Remove(key);

    pair<K, T> keyValuePair;
    keyValuePair.first = key;
    keyValuePair.second = value;

    buckets[bucket].push_front(keyValuePair);
    numKeys++;

    // Check load factor
    if (LoadFactor() > maxLoad) {
        Rehash(2 * numBuckets);
    }
}

template<class K, class T>
void MapT<K, T>::Remove(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (it->first == key) {
            buckets[bucket].remove(*it);
            numKeys--;
            return;
        }
    }
}

template<class K, class T>
bool MapT<K, T>::Contains(K key) {
    // Find the appropriate bucket that key lives in
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (it->first == key) {
            return true;
        }
    }

    return false;
}

template<class K, class T>
T MapT<K, T>::operator[](K key) {
    int bucket = GetHashIndex(key);

    for (auto it = buckets[bucket].begin(); it != buckets[bucket].end(); ++it) {
        if (it->first == key) {
            return it->second;
        }
    }

    throw KeyDoesNotExist();
}

template<class K, class T>
double MapT<K, T>::LoadFactor() {
    return static_cast<double>(numKeys) / numBuckets;
}

template<class K, class T>
void MapT<K, T>::SetMaxLoad(double maxLoad) {
    this->maxLoad = maxLoad;
}

template<class K, class T>
void MapT<K, T>::Rehash(int numBuckets) {
    MapT<K, T> newMap(numBuckets);  // Need to copy over all elements to newMap

    for (int b = 0; b < this->numBuckets; b++) {
        for (auto it = buckets[b].begin(); it != buckets[b].end(); ++it) {
            newMap.Add(it->first, it->second);
        }
    }

    *this = newMap;
}

template<class K, class T>
MapT<K, T> &MapT<K, T>::operator=(const MapT<K, T> &otherMap) {
    delete[]this->buckets;

    this->buckets = new forward_list<pair<K, T> >[otherMap.numBuckets];
    this->numBuckets = otherMap.numBuckets;
    this->numKeys = 0;

    for (int b = 0; b < otherMap.numBuckets; b++) {
        for (auto it = otherMap.buckets[b].begin(); it != otherMap.buckets[b].end(); ++it) {
            this->Add(it->first, it->second);
        }
    }

    return *this;
}

template<class K, class T>
void MapT<K, T>::ResetIterator() {
    mapIter = buckets[currBucket].begin();
    currBucket = 0;
}

template<class K, class T>
pair<K, T> MapT<K, T>::GetNextPair() {
    while (mapIter == buckets[currBucket].end()) {
        currBucket++;
        mapIter = buckets[currBucket].begin();

        if (currBucket >= numBuckets) {
            throw IteratorOutOfBounds();
        }
    }

    pair<K, T> valueToReturn = *mapIter;
    mapIter++;

    return valueToReturn;
}

template<class K, class T>
int MapT<K, T>::GetHashIndex(const K &key) {
    unordered_map <K, T> mapper;
    typename unordered_map<K, T>::hasher hashFunction = mapper.hash_function();
    return static_cast<int>(hashFunction(key) % numBuckets);
}