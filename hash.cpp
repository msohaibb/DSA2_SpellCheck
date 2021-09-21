#include <iostream>
#include "hash.h"
using namespace std;

// constructor
hashTable::hashTable(int size) {
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}
// uses hash function
int hashTable::insert(const string &key, void *pv){

    int hashedKey = hashTable::hash(key);
    // checks if key already exists
    if(contains(key)){
        return 1;
    }
    // rehash if more than half the capacity is used
    if(filled >= (capacity / 2)){
        if(!rehash()){
            return 2;
        }
    }
    // if mapped value is occupied (or lazily deleted), keep moving to the right
    while(data[hashedKey].isOccupied && !data[hashedKey].isDeleted){
        if(hashedKey == capacity - 1){
            hashedKey = 0;
        }
        hashedKey++;
    }
    data[hashedKey].key = key;
    data[hashedKey].isOccupied = true;
    data[hashedKey].pv = pv;
    filled++;
    return 0;


}
// uses the return value of findPos() to determine presence
bool hashTable::contains(const string &key){
    if(findPos(key) == -1){
        return false;
    }
    return true;
}
// will be implemented in the next assignment
/*
void *hashTable::getPointer(const std::string &key, bool *b){
}

int hashTable::setPointer(const std::string &key, void *pv){
}

bool hashTable::remove(const std::string &key){
}
*/
// hash function obtained from https://stackoverflow.com/questions/8567238/hash-function-in-c-for-string-to-int
int hashTable::hash(const string &key){
    int hashVal = 0;

    for(char i : key){
        hashVal = 37 * hashVal + i;
    }

    hashVal %= capacity;
    if(hashVal < 0){
        hashVal += capacity;
    }
    return hashVal;
}
// checks at mapped value, then looks for it manually
int hashTable::findPos(const string &key){
    int hashedKey = hashTable::hash(key);
    while(data[hashedKey].isOccupied){
        if(data[hashedKey].key == key){
            return hashedKey;
        }
        else if(hashedKey == capacity){
            hashedKey = 0;
        }
        hashedKey++;
    }
    return -1;
}
// changes capacity and rehashes based on new capacity
bool hashTable::rehash(){
    if (capacity == getPrime(capacity))
        return false;

    capacity = getPrime(capacity);
    vector<hashItem> temp = data;

    data.clear();
    data.resize(capacity);
    filled = 0;

    for (const hashItem& item : temp){
        if (item.isOccupied){
            insert(item.key, item.pv);
        }
    }

    return true;
}
int hashTable::getPrime(int size){
    //list of primes obtained from https://planetmath.org/goodhashtableprimes
    int primes[] = {24593, 49157, 98317, 196613, 393241, 786433,
                    1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457,
                    1610612741};
    for(int i: primes){
        if(i > size){
            return i;
        }
    }
    return primes[(sizeof(primes)/sizeof(*primes)) - 1];
}
