#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>

using namespace std;

vector <int> classes;
vector <int> teachers;
vector <int> rooms;

const int N_per = 30;
int N_tup = 0;
const int N_pop = 10;

struct Period {
	vector <int> tuples;
};

struct TimeTable {
	Period P[N_per];
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

void Initialize(TimeTable &T)
{
	int lowest = 1;
	int highest = N_per;
	int range = (highest - lowest) + 1;
	int random_integer;
	for(int i=0;i<N_tup;i++)
	{
		random_integer = lowest + (rand() % range);
		T.P[random_integer-1].tuples.push_back(i);	
	}
}

int cost_period(Period P)
{
	int class_cost = 0;
	int teacher_cost = 0;
	int room_cost = 0;
	int N = P.tuples.size();
	for(int j=0;j<N-1;j++)
	{
		for(int k=j+1;k<N;k++)
		{
			if(classes[P.tuples[j]] == classes[P.tuples[k]])
			{
				class_cost++;
			}
			if(teachers[P.tuples[j]] == teachers[P.tuples[k]])
			{
				teacher_cost++;
			}
			if(rooms[P.tuples[j]] == rooms[P.tuples[k]])
			{
				room_cost++;
			}
		}
	}
	return class_cost + teacher_cost + room_cost;	
}

int Cost(TimeTable T)
{
	int ans = 0;
	for(int i=0;i<N_per;i++)
	{
		int class_cost = 0;
		int teacher_cost = 0;
		int room_cost = 0;
		int N = T.P[i].tuples.size();
		//cout<<classes[T.P[i].tuples[0]]<<"*********"<<endl;
		ans += cost_period(T.P[i]);
		/*
		for(int j=0;i<N-1;j++)
		{
			for(int k=j+1;k<N;k++)
			{
				
				if(classes[T.P[i].tuples[j]] == classes[T.P[i].tuples[k]])
				{
					class_cost++;
				}
				
				if(teachers[T.P[i].tuples[j]] == teachers[T.P[i].tuples[k]])
				{
					teacher_cost++;
				}
				if(rooms[T.P[i].tuples[j]] == rooms[T.P[i].tuples[k]])
				{
					room_cost++;
				}
				
			}
		}
		*/
		//ans += class_cost + teacher_cost + room_cost;	
	}
	return ans;
}

int is_Per_Ind(TimeTable T[], int N)
{
	for(int i=0;i<N;i++)
	{
		if(Cost(T[i]) == 0)
		{
			return i;
		}
	}
	return -1;
}

void remove_dup(Period &P)
{
	
	/*
	sort(P.tuples.begin(), P.tuples.end()); 
    auto last = unique(P.tuples.begin(), P.tuples.end());
    P.tuples.erase(last, P.tuples.end());
	*/
	int N = P.tuples.size();
	for(int i=0;i<N-1;i++)
	{
		for(int j=i+1;j<N;j++)
		{
			if(P.tuples[i] == P.tuples[j])
			{
				for(int k=i;k<N-1;k++)
				{
					int temp = P.tuples[k];
					P.tuples[k] = P.tuples[k+1];
					P.tuples[k+1] = temp;
				}
				P.tuples.pop_back();
			}
		}
	}
	
}

void display_per(Period P)
{
	for(int i=0;i<P.tuples.size();i++)
	{
		cout<<P.tuples[i]<<" ";
	}
	cout<<endl;
}

Period Cross_Over_Utility(Period P1, Period P2, vector <int> &lost_tup, int A[])
{
	int min_size;
	int size_1 = P1.tuples.size();
	int size_2 = P2.tuples.size();
	Period temp;
	if(size_1 == 0)
	{
		for(int i=0;i<P2.tuples.size();i++)
		{
			if(A[P2.tuples[i]] == 0)
			{
				temp.tuples.push_back(P2.tuples[i]);
				A[P2.tuples[i]] = 1;
			}
		}
		return temp;
	}
	else if(size_2 == 0)
	{
		for(int i=0;i<P1.tuples.size();i++)
		{
			if(A[P1.tuples[i]] == 0)
			{
				temp.tuples.push_back(P1.tuples[i]);
				A[P1.tuples[i]] = 1;
			}
		}
		return temp;
	}
	Period low, high;
	if(size_1 < size_2)
	{
		min_size = size_1;
		low = P1;
		high = P2;
	}
	else
	{
		min_size = size_2;
		low = P2;
		high = P1;	
	}
	int lowest = 0;
	int highest = min_size - 1;
	int range = (highest - lowest) + 1;
	//srand(time(NULL));
	int site = lowest + (rand() % range);
	/*
	cout<<"Period P1 - ";
	display_per(P1);
	cout<<"Period P2 - ";
	display_per(P2);
	cout<<"Site of crossover = "<<site<<endl;
	*/
	Period temp3, temp4;
	for(int i=0;i<P1.tuples.size();i++)
	{
		if(A[P1.tuples[i]] == 0)
		{
			temp3.tuples.push_back(P1.tuples[i]);
			//A[P1.tuples[i]] = 1;
		}
	}
	for(int i=0;i<P2.tuples.size();i++)
	{
		if(A[P2.tuples[i]] == 0)
		{
			temp4.tuples.push_back(P2.tuples[i]);
			//A[P2.tuples[i]] = 1;
		}
	}
	Period temp1, temp2;
	for(int i=0;i<=site;i++)
	{
		if(A[low.tuples[i]] == 0)
		{
			temp1.tuples.push_back(low.tuples[i]);
			A[low.tuples[i]] = 1;
		}
		if(A[high.tuples[i]] == 0)
		{
			temp2.tuples.push_back(high.tuples[i]);
			A[high.tuples[i]] = 1;	
		}
	}
	for(int i=site+1;i<high.tuples.size();i++)
	{
		if(A[high.tuples[i]] == 0)
		{
			temp1.tuples.push_back(high.tuples[i]);
			A[high.tuples[i]] = 1;	
		}
	}
	for(int i=site+1;i<low.tuples.size();i++)
	{
		if(A[low.tuples[i]] == 0)
		{
			temp2.tuples.push_back(low.tuples[i]);
			A[low.tuples[i]] = 1;
		}
	}
	
	//temp1.display();
	//temp2.display();
	remove_dup(temp1);
	remove_dup(temp2);
	/*
	cout<<"Period temp1 - ";
	display_per(temp1);
	cout<<"Period temp2 - ";
	display_per(temp2);
	
	cout<<"Period temp3 - ";
	display_per(temp3);
	cout<<"Period temp4 - ";
	display_per(temp4);
	*/
	int c1 = cost_period(temp1);
	int c2 = cost_period(temp2);
	
	int c3 = cost_period(temp3);
	int c4 = cost_period(temp4);

	temp = (c1<=c2)?temp1:temp2;
	int T = cost_period(temp);
	temp = (c3<T)?temp3:temp;
	T = cost_period(temp);
	temp = (c4<T)?temp4:temp;
	//vector <int> lost_tup;
	if(cost_period(temp) == c1)
	{
		for(int i=0;i<temp2.tuples.size();i++)
		{
			A[temp2.tuples[i]] = 0;
			lost_tup.push_back(temp2.tuples[i]);
		}
		for(int i=0;i<temp3.tuples.size();i++)
		{
			A[temp3.tuples[i]] = 0;
			lost_tup.push_back(temp3.tuples[i]);
		}
		for(int i=0;i<temp4.tuples.size();i++)
		{
			A[temp4.tuples[i]] = 0;
			lost_tup.push_back(temp4.tuples[i]);
		}
	}
	else if(cost_period(temp) == c2)
	{
		for(int i=0;i<temp1.tuples.size();i++)
		{
			A[temp1.tuples[i]] = 0;
			lost_tup.push_back(temp1.tuples[i]);
		}
		for(int i=0;i<temp3.tuples.size();i++)
		{
			A[temp3.tuples[i]] = 0;
			lost_tup.push_back(temp3.tuples[i]);
		}
		for(int i=0;i<temp4.tuples.size();i++)
		{
			A[temp4.tuples[i]] = 0;
			lost_tup.push_back(temp4.tuples[i]);
		}	
	}
	else if(cost_period(temp) == c3)
	{
		for(int i=0;i<temp4.tuples.size();i++)
		{
			A[temp4.tuples[i]] = 0;
			lost_tup.push_back(temp4.tuples[i]);
		}
		for(int i=0;i<temp2.tuples.size();i++)
		{
			A[temp2.tuples[i]] = 0;
			lost_tup.push_back(temp2.tuples[i]);
		}
		for(int i=0;i<temp1.tuples.size();i++)
		{
			A[temp1.tuples[i]] = 0;
			lost_tup.push_back(temp1.tuples[i]);
		}	
	}
	else if(cost_period(temp) == c4)
	{
		for(int i=0;i<temp3.tuples.size();i++)
		{
			A[temp3.tuples[i]] = 0;
			lost_tup.push_back(temp3.tuples[i]);
		}
		for(int i=0;i<temp2.tuples.size();i++)
		{
			A[temp2.tuples[i]] = 0;
			lost_tup.push_back(temp2.tuples[i]);
		}
		for(int i=0;i<temp1.tuples.size();i++)
		{
			A[temp1.tuples[i]] = 0;
			lost_tup.push_back(temp1.tuples[i]);
		}	
	}
	/*
	
	*/
	/*
	cout<<"Period temp - ";
	display_per(temp);
	*/
	//temp.display();
	for(int i=0;i<temp.tuples.size();i++)
	{
		A[temp.tuples[i]] = 1;
	}
	/*
	cout<<"Lost Tuples - ";
	for(int i=0;i<lost_tup.size();i++)
	{
		cout<<lost_tup[i]<<" ";
	}
	cout<<endl;
	/*
	cout<<"Tuples selected - ";
	for(int i=0;i<N_tup;i++)
	{
		if(A[i] != 0)
		{
			cout<<i<<"***"<<A[i]<<endl;
		}
	}
	*/
	return temp;
}

void Display(TimeTable T)
{
	int sum = 0;
	int A[N_tup] = {0};
	for(int i=0;i<N_per;i++)
	{
		cout<<"Period "<<i+1<<" - ";
		sort(T.P[i].tuples.begin(), T.P[i].tuples.end());
		for(int j=0;j<T.P[i].tuples.size();j++)
		{
			cout<<T.P[i].tuples[j]<<" ";
			A[T.P[i].tuples[j]]++;
		}
		cout<<endl;
		cout<<T.P[i].tuples.size()<<endl<<endl;
		sum += T.P[i].tuples.size();
	}
	cout<<endl;
	for(int i=0;i<N_tup;i++)
	{
		if(A[i] != 1)
		{
			cout<<i<<" *** "<<A[i]<<endl;
		}
	}
	cout<<endl<<sum<<endl<<endl;
}

int c = 0;
TimeTable Cross_Over(TimeTable T1, TimeTable T2)
{
	TimeTable ans;
	int A[N_tup] = {0};
	vector <int> lost_tup;
	for(int i=0;i<N_per;i++)
	{
		ans.P[i] = Cross_Over_Utility(T1.P[i], T2.P[i], lost_tup, A);
		/*
		int lowest = 0;
		int highest = N_per - 1;
		int range = (highest - lowest) + 1;
		for(int j=0;j<lost_tup.size();j++)
		{
			int site = lowest + (rand() % range);
			ans.P[site].tuples.push_back(lost_tup[j]);
		}
		remove_dup(ans.P[i]);
		//Display(ans);
		*/
	}
	sort(lost_tup.begin(),lost_tup.end());
	/*
	if(c == 0)
	{
		Display(ans);
		for(int j=0;j<lost_tup.size();j++)
		{
			//if(A[lost_tup[j]] == 1)
				cout<<lost_tup[j]<<"**"<<A[lost_tup[j]]<<" ";
		}
		cout<<endl<<endl;
		c++;
	}
	*/
	int lowest = 0;
	int highest = N_per - 1;
	int range = (highest - lowest) + 1;
	for(int j=0;j<lost_tup.size();j++)
	{
		if(A[lost_tup[j]] == 0)
		{
			int site = lowest + (rand() % range);
			ans.P[site].tuples.push_back(lost_tup[j]);
			A[lost_tup[j]] = 1;
			remove_dup(ans.P[site]);
		}
	}
	/*
	if(c == 1)
	{
		Display(ans);
		c++;
	}
	*/
	/*
	int A[N_tup] = {0};
	int count = 0;
	for(int i=0;i<N_per;i++)
	{
		for(int j=0;j<ans.P[i].tuples.size();j++)
		{
			if(A[ans.P[i].tuples[j]] == 1)
			{
				//cout<<i<<" "<<ans.P[i].tuples[j]<<endl<<endl;
				//display_per(ans.P[i]);
				
				for(int k = j;k<ans.P[i].tuples.size()-1;k++)
				{
					int temp = ans.P[i].tuples[k];
					ans.P[i].tuples[k] = ans.P[i].tuples[k+1];
					ans.P[i].tuples[k+1] = temp; 
				}
				//ans.P[i].tuples[j] = ans.P[i].tuples[ans.P[i].tuples.size()-1];
				//ans.P[i].tuples[ans.P[i].tuples.size()-1] = temp;
				ans.P[i].tuples.pop_back();
				//display_per(ans.P[i]);
			}
			else
			{
				A[ans.P[i].tuples[j]] = 1;	
			}
		}
		/*
		if(count < 2)
		{
			for(int j=0;j<N_tup;j++)
			{
				if(A[j])
					cout<<j<<"****"<<A[j]<<endl;
			}
			count++;
		}
		
	}
	*/
	return ans;
}


void Mutate(TimeTable &T, vector < pair <int, int> > PC)
{
	int lowest = 0;
	int highest = N_per - 1;
	int range = (highest-lowest) + 1;
	int count = 5;
    sort(PC.begin(), PC.end());
    int from, to;
	for(int i=0;i<count;i++)
	{
		int j = 0;
		//while(j < 2)
		//{
			from = PC[N_per-i-1].second;
			int l = 0;
			int h = T.P[from].tuples.size() - 1;
			int r = (h - l) + 1;
			if(r > 0)
			{
				int tup = l + (rand() % r);
				//to = lowest + (rand() % range);
				to = PC[i].second;
				if(from != to)
				{
					T.P[to].tuples.push_back(T.P[from].tuples[tup]);
					for(int k=tup;k<T.P[from].tuples.size()-1;k++)
					{
						int temp = T.P[from].tuples[k];
						T.P[from].tuples[k] = T.P[from].tuples[k+1];
						T.P[from].tuples[k+1] = temp;
					}
					T.P[from].tuples.pop_back();
					remove_dup(T.P[to]);
				}
			}
		//	j++;	
		//}	
		
	}
	/*
	int max = 0;
	int max_idx = 0;
	for(int i=0;i<N_per;i++)
	{
		if(cost_period(T.P[i]) > max)
		{
			max = cost_period(T.P[i]);
			max_idx = i;
		}
	}
	int lowest = 0;
	int highest = 29;
	int range = (highest-lowest) + 1;
	int target_idx = lowest + (rand() % range);
	
	if(target_idx != max_idx)
	{
		lowest = 0;
		highest = T.P[max_idx].tuples.size();
		range = (highest-lowest) + 1;
		int target_tuple = lowest + (rand() % range);
		T.P[target_idx].tuples.push_back(T.P[max_idx].tuples[target_tuple]);
		for(int k=target_tuple;k<highest-1;k++)
		{
			int temp = T.P[max_idx].tuples[k];
			T.P[max_idx].tuples[k] = T.P[max_idx].tuples[k+1];
			T.P[max_idx].tuples[k+1] = temp;
		}
		T.P[max_idx].tuples.pop_back();
		remove_dup(T.P[target_idx]);
	}
	*/	
}

int Fitness(TimeTable T[], int N)
{
	int ans = 0;
	for(int i=0;i<N;i++)
	{
		ans += Cost(T[i]);
	}
	return ans;
}

int main()
{
	clock_t tStart = clock();
    read_file();
	srand(time(NULL));
	TimeTable T[N_pop];
	
	for(int i=0;i<N_pop;i++)
	{
		Initialize(T[i]);	
	}

	int generation = 0;
	int lowest = 0;
	int highest = N_pop - 1;
	int range = (highest-lowest) + 1;
	srand(time(NULL));
	
	//Display(T[1]);
	TimeTable T1[N_pop];
	
	//T1[0] = Cross_Over(T[2], T[7]);
	//Display(T1[0]);
	
	int count = 0;
	
	while(is_Per_Ind(T,N_pop) == -1 && generation < 50000)
	{
		//cout<<"abcd**************"<<generation<<endl;
		int C[N_pop];
		double prob[N_pop];
		int sum1 = 0;
		for(int i=0;i<N_pop;i++)
		{
			C[i] = Cost(T[i]);
			sum1 += C[i];
		}
		int sum2 = 0;
		for(int i=0;i<N_pop;i++)
		{
			C[i] = sum1 - C[i];
			sum2 += C[i];
		}
		for(int i=0;i<N_pop;i++)
		{
			double x = (double)C[i]/sum2;
			//cout<<"x = "<<x<<endl;
			//x = 1 - x;
			if(i == 0)
			{
				prob[i] = x;
			}
			else
			{
				prob[i] = prob[i-1] + x;
			}
		}
		/*
		for(int i=0;i<N_pop;i++)
		{
			cout<<prob[i]<<" ";
		}
		cout<<endl;
		*/
		for(int i=0;i<N_pop;i++)
		{
			double p1 = (double)rand() / (double)RAND_MAX ;
			double p2 = (double)rand() / (double)RAND_MAX ;
			//int par1 = lowest + (rand() % range);
			//int par2 = lowest + (rand() % range);
			//cout<<p1<<"****"<<p2<<endl;
			int par1, par2;
			for(int j=0;j<N_pop;j++)
			{
				if(p1 <= prob[0])
				{
					par1 = 0;
				}
				else if(p1 <= prob[j] && p1 >= prob[j-1])
				{
					par1 = j;
				}
				if(p2 <= prob[0])
				{
					par2 = 0;
				}
				else if(p2 <= prob[j] && p2 >= prob[j-1])
				{
					par2 = j;
				}
			}
			//cout<<par1<<"&&&&&"<<par2<<endl;
			if(par1 != par2)
			{
				T1[i] = Cross_Over(T[par1], T[par2]);
			}
			else
			{
				T1[i] = Cross_Over(T[0], T[1]);
			}
			
			vector < pair<int,int> > PC;
			for(int j=0;j<N_per;j++)
			{
				PC.push_back(make_pair(cost_period(T1[i].P[j]),j)); 
			}
			
			Mutate(T1[i],PC);
			
			//cout<<"New TimeTable"<<endl;
			/*
			if(count == 0)
			{
				Display(T1[0]);
				cout<<endl<<endl;
				count++;
			}
			*/		
		}
		//cout<<Fitness(T1,N_pop)<<" "<<Fitness(T,N_pop)<<endl;
		vector < pair<float,int> > X;
		for(int i=0;i<N_pop;i++)
		{
			X.push_back(make_pair(Cost(T[i]),i));
		}
		for(int i=0;i<N_pop;i++)
		{
			X.push_back(make_pair(Cost(T1[i]),i+N_pop));
		}
		sort(X.begin(),X.end());
		//cout<<Fitness(T,N_pop)<<" ";
		for(int i=0;i<N_pop;i++)
		{
			if(X[i].second < N_pop)
			{
				T[i] = T[X[i].second];
			}
			else
			{
				T[i] = T1[X[i].second - N_pop];
			}
		}
		cout<<X[0].first<<endl;
		/*
		if(Fitness(T1,N_pop) <= Fitness(T,N_pop))
		{
			for(int i=0;i<N_pop;i++)
			{
				T[i] = T1[i];
			}
		}
		*/

		generation++;
		
	}
	//cout<<Fitness(T,N_pop)<<endl;
	if(is_Per_Ind(T,N_pop) >= 0)
	{
		int idx = is_Per_Ind(T,N_pop);
		cout<<"Generation = "<<generation<<" Index = "<<idx<<endl;
		Display(T[idx]);
	}
	else
	{
		cout<<"No perfect individual found in "<<generation<<" generations"<<endl;
	}
	
	printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return 0;
}