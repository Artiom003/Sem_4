#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <map>
#include <iostream>

//#include <boost/container/flat_map.hpp>
using namespace std;

class Column {
private:
	friend class Logical_Expression;
	friend class Truth_Table;
	string name;
	vector<bool> columns;
	Column(const std::string& col_name, const std::vector<bool>& col_data) : name(col_name), columns(col_data) {}
};

class Truth_Table {
private:
    friend class Logical_Expression;
	Truth_Table(int lines);
	Truth_Table(){}

	vector<Column> name_columns;
	map<string, int> index_name;
	int lines;

	void add_column(string column_name);
	void set_value(string column_name, int row_index, bool value);

	bool get_column_value(const std::string& column_name, int row_index) const;
	string get_table_string();
};
