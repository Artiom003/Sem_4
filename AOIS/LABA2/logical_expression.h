#pragma once
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <unordered_set>
#include "truth_table.h"
#include <bitset>

using namespace std;

class Logical_Expression {
private:
//	friend class Truth_Table;
	vector<char> unique_operands;
	string result_rpn;	
	string expression;
	Truth_Table truth_table;

	string SKNF_exp;
	string SKNF_numeric_form;

	string SDNF_exp;
	string SDNF_numeric_form;

	vector<bool> exp_index_form;
	int exp_index_form_in_decimal;


	Truth_Table create_truth_table();
	int priority(char operation);	
	vector<char> get_unique_operands();
	string to_rpn();
	bool is_operand(string token);
	bool execute_operation(bool operand1, bool operand2, char operation);
	void execute_expression();

	string SKNF();
	string numeric_SKNF();
	string SDNF();
	string numeric_SDNF();
	vector<bool> index_form();
	int index_form_in_decimal();
	

public:
	Logical_Expression(string exp);
	void print_info();

};