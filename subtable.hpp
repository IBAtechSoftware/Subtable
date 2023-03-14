#include <algorithm>
#include <cctype>
#include <map>
#include <sstream>
#include <string>
#include <vector>

inline std::vector<std::string> split(std::string s, std::string delimiter) {
  size_t pos_start = 0, pos_end, delim_len = delimiter.length();
  std::string token;
  std::vector<std::string> res;

  while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
    token = s.substr(pos_start, pos_end - pos_start);
    pos_start = pos_end + delim_len;
    res.push_back(token);
  }

  res.push_back(s.substr(pos_start));
  return res;
}

// Functions
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

class Table {
public:
  std::string m_name;
  std::vector<Table> m_subtables;
  std::map<std::string, std::string> m_values;

  inline std::string getString(std::string key) { return m_values.at(key); }

  inline int getInt(std::string key) { return std::stoi(m_values.at(key)); }

  inline bool getBoolean(std::string key) {
    std::string stringResult = m_values.at(key);

    std::transform(stringResult.begin(), stringResult.end(),
                   stringResult.begin(), ::tolower);
    std::istringstream is(stringResult);
    bool b;
    is >> std::boolalpha >> b;

    return b;
  }

  // WARNING: Arrays are not parsed when the document is loaded, they are parsed
  // when their value is requested
  inline std::vector<std::string> getArray(std::string key) {
    std::string arrayString = m_values.at(key);

    if (arrayString[0] != '[') {
      throw std::runtime_error(
          "Request value is not an array(does not start with [)");
    }

    arrayString.erase(0, 1);
    arrayString.pop_back();

    ltrim(arrayString); // Trim whitespace

    // split by ,
    std::vector<std::string> values = split(arrayString, ",");
    std::vector<std::string> result;

    for (auto val : values){
      ltrim(val);

      result.push_back(val);
    }

    return result;
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