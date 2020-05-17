#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;

//	Author		¸­¬P¦ö B073040031
//	Date		2019/9/21
//	Purpose		Factorial number		 

void carry(vector<int>& process)					//function for carrying decimal vector[] adjust
{
	for(int i=0;i<process.size();i++)				//from first digit to last
	{
		if(process[i]/10)							//if any digit more than 10 let it divided by 10
		{
			if(i==process.size()-1)					//if the vector not enough size to accommodate more digit
				process.push_back(process[i]/10);	//then use push_back to give it 
			else
				process[i+1] += process[i]/10;		//if not need more digit,just plus next place
			process[i] %= 10;						//last remaining 
		}
	}
}

int main()
{
	int n;											//n for input 
	while(cin>>n && n != 0)							//check n not zero, if so ,break
	{
		vector<int> factorial;						//factorial result
		factorial.push_back(1);						//0!=1

		for(int i=1;i<=n;i++)						
		{
			for(int j=0;j<factorial.size();j++)		//let every digit correctly times 10~50 factorial number  
				factorial[j] *= i;					//i is next number,like 4 times (2*3)

			carry(factorial);						//call function to deal with the big integer	
			
			cout<<setw(2)<<i<<"! = ";				//make 1~9 output more beautiful

			for(int k=factorial.size()-1;k>=0;k--)	//output the result (factorial number) digit by digit
				cout<<factorial[k];
				
			cout<<endl;
		}
	}
	return 0;
}
