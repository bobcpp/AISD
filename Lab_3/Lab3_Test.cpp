#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include<string>
#include"../Lab_3/Matrix.h"
#include"../Lab_3/Input.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab3Test
{
	TEST_CLASS(Lab3Test)
	{
	public:
		TEST_METHOD(Path)
		{
			ifstream input("test.txt");
			List<string>* Flights = new List<string>();
			string From = "S";
			string To = "K";

			Input(Flights, input);
			Matrix* matrix = new Matrix(Flights);
			string str = "The lowest price: 50\nPath: S -- M -- K";
			Assert::AreEqual(matrix->Floyd_Warshall(From, To), str);
		}
		TEST_METHOD(NoPath)
		{
			ifstream input("test2.txt");
			List<string>* Flights = new List<string>();
			string From = "K";
			string To = "M";

			Input(Flights, input);
			Matrix* matrix = new Matrix(Flights);
			string str = "There is no path, sorry :(";
			Assert::AreEqual(matrix->Floyd_Warshall(From, To), str);
		}
	};
}
