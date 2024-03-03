#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace Binary {
	class Fixed_point {
	private:
		vector<bool> quotient;
		vector<bool> remainder;
	public:
		void print();
		friend class Integ_num;

		Fixed_point& operator =(const Fixed_point& a);

	};
}