#include <iostream>

using namespace std;

int  max_time_of_jobs(int num_of_jobs, int *R, int *P, int *Q);
int  min_num_from_an_array(int *array, int num_of_elements);
int  max_num_from_an_array(int *array, int num_of_elements);
int* sort_and_return_new_array(int *R, int num_of_elements);
int* sort_easy(int *R, int num_of_elements);

int main()
{
    //  X   = { 0, 1, 2, 3, 4, 5, 6}
    int R[] = {10,13,11,20,30, 0,30};
    int P[] = { 5, 6, 7, 4, 3, 6, 2};
    int Q[] = { 7,26,24,21, 8,17, 0};
    const int num_of_jobs = sizeof(R)/sizeof(R[0]);   // dla przykładu podstawowego wynosi 7
    int pom = 0;
    int X[num_of_jobs];         // przechowywuje kolejność wykonywania się zadań
    int tab_RQ[num_of_jobs][2]; // przechowuje R i Q zadań, aby je porównać (druga tabela, kora byla na ta tablicy)
    int done_jobs_R[num_of_jobs];         // tablica czasow R zadan, ktore zostaly juz wykonane
    int avaliable_jobs[num_of_jobs];      // tablica zadań dostępnych w danej chwili t
    int avaliable_jobs_Q[num_of_jobs];    // tablica czasow Q zadań dostępnych w danej chwili t

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

    for(int krok = 0; krok < num_of_jobs; krok++)    // kolejnych chwil czasu jest 7 i po inich iterujemy
    {
        // jesli aktualna chwila jest mniejsza od poczatku jakiegokolwiek zadania
        tmp_t = min_num_from_an_array(done_jobs_R, num_of_jobs);
        cout << "t = " << t << endl;
        cout << "tmp_t = " << tmp_t << endl;
        if(t < tmp_t)  // dla podstawowego przypadku wykonuje się tylko raz miedzy t = 6 i t = 10
            t = tmp_t;

        for(int i = 0; i < num_of_jobs; i++)    // stprawdzamy ile jest dostepnych zadan w danej chwili t
            if(done_jobs_R[i] <= t)             // jezeli ktorekolwiek zadanie ma R mniejsze od t zapisujemy je
                avaliable_jobs[i] = 0;          // jezeli w danej chwili zadanie jest dostepne wstawiamy 0
        
        for(int i = 0; i < num_of_jobs; i++)    // w odpowiednie miejsca tabeli avaliable_jobs_Q wstawiamy czasy Q zadan
            if(avaliable_jobs[i] == 0)          // dostepnych w danej chwili
                avaliable_jobs_Q[i] = Q[i];

        max_Q = max_num_from_an_array(avaliable_jobs_Q, num_of_jobs);
        cout << "max_Q = " << max_Q << endl;

        for(int i = 0; i < num_of_jobs; i++)    // iterujac przez wszystkie zadania sprawdzamy ktore zadanie jest tym z
            if(Q[i] == max_Q)                   // najwiekszym Q
                max_Q_index = i;                // max_Q_index to indeks zadania z najwiekszym Q, ktore dodajemy do zadan wykonanych

        for(int i = 0; i < num_of_jobs; i++)
                cout << avaliable_jobs[i] << " ";

        t = t + P[max_Q_index];     // modyfikujemy czas
        X[krok] = max_Q_index;      // wrzerzucamy zadanie w kolejnosc
        avaliable_jobs[max_Q_index] = 99;   // wykonane zadanie przyjmuje wartosc rozna od 0 i -1
        avaliable_jobs_Q[max_Q_index] = -1;
        done_jobs_R[max_Q_index] = 9999;
        
        cout << endl;
        cout << endl;
    }

    cout << "kolejnosc uszeregowania to: " << endl;
    for(int i = 0; i < num_of_jobs; i ++)
        cout << X[i] + 1 << " ";
    return 0;
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
