#include "Integ_num.h"

namespace Binary {
	void Integ_num::print_num() {
		cout << "\nNum: " << num << endl;
		cout << "Direct code: ";
		for (int i = 0; i < direct_code.size(); i++) {
			cout << direct_code[i] << " ";
		}
		cout << "\nReturn code: ";
		for (int i = 0; i < return_code.size(); i++) {
			cout << return_code[i] << " ";
		}
		cout << "\nAdded  code: ";
		for (int i = 0; i < additional_code.size(); i++) {
			cout << additional_code[i] << " ";
		}
		cout << endl;
	}

	Integ_num::Integ_num(int num) {
		int buff = num;                                  //num
		this->num = buff;
		while (abs(buff) > 0) {
			int value = abs(buff) % 2;
			direct_code.push_back(value);
			buff /= 2;
		}
		int size = direct_code.size();
		for (int i = 0; i < bytes - size - 1; i++) {
			direct_code.push_back(0);
		}
		if (num >= 0) {
			direct_code.push_back(0);
		}
		else {
			direct_code.push_back(1);
		}
		reverse(direct_code.begin(), direct_code.end()); //direct code
		if (num >= 0) {
			return_code = direct_code;
			additional_code = direct_code;
		}
		else {
			return_code = direct_code;
			for (int i = 1; i < direct_code.size(); i++) {
				return_code[i] = return_code[i] - 1;     //return code
			}
			additional_code = return_code;
			for (int i = additional_code.size() - 1; i != 0; i--) {
				if (additional_code[i] == 0) {
					additional_code[i] = 1;
					break;
				}
				else {
					additional_code[i] = 0;
				}
			}											 //additional code
		}

	}
	Integ_num& Integ_num::operator =(const Integ_num& a) {
		this->direct_code = a.direct_code;
		this->return_code = a.return_code;
		this->additional_code = a.additional_code;
		num = a.num;
		return *this;
	}

	Integ_num Integ_num::operator +(const Integ_num& a) {

		Integ_num sum(0);

		int carry;
		if (!(num >= 0 && a.num >= 0)) carry = 1;
		else { carry = 0; }

		for (int i = additional_code.size() - 1; i >= 0; i--) {
			int bit1 = additional_code[i];
			int bit2 = a.additional_code[i];

			int sumBit = bit1 + bit2 + carry;
			if (sumBit % 2 == 0) {
				sum.additional_code[i] = 0;
			}
			else {
				sum.additional_code[i] = 1;
			}
			carry = sumBit / 2;
		}
		if (num + a.num == -1) {
			sum.additional_code[0] = 1;
		}
		if (!(num >= 0 && a.num >= 0)) {               // if not two positive nums
			for (int i = sum.additional_code.size() - 1; i > 0; i--) {
				if (sum.additional_code[i] == 1) {
					sum.additional_code[i] = 0;
					break;
				}
				else {
					sum.additional_code[i] = 1;
				}
			}
			for (int i = 1; i < sum.direct_code.size(); i++) {
				sum.direct_code[i] = sum.direct_code[i] - 1;
			}
		}

		if (sum.additional_code[0] == 0) {             // when we get additional code of sum
			sum.direct_code = sum.additional_code;
			sum.return_code = sum.additional_code;
		}
		else {
			sum.return_code = sum.additional_code;
			for (int i = sum.return_code.size() - 1; i > 0; i--) {
				if (sum.return_code[i] == 1) {
					sum.return_code[i] = 0;
					break;
				}
				else {
					sum.return_code[i] = 1;
				}
			}												//return code
			sum.direct_code = sum.return_code;
			for (int i = 1; i < sum.direct_code.size(); i++) {
				sum.direct_code[i] = sum.direct_code[i] - 1;
			}												//direct code
		}

		int base = 1;
		for (int i = sum.additional_code.size() - 1; i >= 0; --i) {
			if (sum.additional_code[i]) {
				sum.num += base;
			}
			base *= 2;
		}                                                  //num
		return sum;
	}

	Integ_num Integ_num::operator *(const Integ_num& a) {  //division
		Integ_num mult(0);

		for (int i = bytes / 2 - 1; i >= 0; i--) {
			int carry = 0;  // Перенос

			for (int j = bytes / 2 - 1; j >= 0; j--) {
				int pos = i + j + 1;
				int product = mult.direct_code[pos] + direct_code[i + bytes / 2] * a.direct_code[j + bytes / 2] + carry;
				mult.direct_code[pos] = product % 2;
				carry = product / 2;
			}

			mult.direct_code[i] = carry;
		}
		if (a.num * num < 0) {
			mult.direct_code[0] = 1;
			mult.return_code = mult.direct_code;
			for (int i = 1; i < mult.direct_code.size(); i++) {
				mult.return_code[i] = mult.return_code[i] - 1;     //return code
			}
			mult.additional_code = mult.return_code;
			for (int i = mult.additional_code.size() - 1; i != 0; i--) {
				if (mult.additional_code[i] == 0) {
					mult.additional_code[i] = 1;
					break;
				}
				else {
					mult.additional_code[i] = 0;
				}
			}											 //additional code
		}
		else {
			mult.return_code = mult.direct_code;
			mult.additional_code = mult.direct_code;
		}
		int base = 1;
		for (int i = mult.additional_code.size() - 1; i >= 0; --i) {
			if (mult.additional_code[i]) {
				mult.num += base;
			}
			base *= 2;
		}
		return mult;
	}

