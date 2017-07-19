#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
	 Number of Tuples   = 100
	 Number of Periods  = 30
	 Number of Classes  = 15
	 Number of Teachers = 15
	 Number of Rooms    = 15
	 Number of Periods with 4 tuples = 15
	 Number of Periods with 3 tuples = 10
	 Number of Periods with 2 tuples = 5
	  
*/

const int N_tup = 90;
const int N_per = 30;
const int N_class = 3;
const int N_teacher = 3;
const int N_room = 3;

struct Period {
	vector <int> T;
};

void Generate_tuple(int [], int, int, int);
void txt_Tuples(int [], int [], int []);

int main()
{
	srand(time(NULL));
	Period P[N_per];
	int Class[N_tup] = {0};
	int Teacher[N_tup] = {0};
	int Rooms[N_tup] = {0};
	
	int tuples = 0;
	int n_tup = 0;
	
	while(tuples < N_tup)
	{
		/*
		if(tuples < 60)      // Assign 4 tuples to 15 Periods
		{
			n_tup = 4;
		}
		else if(tuples < 90) // Assign 3 tuples to 10 Periods
		{
			n_tup = 3;
		}
		else                 // Assign 2 tuples to 5 Periods
		{
			n_tup = 2;
		}
		*/
		n_tup = N_tup/30;
		Generate_tuple(Class,tuples,n_tup,N_class);
		Generate_tuple(Teacher,tuples,n_tup,N_teacher);
		Generate_tuple(Rooms,tuples,n_tup,N_room);
		tuples += n_tup;
	}
	txt_Tuples(Class, Teacher, Rooms);
	
	return 0;
}

void Generate_tuple(int A[], int idx1, int idx2, int x)
{
	int hash[x] = {0};
	int lowest = 1;
	int highest = x;
	int range = (highest-lowest) + 1;
	int temp;
	int i = idx1;
	while(i < idx1 + idx2)
	{
		temp = lowest + (rand() % range);
		if(!hash[temp-1])
		{
			hash[temp-1] = 1;
			A[i] = temp;
			i++;
		}
	}
}

void txt_Tuples(int A[], int B[], int C[])
{
	int temp,random,i;
	for(i=0;i<N_tup;i++)
	{
		random=rand()%N_tup;

		temp=A[i];
		A[i]=A[random];
		A[random]=temp;

		temp=B[i];
		B[i]=B[random];
		B[random]=temp;

		temp=C[i];
		C[i]=C[random];
		C[random]=temp;
	}
	ofstream fout;
	fout.open("Tuples.txt");
	for(int i=0;i<N_tup;i++)
	{
		fout<<A[i]<<" "<<B[i]<<" "<<C[i]<<endl;
	}
	fout.close();
}


