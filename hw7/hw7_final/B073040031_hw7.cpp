#include <time.h>
#include <algorithm>            //STL sort()
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//	Author		葉星佑 B073040031
//	Date		2019/11/30
//	Purpose		How much time will many kinds of sort cost \ main fuction can input the length of data and which sort to be used \ "input.txt" file need to have 10's groups of data
//
//  CLOCKS_PER_SEC differ on different computer or environment, so it may cause some problem
//

void insertion_sort(int *, int);            //insertion sort
void heap_sort(vector<int> &);              //heap sort
void maxheap(vector<int> &);
void maxheapify(vector<int> &, int, int);
void radix_sort(int *, int);                //radix sort
int compare(const void *, const void *);    //for qsort()
void output(int, int **, string);           //output the sorted data to file outputX.txt
bool check(int **, int);                    //check if the sort work well

int main() {
    ifstream f;
    f.open("input.txt", ios::in);

    int data_length;                        //before start, I need to know how big is the scale of data would you like to sort
    cout << "Input the length of data being sorted: ";
    cin >> data_length;

    int function;                           //choose the sorting 
    cout << "Input which kind of sort would you use to sort the data " << endl;
    cout << "1 for Insertion sort" << endl
         << "2 for Heap sort" << endl
         << "3 for Radix sort" << endl
         << "4 for C qsort()" << endl
         << "5 for C++ sort()" << endl
         << "0 (zero) for exit" << endl
         << ": ";

    cin >> function;                        
    if (function == 0){						//exit directly
        cout << "Bye" << endl;
        return 0;
    }

    //int array[10][data_length];
    int **array = new int *[10];            //using new
    for (int i = 0; i < 10; i++)
        array[i] = new int[data_length]();

    for (int i = 0; i < 10; i++)            //input data, 10 * DATA_LENGTH
        for (int j = 0; j < data_length; j++)
            f >> array[i][j];

    clock_t sum = 0, clk;                   //'clk' for recording once, 'sum' is 10 times ,and 'cost' is ten times average  
    switch (function) {
        case 1:
            for (int i = 0; i < 10; i++) {
                clk = clock();
                insertion_sort(array[i], data_length);
                clk = clock() - clk;
                sum += clk;
            }
            output(data_length, array, "Insertion Sort");
            break;
        case 2: {  //cross initialization without big parantheses when declaring tmp (vector<int>)
            for (int i = 0; i < 10; i++) {
                vector<int> tmp(array[i], array[i] + data_length);      //suit the data type for heap sort
                clk = clock();
                heap_sort(tmp);
                clk = clock() - clk;
                sum += clk;
                for (int j = 0; j < data_length; j++)                   //change back to array type
                    array[i][j] = tmp.at(j);
            }
            output(data_length, array, "Heap Sort");
        } break;
        case 3:                                                         //I have to find the max value of database, in my case I make it 32767
            for (int i = 0; i < 10; i++) {                              //If need to change, JUST MODIFY THE CODE LINE 173
                clk = clock();
                radix_sort(array[i], data_length);                      //the max value of a data is a DISASTROUS effect for this sorting
                clk = clock() - clk;
                sum += clk;
            }
            output(data_length, array, "Radix Sort");
            break;
        case 4:
            for (int i = 0; i < 10; i++) {
                clk = clock();
                qsort(array[i], data_length, sizeof(int), compare);
                clk = clock() - clk;
                sum += clk;
            }
            output(data_length, array, "C qsort()");
            break;
        case 5:
            for (int i = 0; i < 10; i++) {
                clk = clock();
                sort(array[i], array[i] + data_length);
                clk = clock() - clk;
                sum += clk;
            }
            output(data_length, array, "C++ sort()");
            break;
        default:
            cout << "Wrong input" << endl;
            return 0;
    }

    double cost = (double(sum)) / CLOCKS_PER_SEC / 10;
    cout << "Average cost " << cost << endl;
    cout << endl << "Check the sort completed: " << check(array, data_length) << endl;      //make sure the sort completed
    return 0;
}

void insertion_sort(int *data, int size) {
    for (int i = 1; i < size; i++) {
        int key = data[i];
        int j = i - 1;
        while (key < data[j] && j >= 0) {
            swap(data[j + 1], data[j]);
            j--;
        }
    }
}

void maxheapify(vector<int> &data, int root, int length) {
    int left = 2 * root;
    int right = 2 * root + 1;
    int largest;

    if (left <= length && data[left] > data[root])
        largest = left;
    else
        largest = root;

    if (right <= length && data[right] > data[largest])
        largest = right;

    if (largest != root) {
        swap(data[largest], data[root]);
        maxheapify(data, largest, length);
    }
}

void maxheap(vector<int> &data) {
    for (int i = data.size() / 2; i >= 1; i--)
        maxheapify(data, i, data.size() - 1);
}

void heap_sort(vector<int> &data) {
    data.insert(data.begin(), 0);

    maxheap(data);

    int size = data.size() - 1;
    for (int i = size; i >= 2; i--) {
        swap(data[1], data[i]);
        size--;
        maxheapify(data, 1, size);
    }
    //repeat maxheapify() and ignore the last leaf(max of remaining) 
    data.erase(data.begin());
}

void radix_sort(int *data, int size) {
    int order[10] = {0}, n = 1;

    while (n <= 10000) {                    //THE JUDGMENT NEED TO MATCH THE MAX VALUE OF THE DATABASE
        vector<vector<int>> bucket(10);

        for (int i = 0; i < size; i++) {
            int digit = ((data[i] / n) % 10);
            bucket.at(digit).push_back(data[i]);
            order[digit]++;
        }
        int k = 0;
        for (int i = 0; i < 10; i++) {
            if (order[i] != 0)
                for (int j = 0; j < order[i]; j++, k++)
                    data[k] = bucket.at(i).at(j);
            order[i] = 0;
        }
        n *= 10;
    }
}

int compare(const void *a, const void *b) {
    int c = *(int *)a;
    int d = *(int *)b;
    if (c < d)
        return -1;
    else if (c == d)
        return 0;
    else
        return 1;
}

void output(int size, int **arranged, string kind) {
    ofstream of;
    if (kind == "Insertion Sort")
        of.open("outputA.txt", ios::trunc | ios::out);      //if the target file exist, delete it and then output
    else if (kind == "Heap Sort")
        of.open("outputB.txt", ios::trunc | ios::out);
    else if (kind == "Radix Sort")
        of.open("outputC.txt", ios::trunc | ios::out);
    else if (kind == "C qsort()")
        of.open("outputD.txt", ios::trunc | ios::out);
    else if (kind == "C++ sort()")
        of.open("outputE.txt", ios::trunc | ios::out);

    of << kind << endl;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < size; j++)
            of << arranged[i][j] << endl;
        of << endl;
    }
    of.close();
}

bool check(int **data, int size) {
    for (int i = 0; i < 10; i++)
        for (int j = 1; j < size; j++)
            if (data[i][j] < data[i][j - 1])
                return false;
    return true;
}
