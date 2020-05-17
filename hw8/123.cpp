#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <typeinfo>
#include <math.h>
#include<cstdio>
using namespace std;

class Node
{
public:
	int frequency;
	string merge;
	Node *left, *right;

	Node(int f, int d)
	{
		frequency = f;
		merge = d;
		left = right = NULL;
	}
	Node(const Node &c)
	{
		frequency = c.frequency;
		merge = c.merge;
		left = right = NULL;
	}
	Node(Node *l, Node *r)
	{
		frequency = l->frequency + r->frequency;
		left = (l->merge[0] <= r->merge[0]) ? l : r;
		right = (l->merge[0] > r->merge[0]) ? l : r;
		if (l->merge[0] < r->merge[0])
			merge = l->merge + r->merge;
		else
			merge = r->merge + l->merge;
	}
	Node() {}
};

class compare
{
public:
	bool operator()(Node *c1, Node *c2) const
	{
		if (c1->frequency == c2->frequency)
			return c1->merge > c2->merge;
		else
			return c1->frequency > c2->frequency;
	}
};

void inorderTreeTraversal(Node *current, map<string, string> &table, string code)
{
	if (current)
	{
		inorderTreeTraversal(current->left, table, code + '0');

		if (current->left == NULL && current->right == NULL)
			table[current->merge] = code;
		inorderTreeTraversal(current->right, table, code + '1');
	}
}

Node *huffman(int *f);

Node *readfile(string inputfilename)
{
	fstream f;
	f.open(inputfilename, ios::in);

	int asc[256];
	memset(asc, 0, sizeof(int) * 256);

	while (true)
	{
		unsigned char abit;
		f >> abit;
		if (f.eof())
			break;
		asc[abit]++;
	}
	f.close();
	return huffman(asc);
}

Node *huffman(int *f)
{
	priority_queue<Node *, vector<Node *>, compare> pq;

	for (int i = 0; i < 256; i++)
	{
		if (f[i])
		{
			Node *tmp = new Node(f[i], static_cast<char>(i));
			pq.push(tmp);
		}
	}

	while (pq.size() != 1)
	{
		Node *one = pq.top();
		pq.pop();
		Node *two = pq.top();
		pq.pop();
		Node *tmp = new Node(one, two);
		pq.push(tmp);
	}
	Node *root = pq.top();

	return root;
}

void encode(string inputfilename, string outputfilename)
{
	Node *root = readfile(inputfilename);
	map<string, string> table;
	string code = "";
	inorderTreeTraversal(root, table, code);

	/*	for(auto i:table)
		cout << i.first << " " << i.second <<endl;*/

	fstream f, fout;
	f.open(inputfilename, ios::in | ios::binary);
	fout.open(outputfilename,ios::in | ios::app);
	char input;
	string tmp = "";
	int c_in = 0, c_out = 0;

/*	for (auto i : table)
		fout<<i.first<<" "<<i.second<<endl;*/
	vector<char> hello;
	while (f >> input)
	{
		c_in++;
		tmp.append(table[string(1, input)]);
		while (tmp.size() > 8)
		{
			int x = 0;
			for (int i = 0; i < 8; i++)
				x += (tmp[7 - i] - '0') * pow(2, i);
			hello.push_back(static_cast<char>(x));
			c_out++;
			string tt;
			for (int i = 0; i < tmp.size() - 8; i++)
				tt[i] = tmp[i + 8];
			tmp = tt;
		}
	}

	if (tmp.size() > 0)
	{
		int zero = 8 - tmp.size();
		for(int i=0;i<zero;i++)
			fout<<'0';
		fout<<endl;
/*		fout.close();
		fstream ft;
		ft.open("tmp.txt",ios::out);
		fout.open(outputfilename,ios::in);
		char tc, rd;
		string ts;
		for(auto i: table)
			fout>>tc>>ts;
		while(fout>>rd)
			ft<<rd;
		ft.close();
		fout.close();

		fout.open(outputfilename,ios::out);
		ft.open("tmp.txt",ios::in);		
		for(int i=0;i<zero;i++)
			fout<<0;
		fout<<endl;
		for(auto i:table)
			fout<<i.first<<" "<<i.second<<endl;
		while(ft>>rd)
			fout<<rd;
		ft.close();*/
		c_out++;
		int x;

		for (int i = 0; i < tmp.size(); i++)
			x += (tmp[tmp.size() - 1 - i] - '0') * pow(2, i);
		hello.push_back(static_cast<char> (x));	
	}

	
	for (auto i : table)
		fout<<i.first<<" "<<i.second<<endl;
	for(int i=0;i<hello.size();i++)
		fout<<hello.at(i);

	f.close();
	fout.close();

	float rate = float(c_out) / float(c_in);
	cout << "rate =  " << rate << endl;
}

/*void check()
{
	fstream f;
	f.open("output.txt",ios::in);
	char s;
	int count = 0;
	while(f>>s)
		count++;
	cout<<count<<endl;
	f.close();
}*/
//---------------------------------------------------------------------------------

void decode(string input, string output)
{
	map<char, string> table;
	fstream f, fout;
	f.open(input, ios::in | ios::binary);
	fout.open(output, ios::out | ios::app);

	char key;
	string value;

	while (f >> key)
	{
		for (auto i : table)
			if (i.first == key)
				break;
		f >> value;
		table[key] = value;
	}

/*	for (auto i : table)
		cout << i.first << " " << i.second << endl;*/

	string tmp = "";
	do
	{
		int decimal = static_cast<int>(key);
		int r;

		for (int i = 0; i < 8; i++)
		{
			r = decimal % 2;
			tmp += static_cast<char>(int(r - '0'));
			decimal /= 2;
		}
//		cout << tmp;
		for (auto i : table)
		{
			for (int j = 0; j < i.second.size(); j++)
			{
				if (tmp[j] != i.second[j])
					break;
				else if (tmp[j] == i.second[i.second.size() - 1])
				{
					string y;
					fout << i.first;
					for (int k = 0; k < tmp.size() - j - 1; k++)
						y[k] = tmp[k + j + 1];
					tmp = y;
				}
			}
		}
	} while (f >> key);

	f.close();
	fout.close();
}

int main()
{
	string input, output;
	cout<<"Enter the input_file_name and output_file_name for compress:";
	cin>>input>>output;
	encode(input, output);
/*	cout<<"Enter the input_file_name and output_file_name for decompress";
	cin>>input>>output;
	decode("intput", "output");*/
	//	check();
	return 0;
}