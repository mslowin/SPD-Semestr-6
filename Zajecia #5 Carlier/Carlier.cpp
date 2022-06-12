#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int  max_time_of_jobs(int num_of_jobs, int *R, int *P, int *Q);
int  min_num_from_an_array(int *array, int num_of_elements);
int  max_num_from_an_array(int *array, int num_of_elements);
int* sort_and_return_new_array(int *R, int num_of_elements);
int  schrage(const int num_of_jobs, int *R, int *P, int *Q);
int  schragePodzial(const int num_of_jobs, int *R, int *P, int *Q);

int main()
{
    string s[9] = { "data.000:","data.001:","data.002:","data.003:","data.004:",
        "data.005:","data.006:","data.007:","data.008:" };
    string tmp; 
    ifstream data("schr.data.txt");
    int N;
    int R[100];
    int P[100];
    int Q[100];
    int X[100];

    for(int i = 0; i < 9; i++) //petla for sluzaca do przemieszczania sie pomiedzy ośmioma zbiorami danych
    {
        while(tmp != s[i]) 
            data >> tmp; 
        data >> N;
        for (int j = 0; j < N; j++)
            data >> R[j] >> P[j] >> Q[j];

        const int num_of_jobs = sizeof(R)/sizeof(R[0]);   // dla przykładu podstawowego wynosi 7

        int Cmax;
        Cmax = schrage(N, R, P, Q);
        cout << Cmax << endl;
    }

    return 0;
}

int  schragePodzial(const int num_of_jobs, int *R, int *P, int *Q)
{
    int* X = new int [num_of_jobs];
    int* tab_RQ = new int [num_of_jobs];
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

    int temp = 0;   // zmienna pomocnicza do iteracji po tablicy sortR
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

            for(int i = 0; i < N; i++)              // iterujac przez wszystkie zadania sprawdzamy ktore zadanie jest tym z
                if(avaliable_jobs_Q[i] == max_Q)    // najwiekszym Q
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

    delete[] X;
    delete[] tab_RQ;
    delete[] done_jobs_R;
    delete[] avaliable_jobs;
    delete[] avaliable_jobs_Q;
    delete[] C;

    return Cmax;
}

int  schrage(const int num_of_jobs, int *R, int *P, int *Q)
{
    int* X = new int [num_of_jobs];
    int* tab_RQ = new int [num_of_jobs];
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

    int temp = 0;   // zmienna pomocnicza do iteracji po tablicy sortR
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

    delete[] X;
    delete[] tab_RQ;
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
