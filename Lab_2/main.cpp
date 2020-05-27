#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include "map.h"
using namespace std;

class HuffmanNode
{
	public:
		int sum;
		char symbol;
		HuffmanNode* left, * right;
		HuffmanNode()
		{
			left = right = nullptr;
		}
		HuffmanNode(HuffmanNode* L, HuffmanNode* R)
		{
			left = L;
			right = R;
			sum = L->sum + R->sum;
		}
};

void ListSorting(List<HuffmanNode*> &list)
{
	List<HuffmanNode*>::Node *left = list.start;
	List<HuffmanNode*>::Node *right = list.start->next;		//element that will be next after head element
	List<HuffmanNode*>::Node *tempo = new List<HuffmanNode*>::Node; 	//node for saving of temporary info
	while (left->next)	//bypass except far right
	{                 
		while (right)	//bypass of all, relative to the left for this moment
		{             
			if ((left->info->sum) >= (right->info->sum))	//is reinstall required?
			{        
				swap(left->info, right->info);
			}
			right = right->next;	//to avoid looping
		}
		left = left->next;
		right = left->next;
	}
}

void HuffmanTree(List<HuffmanNode*>& tree)
{
	while (tree.get_size() != 1)
	{
		ListSorting(tree);

		HuffmanNode* SonLeft = tree.start->info;
		tree.pop_front();

		HuffmanNode* SonRight = tree.start->info;
		tree.pop_front();

		HuffmanNode* parent = new HuffmanNode(SonLeft, SonRight);
		tree.push_back(parent);
	}
}

void HuffmanMap(HuffmanNode* root, map<char, bool*>& table, List<bool>& listCode)
{
	if (root->left != nullptr)
	{
		listCode.push_back(false);
		HuffmanMap(root->left, table, listCode);
	}

	if (root->right != nullptr)
	{
		listCode.push_back(true);
		HuffmanMap(root->right, table, listCode);
	}

	if (root->left == nullptr && root->right == nullptr)
	{
		table.find(root->symbol)->info.second = new bool[listCode.get_size()];
		for (int i = 0; i < listCode.get_size(); i++)
		{
			table.find(root->symbol)->info.second[i] = listCode.get_pointer(i)->info;
		}
	}

	if (listCode.get_size() == 0)
		return;

	listCode.pop_back();
}



void PrintTable(map<char, bool*>::Tree::Node *root)
{
	int arrSize;
	if (root->info.first != 0)
	{
		PrintTable(root->right);

		if (root->info.first == ' ')
			cout << "Char: Space" << "   Code: ";
		else
			cout <<"Char: "<< root->info.first << "       Code: ";

		arrSize = _msize(root->info.second) / sizeof(root->info.second[0]);

		for (int i = 0; i < arrSize; i++)
		{
			cout << root->info.second[i];
		}

		cout << endl;
		PrintTable(root->left);
	}
}

void Huffman(string str)
{
	map<char, size_t> card;
	map<char, bool*> table;
	int Memory = 0;

	system("cls");
	cout << "Source string:\n" << str << endl;
	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] != 0)
		{
			card.insert(str[i], i);
			table.insert(str[i], nullptr);
			++Memory;
		}
	}

	List<char> list = card.get_keys();
	List<HuffmanNode*> tree;

	while (list.get_size() != 0)
	{
		HuffmanNode* element = new HuffmanNode();
		element->sum = list.start->sum;
		element->symbol = list.start->info;
		tree.push_back(element);
		list.pop_front();
	}
	cout << "Memory:  " << Memory * 8 << " bit\n" << endl;

	float Compression = Memory * 8;
	Memory = 0;
	int arrSize;
	char ch = 'a';
	int i = 0;
	ch = str[i];

	HuffmanTree(tree);
	HuffmanNode* root = tree.start->info;
	List<bool> listCode;

	HuffmanMap(root, table, listCode);
	cout << "Coding result: " << endl;

	while (ch != 0)
	{
		i++;
		arrSize = _msize(table.find(ch)->info.second) / sizeof(table.find(ch)->info.second[0]);
		Memory = Memory + arrSize;
		for (int i = 0; i < arrSize; i++)
			cout << table.find(ch)->info.second[i];
		cout << " ";
		ch = str[i];
	}
	cout << endl;
	cout << "Memory:  " << Memory << " bit" << endl;

	Compression = Compression / Memory;
	cout << "\nCompression Factor = " << floor(Compression * 100) / 100 << endl;
	cout << "\nTable:" << endl;
	PrintTable(table.tree->root);
}

int main()
{
	string string;
	getline(cin, string);
	Huffman(string);
}