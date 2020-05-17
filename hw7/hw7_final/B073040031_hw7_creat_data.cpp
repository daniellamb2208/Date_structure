#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#define DATA_LENGTH 500000  //control the amount of data
using namespace std;

//THE CODE IS FOR GENERATING DATA TO BE SORTED,YOU HAVE TO ASSIGN 'DATA_LENGTH', THEN USE IT. 
//GENERATE TEN DATABASE A TIME
//RANGE 0-32767 WILL INFLUENCE RADIX SORT

int main() {
    srand(time(NULL));                              //random seed
    ofstream of;
    of.open("input.txt", ios::trunc | ios::out);    //if file exist, delete it and write new data on
    for (int i = 0; i < 10; i++) {                  //10 data-base
        for (int j = 0; j < DATA_LENGTH; j++) {
            of << rand() % 32768 << " ";            //my data's range is between 0 and 32767, if change, need to modify the code of RADIX sort !!!
        }
        of << endl;
    }
    of.close();

/*    int x, count = 0;                             //testing whether the number of data is correct
    ifstream f;
    f.open("input.txt", ios::in);
    while (f >> x)
        count++;
    cout << count << endl;
    f.close();
*/
    return 0;
}
