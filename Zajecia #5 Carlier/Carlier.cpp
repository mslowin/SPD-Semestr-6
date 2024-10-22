#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int  max_time_of_jobs               (int num_of_jobs, int *R, int *P, int *Q);
int  min_num_from_an_array          (int *array, int num_of_elements);
int  max_num_from_an_array          (int *array, int num_of_elements);
int* sort_and_return_new_array      (int *R, int num_of_elements);
int  schrage                        (const int num_of_jobs, int *R, int *P, int *Q, int *X);
int  schragePodzial                 (const int num_of_jobs, int *R, int *P, int *Q, int *X);
bool are_all_jobs_finished          (const int num_of_jobs, int *avaliable_jobs);
void jobs_avaliable_at_specific_time(int t, const int num_of_jobs, int *done_jobs_R, int *R);
int  second_min_num_from_an_array   (int *array, int num_of_elements);
void check_block                    (const int num_of_jobs, int* R, int* P, int* Q, int* X, int& newI, int& newR, int& newQ);
void carlier                        (const int num_of_jobs, int* R, int* P, int* Q, int* X, int& UB);


int main()
{
    string s[9] = { "data.000:","data.001:","data.002:","data.003:","data.004:",
        "data.005:","data.006:","data.007:","data.008:" };
    string tmp; 
    ifstream data("carl.data.txt");

    for(int i = 0; i < 9; i++) //petla for sluzaca do przemieszczania sie pomiedzy ośmioma zbiorami danych
    {
        int N;
        int R[100];
        int P[100];
        int Q[100];
        int X[100];
        //  X   = { 0, 1, 2, 3, 4, 5, 6}
        // int R[] = {10,13,11,20,30, 0,30};
        // int P[] = { 5, 6, 7, 4, 3, 6, 2};
        // int Q[] = { 7,26,24,21, 8,17, 0};

        cout << endl << "----------------------data.00" << i << endl;
        while(tmp != s[i]) 
            data >> tmp; 
        data >> N;
        for (int j = 0; j < N; j++)
        {
            data >> R[j] >> P[j] >> Q[j];   // czytanie danych z pliku
        }
        // N = 7;

        int Cmax;
        int LB;     // dolne ograniczenie
        int UB;     // gorne ograniczenie
        
        UB = schrage(N, R, P, Q, X);       // gorne ograniczenie to wynik schrage, bo nie moze byc gorzej od tego
		cout << "Schrage: " << UB << endl;
        carlier(N, R, P, Q, X, UB);
		cout << "Schrage z podzialem: " << schragePodzial(N, R, P, Q, X) << endl;
		cout << "Carlier: " << UB << endl;
    }

    cout << endl;
    return 0;
}

