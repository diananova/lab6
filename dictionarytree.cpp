#include "dictionary.h"
using namespace dict;

Dictionary dict::createEmptyDict() {
    
    Node *root = new Node;
    root->leftChild = NULL;
    root->rightChild = NULL;
    Dictionary d = root;
    return d;
    
 }

 bool isEmpty(const Dictionary &d) {
     return d==NULL;
 }
 
Error dict::insertElem(const Key k, const Value v, Dictionary& d) { //works
    Elem e;
    e.key = k;
    e.value = v;
    if (isEmpty(d)) {
        Node* new_node = new Node;
        new_node->keyVal = e;
        new_node->leftChild = NULL;
        new_node->rightChild = NULL;
        d = new_node;
        return OK;
    }
    else if (e.key==d->keyVal.key) {
        cout<<"elemento gia' presente"<<endl;
        return FAIL;
    }
    else if (e.key < d->keyVal.key)
        dict::insertElem(k, v, d->leftChild);
    else if (e.key > d->keyVal.key)
        dict::insertElem(k, v, d->rightChild);
    return FAIL;
}
    
dictionaryElem deleteMin(Dictionary &d) { //funzione aux
    if (isEmpty(d->leftChild))   //a points to the smallest element
        d = d->rightChild;  //deleted
    else 
         deleteMin(d->leftChild);   //traverse till if condition is true
    return d->keyVal;
}

Error dict::deleteElem(const Key k, Dictionary& d) {
        if (isEmpty(d))
            return FAIL;
        if (k < d->keyVal.key)
            dict::deleteElem(k, d->leftChild);
        else if (k > d->keyVal.key)
            dict::deleteElem(k, d->rightChild);
        //k = d->keval.key
        else if ((isEmpty(d->leftChild)) && (isEmpty(d->rightChild)))
            d = NULL; //non ha figli quindi lo cancello
        else if (isEmpty(d->leftChild)) //d ha solo figlio destro
            d = d->rightChild;
        else if (isEmpty(d->rightChild))   //d ha solo figlio sinistro
            d = d->leftChild;
        else //both children are present
            d->keyVal = deleteMin(d->rightChild);
        return OK;

}

Value dict::search(const Key k, const Dictionary &d) {
    if (isEmpty(d))
        return emptyValue;
    if (k==d->keyVal.key)
        return d->keyVal.value;
    else if (k < d->keyVal.key)
        return dict::search(k, d->leftChild);
    else if (k > d->keyVal.key)
        return dict::search(k, d->rightChild);
    else
        return emptyValue;
}

void print(const dict::Dictionary &d)
{
    if (isEmpty(d))
        return;
    cout<<d->keyVal.key<<" "<<d->keyVal.value<<endl;
    print(d->leftChild);
    print(d->rightChild);
}


dict::Dictionary readFromFile(string nome_file)
{
    ifstream ifs(nome_file.c_str()); // apertura di uno stream associato ad un file, in lettura
    if (!ifs) {
        cout << "\nErrore apertura file, verificare di avere inserito un nome corretto\n"; 
        return createEmptyDict();
    }  
    // cout << "\n[dict::readFromFile] Apertura file completata\n";
    return readFromStream(ifs);
}

dict::Dictionary readFromStdin()
{
    cout << "\nInserire una sequenza di linee che rispettano la sintassi key: value.<enter>\nDigitare CTRL^ D per terminare l'inserimento\n";
    Dictionary d = readFromStream((std::cin));
// Questa serve per aggirare un bug di alcune versioni attuali di glibc.
    clearerr(stdin);
    return d;
}
dict::Dictionary readFromStream(istream& str)
{
    Dictionary d = createEmptyDict();     
    string key, kcopy;
    string value;
    getline (str, key, ':'); 
    getline (str, value); 
    while (!str.eof())  
        {     
        kcopy = key;
        removeBlanksAndLower(kcopy);   
        insertElem(kcopy, value, d); // FINCHE' NON IMPLEMENTATE LA INSERTELEM, NON PUO' FUNZIONARE CORRETTAMENTE: la insertElem e' la prima funzione che dovete implementare
        getline (str, key, ':'); 
        getline (str, value); 
        }
    str.clear();
    return d;
}


