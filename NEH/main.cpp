#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int  NEH(int N, int M, int*P, int*X);
int  cmax(int N, int M, int *P, int *X);
void wypisz_dane(int N, int M, int*P);

int main()
{
    string tmp; 
    ifstream data("neh.data.txt");
    string s="data.",s1;
    int N;          //ilosc zadan (np. w pierwszym zestawie wynosi 4)
    int M;          //liczba maszyn (np. w pierwszym zestawie wynosi 3)
    int P[10000];   //zadania
    int X[1000];    //kolejnosc/uszeregowanie
    int cmax;       //cmax dla pojedynczego zestawu danych

    for(int i = 0; i < 1; i++) {                  //petla for do iteracji po wszystkich 120 zbiorach danych
    //TODO:    zamienic w petli for, żeby i < 121

        //----------------------------------------------------------WCZYTYWANIE DANYCH
        if(i < 10) {
            s1 = "data.00" + to_string(i) + ":";
        }
        else if(i < 100) {
            s1 = "data.0" + to_string(i) + ":";
        }
		else
		{
			s1 = "data." + to_string(i) + ":";
		}
        while(tmp != s1) 
            data >> tmp; 
        data >> N >> M;
        for (int j = 0; j < N * M; j++)
            data >> P[j];
        for (int j = 0; j < N; j++)
            X[j] = j;
        //----------------------------------------------------------------------------


        //------------------------------------------------------------WYPISANIE DANYCH
        wypisz_dane(N, M, P);
        //----------------------------------------------------------------------------

        
        cmax = NEH(N, M, P, X);
        cout << s1 <<" cmax: " << cmax <<endl;
    }
    return 0;
}

int NEH(int N, int M, int*P, int*X) {
    for(int n = 0; n < N; n++) {         //petla for dla zadan (zadania: 1, 2, 3, 4)
        for(int m = 0; m < M; m++) {     //wewnetrzna petla for dla maszyn (maszyny: 1, 2, 3)
            //TODO: Tutaj należy optymalnie uszeregować zadania, aby potem obliczyc ich Cmax
        }
    } 
    return cmax(N, M, P, X);    //funkcja zwraca wynik funkcji cmax(), czyli podaje na wejscie obliczoną, optymalną kolejność, a zwracany jest cmax dla takiej kolejnosci
}

/**
 * @brief Funkcja oblicza Cmax dla konkretnego ulozenia zadan na maszynie
 * 
 * @param N ilosc zadan
 * @param M ilosc maszyn
 * @param P zadania
 * @param X kolejnosc/uszeregowanie
 * @return (int) Cmax dla uszeregowania
 */
int  cmax(int N, int M, int *P, int *X) {
    int C[100];                     //momenty zakonczenia poszczegolnych zadan
	for (int m = 0; m <= M; m++)    //petla for dla maszyn 
		C[m] = 0;                   //przypisanie wszystkim maszynom C = 0 (bez zadan maszyny nie pracuja)

	for (int n = 0; n < N; n++)                         //petla for dla zadan
		for (int m = 1; m <= M; m++)                    //wewnetrzna petla for dla maszyn
			C[m] = max(C[m],C[m-1]) + P[(m-1)+X[n]*M];  //obliczenie C dla konkretnego zadania na konkretnej maszynie

	return C[M];    //zwracamy C dla ostatniego zadania na ostatniej maszynie, czyli Cmax
}

/**
 * @brief Funkcja wypisuje dane zampisane w tablicy P
 * 
 * @param N ilosc zadan
 * @param M ilosc maszyn
 * @param P zadania
 */
void wypisz_dane(int N, int M, int*P) {
    int pom = 0;
    for(int i = 0; i < N * M; i++) {
        cout << P[i] << " ";
        pom++;
        if(pom == 3) {
            cout << endl; 
            pom = 0;
        }
    }
}