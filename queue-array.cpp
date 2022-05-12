#include "queue-array.h"

using namespace queue;


/****************************************************************/
/* 			FUNZIONI AUSILIARIE 			*/
/****************************************************************/


/****************************************************************/
void add(int pos, Tree e, Queue& l) // aggiunge e nella posizione pos
{
   if (pos < 0 || pos > l.size) {cout << "\nPosizione fuori range, operazione ignorata\n"; return;}
   
   if (l.size == l.maxsize) // l'array e' pieno, per poter inserire un nuovo Treeento devo ridimensionare l'array espandendolo; l'unico modo e' creare un array piu' grande e copiare in esso gli Treeenti di l
      {
      cout << "\nMessaggio di sistema: Espansione dell'array\n";
      l.size++;
      l.maxsize += BLOCKDIM;
      Tree* auxArray = new Tree[l.maxsize];
      for (int i=0; i<pos; ++i)
          auxArray[i] = l.queue[i];
      auxArray[pos] = e;
      for (int i=pos+1; i<l.size; ++i)
          auxArray[i] = l.queue[i-1];
      delete[] l.queue;
      l.queue = auxArray; 
      return;
      }

   // se la funzione non ha incontrato un return, vuole dire che pos e' nel range corretto e l'array non e' pieno; devo solo posizionare l'Treeento in pos e shiftare a destra gli altri, aggiornando la size della lista
     l.size++;
     for (int i=l.size-1; i>pos; --i)
           l.queue[i] = l.queue[i-1];
     l.queue[pos] = e;
     return;
}


/****************************************************************/
Tree remove(int pos, Queue& l)
{
   if (pos < 0 || pos >= l.size) 
     {
      cout << "\nPosizione fuori range, operazione ignorata, si restituisce " << emptyNode << "\n"; 
      return emptyNode;
     }
  
// se rimuovendo l'Treeento si liberano BLOCKDIM celle, allora ridimensioniamo l'array; l'unico modo e' creare un array piu' piccolo e copiare in esso gli Treeenti di l
   if (l.maxsize-l.size+1==BLOCKDIM && l.maxsize>BLOCKDIM)
   {
      cout << "\nMessaggio di sistema: Contrazione dell'array\n";
      l.size--;
      l.maxsize -= BLOCKDIM;
      Tree* auxArray = new Tree[l.maxsize];
      for (int i=0; i<pos; ++i)
          auxArray[i] = l.queue[i];
      for (int i=pos; i<l.size; ++i)
          auxArray[i] = l.queue[i+1];
      Tree tmp=l.queue[pos];
      delete[] l.queue;
      l.queue = auxArray; 
      return tmp;
   }

// se la funzione non ha incontrato un return, vuole dire che pos e' nel range corretto e la lista non puo' essere ridotta di dimensione; devo solo restituire l'Treeento in pos e shiftare a sinistra gli altri, aggiornando la size della lista.
     Tree tmp=l.queue[pos];
     for (int i=pos+1; i<l.size; ++i)
           l.queue[i-1]=l.queue[i];
     l.size--;
     return tmp;
}


/****************************************************************/
/* 			FUNZIONI SULLE CODE 			*/
/****************************************************************/

Queue queue::createEmpty(){
    Queue q;
    q.size = 0;
    q.maxsize = BLOCKDIM;
    Tree* aux = new Tree[BLOCKDIM];
    q.queue = aux;
    return q;
}


/****************************************************************/
void queue::enqueue(Tree e, Queue& l) // aggiunge e in coda
{
   add(l.size, e, l);
}


/****************************************************************/
Tree queue::dequeue(Queue& l) // rimuove il primo Treeento e lo restituisce
{
   return remove(0, l);
}


/****************************************************************/
Tree queue::first(Queue& l) // restituisce il primo Treeento
{
   if (isEmpty(l)) return emptyNode;   
   else return l.queue[0];
}




/****************************************************************/
bool queue::isEmpty(const Queue& l)
{
   return (l.size == 0);
}


/****************************************************************/
void print(const Queue& l)
{
cout << endl;
for (int i=0; i<l.size; ++i)
   cout << (l.queue[i]->elem).freq << "; "; 
cout << endl;
}
