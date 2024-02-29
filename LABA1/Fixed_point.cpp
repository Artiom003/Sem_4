#include "Fixed_point.h"

namespace Binary {
	Fixed_point::Fixed_point(float num) {
		sign = (num < 0) ? 1 : 0;
		int value = num;
	}
	void Fixed_point::print() {
		cout << "Fixed_point: ";
		cout << "|"<< quotient[0] << "| ";
		for (int i = 1; i < quotient.size(); i++) {
			cout << quotient[i]  << " ";
		}
		cout << ".";
		for (int i = 0; i < remainder.size(); i++) {
			cout << remainder[i]<< " ";
		}
		cout << endl;
	}
	Fixed_point& Fixed_point::operator =(const Fixed_point& a) {
		sign = a.sign;
		quotient = a.quotient;
		remainder = a.remainder;
		return *this;
	}
}