	Fixed_point Integ_num::operator/(const Integ_num& a) {
		Fixed_point div;

		int size = 0;
		for (int i = 1; i < bytes; i++) {
			if (direct_code[i] == 1) {
				break;
			}
			size++;
		}
		vector<bool> num1;
		if (num > 0) {
			num1.push_back(0);
		}
		else if (num < 0) {
			num1.push_back(1);
		}

		for (int i = 1 + size; i < bytes; i++) {
			num1.push_back(direct_code[i]);
		}

		size = 0;
		for (int i = 1; i < bytes; i++) {
			if (a.direct_code[i] == 1) {
				break;
			}
			size++;
		}
		vector<bool> num2;
		if (a.num > 0) {
			num2.push_back(0);
		}
		else if (a.num < 0) {
			num2.push_back(1);
		}

		for (int i = 1 + size; i < bytes; i++) {
			num2.push_back(a.direct_code[i]);
		}
		if (num1.empty()) {
			num1.push_back(0);
		}
		if (num2.empty()) {
			num2.push_back(0);
		}

		if (num == 0 && a.num != 0) {
			div.quotient.push_back(0);
			div.remainder.push_back(0);
			return div;
		}
		if (a.num == 0) {
			throw runtime_error("Error");
			return div;
		}

		/////////////////////////////////////////////////////////
		string divisible_num;
		for (bool num : num1) {
			divisible_num += num ? '1' : '0';
		}
		string divider_num;
		for (bool num : num2) {
			divider_num += num ? '1' : '0';
		}

		string division_result_int, division_result_float, to_division;
		char sign_result = divisible_num[0] == divider_num[0] ? '0' : '1', element;
		division_result_int.insert(0, 1, sign_result);

		divisible_num.erase(0, 1);
		divider_num.erase(0, 1);
		to_division = divisible_num.substr(0, divider_num.size() - 1);
		for (int i = divider_num.size() - 1; i < divisible_num.size(); i++)
		{
			to_division += divisible_num[i];
			element = compare_binary_int_norm(to_division.insert(0, 1, '0'), divider_num.insert(0, 1, '0')) ? '1' :
				abs(direct_transform_to_decimal(to_division.insert(0, 1, '0'))) == abs(direct_transform_to_decimal(divider_num.insert(0, 1, '0'))) ? '1' : '0';
			division_result_int += element;
			if (element == '1')
			{
				to_division = transform_direct(direct_transform_to_decimal(to_division.insert(0, 1, '0')) - direct_transform_to_decimal(divider_num.insert(0, 1, '0')));
				to_division.erase(0, 1);
			}
		}
		if (direct_transform_to_decimal(to_division.insert(0, 1, '0')) != 0)
		{
			division_result_float = "0";
			while (direct_transform_to_decimal(to_division.insert(0, 1, '0')) != 0 && division_result_float.size() <= 5)
			{
				to_division += '0';
				element = compare_binary_int_norm(to_division.insert(0, 1, '0'), divider_num.insert(0, 1, '0')) ? '1' :
					abs(direct_transform_to_decimal(to_division.insert(0, 1, '0'))) == abs(direct_transform_to_decimal(divider_num.insert(0, 1, '0'))) ? '1' : '0';
				division_result_float += element;
				if (element == '1')
				{
					to_division = transform_direct(direct_transform_to_decimal(to_division.insert(0, 1, '0')) - direct_transform_to_decimal(divider_num.insert(0, 1, '0')));
					to_division.erase(0, 1);
				}
			}
			division_result_float.erase(0, 1);
		}
		else {
			division_result_float = "0";
		}

		for (char bit : division_result_int) {
			div.quotient.push_back(bit == '1');
		}

		for (char bit : division_result_float) {
			div.remainder.push_back(bit == '1');
		}
		return div;
	}

	bool Integ_num::compare_binary_int_norm(string first, string second) {
		return abs(direct_transform_to_decimal(first)) > abs(direct_transform_to_decimal(second));
	}

	int Integ_num::direct_transform_to_decimal(string directCode) {
		char sign = directCode[0];
		directCode.erase(0, 1);
		int result = 0;
		reverse(directCode.begin(), directCode.end());
		for (int i = 0; i <= directCode.size() - 1; i++)
			result += (directCode[i] - '0') * pow(2, i);
		result = sign == '0' ? result : (-1 * result);
		return result;
	}

	string Integ_num::transform_direct(int num) {
		string result = "0";
		int divisible = num < 0 ? (-1 * num) : num, remainder;
		while (divisible != 1 && divisible != 0)
		{
			remainder = divisible % 2;
			result += remainder + '0';
			divisible /= 2;
		}
		result += divisible + '0';
		result.erase(0, 1);
		remainder = num < 0 ? 1 : 0;
		result += remainder + '0';
		reverse(result.begin(), result.end());
		return result;
	}

}
