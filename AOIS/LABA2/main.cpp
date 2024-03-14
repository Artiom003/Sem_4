#include "logical_expression.h"

int main() {
	string str; // (a>!b)~(b>!c)|a&c
	cout << "Enter logical expression: ";
	cin >> str;
	Logical_Expression exp(str);
	exp.print_info();
	return 0;
}