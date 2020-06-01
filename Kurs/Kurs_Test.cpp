#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../Kurs/MaxFlow.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KursTest
{
	TEST_CLASS(Exceptions)
	{
	public:
		TEST_METHOD(IncorrectFirst)
		{
			try
			{
				ifstream input("C:\\Kurs\\Input2.txt");
				Flow flow(input);
			}
			catch (exception & ex)
			{
				Assert::AreEqual(ex.what(), "There is no space after first symbol. Input is incorrect!   Line: 2");
			}
		}
		TEST_METHOD(IncorrectSecond)
		{
			try
			{
				ifstream input("C:\\Kurs\\Input3.txt");
				Flow flow(input);
			}
			catch (exception & ex)
			{
				Assert::AreEqual(ex.what(), "There is no space after second symbol. Input is incorrect!   Line: 2");
			}
		}
		TEST_METHOD(IncorrectThird)
		{
			try
			{
				ifstream input("C:\\Kurs\\Input4.txt");
				Flow flow(input);
			}
			catch (exception & ex)
			{
				Assert::AreEqual(ex.what(), "There is some trouble with third symbol. Input is incorrect!   Line: 2");
			}
		}
		TEST_METHOD(Empty)
		{
			try
			{
				ifstream input("C:\\Kurs\\Input5.txt");
				Flow flow(input);
			}
			catch (exception & ex)
			{
				Assert::AreEqual(ex.what(), "Data input is incorrect! Line: 2");
			}
		}
		TEST_METHOD(VertexTotself)
		{
			try
			{
				ifstream input("C:\\Kurs\\Input8.txt");
				Flow flow(input);
			}
			catch (exception & ex)
			{
				Assert::AreEqual(ex.what(), "Vertex path to itself is impossible! Line: 2");
			}
		}
	};
	
	TEST_CLASS(KursTest)
	{
	public:
		TEST_METHOD(TaskExample)
		{
			ifstream input("C:\\Kurs\\Input1.txt");
			Flow flow(input);
			Assert::AreEqual(flow.MaxFlow(), 5);
		}
		TEST_METHOD(TaskExampleIstokStok)
		{
			ifstream input("C:\\Kurs\\Input6.txt");
			Flow flow(input);
			Assert::AreEqual(flow.MaxFlow(), 25);
		}
		TEST_METHOD(IstokStokOnly)
		{
			ifstream input("C:\\Kurs\\Input7.txt");
			Flow flow(input);
			Assert::AreEqual(flow.MaxFlow(), 20);
		}
		TEST_METHOD(LargeExample)
		{
			ifstream input("C:\\Kurs\\Input9.txt");
			Flow flow(input);
			Assert::AreEqual(flow.MaxFlow(), 19);
		}
	};

}
