#include <iostream>
#include <fstream>
#include "hash.cpp"


void readDictionary(const string& dictFilename, hashTable table){
    ifstream dictionaryFile(dictFilename);

    string line;
    while(getline(dictionaryFile, line)){
        table.insert(line);
    }
}

void parse(const string& inputFilename, const string& outputFilename, hashTable dictionaryTable){
    ifstream input(inputFilename);
    //ofstream output(outputFilename);
    string line;

    while(getline(input, line)){
        int index = 0;
        for(char letter : line){
            if(letter < '0' || (letter > '9' && letter < 'A') || (letter > 'Z' && letter < 'a') || letter > 'z'){

            }
            index++;
        }
    }
}

int main(){
    hashTable theDictionaryTable;
    readDictionary("wordlist_small", theDictionaryTable);
    parse("lyrics.txt", "MYOUT_lyrics_small.txt", theDictionaryTable);
}
