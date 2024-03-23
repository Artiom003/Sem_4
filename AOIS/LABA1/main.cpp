#include "header.h"

#include "windows.h"                                       //
HANDLE hConsole;                                           //

int main() {
	int a,b;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);            //
	SetConsoleTextAttribute(hConsole, 11);                 //
	cout << "Enter the first num: ";              
	cin >> a;
	Integ_num num1(a);

	num1.print_num();
	SetConsoleTextAttribute(hConsole, 3);                  //
	cout << "\nEnter the second num: ";
	cin >> b;
	Integ_num num2(b);
	num2.print_num();

	Integ_num num3(0);

	SetConsoleTextAttribute(hConsole, 9);                  //
	cout << "\nsum:" << endl;
	num3 = num1 + num2;
	num3.print_num();

	SetConsoleTextAttribute(hConsole, 6);                  //
	cout << "\nmultiplication:" << endl;
	num3 = num1 * num2;
	num3.print_num();

	SetConsoleTextAttribute(hConsole, 10);                  //
	cout << "\ndivision:" << endl;
	Fixed_point num = num1 / num2;
	num.print();

	SetConsoleTextAttribute(hConsole, 13);                  //
	float n;
	cout << "\nEnter the floating point number1:  ";
	cin >> n;
	Floating_point num4(n);
	float n1;
	cout << "Enter the floating point number2:  ";
	cin >> n1;
	cout << endl;
	Floating_point num5(n1);
	num4.print_num();
	num5.print_num();
	cout << "\nsum:\n";
	Floating_point num6 = num4 + num5;
	num6.print_num();


	SetConsoleTextAttribute(hConsole, 4);                  //
	cout << "\n---------------------------------------------------------------------------------------" << endl;

	return 0;
}