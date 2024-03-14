#include "logical_expression.h"



Logical_Expression::Logical_Expression(string exp) {
    this->expression = exp;
    this-> result_rpn = to_rpn();
    this->unique_operands = get_unique_operands();
    this->truth_table = create_truth_table();
    execute_expression();

    this->SDNF_exp = SDNF();
    this->SDNF_numeric_form = numeric_SDNF();

    this->SKNF_exp = SKNF();
    this->SKNF_numeric_form = numeric_SKNF();

    this->exp_index_form = index_form();
    this->exp_index_form_in_decimal = index_form_in_decimal();
}


void Logical_Expression::print_info() {
    /*cout << "Reverse Polish natation: " << result_rpn << "\nOperands: ";
    for (int i = 0; i < unique_operands.size(); i++) {
        cout << unique_operands[i];
    }*/
    cout << "Truth table:\n" << truth_table.get_table_string() << endl;

    cout << "SDNF expression: " << SDNF_exp << endl;
    cout << "SDNF numeric form: " << SDNF_numeric_form << endl;

    cout << "SKNF expression: " << SKNF_exp << endl;
    cout << "SKNF numeric form: " << SKNF_numeric_form << endl;

    cout << "Index form: ";
    for (const auto& element : exp_index_form) {
        cout << element << " ";
    }
    cout << endl;
    cout << "Index form in decimal: " << exp_index_form_in_decimal << endl;
}

Truth_Table Logical_Expression::create_truth_table() {
    int count_operands = unique_operands.size();
    int lines = pow(2, count_operands);
    Truth_Table table(lines);

    for (char operand : unique_operands) {
        string column_name(1, operand); // Преобразование символа в строку
        table.add_column(column_name);
    }

    for (int i = 0; i < lines; i++) {
        string binary = std::bitset<32>(i).to_string().substr(32 - count_operands);
        vector<bool> rowValues;
        for (char c : binary) {
            rowValues.push_back(c == '1');
        }
        for (int j = 0; j < rowValues.size(); j++) {
            table.set_value(string(1,unique_operands[j]), i, rowValues[j]);
        }
    }
    return table;
}

vector<char> Logical_Expression::get_unique_operands() {

    unordered_set<char> operands;

    for (char c : result_rpn) {
        if (isalpha(c) || isdigit(c)) {
            operands.insert(c);
        }
    }

    vector<char> result;
    for (char operand : operands) {
        result.push_back(operand);
    }
    return result;
}

string Logical_Expression::to_rpn() {
    stack<char> stack;
    string result = "";
    int open_parenttheses = 0;
    int close_parenttheses = 0;

    for (char s : expression) {
        if (isalpha(s) || isdigit(s)) {
            result += s;
        }
        else if (s == '(') {
            stack.push(s);
            open_parenttheses++;
        }
        else if (s == ')') {

            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                stack.pop();
            }
            stack.pop();
            close_parenttheses++;
        }
        else {
            while (!stack.empty() && priority(stack.top()) >= priority(s)) {
                result += stack.top();
                stack.pop();
            }
            stack.push(s);
        }
    }

    while (!stack.empty()) {
        result += stack.top();
        stack.pop();
    }
            return result;

}

int Logical_Expression::priority(char operation) {
    switch (operation)
    {
    case '!':
        return 5;
    case '&':
        return 4;
    case '|':
        return 3;
    case '>':
        return 2;
    case '~':
        return 1;
    default:
        return 0;
    }
}

bool Logical_Expression::is_operand(string token) {
    return token != "!" && token != "&" && token != "|" && token != ">" && token != "~";
}

