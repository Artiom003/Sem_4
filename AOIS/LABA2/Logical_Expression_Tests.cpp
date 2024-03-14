#include "pch.h"
#include "CppUnitTest.h"
#include "..//LABA2/logical_expression.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicalExpressionTests
{
	TEST_CLASS(LogicalExpressionTests)
	{
	public:
		TEST_METHOD(TestExpression)
		{
			Logical_Expression exp("a|b&c~!a>h");
			exp.print_info();
		}
	};
}
