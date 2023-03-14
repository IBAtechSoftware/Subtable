#include "subtable.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

SubTable::SubTable(){  }

void SubTable::loadDocument(std::string filePath) {
  m_rootTable.m_name = "ROOT";

  m_tables.push_back(&m_rootTable);

  m_currentTable = m_tables.back();

  std::ifstream ifs(filePath);
  std::string line;

  while (std::getline(ifs, line)) {

    ltrim(line);

    if (line[0] == '?') {
      line.erase(0, 1); // Remove ?
      ltrim(line);

      // Split by space
      auto lineParsed = split(line, " ");

      if (lineParsed.size() < 2) {
        throw std::runtime_error("Invalid create table syntax");
      }

      if (lineParsed[1] != "{") {
        throw std::runtime_error("Expected {");
      }

      Table newTable{};
      newTable.m_name = lineParsed[0];

      // Insert a pointer to the subtable into the global Tables vector

      m_currentTable->m_subtables.push_back(newTable);

      m_tables.push_back(&m_currentTable->m_subtables.back());

      m_currentTable = &m_currentTable->m_subtables.back();
      m_tableIndex++;
    }

    if (line[0] == '@') {
      line.erase(0, 1); // Remove the first character(@)
      ltrim(line);

      std::vector<std::string> tableInsertSplit = split(line, "=");

      if (tableInsertSplit.size() < 2) {
        throw std::runtime_error(
            "Invalid syntax for table insert, example: @Test=123");
      }

      std::string tableKey = tableInsertSplit[0];
      std::string tableValue = tableInsertSplit[1];

      tableKey.pop_back();
      ltrim(tableValue);

      m_currentTable->m_values.insert(
          std::pair<std::string, std::string>(tableKey, tableValue));
    }

    if (line[0] == '}') {
      m_tableIndex--;
      m_currentTable = m_tables[m_tableIndex];
    }
  }
}