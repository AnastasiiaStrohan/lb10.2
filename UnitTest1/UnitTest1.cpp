#include "pch.h"
#include "CppUnitTest.h"
#include "../lb10.2/lb10.2.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student students[3] = {
				{"Smith", 2, COMPUTER_SCIENCE, 4.5, 4.8, 4.9},
				{"Johnson", 3, MATHEMATICS, 3.0, 3.5, 4.0},
				{"Williams", 1, PHYSICS, 4.8, 4.9, 5.0}
			};

			// Виклик функції для сортування
			sortStudents(students, 3);

			// Перевірка порядку сортування
			Assert::AreEqual(string("Williams"), students[0].lastName);
			Assert::AreEqual(string("Smith"), students[1].lastName);
			Assert::AreEqual(string("Johnson"), students[2].lastName);
		}

		TEST_METHOD(TestBuildIndexArray)
		{
			// Ініціалізація тестових даних
			Student students[3] = {
				{"Smith", 2, COMPUTER_SCIENCE, 4.5, 4.8, 4.9},
				{"Johnson", 3, MATHEMATICS, 3.0, 3.5, 4.0},
				{"Williams", 1, PHYSICS, 4.8, 4.9, 5.0}
			};

			int indexArray[3];
			buildIndexArray(students, indexArray, 3);

			// Перевірка порядку індексів
			Assert::AreEqual(2, indexArray[0]); // Williams (найвищий середній бал)
			Assert::AreEqual(0, indexArray[1]); // Smith
			Assert::AreEqual(1, indexArray[2]); // Johnson
		}

		
	};
}
