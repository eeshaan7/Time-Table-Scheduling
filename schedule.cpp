#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


struct Node {
	vector <int> tuples;
};

const int N_per = 30;  // Number of periods  = 30
int N_tup = 0; // Number of tuples   = 100

vector <int> classes;
vector <int> teachers;
vector <int> rooms;


int is_Compatible(int i, int j)
{
	if(classes[i] == classes[j] || teachers[i] == teachers[j] || rooms[i] == rooms[j])
	{
		return 0;
	}
	return 1;
}

int main()
{
	clock_t tStart = clock();
	// Reading from File
	
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

	// Implementing greedy algorithm similar to Partitioned Interval Scheduling

	int tuples[N_tup] = {0};
	Node P[N_per];
	int flag = 0;
	for(int i=0;i<N_tup;i++)
	{
		flag = 0;
		int label[N_per] = {0};
		for(int j=0;j<i;j++)
		{
			if(is_Compatible(i,j) == 0)
			{
				label[tuples[j]]++;
			}
		}
		for(int j=0;j<N_per;j++)
		{
			if(label[j] == 0)// && P[j].tuples.size() < 4)
			{
				tuples[i] = j;
				P[j].tuples.push_back(i);
				flag = 1;
				//cout<<"Tuple "<<i+1<<" alloted"<<endl<<endl;
				break;
			}
		}
		if(flag == 0)
		{
			cout<<"Tuple "<<i+1<<" Not alloted"<<endl<<endl;
			break;
		}
	}

	// Displaying final timetable

	for(int i=0;i<30;i++)
	{
		cout<<"Period "<<i+1<<" - ";
		for(int j=0;j<P[i].tuples.size();j++)
		{
			cout<<P[i].tuples[j]<<" ";
		}
		cout<<endl;
	}
	printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	
}