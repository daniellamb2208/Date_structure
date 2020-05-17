#include<iostream>
#include<vector>		//store data in the stack
#include<iomanip>		//for making output more beautiful
using namespace std;

//	Author		¸­¬P¦ö B073040031
//	Date		2019/10/12
//	Purpose		Knight path in n*n map

class stack
{										//					(a,b,c)
	private:							//					(1,1,3)
        vector<vector<int>> record;		//2-dimension like 	(0,0,8)

    public:
    	stack() {};						//constructor
    	~stack() { record.clear();};	//destructor
        void push(int,int,int);
        void pop();
        vector<int> top();				//return being-pop data for getting previous position and back*
		bool isempty();					//check the stack is empty or not
};

bool check(int** map, int x, int y,int s)	//make sure the next step is legal(no out of range and hadn't been visited)
{
	if((x>=0 && x<s) && (y>=0 && y<s) && !map[x][y])	// 0 <= x,y < map_size , !map[x][y] next_step must be 0 there
		return true;
	else
		return false;
}

int main()
{
    for(int i=1;i<=6;i++)				//n = 1,2,3,4,5,6
    {
		stack knight;	
        int** map = new int*[i];		//declare a 2-dimension array  
        for(int j=0;j<i;j++)
        	map[j] = new int[i];	
        for(int j=0;j<i;j++)			//and initialize all elements to 0
			for(int k=0;k<i;k++)
				map[j][k] = 0;	
		//mx,my is now where the knight is
		//step  is how many steps knight has took and let it leave trace on 2-d-array-map
		//back* is which direction it attempts to move, and in order to record which one had tried when go back to the previous step 
		int mx = 0, my = 0, step = 1, back = 0;
        map[mx][my] = step;				//the very first step 1
        knight.push(0,0,8);				//(0,0, ) is upper-left corner	( , ,8) will force it to go ahead

        while(true)
        {
        	if(step == i*i)				//if fill all the space in, print the map
			{
				for(int j=0;j<i;j++)
				{
					for(int k=0;k<i;k++)
						cout<<setw(3)<<map[j][k];		//setw() in header <iomanip>
					cout<<endl;
				}
				break;
			}
			else if(knight.isempty())	//there is nothing in the stack, meaning no solution (pop all)
			{
				cout<<"No solution"<<endl;
				break;
			}
			
        	if(check(map,mx-2,my+1,i) && back<1)		//the direction changing order is clockwise											
        	{											//direction 1
        		knight.push(mx,my,1);					//push now position and direction
        		map[mx-=2][my+=1] = ++step;				//here on the map get right step  
        		back = 0;								//let next moving-try start from the fisrt direction
			}
			else if(check(map,mx-1,my+2,i) && back<2)	//direction 2
        	{
        		knight.push(mx,my,2);
        		map[mx-=1][my+=2] = ++step;
        		back = 0;
			}
			else if(check(map,mx+1,my+2,i) && back<3)	//direction 3
        	{
        		knight.push(mx,my,3);
        		map[mx+=1][my+=2] = ++step;
        		back = 0;
			}
			else if(check(map,mx+2,my+1,i) && back<4)	//direction 4
        	{
        		knight.push(mx,my,4);
        		map[mx+=2][my+=1] = ++step;
      		back = 0;
			}
			else if(check(map,mx+2,my-1,i) && back<5)	//direction 5
        	{
        		knight.push(mx,my,5);
        		map[mx+=2][my-=1] = ++step;
       		back = 0;
			}
			else if(check(map,mx+1,my-2,i) && back<6)	//direction 6
        	{
        		knight.push(mx,my,6);
        		map[mx+=1][my-=2] = ++step;
        		back = 0;
			}
			else if(check(map,mx-1,my-2,i) && back<7)	//direction 7
        	{
        		knight.push(mx,my,7);
        		map[mx-=1][my-=2] = ++step;
        		back = 0;
			}
			else if(check(map,mx-2,my-1,i) && back<8)	//direction 8
        	{
        		knight.push(mx,my,8);
        		map[mx-=2][my-=1] = ++step;
        		back = 0;
			}
			else										//when it test all 8 direction and not find the can-go path
			{											//it will back to last step and try not-yet-tried direction
				vector<int> t = knight.top();			
				back =  t[2];							//get previously direction in order to try the rear-order direction
				map[mx][my]= 0;							//reset the wrong-try step to 0
				knight.pop();
				mx = t[0];								//position go back to the previous position
				my = t[1];
				step--;									//step minus 1
			}
		}
		cout<<endl;
    }
    return 0;
}

void stack :: push(int a,int b,int c)
{
	vector<int> p;
	p.push_back(a);
	p.push_back(b);
	p.push_back(c);
	
	record.push_back(p);
}
void stack :: pop()
{ 
	record.pop_back(); 
}
vector<int> stack :: top() 
{
	return record[record.size()-1];
}

bool stack :: isempty() 
{
	return record.empty(); 
}
