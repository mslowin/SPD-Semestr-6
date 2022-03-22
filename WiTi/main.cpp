#include <iostream>
#include <fstream>

using namespace std;

int witi(int*p, int*d, int*w, int N);

struct zadanie
{
	int p;		//czas w jakim zadanie jest wykonywane		
	int w;		//waga zadania, w zależności od jej wielkości naliczna jest kara
	int d;		//deadline do którego zadanie powinno być wykonane i od którego liczona jest kara za spóźnienie
};

int main() 
{
    zadanie zad[100];
    int c, n;

    //---------------------------------------------------WCZYTYWANIE
    ifstream data("witi.data.txt");
    string tmp; 
    while(tmp!="data.10:") 
        data>>tmp; 
    data>>n;
    for(int i=0;i<n;i++) 
        data>>zad[i].p>>zad[i].w>>zad[i].d;
    
    data.close();
    //--------------------------------------------------------------   

    //----------------------------------------------WYPISANIE DANYCH
    for(int i=0;i<n;i++) 
        cout << zad[i].p << " " << zad[i].w << " " << zad[i].d << endl;
    //-------------------------------------------------------------- 

    int N = 1 << n;         //przesunięcie wartości N o n bitów w lewo. Na przykład dla N = 1 << 3,   wartość N byłaby równa 8, a dla << 4, 16
                            //dla 10 operacji (jak w witi.dane.txt) N w tym momencie wynosi 1024
    int* F = new int[N];    //deklaracja nowej tablicy F o rozmiarze N
    F[0] = 0;
    //TODO: for(...){WiTi}
    for (int set = 1; set < N; set++)
    {
        c = 0;
        cout << endl << "------------";
        for (int i = 0, b = 1; i < n; i++, b *= 2)
        {            
            // cout << endl << i << " " << b << " " << set;
            if (set & b)
            {
                // cout <<  " HELLO";
                c += zad[i].p;
                cout << endl << zad[i].p;
            }
        }
    }
    delete[] F;

    return 0;
}

// int witi(int*p, int*d, int*w, int N, int*X) {}