void check_block(const int num_of_jobs, int* R, int* P, int* Q, int* X, int& newI, int& newR, int& newQ)
{
    int Cmax = 0;
	int placeB = -100; // pozycja zadania B w bloku krytycznym
    int length_m = 0;  // dlugosc uszeregowania zadan bez Q (pierwsze R + P poszczegolnych zadan)
	int tab_pom[100];

    // sprawdzenie dlugosci bloku krytycznego
	for(int i = 0; i < num_of_jobs; i++) // petla iterujaca po wszystkich zadaniach
	{
		int j = X[i];         // przypisanie kolejnosci zadan   
        if(length_m >= R[j])
            tab_pom[i] = 1;   // dzieki tab_pom mozna rozroznic bloki krytyczne jako jedynki oddzielone od siebie zerami
        else
            tab_pom[i] = 0;   // jesli konczy sie blok krytyczny (np przerwa na maszynie) to wstawiamy 0
        
		length_m = P[j] + max(length_m, R[j]); // aktualizacja dlugosci length_m

		if(Cmax < length_m + Q[j]) {    // jesli Cmax odcinka jest mniejszy od length_m + Q, czyli jesli nie skonczyl sie blok krytyczny
			placeB = i;                 // miejsce zadania konczacego blok przesuwana jest dalej
            Cmax = length_m + Q[j];     // Cmax dla pewnej dlugosci uszeregowania zadan
		}
	}

	int i = placeB;             // indeks zadania konczacego blok krytyczny
    int j = -1;                 // wyzerowanie kolejnosci
	int zadB_R = R[X[placeB]];  // czas przybycia ostatniego zadania z bloku
	int zadB_P = P[X[placeB]];  // czas wykonania ostatniego zadania z bloku
	int zadB_Q = Q[X[placeB]];  // czas stygniecia ostatniego zadania z bloku

	while(tab_pom[i])   // wykonuj zawsze, jesli istnieje blok krytyczny
	{
		if(Q[X[--i]] < zadB_Q) // pierwsze zadanie poprzedzajace zadB, ktore ma mniejsze Q niz zadB, konczy blok od przodu
		{
			j = X[i];   // miejsce, w korym zaczyna sie blok krytyczny
			break;
		}
		zadB_R = min(zadB_R, R[X[i]]); // aktualizacja R bloku
		zadB_P += P[X[i]];             // aktualizacja P bloku            
	}
    // stworzenie nowych problemow - nowych wezlow
	newI = j;                 // indeks zadania rozpoczynajacego blok
	newR = zadB_R + zadB_P;   // nowa wartosc R (np. na slajdach z 10 zrobilo sie 28)
	newQ = zadB_Q + zadB_P;   // nowa wartosc Q (np. na slajdach wezel 3 - newQ = 38)
}

void carlier(const int num_of_jobs, int* R, int* P, int* Q, int* X, int& UB)
{
    if(schragePodzial(num_of_jobs, R, P, Q, X) < UB)  // jesli schrage z podzialem zwroci wartosc wieksza 
    {                                                  // lub rowna gornej granicy, to wychodzimy z funkcji

        int U = schrage(num_of_jobs, R, P, Q, X);  // liczymy nowy Cmax ze schrage
        if (U < UB)     // jesli schrage zwroci wartosc mniejsza niz aktualne UB
            UB = U;     // to zmniejszamy UB (upper bound) - bedzie to rowniez wynik algorytmu
        
        int new_index, new_r, new_q;
        check_block(num_of_jobs, R, P, Q, X, new_index, new_r, new_q);

        if(new_index > 0) // jesli istnieje blok krytyczny
        {
            int pomR = R[new_index];   // zmienne pomocnicze do przechowywania 
            int pomQ = Q[new_index];   // wartosci orginalnych R i Q
            R[new_index] = new_r;      // chwilowa zamiana czasu dostarczenia R, zeby sprawdzic wezel dla nowego R 
            carlier(num_of_jobs, R, P, Q, X, UB);
            R[new_index] = pomR;       // powrot do wczesniejszego R
            Q[new_index] = new_q;      // chwilowa zmiana czasu stygniecia Q, zeby sprawdzic wezel dla nowego Q
            carlier(num_of_jobs, R, P, Q, X, UB);
            Q[new_index] = pomQ;       // powrot do wczesniejszego Q
        }
    }
}

