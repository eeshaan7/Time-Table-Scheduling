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
		//cout<<random_integer<<endl;	
	}
	//cout<<"\n";
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
		ans += cost_period(T.P[i]);
		
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


/////////////////////////////////////// USEFUL FUNSTIONS /////////////////////////////////////

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

void display_per(Period P)
{
	for(int i=0;i<P.tuples.size();i++)
	{
		cout<<P.tuples[i]<<" ";
	}
	cout<<endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////


Period Cross_Over_Utility(Period P1, Period P2, int A[])
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
	
	
	if(size_1 < size_2)
	{
		min_size = size_1;
	}
	else
	{
		min_size = size_2;	
	}
	
	int lowest = 0;
	int highest = min_size - 1;
	int range = (highest - lowest) + 1;
	//srand(time(NULL));
	int site = lowest + (rand() % (1+range));  ////////////////////
	
	for(int i=0;i<site;i++)
	{
		if(A[P1.tuples[i]] == 0)
		{
			temp.tuples.push_back(P1.tuples[i]);
			A[P1.tuples[i]] = 1;
		}
	}
	
	for(int i=site;i<P2.tuples.size();i++)
	{
		if(A[P2.tuples[i]] == 0)
		{
			temp.tuples.push_back(P2.tuples[i]);
			A[P2.tuples[i]] = 1;
		}
	}
	


	return temp;
}



TimeTable Cross_Over(TimeTable T1, TimeTable T2)
{
	TimeTable ans;
	int A[N_tup] = {0};
	
	for(int i=0;i<N_per;i++)
	{
		ans.P[i] = Cross_Over_Utility(T1.P[i], T2.P[i], A);
		
	}
	


	int lowest = 0;
	int highest = N_per - 1;
	int range = (highest - lowest) + 1;
	for(int i=0;i<N_tup;i++)
	{
		if(A[i] == 0)
		{
			int site = lowest + (rand() % range);
			ans.P[site].tuples.push_back(i);
			A[i] = 1;
		}
	}
	
	return ans;
}




