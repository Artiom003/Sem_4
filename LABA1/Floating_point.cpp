#include "Floating_point.h"

namespace Binary {
	void Floating_point::print_num() {
		//cout << "Decimal_exp: " << decimal_exp << endl;
		//cout << "Floating point: ";
		cout << sign << " | ";
		for (int i = 0; i < 8; i++) {
			cout << exponent[i] <<" ";
		}
		cout << "| ";
		for (int i = 0; i < 23; i++) {
			cout << mantissa[i] <<" ";
		}
		cout << " - num: " << value;
		cout << endl;
	}
	Floating_point::Floating_point(float num) {
		value = num;
		if (num == 0) {
			sign = 0;
			for (int i = 0; i < 8; i++) {
				exponent.push_back(0);
			}
			for (int i = 0; i < 23; i++) {
				mantissa.push_back(0);
			}
			decimal_exp = 0;
			return;
		}
		if (num < 0) {
			num = -num;
		}
		int bit_remainder = 1000;
		int quotient_num = num;
		float remainder_num = num - quotient_num;

		vector<bool> quotient;
		vector<bool> remainder;

		if (num < 1) {
			quotient.push_back(0);
		}
		int buff = quotient_num;                                  //num
		while (abs(buff) > 0) {
			int value = abs(buff) % 2;
			quotient.push_back(value);
			buff /= 2;
		}
		reverse(quotient.begin(), quotient.end()); //direct code

		for (int i = 0; i < bit_remainder; ++i) { // Примерно 24 бита для хранения дробной части
			remainder_num *= 2;
			if (remainder_num >= 1) {
				remainder.push_back(1);
				remainder_num -= 1;
			}
			else {
				remainder.push_back(0);
			}
		}

		///////////////////////////////////////////////////////////////////convert fixed point to floating point
		int n;
		if (abs(value) < 1 && abs(value) > 0 ) {
			if (value < 0) {
				sign = 1;
			}
			else {
				sign = 0;
			}
			n = -1;
			for (int i = 0; i < remainder.size() && remainder[i] != 1; i++) {
				if (i == remainder.size() - 1) {
					n = 0;
					break;
				}
				n--;
			}
		}
		else if (value < 0) {
			n = quotient.size() - 1;
			sign = 1;
		}
		else {
			n = quotient.size() - 1;
			sign = 0;
		}

		int size_bit;
		if (n >= 0) {

			for (int i = 1; i < quotient.size() && mantissa.size() < 23; i++) { //первый бит не записываем
				mantissa.push_back(quotient[i]);
			}
			for (int i = 0; i < remainder.size() - 1 && mantissa.size() < 23; i++) {
				mantissa.push_back(remainder[i]);
			}
			size_bit = mantissa.size();
			for (int i = 0; i < 23 - size_bit; i++) {
				mantissa.push_back(0);
			}
		}
		else {
			for (int i = -n; i < bit_remainder; i++) {
				mantissa.push_back(remainder[i]);
			}
			size_bit = mantissa.size();
			for (int i = 0; i < 23 - size_bit; i++) {
				mantissa.push_back(0);
			}
		}
		decimal_exp = 127 + n;
		buff = decimal_exp;
		while (abs(buff) > 0) {
			int value = abs(buff) % 2;
			exponent.push_back(value);
			buff /= 2;
		}
		int size = exponent.size();
		for (int i = 0; i < 8 - size; i++) {
			exponent.push_back(0);
		}
		reverse(exponent.begin(), exponent.end());     //exponent

	}
	Floating_point& Floating_point::operator =(const Floating_point& a) {
		value = a.value;
		sign = a.sign;
		decimal_exp = a.decimal_exp;
		mantissa = a.mantissa;
		exponent = a.exponent;
		return *this;
	}
	Floating_point Floating_point::operator +(const Floating_point& a) {

		Floating_point sum(0);
		if (sum.mantissa == mantissa && sum.exponent == exponent) {
			return a;
		}
		if (sum.mantissa == a.mantissa && sum.exponent == a.exponent){
			return *this;		

		}
		sum = a;
		vector<bool> mantissa_less_num = a.mantissa;
		if (decimal_exp > a.decimal_exp) {
			sum = *this;
			mantissa_less_num = a.mantissa;
		}
		else if (decimal_exp == a.decimal_exp) {
			for (int i = 0; i < 23; i++) {
				if (mantissa[i] == a.mantissa[i]) {
				}
				else if (exponent[i] > a.exponent[i]) {
					sum = *this;
					mantissa_less_num = a.mantissa;
					break;
				}
				else {
					sum = a;
					mantissa_less_num = mantissa;
					break;
				}
			}
		}
		else {
			sum = a;
			mantissa_less_num = mantissa;
		}                                             //определили sum = большему числу

		int n = abs(decimal_exp - a.decimal_exp);

		auto iter = sum.mantissa.cbegin();   // константный итератор указывает на первый элемент
		sum.mantissa.insert(iter, 1);
		iter = sum.mantissa.cbegin();
		sum.mantissa.insert(iter, 0);
		iter = mantissa_less_num.cbegin();   // константный итератор указывает на первый элемент
		mantissa_less_num.insert(iter, 1);

		iter = mantissa_less_num.cbegin();

		mantissa_less_num.insert(iter, n+1, 0);

		int carry = 0;
		vector<bool> buff = sum.mantissa;


		for (int i = buff.size() - 1; i >= 0; i--) {
			int bit1 = buff[i];
			int bit2 = mantissa_less_num[i];

			int sumBit = bit1 + bit2 + carry;
			if (sumBit % 2 == 0) {
				sum.mantissa[i] = 0;
			}
			else {
				sum.mantissa[i] = 1;
			}
			carry = sumBit / 2;
		}

		sum.value = value + a.value;
		if (sum.mantissa[0] == 1) {
			sum.decimal_exp++;
			for (int i = sum.exponent.size() - 1; i >= 0; i--) {
				if (sum.exponent[i] == 0) {
					sum.exponent[i] = 1;
					break;
				}
				else {
					sum.exponent[i] = 0;
				}
			}
			iter = sum.mantissa.cbegin(); // указатель на первый элемент
			sum.mantissa.erase(iter);
		}
		else {
			iter = sum.mantissa.cbegin(); // указатель на первый элемент
			sum.mantissa.erase(iter);
			iter = sum.mantissa.cbegin();
			sum.mantissa.erase(iter);
		}

		return sum;
	}
}