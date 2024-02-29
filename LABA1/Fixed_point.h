#pragma once

#include <iostream>
#include <vector>

using namespace std;

namespace Binary {
	class Fixed_point {
	private:
		bool sign;
		vector<bool> quotient;
		vector<bool> remainder;
	public:
		Fixed_point() {};
		Fixed_point(float);
		void print();
		friend class Integ_num;

		Fixed_point& operator =(const Fixed_point& a);

	};
}