bool Logical_Expression::execute_operation(bool operand1, bool operand2, char operating) {
    switch (operating)
    {
    case '&':
        return operand1 && operand2;
    case '|':
        return operand1 || operand2;
    case '>':
        return !operand1 || operand2;
    case '~':
        return operand1 == operand2;
    }
}
void Logical_Expression::execute_expression() {

    stack<string> stack;
    vector<char> tokens;

    for (char c : result_rpn) {
        tokens.push_back(c);
    }

    for (auto token : tokens) {

        string token_string(1, token);
        if (is_operand(token_string)) {
            stack.push(token_string);
        }
        else {
            string operand1, operand2;
            if (token == '!') {
                operand1 = stack.top();
                stack.pop();
                string result_column = "(!" + operand1 + ")";
                truth_table.add_column(result_column);
                for (int i = 0; i < truth_table.lines; i++) {
                    bool val = !truth_table.get_column_value(operand1, i);

                    truth_table.set_value(result_column, i, val);
                }
                stack.push(result_column);
            }
            else {
                operand2 = stack.top();
                stack.pop();
                operand1 = stack.top();
                stack.pop();
                string result_column = "(" + operand1 + token + operand2 + ")";
                truth_table.add_column(result_column);
                for (int i = 0; i < truth_table.lines; i++) {
                    bool val1 = truth_table.get_column_value(operand1, i);
                    bool val2 = truth_table.get_column_value(operand2, i);
                    bool result = execute_operation(val1, val2, token);
                    truth_table.set_value(result_column, i, result);
                }
                stack.push(result_column);

            }
        }
    }
}
string Logical_Expression::SKNF() {

    vector<string> cnfClauses;

    int lastIndex = truth_table.name_columns.size() - 1;

    auto string_join = [](const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += delimiter;
            }
        }
        return result;
        };

    for (int i = 0; i < truth_table.lines; i++) {
        if (!truth_table.name_columns[lastIndex].columns[i]) {
            vector<string> disjunction;
            for (size_t j = 0; j < unique_operands.size(); j++) {
                char operand = unique_operands[j];
                bool operandValue = truth_table.name_columns[truth_table.index_name[string(1, operand)]].columns[i];

                if (operandValue) {
                    disjunction.push_back("!" + string(1, operand));
                }
                else {
                    disjunction.push_back(string(1, operand));
                }

            }
            cnfClauses.push_back("(" + string_join(disjunction, "|") + ")");
        }
    }

    string result = string_join(cnfClauses, "&");
    return result;
}

string Logical_Expression::numeric_SKNF() {

    string result = "(";

    int lastIndex = truth_table.name_columns.size() - 1;

    for (int i = 0; i < truth_table.lines; i++) {
        if (truth_table.name_columns[lastIndex].columns[i]) {
            result = result + to_string(i) + ",";
        }
    }
    result.pop_back();
    result = result + ") |";

    return result;
}

string Logical_Expression::SDNF() {


    vector<string> cnfClauses;

    int lastIndex = truth_table.name_columns.size() - 1;

    auto string_join = [](const vector<string>& vec, const string& delimiter) {
        string result;
        for (size_t i = 0; i < vec.size(); i++) {
            result += vec[i];
            if (i != vec.size() - 1) {
                result += delimiter;
            }
        }
        return result;
        };

    for (int i = 0; i < truth_table.lines; i++) {
        if (truth_table.name_columns[lastIndex].columns[i]) {
            vector<string> disjunction;
            for (size_t j = 0; j < unique_operands.size(); j++) {
                char operand = unique_operands[j];
                bool operandValue = truth_table.name_columns[truth_table.index_name[string(1, operand)]].columns[i];

                if (!operandValue) {
                    disjunction.push_back("!" + string(1, operand));
                }
                else {
                    disjunction.push_back(string(1, operand));
                }

            }
            cnfClauses.push_back("(" + string_join(disjunction, "&") + ")");
        }
    }

    string result = string_join(cnfClauses, "|");
    return result;
}
string Logical_Expression::numeric_SDNF() {

    string result = "(";

    int lastIndex = truth_table.name_columns.size() - 1;

    for (int i = 0; i < truth_table.lines; i++) {
        if (!truth_table.name_columns[lastIndex].columns[i]) {
            result = result + to_string(i) + ",";
        }
    }
    result.pop_back();
    result = result + ") &";

    return result;
}

vector<bool> Logical_Expression::index_form() {
    vector<bool> result;
    int lastIndex = truth_table.name_columns.size() - 1;

    for (int i = 0; i < truth_table.lines; i++) {
        result.push_back(truth_table.name_columns[lastIndex].columns[i]);
    }
    return result;
}
int Logical_Expression::index_form_in_decimal() {

    int decimal = 0;
    int base = 1;
    for (int i = exp_index_form.size() - 1; i >= 0; i--) {
        if (exp_index_form[i]) {
            decimal += base;
        }
        base *= 2;
    }
    return decimal;
}