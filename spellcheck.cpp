#include <iostream>
#include <fstream>
#include "hash.cpp"
#include "hash.h"


vector<string> sentenceSplit(string line){
    string temp1;
    string temp2;
    vector<string> brokenLine;

    int index = 0;
    int wordNo = 0;
    bool numberPresence;

    for(char letter : line){
        if(letter >= '0' && letter <= '9'){
            numberPresence = true;
        }
        if((letter != '\'' && letter != '-') && letter < 'A' || (letter > 'Z' && letter < 'a') || letter > 'z') {
            temp1 = line.substr(0, index);
            line = line.substr(index, line.length());
            if(numberPresence){
                index = 0;
                continue;
            }
            else{
                brokenLine[wordNo] = temp1;
                wordNo++;
                index = 0;
            }
        }
        index++;
    }
    return brokenLine;
}

void readDictionary(const string& dictFilename, hashTable table){
    ifstream dictionaryFile(dictFilename);

    string line;
    while(getline(dictionaryFile, line)){
        table.insert(line);
    }
}

void parse(const string& inputFilename, const string& outputFilename, hashTable dictionaryTable){
    ifstream input(inputFilename);
    ofstream output(outputFilename);
    string line;

    vector<string> words;
    int lineNumber = 1;

    while(getline(input, line)){
        words = sentenceSplit(line);
        for(const string& word : words){
            if(word.length() > 20){
                output << "Long word at line " << lineNumber << ", starts: " << word.substr(0, 20) << endl;
            }
            if(!dictionaryTable.contains(word)){
                output << "Unknown word at line " << lineNumber << ": " << endl;
            }
        }
        lineNumber++;
    }
}

int main(){
    hashTable theDictionaryTable;

    string input1;
    string input2;
    string output;

    cout << "Name of dictionary file:";
    cin >> input1;

    cout << "Name of input file:";
    cin >> input2;

    cout << "Name of output file:";
    cin >> output;



    readDictionary(input1, theDictionaryTable);
    parse(input2, output, theDictionaryTable);

    return 0;
}
