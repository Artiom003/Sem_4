#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace Binary {
	class Floating_point {
	private:
		float value;
		bool sign;
		int decimal_exp;
		vector<bool> mantissa;
		vector<bool> exponent;
	public:
		Floating_point(float);
		void print_num();

		Floating_point& operator =(const Floating_point& a);
		Floating_point operator +(const Floating_point& a);
	};
}