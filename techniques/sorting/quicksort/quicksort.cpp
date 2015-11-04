#include <iostream>

using namespace std;

template <class T>
int particiona(T v, int a, int b) {
	int i, j;

	i = a;
	for ( j=i+1; j<=b; j++ )
		if ( v[j] < v[a] ) {
			i++;
			troca(&v[j], &v[i]);
		}
	
	troca(&v[i], &v[a]);

	return i;
}

template <class T>
void quicksort(T v, int a, int b) {
	if ( not(a < b) ) return;
	int meio = particiona(v, a, b);
	quicksort(v, a, meio - 1);
	quicksort(v, meio + 1, b);
} 

template <class T>
void troca(T *a, T *b) {
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

template <typename T>
void imprime(T v[], int tam) {
	int 	i;
	for ( i=0; i<tam; i++ )
		cout << v[i] << endl;
}

int main() {
	int 	v[] = { 10, 3, 6, 2, 7, 3, 8 }, 
		tam = sizeof(v)/sizeof(int);
	quicksort(v, 0, tam-1);
	imprime(v, tam);
}
