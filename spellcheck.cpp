#include <iostream>
#include <fstream>
#include <algorithm>
#include "hash.h"
#include <ctime>


using namespace std;


// takes a string, separates by the separators, and puts them into vector
vector<string> sentenceSplit(const string& line){
    string temp;
    vector<string> brokenLine;

    bool numberPresence;

    for(char letter : line){
        if(isdigit(letter)){
            numberPresence = true;
        }
        if(letter >= 'A' && letter <= 'Z'){
            letter += 32;
        }

        if(isdigit(letter) || letter == '\'' || letter == '-' || isalpha(letter)){
            temp += letter;
        }
        else if(numberPresence){
            temp.clear();
            numberPresence = false;
        }
        else if(!temp.empty()){
            brokenLine.push_back(temp);
            temp.clear();
        }
    }
    return brokenLine;
}

// inserts dictionary into hash table
void readDictionary(const string& dictFilename, hashTable *table){
    ifstream dictionaryFile(dictFilename);

    string line;
    while(getline(dictionaryFile, line)){
        transform(line.begin(), line.end(), line.begin(), ::tolower); //lowercase everything
        table->insert(line);
    }

}
// looks through input file and uses hash table to spell check
void parse(const string& inputFilename, const string& outputFilename, hashTable *dictionaryTable){
    ifstream input(inputFilename);
    ofstream output(outputFilename);
    string line;

    vector<string> words;
    int lineNumber = 1;

    while(getline(input, line)){
        words = sentenceSplit(line + " ");
        for(const string& word : words){
            if(word.length() > 20){
                output << "Long word at line " << lineNumber << ", starts: " << word.substr(0, 20) << endl;
            }
            else if(!dictionaryTable->contains(word)){
                output << "Unknown word at line " << lineNumber << ": " << word << endl;
            }
        }
        lineNumber++;
    }
}
// declares hash table, passes it to functions, and times the process
int main(){
    auto *theDictionaryTable = new hashTable(1003);

    string input1;
    string input2;
    string output;

    cout << "Name of dictionary file: ";
    cin >> input1;

    cout << "Name of input file: ";
    cin >> input2;

    cout << "Name of output file: ";
    cin >> output;


    clock_t t1 = clock();
    readDictionary(input1, theDictionaryTable);
    clock_t t2 = clock();
    parse(input2, output, theDictionaryTable);
    clock_t t3 = clock();


    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    double timeDiff1 = ((double) (t3 - t2)) / CLOCKS_PER_SEC;
    cout << "Spell-check complete. Dictionary CPU time was " << timeDiff << " seconds.\n";
    cout << "Spell-check complete. Parse CPU time was " << timeDiff1 << " seconds.\n";


    return 0;
}