//////////////////////////////////// MAIN STARTS //////////////////////////////////////


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
	//int lowest = 0;
	//int highest = N_pop - 1;
	//int range = (highest-lowest) + 1;
	
	TimeTable T1[N_pop];
	TimeTable T3[N_pop];
	
	//T1[0] = Cross_Over(T[2], T[7]);
	//Display(T1[0]);
	
	int count = 0;
        bool found=false; 
	int found_index;
		
	while(generation < 100000)
	{
	        generation++;
	        cout<<"Generation: "<<generation<<endl;
		//cout<<"abcd**************"<<generation<<endl;
		double C[N_pop];
		double C_orig[N_pop];
		double C1[N_pop];
		double prob[N_pop];
		double sum1 = 0;
	        

	        
	        for(int i=0;i<N_pop;i++)
		{
			C[i] = Cost(T[i]);
			C_orig[i]=C[i];
			//cout<<"Cost: "<<C[i]<<endl;
			sum1 += C[i];
			if(C[i]==0)
			{
			        found=true;
			        found_index=i;
			}
		}
		
		if(found)
		{
		        cout<<"Here is the required timetable\n";
		        Display(T[found_index]);
		        
		        break;
		}
		
		double sum2 = 0;
		
		for(int i=0;i<N_pop;i++)
		{
			C[i] = sum1 / C[i];
			sum2 += C[i];
		}
		
		
		double x = C[0]/sum2;
		prob[0]=x;
		for(int i=1;i<N_pop;i++)
		{
			x = C[i]/sum2;
			prob[i] = prob[i-1] + x;
		}
		
		///////////////////////////////// PRINTING ////////////////////////////////
		/*
		for(int i=0;i<N_pop;i++)
		{
			cout<<prob[i]<<" ";
		}
		
		cout<<endl;
		*/
		///////////////////////////////////////////////////////////////////////////
		
		for(int i=0;i<N_pop;i++)
		{
			double p1 = (double)rand() / (double)RAND_MAX ;
			double p2 = (double)rand() / (double)RAND_MAX ;
		        
		        int par1, par2;
		        
		        if(p1 <= prob[0])
			{
				par1 = 0;
			}
			else
			{
			        for(int j=1;j<N_pop;j++)
			        {
				        
				        if(p1 <= prob[j] && p1 >= prob[j-1])
				        {
				        	par1 = j;
				        	break;
				        }
			        } 
			}
			par2=par1;
			
			while(par2==par1)
			{
			        
			        if(p2 <= prob[0])
			        {       
				        par2 = 0;
			        }
			        else
			        {
			                for(int j=1;j<N_pop;j++)
			                {
			                	if(p2 <= prob[j] && p2 >= prob[j-1])
			                	{
			                		par2 = j;
			                		break;
			                	}
			                }
			        }
			        p2 = (double)rand() / (double)RAND_MAX ;
			}
			// Now the two parents to be used are selected
			
			//cout<<"Parents Selected: "<<par1<<" and "<<par2<<endl;
			
			T1[i] = Cross_Over(T[par1], T[par2]);
		        //cout<<"Parents: "<<par1<<" and "<<par2<<endl;
		        C1[i]=Cost(T1[i]);
		        //cout<<"Cost of Child: "<<C1[i]<<"\n"; ////////////////////////////////////////////        
		
		
		
		}
		int mini=C1[0];
		for(int k=0;k<N_pop;k++)
		{
		        //T[k]=T1[k];
		        if(C1[k]<mini)
		        {
		                mini=C1[k];
		        }
		}
		cout<<"\n\n\nMINIMUM: COST: "<<mini<<"\n\n\n";
		
		vector < pair<float,int> > X;
		for(int i=0;i<N_pop;i++)
		{
			X.push_back(make_pair(C_orig[i],i));
		}
		for(int i=0;i<N_pop;i++)
		{
			X.push_back(make_pair(C1[i],i+N_pop));
		}
		sort(X.begin(),X.end());
		
		//cout<<"VECTOR X: "<<endl;
		
		/*
		for(int i=0;i<2*N_pop;i++)
		{
		        cout<<X[i].first<<" "<<X[i].second<<endl;
		}
		cout<<"-----------\n";
		*/
		int random[N_pop];
		for(int i=0;i<N_pop;i++)
		{
		        random[i]=i;
		}
		for(int i=0;i<N_pop;i++)
		{
		        int k=rand()%N_pop;
		        int temp=random[i];
		        random[i]=random[k];
		        random[k]=temp;
		}
		
		
		for(int i=0;i<N_pop;i++)
		{
		        int pos=X[i].second;
		        if(pos<N_pop)
		        {
		                T3[random[i]]=T[pos];
		        }
		        else
		        {
		                T3[random[i]]=T1[pos-N_pop];
		        }
		}
		//cout<"now here\n";
		
		for(int i=0;i<N_pop;i++)
		{
		        T[i]=T3[i];
		        //cout<<Cost(T[i])<<endl;
		}
		
		
		//cout<<"1\n";
		/////////////////////// MUTATING
		int timetable=rand()%N_pop;
		int period1=rand()%N_per;
		while(T[timetable].P[period1].tuples.size()==0)
		{
		        period1=rand()%N_per;
		}
		//cout<<"2\n";
		int period2=rand()%N_per;
		while(period2==period1)
		{
		        period2=rand()%N_per;
		}
		//cout<<"3\n";
		int tup=rand()%(T[timetable].P[period1].tuples.size());
		int tup_val=T[timetable].P[period1].tuples[tup];
		
		T[timetable].P[period1].tuples.erase(T[timetable].P[period1].tuples.begin() + tup);
		
		T[timetable].P[period2].tuples.push_back(tup_val);    
		
	
	printf("\nTime taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	       
}