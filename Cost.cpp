#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

using namespace std;

vector <int> classes;
vector <int> teachers;
vector <int> rooms;

const int N_per = 30;
int N_tup = 0;

const int M = 7;

struct Period {
	vector <int> tuples;
};

void read_file()
{
	ifstream fil;
	fil.open("Tuples.txt");
	int class_temp;
	int teacher_temp;
	int room_temp;
	fil>>class_temp;
	while(!fil.eof())
	{
		classes.push_back(class_temp);
		fil>>teacher_temp;
		teachers.push_back(teacher_temp);
		fil>>room_temp;
		rooms.push_back(room_temp);
		fil>>class_temp;
		N_tup++;
	}
	fil.close();
}

void Initialize(Period P[])
{
	int lowest = 1;
	int highest = N_per;
	int range = (highest - lowest) + 1;
	int random_integer;
	for(int i=0;i<N_tup;i++)
	{
		random_integer = lowest + (rand() % range);
		P[random_integer-lowest].tuples.push_back(i);	
	}
}

void Initialize_2(Period P[])
{
        int siz;
       	for(int i=0;i<N_per;i++)
	{
	        siz=P[i].tuples.size();
		for(int j=0;j<siz;j++)
		{
		        P[i].tuples.pop_back();	
		}
	}
        
	int lowest = 1;
	int highest = N_per;
	int range = (highest - lowest) + 1;
	int random_integer;
	for(int i=0;i<N_tup;i++)
	{
		random_integer = lowest + (rand() % range);
		P[random_integer-lowest].tuples.push_back(i);	
	}
}

// To compute cost of a particlar period for a particular tuple
int Period_Cost(Period P[], int tup, int idx)
{
	int cost_i = 1, cost_j = 1, cost_k = 1;
	int count_i = 0, count_j = 0, count_k = 0;

	for(int i=0;i<P[idx].tuples.size();i++)
	{
		if(P[idx].tuples[i] != tup)
		{
			if(classes[P[idx].tuples[i]] == classes[tup])
			{
				count_i++;
			}
			if(teachers[P[idx].tuples[i]] == teachers[tup])
			{
				count_j++;
			}
			if(rooms[P[idx].tuples[i]] == rooms[tup])
			{
				count_k++;
			}
		}
	}
	if(count_i)
	{
		cost_i = pow(M,count_i);
	}
	if(count_j)
	{
		cost_j = pow(M,count_j);
	}
	if(count_k)
	{
		cost_k = pow(M,count_k);
	}
	return cost_i*cost_j*cost_k;
}

void Update_Matrix(int A[][N_per], Period P[])
{
	for(int i=0;i<N_tup;i++)
	{
		for(int j=0;j<N_per;j++)
		{
			A[i][j] = Period_Cost(P,i,j);
		}
	}
}

void Update_Matrix_2(int A[][N_per], Period P[], int per1, int per2)
{
        /*
        for(int j=0;j<P[per1].tuples.size();j++)
	{
		A[P[per1].tuples[j]][per1] = Period_Cost(P,P[per1].tuples[j],per1);	
	}
	
	for(int j=0;j<P[per2].tuples.size();j++)
	{
		A[P[per2].tuples[j]][per2] = Period_Cost(P,P[per2].tuples[j],per2);	
	}
	*/
	
	for(int i=0;i<N_tup;i++)
	{
		
		A[i][per1] = Period_Cost(P,i,per1);
		A[i][per2] = Period_Cost(P,i,per2);
		
	}
	
	
}




void Update_Cost(int C[], Period P[], int A[][N_per])
{
	for(int i=0;i<N_per;i++)
	{
		for(int j=0;j<P[i].tuples.size();j++)
		{
			C[P[i].tuples[j]] = A[P[i].tuples[j]][i];	
		}
	}
}

int Find_Best_Period(int A[][N_per], int i)
{
	int pos = 0, min = A[i][0];
	for(int j=0;j<N_per;j++)
	{
		if(A[i][j] < min)
		{
			min = A[i][j];
			pos = j;
		}
	}
	return pos;
}

int Find_Second_Best_Period(int A[][N_per], int i)
{
	int pos = 0, pos_2 = 1, min = A[i][0], min_2 = A[i][1];
	for(int j=0;j<N_per;j++)
	{
		if(A[i][j] < min)
		{
			pos_2 = pos;
			min_2 = min;
			min = A[i][j];
			pos = j;
		}
		else if(A[i][j] < min_2)
		{
			pos_2 = j;
			min_2 = A[i][j];
		}
	}
	return pos_2;
}

