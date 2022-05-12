#include <iostream>
#include <vector> 
#include <stdlib.h>
#include <fstream> 
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string.h>
#include <string>
#include <cstring>

// Implementa QUEUE con strutture indicizzate e tipo base Tree dotato di ordinamento

using namespace std;

typedef struct {
    float freq;
    char character;
} Elem;


struct Node {
	Elem elem;
	string peso;
	Node* left;
	Node* right;
};

typedef Node* Tree;

enum Error {OK, FAIL};



namespace queue{

const Tree emptyNode = NULL;

const int BLOCKDIM = 1000;

typedef struct {
    Tree* queue;
    int size;
    int maxsize;
} Queue;


const int FINEINPUT = -1000000;
Queue createEmpty();         /* restituisce la coda vuota */
bool isEmpty(const Queue&);
void enqueue(Tree, Queue&);  /* inserisce l'Treeento "da una parte" della coda */
Tree dequeue(Queue&);        /* cancella l'Treeento (se esiste) "dall'altra parte della coda" e lo restituisce; se la coda è vuota la condizione è di errore. Lo segnaliamo restituendo EMPTYTree (potremmo in alternativa sollevare un'eccezione) */
Tree first(Queue&);          /* restituisce l'Treeento in prima posizione (se esiste) senza cancellarlo; se la coda è vuota la condizione è di errore. Lo segnaliamo restituendo EMPTYTree (potremmo in alternativa sollevare un'eccezione) */

}

void add(int, Tree, queue::Queue&);
void print(const queue::Queue&);
