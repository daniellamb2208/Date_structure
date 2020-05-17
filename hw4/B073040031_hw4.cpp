#include<iostream>
#include<iomanip>
using namespace std;

//	Author		葉星佑 B073040031
//	Date		2019/10/20
//	Purpose		Knight path in n*n map (recursion)

int orientation[8][2] = {-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2,-2,-1};      //next-step position difference

int find_last_direction(int **map,int size, int step, int x, int y)     //find the previous direction
{
    int lx,ly;                                                          //previous step (x,y)
    for(int i =0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            if(map[i][j] == step-1)
            {
                lx = i;
                ly = j;
            }
        }
    }
    for(int i=0;i<8;i++)                                                //compared difference between current and previous with orientation
        if((orientation[i][0] == (x-lx)) && (orientation[i][1] == (y-ly)))
            return i;
}
/*void knight_path(int **map, int size, int step, int x, int y, int direction)              //stack overflow as n=6
{
    map[x][y] = step;                                                   //It's sure that next position is can-go
    if(step == size * size)                                             //if all vacancy is full  
    {      
        for(int i=0;i<size;i++)                                         //output the path map
        {
            for(int j=0;j<size;j++)
                cout<<setw(3)<<map[i][j]<<" ";                          //setw() for not crowding
            cout<<endl;
        }
        return;
    }
    if((direction < 8) && ((x+orientation[direction][0])>=0 && (x+orientation[direction][0])<size) && ((y+orientation[direction][1])>=0 && (y+orientation[direction][1])<size) && (!map[orientation[direction][0] + x][orientation[direction][1] + y]))     //check next position is empty and x,y are not out of range
        knight_path(map, size, step+1, x+orientation[direction][0], y+orientation[direction][1], 0);
    else if(direction < 8)                                              //if next one cannot go, test direction+1
        knight_path(map, size, step, x, y, direction+1);
    else
    {
        if(step == 1)                                                   //backward to 1 means there is no solution. Surely, it have been tested all 8 direction for step 1
        {
            cout<<"No solution"<<endl;
            return;
        }
        direction = find_last_direction(map,size,step,x,y);             //get the previous direction for not test the same direction repeatedly
        map[x][y] = 0;                                                  //reset the point in path map where no road to next step
        knight_path(map,size,step-1,x-orientation[direction][0],y-orientation[direction][1],(direction>=7)? 8:direction+1);         //step minus one; (x,y) back to previous position; If all direction had been tested, give the value 8 in order to force to it go back again.                                                                         
    }
}*/
void knight_path(int **map, int size, int step, int x, int y, int direction)    //recurive function
{
    map[x][y] = step;                                                           //mark the steps on the path map, after checked

    if(step == size * size)                                                     //if all vacancy is full
    {      
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<size;j++)
                cout<<setw(3)<<map[i][j];                                       //setw() for not crowding
            cout<<endl;
        }
        return;                                                                 //mission completed
    }
    bool check = false;                                                         //check the knight can move to next position, default to false
    while(direction < 8)                                                        //make sure it will test 8 direction
    {                                                                                  
        if(((x+orientation[direction][0])>=0 && (x+orientation[direction][0])<size) && ((y+orientation[direction][1])>=0 && (y+orientation[direction][1])<size) && (!map[orientation[direction][0] + x][orientation[direction][1] + y]))
        {                                                                       //x,y are not out of range and next position is empty(value 0)
            step++;                                                             //move forward next position
            x+=orientation[direction][0];                                           
            y+=orientation[direction][1];
            direction=0;                                                        //direction start from 0 (to 7) in new test
            check = true;                                                       //can go to next one
            break;
        }
        else
            direction++;                                                        //next direction
    }
    if(check)
        knight_path(map,size,step,x,y,direction);
   else
    {
        if(step == 1)                                                           //backward to 1 means there is no solution. Surely, it have been tested all 8 direction for step 1
        {
            cout<<"No solution"<<endl;
            return;                                                             //mission falled
        }
        direction = find_last_direction(map,size,step,x,y);                     //get previous direction for not repeatedly testing
        map[x][y] = 0;                                                          //reset here where no way to solution
        knight_path(map,size,step-1,x-orientation[direction][0],y-orientation[direction][1],(direction>=7)? 8:direction+1);         //step minus one; (x,y) back to previous position; If all direction had been tested, give the value 8 in order to force it to go backwards again. 
    }
}

int main()
{
    for(int i=1;i<=6;i++)                                                       //n = 1, 2, 3, 4, 5, 6
    {
        int **map = new int*[i];                                                //declare a 2-dimension array
        for(int j=0;j<i;j++)
            map[j] = new int[i];
        for(int j=0;j<i;j++)                                                    //and initialize all elements to 0
            for(int k=0;k<i;k++)
                map[j][k] = 0;

        knight_path(map,i,1,0,0,0);                                             //calculate
        cout<<endl;                                                             //seperate every situation
    }
    return 0;
}
