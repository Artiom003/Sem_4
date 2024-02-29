#pragma once

#include "Fixed_point.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace Binary {
	class Integ_num {
	private:
		int num;
		vector<bool> direct_code;
		vector<bool> return_code;
		vector<bool> additional_code;
		int bytes = 64;
	public:

		Integ_num(int);
		void print_num();

		bool compare_binary_int_norm(string first, string second);
		int direct_transform_to_decimal(string directCode);
		string transform_direct(int num);

		Integ_num& operator =(const Integ_num& a);
		Integ_num operator +(const Integ_num& a);
		Integ_num operator *(const Integ_num& a);
		Fixed_point operator /(const Integ_num& a);

	};
}