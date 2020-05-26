#include "pch.h"
#include "CppUnitTest.h"
#include "../Project2/map.h"
#include <stdexcept>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(InsertFind)
		{
			map<int, int> map;
			bool bef = map.find(4);
			map.insert(4, 1);
			bool aft = map.find(4);
			Assert::AreEqual(!bef, aft);
		}

		TEST_METHOD(GetKeys)
		{
			map<int, int> map;
			map.insert(4, 1);
			map.insert(5, 2);
			List<int> list = map.get_keys();
			int sum = 0;
			while (list.isCurrent())
				sum += list.next();
			Assert::IsTrue(sum == 9);
		}

		TEST_METHOD(GetValues)
		{
			map<int, int> map;
			map.insert(4, 1);
			map.insert(5, 2);
			List<int> list = map.get_values();
			int sum = 0;
			while (list.isCurrent())
				sum += list.next();
			Assert::IsTrue(sum == 3);
		}

		TEST_METHOD(Remove)
		{
			map<int, int> map;
			map.insert(5, 1);
			bool bef = map.find(5);
			map.remove(5);
			bool aft = map.find(5);
			Assert::AreEqual(bef, !aft);
		}

		TEST_METHOD(Clear)
		{
			map<int, int> map;
			map.insert(4, 1);
			map.insert(5, 2);
			map.clear();
			Assert::AreEqual(!map.find(4), !map.find(5));
		}		
	};
}