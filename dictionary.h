#include <iostream>
#include <stdexcept>
#include <vector> 
#include <fstream> 
#include <chrono>          // necessario compilare con -std=c++11
#include <stdlib.h>        // srand, rand
#include <string>          // std::string

#include "string-utility.h"

using namespace std::chrono; 
using namespace std; 
namespace dict {
enum Error {OK, FAIL};

typedef string Key; 
typedef string Value;

const Key emptyKey = "###RESERVED KEYWORD### EMPTY KEY";
const Value emptyValue = "###RESERVED KEYWORD### EMPTY VALUE";

struct dictionaryElem {
    Key    key;
    Value value;
};

struct Node {
    dictionaryElem keyVal; /* elemento del dictionary, ovvero coppia chiave-valore */
    Node* leftChild;
    Node* rightChild;
};

typedef dictionaryElem Elem;
typedef Node* Dictionary;

Error insertElem(const Key, const Value, Dictionary&);
Error deleteElem(const Key, Dictionary&);
Value search(const Key, const Dictionary&);
Dictionary createEmptyDict();
} //end namespace dict

dict::Dictionary readFromFile(string);
dict::Dictionary readFromStdin();
dict::Dictionary readFromStream(istream&);
void print(const dict::Dictionary&);
