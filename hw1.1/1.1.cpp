#include<iostream>
#include<iomanip>
using namespace std;

//	Author		¸­¬P¦ö B073040031
//	Date		2019/9/21
//	Purpose		Magic Square	

void magicsquare(int n)			//make ms and show it
{								//n is given 
	cout<<"This is "<<n<<"x"<<n<<" magic square"<<endl;
 
	int** ma = alloca(m*n*sizeof(int));				//declare an 2 dimension array with given number n
	
	for(int i=0;i<n;i++)		//initialization
	{
		for(int j=0;j<n;j++)	
			ma[i][j] = 0;
	}
	
	int x = 0,y = n/2;
	ma[x][y] = 1;				//firstly fill 1 in
	for(int i=2;i<=n*n;i++)		//fill 2~n*n in the right place respectively
	{
		int a = x - 1;			//(a,b) for temporarily store new (x,y)
		int b = y - 1;			//put next number upper-left corner
		
		if(a < 0)				//check the coordinate(a,b) in the range
			a+=n;				
		if(b < 0)
			b+=n;
		
		if(ma[a][b] != 0)		//if there the target place is already occupied,
		{						//then put it under the last number
			x++;
			x%=n;				//for not being out of the range
			ma[x][y] = i;
		}
		else
		{
			ma[a][b] = i;
			x = a;
			y = b; 
		}
	}
	
	for(int i=0;i<n;i++)		//output the magic square
	{
		for(int j=0;j<n;j++)
			cout<<setw(3)<<ma[i][j]<<" ";	//align to the right (3spaces)
		cout<<endl;	
	}
	cout<<endl;
}


int main()
{	
	//call function
	magicsquare(1);		//cout<<"1";
	magicsquare(3);
	magicsquare(5);
	magicsquare(7);
	magicsquare(9);
	
	return 0;
}
