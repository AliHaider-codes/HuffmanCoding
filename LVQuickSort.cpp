#include "LVQuickSort.h"

void scambia(vector<float>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

void scambia(vector<char>& v, int i, int j)
{ 
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}


int partizionaInPlace(vector<float>& v, int inizio, int fine, vector<char>& w)
{
   int pivotIndex = inizio+rand()%(fine-inizio+1); // scelgo un indice a caso tra inizio e fine: sara' il mio pivot
   scambia(w, pivotIndex, inizio);
   scambia(v, pivotIndex, inizio); // metto il pivot all'inizio della sequenza da riordinare
   int i = inizio+1;
   for (int j=inizio+1; j<=fine; ++j)
       {
       if (v[j] < v[inizio]) // confronto con il pivot che e' all'inizio
          {
          scambia(v, i, j);
          scambia(w, i, j);
          ++i;
          }
       }
	 scambia(v, inizio, i-1);
	 scambia(w, inizio, i-1);
   return i-1;
}


void qs(vector<float>& v, int inizio, int fine, vector<char>& w)
{
    if (inizio < fine)
      {   
          int pivot_index=partizionaInPlace(v, inizio, fine, w);
          qs(v, inizio, pivot_index-1, w);
          qs(v, pivot_index+1, fine, w);
      }
}


void LVQuickSort(vector<float>& v, vector<char>& w)
{
   srand(time(NULL)); // srand per fissare il seme della generazione pseudo-casuale
   qs(v, 0, v.size()-1, w);
}
