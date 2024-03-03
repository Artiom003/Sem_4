#include "pch.h"
#include "CppUnitTest.h"
#include "..//LABA1/header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Binary {
	namespace BinaryTests
	{
		TEST_CLASS(Binary_Tests)
		{
		public:
			TEST_METHOD(Check_initialization)
			{
				Integ_num a(1);
				Integ_num b(-2);
				Integ_num c(0);
				Fixed_point f;
				Floating_point j(0);
				Floating_point k(-3);
				Floating_point l(-0.076);
				Floating_point n(0.07876);
				Floating_point o(67.07876);
				Floating_point p(-67.07876);
			}
			TEST_METHOD(Check_print_info)
			{
				Integ_num a(1934);
				a.print_num();
				Floating_point b(-0.098);
				b.print_num();
				Integ_num c(11);
				Fixed_point f = a / c;
				f.print();
			}
			TEST_METHOD(Check_operation_sum_with_integ_num)
			{
				Integ_num a(1);
				Integ_num d(0);
				Integ_num b(-2);
				Integ_num c = a + b;
				c = d + d;
				c = d + a;
				c = b + d;
			}
			TEST_METHOD(Check_operation_multiplication_with_integ_num)
			{
				Integ_num a(1);
				Integ_num d(0);
				Integ_num b(-2);
				Integ_num c = a * b;
				c = d * d;
				c = d * a; 
				c = b * d;
			}
			TEST_METHOD(Check_get_and_set_bits_of_integ_num)
			{
				Integ_num a(1);
				a.set_bits(8);
				Assert::AreEqual(8, a.get_bits());
			}
			TEST_METHOD(Check_operation_division_with_integ_num)
			{
				Integ_num a(1);
				Integ_num d(0);
				Integ_num b(-2);
				Integ_num k(7);
				Integ_num n(9);
				Fixed_point c = a / b;
				Fixed_point t;
				c = b / a;
				c = b / b;
				c = d / a;
				c.print();
				t = n / k;
			}
			TEST_METHOD(Check_operation_sum_with_floating_point)
			{
				Floating_point j(0);
				Floating_point k(-3);
				Floating_point l(-0.076);
				Floating_point n(0.007876);
				Floating_point o(67.07876);
				Floating_point p(-67.07876);
				Floating_point a(76425);
				j + j;
				p + o;
				l + j;
				l + k;
				n + a;
				o + p;
				j + l;
				k + l;
				a + n;
				Floating_point d(5);
				Floating_point b(3.01);
				Floating_point c(3.03);
				d + b;
				b + c;
				c + b;
				Floating_point z(0.0000000000000000000000000001);
			}
			TEST_METHOD(Check_error_division_by_zero)
			{
				Integ_num a(1);
				Integ_num d(0);
				Assert::ExpectException<exception>([&]() {
					Fixed_point c = a / d;
				});
			}
			TEST_METHOD(Check_error_in_bits_sum)
			{
				Integ_num a(1);
				a.set_bits(16);
				Integ_num d(3);
				d.set_bits(64);
				Assert::ExpectException<exception>([&]() {
					a + d;
				});
			}
			TEST_METHOD(Check_error_in_bits_multiplication)
			{
				Integ_num a(1);
				a.set_bits(16);
				Integ_num d(3);
				d.set_bits(64);
				Assert::ExpectException<exception>([&]() {
					a * d;
				});
			}
			TEST_METHOD(Check_error_in_bits_division)
			{
				Integ_num a(1);
				a.set_bits(16);
				Integ_num d(3);
				d.set_bits(64);
				Assert::ExpectException<exception>([&]() {
					a / d;
				});
			}
			TEST_METHOD(Check_error_in_bits_equal)
			{
				Integ_num a(1);
				a.set_bits(16);
				Integ_num d(3);
				d.set_bits(64);
				Assert::ExpectException<exception>([&]() {
					a = d;
					});
			}
				
		};
	}
}