int  schragePodzial(const int num_of_jobs, int *R, int *P, int *Q, int *X)
{
    int* done_jobs_R = new int [num_of_jobs];
    int* avaliable_jobs = new int [num_of_jobs];
    int* avaliable_jobs_Q = new int [num_of_jobs];
    int* C = new int [num_of_jobs];

    int N = num_of_jobs;
    int Cmax;                             // Całkowity czas uszeregowania liczony na końcu

    for (int i = 0; i < num_of_jobs; i++) // przypisanie kolejności 1,2,3,... do tablicy X[]
    {
        X[i] = i;
        done_jobs_R[i] = R[i];
        avaliable_jobs[i] = -1;
        avaliable_jobs_Q[i] = -1;
    }

    int t = 0;
    int max_Q = 0;
    int t_next;
    int max_Q_index = 0;
    int krok = 0;

    while(are_all_jobs_finished(num_of_jobs, avaliable_jobs) == false)
    {

        if(krok == 0)
            t_next = 999;
        else
        {
            t_next = min_num_from_an_array(done_jobs_R, N);
            // jesli aktualna chwila jest mniejsza od poczatku jakiegokolwiek zadania
            if(t < t_next)  // dla podstawowego przypadku wykonuje się tylko raz miedzy t = 6 i t = 10
            {
                t = t_next;
                t_next = second_min_num_from_an_array(done_jobs_R, N);
            }
        }

        for(int i = 0; i < N; i++)    // stprawdzamy ile jest dostepnych zadan w danej chwili t
            if(done_jobs_R[i] <= t)             // jezeli ktorekolwiek zadanie ma R mniejsze od t zapisujemy je
                avaliable_jobs[i] = 0;          // jezeli w danej chwili zadanie jest dostepne wstawiamy 0
        
        for(int i = 0; i < N; i++)    // w odpowiednie miejsca tabeli avaliable_jobs_Q wstawiamy czasy Q zadan
            if(avaliable_jobs[i] == 0)          // dostepnych w danej chwili
                avaliable_jobs_Q[i] = Q[i];

        max_Q = max_num_from_an_array(avaliable_jobs_Q, N);
        // cout << "max_Q = " << max_Q << endl;

        // for(int i = 0; i < N; i++)              
        //     cout << done_jobs_R[i] << " " ;

        for(int i = 0; i < N; i++)              // iterujac przez wszystkie dostępne zadania sprawdzamy ktore zadanie jest tym z
            if(avaliable_jobs_Q[i] == max_Q)    // najwiekszym Q
            {
                max_Q_index = i;                // max_Q_index to indeks zadania z najwiekszym Q, ktore dodajemy do zadan wykonanych
                break;
            }
        
        // cout << endl << "t_next = " << t_next << endl;
        // cout << "t = " << t << endl;
        // cout << "P = " << P[max_Q_index] << endl;

        if(t_next < t + P[max_Q_index])
        {
            done_jobs_R[max_Q_index] = 9999;
            P[max_Q_index] = P[max_Q_index] - (t_next - t);
            t = t_next;
        }
        if(t_next >= t + P[max_Q_index])
        {
            t = t + P[max_Q_index];
            // avaliable_jobs[max_Q_index] = 99;       // wykonane zadanie przyjmuje wartosc rozna od 0 i -1
            // avaliable_jobs_Q[max_Q_index] = -1;     // czas Q wykonanego zadania zmieniamy tak, żeby nie przeszkadzał przy wyliczaniu maksymalnego Q w kolejnych krokach
            done_jobs_R[max_Q_index] = 9999;        // czas R wykonanego zadania zmieniamy tak, żeby nie zmieścił się w warunku if(done_jobs_R[i] <= t) 
        }
        
        // cout << "dostepne zadania zaznaczone sa zerem:  (-1 <- tych jeszcze nie ma, 99 <- zakonczone)" << endl;
        // for(int i = 0; i < N; i++)
        //         cout << avaliable_jobs[i] << " ";

        avaliable_jobs[max_Q_index] = 99;       // wykonane zadanie przyjmuje wartosc rozna od 0 i -1
        avaliable_jobs_Q[max_Q_index] = -1;     // czas Q wykonanego zadania zmieniamy tak, żeby nie przeszkadzał przy wyliczaniu maksymalnego Q w kolejnych krokach
        // done_jobs_R[max_Q_index] = 9999;        // czas R wykonanego zadania zmieniamy tak, żeby nie zmieścił się w warunku if(done_jobs_R[i] <= t) 
        C[max_Q_index] = t + Q[max_Q_index];    // obliczenie C dla dodawanego zadania
        krok++;
    }

    Cmax = max_num_from_an_array(C, N);

    delete[] done_jobs_R;
    delete[] avaliable_jobs;
    delete[] avaliable_jobs_Q;
    delete[] C;

    return Cmax;
}