bool Perfect_Timetable(int C[])
{
	for(int i=0;i<N_tup;i++)
	{
		//cout<<i<<"^^^^^"<<C[i]<<endl;
		if(C[i] > 1)
		{
			return false;
		}
	}
	return true;
}

void Add_Tuple(Period P[], int tup, int idx)
{
	P[idx].tuples.push_back(tup);
	sort(P[idx].tuples.begin(),P[idx].tuples.end());       ////////////////// Why sorting is done??
}

void Remove_Tuple(Period P[], int tup, int idx)
{
	int temp;
	for(int i=0;i<P[idx].tuples.size()-1;i++)
	{
		if(P[idx].tuples[i] == tup)
		{
			temp = P[idx].tuples[i];
			P[idx].tuples[i] = P[idx].tuples[i+1];
			P[idx].tuples[i+1] = temp; 
		}
	}
	P[idx].tuples.pop_back();
}

void Display(Period P[])
{
	for(int i=0;i<N_per;i++)
	{
		cout<<"Period "<<i+1<<" - ";
		for(int j=0;j<P[i].tuples.size();j++)
		{
			cout<<P[i].tuples[j]<<" ";
		}
		cout<<endl;
	}
}

/*
void Write_File(Period P[])
{
	for(int i=0;)
}
*/

int main()
{
	clock_t tStart = clock();
        read_file();
        cout<<N_tup<<" tuples"<<endl;
	srand(time(NULL));
	Period P[N_per];
	// P is the array of periods
	Initialize(P);
	int A[N_tup][N_per];
	int C[N_tup];
	
	
	// No use
	/*
	for(int i=0;i<N_tup;i++)
	{
		C[i] = 0;
		for(int j=0;j<N_per;j++)
		{
			A[i][j] = 0;
		}
	}
	*/

	Update_Matrix(A,P);
	Update_Cost(C,P,A);
	
	// PRINTING
	for(int i=0;i<N_tup;i++)
	{
		for(int j=0;j<N_per;j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	for(int i=0;i<N_tup;i++)
	{
		cout<<i<<"****"<<C[i]<<endl;
	}
	cout<<endl<<endl;
	cout<<"Initial Timetable\n";
	Display(P);
	// PRINTING ENDS	

	int target_pos;
	int iter = 0;
	int count1 =0;///////////////////
	int iter2 =0;
	int iter3 =0;
	
	
	while(!Perfect_Timetable(C))// && (double)(clock() - tStart)/CLOCKS_PER_SEC < 5)
	{
	        if(iter2==200)
	        {
	                iter3++;
	                cout<<iter3<<"\n";
	                iter2=0;
	                Initialize_2(P);
	                //Display(P);
	                Update_Matrix(A,P);
	                Update_Cost(C,P,A);
	        }
		for(int i=0;i<N_per;i++)
		{
			for(int j=0;j<P[i].tuples.size();j++)
			{
			    count1++;
				target_pos = Find_Best_Period(A,P[i].tuples[j]);
				/*
				if(target_pos == i && C[P[i].tuples[j]] != 1)
				{
					//cout<<"abcd"<<endl;
					target_pos = Find_Second_Best_Period(A,P[i].tuples[j]);
				}
				*/
				Add_Tuple(P,P[i].tuples[j],target_pos);
				Remove_Tuple(P,P[i].tuples[j],i);
				
				//cout<<count1<<endl;
				
				//Update_Matrix(A,P);
				Update_Matrix_2(A,P,i,target_pos);
				/*
				if(i!=target_pos)
				{
				        Update_Matrix_2(A,P,i,target_pos);
			        }
			        */
			}
		}
		Update_Cost(C,P,A);
		iter++;
		iter2++;
		//cout<<iter2<<endl;
	}
	// PRINTING
	for(int i=0;i<N_tup;i++)
	{
		for(int j=0;j<N_per;j++)
		{
			cout<<A[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<endl;
	for(int i=0;i<N_tup;i++)
	{
		cout<<i<<"****"<<C[i]<<endl;
	}
	cout<<endl<<endl;

	cout<<"\nFinal Timetable\n";
	Display(P);	
	cout<<"Iterations = "<<iter<<endl<<endl;
	printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}
