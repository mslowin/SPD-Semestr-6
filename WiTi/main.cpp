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

    //--------------------------------------------------WCZYTYWANIE DANYCH
    ifstream data("witi.data.txt");
    string tmp; 
    while(tmp!="data.10:") 
        data>>tmp; 
    data>>n;
    for(int i=0;i<n;i++) 
        data >> zad[i].p >> zad[i].w >> zad[i].d;
    data.close();
    //--------------------------------------------------------------------



    //----------------------------------------------------WYPISANIE DANYCH
    for(int i=0;i<n;i++) 
        cout << zad[i].p << " " << zad[i].w << " " << zad[i].d << endl;
    //--------------------------------------------------------------------



    int N = 1 << n;           //przesunięcie wartości N o n bitów w lewo. Na przykład dla N = 1 << 3,   wartość N byłaby równa 8, a dla << 4, 16
                              //dla 10 operacji (jak np. w data.10:) liczba N wynosi 1024
    int* F = new int[N];      //deklaracja nowej tablicy F o rozmiarze N, tu przechowywane beda optymalne kary dla kolejnych iteracji N
    F[0] = 0;                 //kara w przypadku gdy nie ma zadnych zadan na maszynie wynosi F[0] = 0 

    for (int set = 1; set < N; set++)                       //petla for iterujaca po wszystkich mozliwosciach ustawienia zadan w systemie binarnym (np dla 4 zadan: 0000 0001 0010 0011 0100 0101 0111 ...)
    {
        c = 0;                                              //czas zadan, ktore juz sie wykonaly, czas zakonczenia ostatniego zadania na maszynie
        for (int i = 0, bin = 1; i < n; i++, bin *= 2)      //bin = 1, 2, 4, 8, ... iteracja nastepuje poprzez mnzenie przez 2, gdyz w ten sposob przeuwamy binarna dwojke w lewo
        {
            if (set & bin)                                  //operacja AND jest prawdziwa, jeśli zadanie (dla 4 zadan: bin = 0001, 0010, 0100, ...) zawiera się w set
            {
                c += zad[i].p;                              //do czasu calkowitego dodajemy czas wykonywania konkretnego zadania
            }
        }
        F[set] = 999999;                                    //ustawiamy na poczatku F na duza liczbe, zeby skorzystac bez przeszkod z funkcji min() przy pierwszej teracji
        for (int k = 0, bin = 1; k < n; k++, bin *= 2)      //Kolejna petla for iterujaca binarne zadania (identyczna jak poprzedznia)
        {
            if (set & bin)                                  //if rowniez jest taki sam jak wczesniej, gdyz chcemy sprawdzic ile wynosilaby kara dla dokladnie takich smych ustawien
            {
                F[set] = min(F[set], F[set - bin] + zad[k].w * max(c - zad[k].d, 0)); //wybieramy najmniejsza wartosc kary za pomoca funkcji min()
            }
        }
    }
    cout << "Optymalne rozwiazanie: " << F[N - 1] << endl;  //ostatnie pole tablicy (same jedynki) jest optymalnym rozwiazaniem, analogicznie jak bylo to obliczone w prezentacji i na tablicy
    
    delete[] F;
    return 0;
}