void jobs_avaliable_at_specific_time(int t, const int num_of_jobs, int *done_jobs_R, int *R)
{
    int* jobs_avaliable_now = new int [num_of_jobs];

    for(int i = 0; i < num_of_jobs; i++)
    {
        jobs_avaliable_now[i] = 0;
        if(t == done_jobs_R[i])
            jobs_avaliable_now[i] = 1;
        cout << jobs_avaliable_now[i] << " ";
    }
    cout << endl;
}

bool are_all_jobs_finished (const int num_of_jobs, int *avaliable_jobs) 
{
    int licznik = 0;
    for(int i = 0; i < num_of_jobs; i++)
    {
        if(avaliable_jobs[i] == 99)     // jesli kolejne zadania są wykonane to dodajemy licznik
            licznik++;
    }
    if(licznik == num_of_jobs)          // jesli wszystkie zadania wykonane, zwracamy true
        return true;
    // cout << "licznik = " << licznik << endl;

    return false;
}

int  schrage(const int num_of_jobs, int *R, int *P, int *Q, int *X)
{
    int* done_jobs_R = new int [num_of_jobs];
    int* avaliable_jobs = new int [num_of_jobs];
    int* avaliable_jobs_Q = new int [num_of_jobs];
    int* C = new int [num_of_jobs];

    int N = num_of_jobs;
    int Cmax;                             // Całkowity czas uszeregowania liczony na końcu

    for (int i = 0; i < num_of_jobs; i++) // przypisanie kolejności 1,2,3,... do tablicy X[]
    {
        X[i] = i;
        done_jobs_R[i] = R[i];
        avaliable_jobs[i] = -1;
        avaliable_jobs_Q[i] = -1;
    }

    int tmp_t = 0;
    int t = 0;
    int max_Q = 0;
    int max_Q_index = 0;


        for(int krok = 0; krok < N; krok++)    // kolejnych chwil czasu jest 7 i po inich iterujemy
        {
            tmp_t = min_num_from_an_array(done_jobs_R, N);

            // jesli aktualna chwila jest mniejsza od poczatku jakiegokolwiek zadania
            if(t < tmp_t)  // dla podstawowego przypadku wykonuje się tylko raz miedzy t = 6 i t = 10
                t = tmp_t;

            for(int i = 0; i < N; i++)    // stprawdzamy ile jest dostepnych zadan w danej chwili t
                if(done_jobs_R[i] <= t)             // jezeli ktorekolwiek zadanie ma R mniejsze od t zapisujemy je
                    avaliable_jobs[i] = 0;          // jezeli w danej chwili zadanie jest dostepne wstawiamy 0
            
            for(int i = 0; i < N; i++)    // w odpowiednie miejsca tabeli avaliable_jobs_Q wstawiamy czasy Q zadan
                if(avaliable_jobs[i] == 0)          // dostepnych w danej chwili
                    avaliable_jobs_Q[i] = Q[i];

            max_Q = max_num_from_an_array(avaliable_jobs_Q, N);

            for(int i = 0; i < N; i++)    // iterujac przez wszystkie zadania sprawdzamy ktore zadanie jest tym z
                if(avaliable_jobs_Q[i] == max_Q)                   // najwiekszym Q
                {
                    max_Q_index = i;                // max_Q_index to indeks zadania z najwiekszym Q, ktore dodajemy do zadan wykonanych
                    break;
                }

            t = t + P[max_Q_index];     // modyfikujemy czas
            X[krok] = max_Q_index;      // wrzerzucamy zadanie w kolejnosc

            avaliable_jobs[max_Q_index] = 99;       // wykonane zadanie przyjmuje wartosc rozna od 0 i -1
            avaliable_jobs_Q[max_Q_index] = -1;     // czas Q wykonanego zadania zmieniamy tak, żeby nie przeszkadzał przy wyliczaniu maksymalnego Q w kolejnych krokach
            done_jobs_R[max_Q_index] = 9999;        // czas R wykonanego zadania zmieniamy tak, żeby nie zmieścił się w warunku if(done_jobs_R[i] <= t) 
            C[max_Q_index] = t + Q[max_Q_index];    // obliczenie C dla dodawanego zadania
        }

        // cout << endl << "kolejnosc uszeregowania to: " << endl;
        // for(int i = 0; i < N; i ++)
        //     cout << X[i] + 1 << " ";

        Cmax = max_num_from_an_array(C, N);
        // cout << endl << "Cmax = " << Cmax << endl << endl;

    // delete[] X;
    delete[] done_jobs_R;
    delete[] avaliable_jobs;
    delete[] avaliable_jobs_Q;
    delete[] C;

    return Cmax;
}

