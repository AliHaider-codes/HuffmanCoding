/*
Huffman Coding
4811831		Haider Ali
4861715		Pedemonte Giacomo

Compile with --> g++ *.cpp
*/

#include "LVQuickSort.h"
#include "queue-array.h"

using namespace std;
using namespace queue;

#define maxAltezzaAlbero 500

vector<char> leggiVettoreDaFile(string nome_file)
{
	ifstream ifs(nome_file.c_str());
    vector<char> v;
    char dato;
    ifs>>dato;
    if (!ifs) throw runtime_error("Errore inserimento dati\n");
   	while(!ifs.eof())
    {          
        v.push_back(dato);   // put into vector
        ifs>>dato;
    }
	return v;
}

vector<char> removeduplicates(vector<char> v)
{
	vector<char> v1 = v;
	auto end = v1.end();
	for (auto i = v1.begin(); i != end; ++i)
	{
		end = remove(i + 1, end, *i);
	}

	v1.erase(end, v1.end());
	return v1;
}

vector <float> freq (vector<char> v){
	vector <char> v_NoDup = removeduplicates(v);
	int M = v_NoDup.size();
	vector <float> f(M);
	
	for(int i = 0; i<M; i++) f[i] = 0;
	
	for(int i = 0; i<M; i++){
		for(int j = 0; j<v.size(); j++){
			if(v_NoDup[i] == v[j]) f[i]++;
		}
	}
	return f;
}

Tree createLeaf(float freq, char character){
	Tree leaf = new Node;
	(leaf->elem).freq = freq;
	(leaf->elem).character = character;
	leaf->left = emptyNode;
	leaf->right = emptyNode;
	leaf->peso = "";
	return leaf;
}

Tree createNode(Tree left, Tree right){
	Tree Nodo = new Node;
	(Nodo->elem).freq = (left->elem).freq + (right->elem).freq;
	(Nodo->elem).character = '\0';
	Nodo->left = left;
	Nodo->right = right;
	Nodo->peso = "";
	return Nodo;
}

Tree huffman(Queue &q, int size){
	for(int i = 0; i<size; i++){
		Tree t1 = dequeue(q);
		Tree t2 = dequeue(q);
		Tree nodo = createNode(t1, t2);
		int j=0;
		for (;j<q.size && (nodo->elem).freq > (q.queue[j]->elem).freq ; ++j);
		add(j, nodo, q);
	}
	return q.queue[0];
}

void prinTree(const Tree r, int depth){
	if (r == emptyNode) return;	
	
	string indent = "--";
	
	for (int i=0; i<depth; i++) 
		cout << indent;
	
	cout << (r->elem).freq << endl;
	
	prinTree(r->left, depth+1);             	
	prinTree(r->right, depth+1);            	
}

void printArray(char arr[], int n) {
  int i;
  for (i = 0; i < n; ++i)
    cout << arr[i];

  cout << "\n";
}

int isLeaf(Tree root) {
  return (root->left==emptyNode) && (root->right==emptyNode);
}

int x = 0;

void printCodes(const Tree t, char arr[], int top, string s[], char v[]) {
  if (t->left != emptyNode) {
    arr[top] = '0';
    printCodes(t->left, arr, top + 1, s, v);
  }

  if (t->right != emptyNode) {
    arr[top] = '1';
    printCodes(t->right, arr, top + 1, s, v);
  }
  if (isLeaf(t)) {
    cout << (t->elem).character << " --> ";
    printArray(arr, top);
	s[x] = "";
	for(int i = 0; i<top ; i++)
		s[x] = s[x] + arr[i];
	v[x] = (t->elem).character;
	x++;
  }
}

int main() {
    string nome_file;
	char arr[maxAltezzaAlbero];
	int top = 0;
	string s[maxAltezzaAlbero];
	char v[maxAltezzaAlbero];
	
    cout << "\nInserire il nome del file da cui leggere (100.txt; 1000.txt; 100000.txt) > ";
    cin >> nome_file;
	vector<char> lettura = leggiVettoreDaFile(nome_file);
	
	cout << endl;
	
	vector<char> r = removeduplicates(lettura);
	vector<float> f = freq(lettura);
	LVQuickSort(f, r);
	
	for(int i = 0; i<f.size(); i++)
		f[i] = f[i]/lettura.size();
		
	float H = 0;
	for(int i = 0; i<f.size(); i++)
		H += f[i] * log2(1/f[i]);

	Queue coda = createEmpty();
	
	for(int i = 0; i<f.size(); i++){
		enqueue(createLeaf(f[i], r[i]), coda);
	}

	Tree root = huffman(coda, f.size()-1);

	prinTree(root, 0);
	cout << endl;
	printCodes(root, arr, top, s, v);

	//riordinamento per lunghezza attesa
	char aux;
	string aux2;
	for(int i = 0; i < f.size(); i++){
		for(int j = 0; j < f.size(); j++)
			if(r[i] == v[j]){
				aux = v[i];
				aux2 = s[i];
				v[i] = r[i];
				s[i] = s[j];
				s[j] = aux2;
				v[j] = aux;
			}
	}
	
	float L = 0;
	for(int i = 0; i < x; i++)
		L += f[i]*s[i].length();
	
	cout << "\nEntropia --> " << H << endl ;
	cout << "\nLunghezza attesa --> "<< L << endl;
	if(L >= H)
		cout << "\n<L> >= H, la codifica puo' essere univocamente decifrabile\n\n";
	else
		cout << "\n<L> < H, la codifica non e' univocamente decifrabile\n\n";

    return 0;
}
