#include "truth_table.h"

Truth_Table::Truth_Table(int lines) {
	this->lines = lines;

}

void Truth_Table::add_column(string column_name) {

    if (index_name.find(column_name) == index_name.end()) {
        name_columns.push_back(Column{ column_name, vector<bool>(lines, false) });
        index_name[column_name] = index_name.size();
    }
}

void Truth_Table::set_value(string column_name, int row_index, bool value) {

    if (row_index >= 0 && row_index < lines) {
        for (auto& column : name_columns) {
            if (column.name == column_name && row_index < column.columns.size()) {
                column.columns[row_index] = value;
                return;
            }
        }
    }
    else {
        for (auto& column : name_columns) {
            if (column.columns.size() < lines) {
                column.columns.resize(lines, false);
            }
        }
        for (auto& column : name_columns) {
            if (column.name == column_name && row_index < column.columns.size()) {
                column.columns[row_index] = value;
                return;
            }
        }
    }
}

string Truth_Table::get_table_string() {
    ostringstream tableString;
    map<string, int> columnWidths;
    vector<string> columnOrder;

    for (const auto& column : name_columns) {
        int maxColumnWidth = column.name.length();

        for (const auto& value : column.columns) {
            int valueLength = value ? 1 : 0;
            string valueString = value ? "1" : "0";
            if (valueString.length() > maxColumnWidth)
                maxColumnWidth = valueString.length();
        }

        columnWidths[column.name] = maxColumnWidth;
        columnOrder.push_back(column.name);
    }

    for (const auto& columnName : columnOrder) {
        tableString << " |  " << std::setw(columnWidths[columnName]) << columnName;
    }
    tableString << '\n';

    for (int i = 0; i < lines; i++) {
        for (const auto& columnName : columnOrder) {
            string valueString = name_columns[index_name[columnName]].columns[i] ? "1" : "0";
            tableString << " |  " << std::left << std::setw(columnWidths[columnName]) << valueString ;
        }
        tableString << '\n';
    }

    return tableString.str();
}

bool Truth_Table::get_column_value(const std::string& column_name, int row_index) const {
    for (const auto& column : name_columns) {
        if (column.name == column_name && row_index < column.columns.size()) {
            return column.columns[row_index];
        }
    }
    return false;  // Или любое значение по умолчанию в случае отсутствия столбца/строки
}