int  max_num_from_an_array(int *array, int num_of_elements)
{
    int *newArray = new int [num_of_elements];  // utworzenie nowej tablicy, która będzie sortowana
    int temp = 0;
    for(int i = 0; i < num_of_elements; i++)    // przypisanie nowej tablicy zmiennych z tablicy array
        newArray[i] = array[i];
    
    for(int i = 0; i < num_of_elements; i++)
	{		
		for(int j = i + 1; j < num_of_elements; j++)
		{
			if(newArray[i] > newArray[j])
			{
				temp = newArray[i];
				newArray[i] = newArray[j];
				newArray[j] = temp;
			}
		}
	}

    return newArray[num_of_elements-1];
}

int  second_min_num_from_an_array(int *array, int num_of_elements)
{
    int *newArray = new int [num_of_elements];  // utworzenie nowej tablicy, która będzie sortowana
    int temp = 0;
    for(int i = 0; i < num_of_elements; i++)    // przypisanie nowej tablicy zmiennych z tablicy array
        newArray[i] = array[i];
    
    for(int i = 0; i < num_of_elements; i++)
	{		
		for(int j = i + 1; j < num_of_elements; j++)
		{
			if(newArray[i] > newArray[j])
			{
				temp = newArray[i];
				newArray[i] = newArray[j];
				newArray[j] = temp;
			}
		}
	}

    return newArray[1];
}

int  min_num_from_an_array(int *array, int num_of_elements)
{
    int *newArray = new int [num_of_elements];  // utworzenie nowej tablicy, która będzie sortowana
    int temp = 0;
    for(int i = 0; i < num_of_elements; i++)    // przypisanie nowej tablicy zmiennych z tablicy array
        newArray[i] = array[i];
    
    for(int i = 0; i < num_of_elements; i++)
	{		
		for(int j = i + 1; j < num_of_elements; j++)
		{
			if(newArray[i] > newArray[j])
			{
				temp = newArray[i];
				newArray[i] = newArray[j];
				newArray[j] = temp;
			}
		}
	}

    return newArray[0];
}

int* sort_and_return_new_array(int *R, int num_of_elements)
{
    // static int newArray[num_of_elements];
    int *newArray = new int [num_of_elements];  // utworzenie nowej tablicy, która będzie sortowana
    int temp = 0;
    for(int i = 0; i < num_of_elements; i++)    // przypisanie nowej tablicy zmiennych z tablicy R
        newArray[i] = R[i];
    

    for(int i = 0; i < num_of_elements; i++)
	{		
		for(int j = i + 1; j < num_of_elements; j++)
		{
			if(newArray[i] > newArray[j])
			{
				temp = newArray[i];
				newArray[i] = newArray[j];
				newArray[j] = temp;
			}
		}
	}
    
    return newArray;
}

int max_time_of_jobs(int num_of_jobs,int *R, int *P, int *Q)
{
  // funkcja zlicza całkowity maksymalny czas w najgorszym przypadku działania. Tego czasu na pewno nie da się przekroczyć
  // prawdopodobnie na późniejszym etapie pisania programu nie będzie trzeba obliczać tego czasu
    int max_time = 0;
    for(int i = 0; i < num_of_jobs; i ++)
    {
        max_time = max_time + R[i] + P[i] + Q[i];
    }
    return max_time;
}
