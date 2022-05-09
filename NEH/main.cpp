#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int  NEH(int N, int M, int*P, int*X);
int  cmax(int N, int M, int*P, int*X);
void priorytety(int N, int M, int*P, int*X);
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
    int Cmax;       //cmax dla pojedynczego zestawu danych

    for(int i = 0; i < 2; i++) {                  //petla for do iteracji po wszystkich 120 zbiorach danych
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
            X[j] = j;                   //Na ten moment uszeregowanie zadań to: 0, 1, 2, 3, ...
        //----------------------------------------------------------------------------


        //------------------------------------------------------------WYPISANIE DANYCH
        // wypisz_dane(N, M, P);
        //----------------------------------------------------------------------------

        
        Cmax = NEH(N, M, P, X);
        // Cmax = cmax(N, M, P, X);        // W ten sposób znajdujemy Cmax dla najprostszego uszeregowania 0, 1, 2, 3
        cout << s1 <<" cmax: " << Cmax <<endl;
    }
    return 0;
}

/**
 * @brief Funkcja oblicza optymalne uszeregowanie zadań za pomocą algorytmu NEH
 * 
 * @param N ilosc zadan
 * @param M ilosc maszyn
 * @param P zadania
 * @param X kolejnosc/uszeregowanie
 * @return (int) Cmax dla uszeregowania
 */
int NEH(int N, int M, int*P, int*X) {
    // priorytety(N, M, P, X);              //przypisanie zadaniom ich priorytetów

    // for(int n = 0; n < N; n++) {         //petla for dla zadan (zadania: 1, 2, 3, 4)
    //     for(int m = 0; m < M; m++) {     //wewnetrzna petla for dla maszyn (maszyny: 1, 2, 3)
    //         //TODO: Tutaj należy optymalnie uszeregować zadania, aby potem obliczyc ich Cmax
    //     }
    // } 

    //! Jakiś błąd pojawia się w obliczniu kolejności zadań X
    for (int n = 0; n < N; n++)
	{
		int bestP = -1, bestCmax = 999999999;
		for (int p = n; p >= 0; p--)    //wstawienie zadania w kolejne miejsca i sprawdzenie cmax
		{
			int tmp = cmax(n + 1, M, P, X);
			if (bestCmax > tmp)
			{
				bestCmax = tmp;
				bestP = p;
			}
			if (p > 0)
			{
				swap(X[p], X[p - 1]);
			}
		}
		for (int i = 0; i < bestP; i++)
		{
			swap(X[i], X[i + 1]);
		}

        // // ------------------ TEST X -----------------
        // for (auto i = 0; i < N; i++)
        // {
        //     cout << X[i] + 1 << " ";
        // }
        // cout << endl;
        // // -------------------------------------------
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
 * @brief Funkcja szereguje zadania w zależności od priorytetów
 * 
 * @param N ilość zadań
 * @param M ilość maszyn
 * @param P zadania
 * @param X kolejnosc/uszeregowanie
 */
void priorytety(int N, int M, int*P, int*X) {
    int* W = new int[N];                    //nowa tablica omega
	for (int c = 0; c < N; c++)	            //petla for dla zadań       
		for (int d = 0; d < M; d++)         //petla for dla maszyn
			W[c] += P[c * M + d];           //przypisanie priorytetu każdemu zadaniu

	for (int b = 0; b < N - 1; b++)
		for (int a = 0; a < N - 1; a++)
			if (W[a] < W[a + 1])            //sortowanie zadań priorytetami
			{
				swap(W[a], W[a + 1]);       //zamiana priorytetów    
				swap(X[a], X[a + 1]);       //zamiana kolejności
			}

	delete[]W;
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
        if(pom == M) {
            cout << endl; 
            pom = 0;
        }
    }
}
