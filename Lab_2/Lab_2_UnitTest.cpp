#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include "../Lab_2/map.h"
#include "../Lab_2/main.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Lab2UnitTest
{
	TEST_CLASS(Lab2UnitTest)
	{
	public:
		TEST_METHOD(InsertFind)
		{
			map<int, int> card;
			bool before = card.find(5);
			card.insert(5, 1);
			bool after = card.find(5);
			Assert::AreEqual(!before, after);
		}
		TEST_METHOD(Remove)
		{
			map<int, int> card;
			card.insert(5, 1);
			bool before = card.find(5);
			card.remove(5);
			bool after = card.find(5);
			Assert::AreEqual(before, !after);
		}
		TEST_METHOD(Clear)
		{
			map<int, int> card;
			card.insert(5, 1);
			card.insert(6, 2);
			card.clear();
			bool findTwoElements;
			if (card.find(5) == nullptr && card.find(6) == nullptr) findTwoElements = false;
			Assert::IsFalse(findTwoElements);
		}
		TEST_METHOD(GetKeys)
		{
			map<int, int> card;
			card.insert(5, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			List<int> list = card.get_keys();
			int sum_of_keys = 0;
			while (list.isCurrent())
				sum_of_keys += list.next();
			Assert::IsTrue(sum_of_keys == 18);
		}
		TEST_METHOD(GetValues)
		{
			map<int, int> card;
			card.insert(5, 1);
			card.insert(6, 2);
			card.insert(7, 3);
			List<int> list = card.get_values();
			int sum_of_values = 0;
			while (list.isCurrent())
				sum_of_values += list.next();
			Assert::IsTrue(sum_of_values == 6);
		}
		TEST_METHOD(ListSort)
		{
			List<HuffmanNode*> list;
			HuffmanNode* sum = new HuffmanNode;
			sum->symbol = 'a';
			sum->sum = 19;
			HuffmanNode* b = new HuffmanNode;
			b->symbol = 'b';
			b->sum = 7;
			list.push_back(b);
			list.push_back(sum);
			ListSorting(list);
			Assert::AreEqual(list.get_pointer(0)->info->symbol, 'b');
			Assert::AreEqual(list.get_pointer(1)->info->symbol, 'a');
		}
		TEST_METHOD(HaffmanTree)
		{
			List<HuffmanNode*> list;
			HuffmanNode* sum = new HuffmanNode;
			sum->symbol = 'a';
			sum->sum = 19;
			HuffmanNode* b = new HuffmanNode;
			b->symbol = 'b';
			b->sum = 7;
			HuffmanNode* symbol = new HuffmanNode;
			symbol->symbol = 'c';
			symbol->sum = 24;
			list.push_back(symbol);
			list.push_back(b);
			list.push_back(sum);
			HuffmanTree(list);
			Assert::AreEqual(list.start->info->left->symbol, 'c');
			Assert::AreEqual(list.start->info->right->left->symbol, 'b');
			Assert::AreEqual(list.start->info->right->right->symbol, 'a');
		}
		TEST_METHOD(HaffmanMap)
		{
			List<HuffmanNode*> list;
			HuffmanNode* sum = new HuffmanNode;
			sum->symbol = 'a';
			sum->sum = 19;
			HuffmanNode* b = new HuffmanNode;
			b->symbol = 'b';
			b->sum = 7;
			HuffmanNode* symbol = new HuffmanNode;
			symbol->symbol = 'c';
			symbol->sum = 24;
			list.push_back(symbol);
			list.push_back(b);
			list.push_back(sum);
			HuffmanTree(list);
			HuffmanNode* root = list.start->info;
			List<bool> listCode;
			map<char, bool*> table;
			table.insert('a', nullptr);
			table.insert('b', nullptr);
			table.insert('c', nullptr);
			HuffmanMap(root, table, listCode);
			Assert::AreEqual(table.find('c')->info.second[0], false);
			Assert::AreEqual(table.find('b')->info.second[0], true);
			Assert::AreEqual(table.find('b')->info.second[1], false);
			Assert::AreEqual(table.find('a')->info.second[0], true);
			Assert::AreEqual(table.find('a')->info.second[1], true);
		}
	};
}
