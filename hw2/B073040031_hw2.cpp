#include<iostream>
#include<vector>						//for print the data in a row
using namespace std;

//	Author		¸­¬P¦ö B073040031
//	Date		2019/9/23
//	Purpose		make set-class contain multiple operations with C++

class Tset
{
	private:
		bool element[256];				//store elements by string-bit ( ASCII code)
		
	public:
		Tset();							//constructor
		Tset(const Tset&);				//copy constructor
		~Tset() {}						//destructor
		friend const Tset operator + (const Tset&, const Tset&);		//union (OR) 
		friend const Tset operator * (const Tset&, const Tset&);		//intersection (AND)
		friend const Tset operator - (const Tset&, const Tset&);		//difference
		friend const bool operator >= (const Tset&, const Tset&);		//contain
		bool in(const char);											//belong to	(in-function)
		friend ostream& operator <<(ostream&, const Tset&);				//operator overload for output
		friend istream& operator >>(istream&, Tset&);					//operator overload for input
};

int main()
{
	int num;					//numbers records of data
	cin>>num;
	
	vector<Tset> A,B;			//all data store in a vector for output them in a row
	vector<char> x;
	
	for(int i=0;i<num;i++)		
	{
		Tset a,b;
		char q;
		cin.ignore();			//for not eat the '\n' with getline
		cin>>a>>b;				//input data respectively
		cin.get(q);				//input char 
		
		A.push_back(a);
		B.push_back(b);
		x.push_back(q);		
	}
	
	for(int i=0;i<num;i++)
	{
		Tset C,D;				//request in the note
		C = A[i] + B[i];
		D = A[i] * B[i];
		
		cout<<"\n"<<"Test Case "<<i+1<<":"<<endl;
		cout<<"A: "<<A[i]<<endl;
		cout<<"B: "<<B[i]<<endl;
		cout<<"A+B: "<<A[i]+B[i]<<endl;
		cout<<"A*B: "<<A[i]*B[i]<<endl;
		cout<<"A-B: "<<A[i]-B[i]<<endl;
		cout<<"B-A: "<<B[i]-A[i]<<endl;
		cout<<"A "<<((A[i]>=B[i])? "contains ":"does not contain ")<<"B"<<endl;		//ternary operator		
		cout<<"B "<<((B[i]>=A[i])? "contains ":"does not contain ")<<"A"<<endl;
		cout<<"\'"<<x[i]<<"\'"<<" is"<<((A[i].in(x[i]))? " ":" not ")<<"in "<<"A"<<endl;
		cout<<"\'"<<x[i]<<"\'"<<" is"<<((B[i].in(x[i]))? " ":" not ")<<"in "<<"B"<<endl;
	}
	return 0;
}

Tset::Tset()					//normal constructor set all element false means they been not appearred yet
{
	for(int i=0;i<256;i++) 
		element[i] = false;
}

Tset::Tset(const Tset& e)		//copy constructor
{
	for(int i=0;i<256;i++)
		this->element[i] = e.element[i];
}
		
const Tset operator + (const Tset& a, const Tset& b)
{
	Tset done;
	for(int i=0;i<256;i++)								//a + b -> a OR b
		if(a.element[i] || b.element[i])
			done.element[i] = true;
	return done;
}
const Tset operator * (const Tset& a, const Tset& b)
{
	Tset done;
	for(int i=0;i<256;i++)								//a * b -> a AND b
		if(a.element[i] && b.element[i])
			done.element[i] = true;
	return done;
} 
const Tset operator - (const Tset& a, const Tset& b)	
{
	Tset done;
	for(int i=0;i<256;i++)								//a - b -> a AND NOT(b)
		if(a.element[i] && !(b.element[i])) 
			done.element[i] = true;
	return done;
}
const bool operator >= (const Tset& a, const Tset& b)
{
	bool contain = true;
	for(int i=0;i<256;i++)								//a contain b -> (a AND b == b)
		if(!((a.element[i] && b.element[i]) == b.element[i]))
			contain = false;
	return contain;
}
bool Tset::in(const char x)
{
	if(this->element[static_cast<int>(x)])				//test element[(ASCII code number)] figure out wheather the x is in the set
		return true;
	else
		return false;
}
ostream& operator <<(ostream& o, const Tset& output)
{
	o<<"{";
	for(int i=0;i<256;i++)
		if(output.element[i])
			o<<static_cast<char>(i);					//converse ASCII to char
	o<<"}";
	return o;
}
istream& operator >>(istream& i,Tset& fill)
{
	string input;
	getline(i,input);									//get all the line data
	for(int j=0;j<input.size();j++)
		fill.element[input[j]] = true;
	return i;
}
