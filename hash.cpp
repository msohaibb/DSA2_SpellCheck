#include <iostream>
#include "hash.h"
using namespace std;


//int size = 0;

hashTable::hashTable(int size) {
    capacity = getPrime(size);
    filled = 0;
    data.resize(capacity);
}



int hashTable::insert(const std::string &key, void *pv){
    int hashedKey = hashTable::hash(key);

    if(contains(key)){
        return 1;
    }

    if(filled * 2 >= capacity){
        if(!rehash()){
            return 2;
        }
    }
    while(data[hashedKey].isOccupied && !data[hashedKey].isDeleted){
        if(hashedKey == capacity){
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

bool hashTable::contains(const std::string &key){
    if(findPos(key) == -1){
        return false;
    }
    return true;
}
/*
void *hashTable::getPointer(const std::string &key, bool *b){
}

int hashTable::setPointer(const std::string &key, void *pv){
}

bool hashTable::remove(const std::string &key){
}
*/

int hashTable::hash(const std::string &key){
    std::hash<std::string> hashFunction;
    return (int)hashFunction(key);
}

int hashTable::findPos(const std::string &key){
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

bool hashTable::rehash(){
    if (capacity == getPrime(capacity))
        return false;

    capacity = getPrime(capacity);
    vector<hashItem> temp = data;

    data.clear();
    data.resize(capacity);
    filled = 0;

    for (hashItem item : temp){
        if (item.isOccupied){
            insert(item.key, item.pv);
        }
    }

    return true;
}
int hashTable::getPrime(int size){
    //list of primes obtained from https://planetmath.org/goodhashtableprimes
    int primes[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433,
                    1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611, 402653189, 805306457,
                    1610612741};
    for(int i: primes){
        if(i > size){
            return i;
        }
    }
    return primes[(sizeof(primes)/sizeof(*primes)) - 1];
}
