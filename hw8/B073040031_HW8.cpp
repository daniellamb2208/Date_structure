#include<iostream>
#include"123.cpp"
using namespace std;

int main(int argc, char* argv[])
{
    if(argv[1] == "-c")
        encode(argv[3],argv[5]);
    else if(argv[1] == "-u")
        decode(argv[3],argv[5]);
        
    return 0;
}
