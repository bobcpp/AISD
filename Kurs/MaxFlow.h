#pragma once
#include <fstream>
#include "List.h"
#include<string>
#include"Map.h"
using namespace std;

template<typename T>
T min(T a, T b)
{
	return a > b ? b : a;
}

class Flow 
{
public:
	//the push-relabel algorithm for the maximal network flow//
	int MaxFlow()
	{
		if (Amount > 2)
		{
			for (int i = 0; i < Amount; i++)
			{
				if (i == s)
					continue;
				e[i] = c[s][i];	c[i][s] += c[s][i];
			}
			h[s] = Amount;

			List<int> l;
			int current_;
			int current = 0;
			int old;

			for (int i = 0; i < Amount; i++)
				if (i != s && i != t)
					l.push_front(i);
			current_ = l.at(0);

			while (current != l.get_size())
			{
				old = h[current_];
				discharge(current_);
				if (h[current_] != old)
				{
					l.push_front(current_); l.remove(++current);
					current_ = l.at(0); current = 0;
				}
				current++;
				if (current < l.get_size())
					current_ = l.at(current);
			}

			return e[t];
		}

		else
			return c[0][1];
	}

	//push//
	void push(int u, int v)
	{
		int f = min(e[u], c[u][v]);
		e[u] -= f;       e[v] += f;
		c[u][v] -= f;    c[v][u] += f;
	}

	//lift//
	void lift(int u)
	{
		int min = 2 * Amount + 1;

		for (int i = 0; i < Amount; i++)
			if (c[u][i] && (h[i] < min))
				min = h[i];
		h[u] = min + 1;
	}

	//discharge//
	void discharge(int u)
	{
		int V = 0;
		while (e[u] > 0)
		{
			if (c[u][V] && h[u] == h[V] + 1)
			{
				push(u, V); V = 0; continue;
			}
			V++;
			if (V == Amount)
			{
				lift(u); V = 0;
			}
		}
	}

	~Flow() 
	{
		delete[] e;
		delete[] h;
		for (int i = 0; i < Amount; ++i)
			delete[] c[i];
	}
	
	Flow(ifstream& file)
	{
		Map<char, int>* CharToNum = new Map<char, int>();
		Amount = 0;
		int StringN = 1;

		while (!file.eof()) 
		{
			string String;
			getline(file, String);
			if (String.size() >= 5) //cause five is min length of string to correct input
			{
				if (!((String[0] >= 'A' && String[0] <= 'Z') && (String[1] == ' '))) 
				{
					throw std::exception(string(("There is no space after first symbol. Input is incorrect!   Line: " + to_string(StringN))).c_str());
				}
				if (!((String[2] >= 'A' && String[2] <= 'Z') && (String[3] == ' '))) 
				{
					throw std::exception(string(("There is no space after second symbol. Input is incorrect!   Line: " + to_string(StringN))).c_str());
				}
				string cur;

				for (int i = 4; i < String.size(); ++i) 
				{
					if (String[i] >= '0' && String[i] <= '9') cur += String[i];
					else 
					{
						throw std::exception(string(("There is some trouble with third symbol. Input is incorrect!   Line: " + to_string(StringN))).c_str());
					}
				}
				if (!CharToNum->find_is(String[0]))
				{
					CharToNum->insert(String[0], Amount);
					++Amount;
				}
				if (!CharToNum->find_is(String[2])) 
				{
					CharToNum->insert(String[2], Amount);
					++Amount;
				}

			}
			else throw std::exception(string(("Data input is incorrect! Line: " + to_string(StringN))).c_str());
			StringN++;
		}
//stok//
		if (CharToNum->find_is('S')) s = CharToNum->find('S');
		else throw std::exception("There is no Istok!");
//istok//
		if (CharToNum->find_is('T')) t = CharToNum->find('T');
		else throw std::exception("There is no Stok!");

		file.clear();
		file.seekg(ios::beg);
		e = new int[Amount];
		h = new int[Amount];
		c = new int*[Amount];
		for (int i = 0; i < Amount; ++i) {e[i] = 0;	h[i] = 0;}
		for (int i = 0; i < Amount; ++i) 
		{
			c[i] = new int[Amount];
			for (int j = 0; j < Amount; ++j)
				c[i][j] = 0;
		}
		StringN = 1;
//itself//
		while (!file.eof()) 
		{
			string s1;
			int V1, V2;
			getline(file, s1);
			V1 = CharToNum->find(s1[0]);
			V2 = CharToNum->find(s1[2]);
			if (V1 == V2) throw std::exception(string("Vertex path to itself is impossible! Line: " + to_string(StringN)).c_str());
			c[V1][V2] = stoi(s1.substr(4));
			StringN++;
		}
	}

private:
	int* e;
	int** c;
	int* h;
	int Amount, s, t;
};