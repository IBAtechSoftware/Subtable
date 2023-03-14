#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
#include <sstream>


class Table {
public:
  std::string m_name;
  std::vector<Table> m_subtables;
  std::map<std::string, std::string> m_values;

  inline std::string getString(std::string key) { return m_values.at(key); }

  inline int getInt(std::string key) { return std::stoi(m_values.at(key)); }

  inline bool getBoolean(std::string key){
    std::string stringResult = m_values.at(key);

    std::transform(stringResult.begin(), stringResult.end(), stringResult.begin(), ::tolower);
    std::istringstream is(stringResult);
    bool b;
    is >> std::boolalpha >> b;
    
    return b;
  }

  inline Table getSubtable(std::string key) {
    for (auto table : m_subtables) {
      if (table.m_name == key) {
        return table;
      }
    }

    throw std::runtime_error("Cannot find subtable");
  }
};

inline Table *queryForTable(std::vector<Table *> tables, std::string name) {
  for (auto table : tables) {
    if (table->m_name == name) {
      return table;
    }
  }

  throw std::runtime_error("Cannot find table");
}

// Main subtable parser class, for a single document
class SubTable {
public:
  SubTable();

  void loadDocument(std::string filePath);

  inline Table getTable(std::string key) {
    // query for table

    return *queryForTable(m_tables, key);
  }

private:
  Table m_rootTable;
  std::vector<Table *> m_tables;
  Table *m_currentTable;
  int m_tableIndex = 0;
};