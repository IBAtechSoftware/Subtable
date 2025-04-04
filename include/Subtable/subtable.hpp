#pragma once

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

  /**
   Returns the value from the table as a string
  */
  inline std::string getString(std::string key) { return m_values.at(key); }

  /**
   Returns the value from the table as a integer
  */
  inline int getInt(std::string key) { return std::stoi(m_values.at(key)); }

  /**
   Returns the value from the table as a boolean
  */
  inline bool getBoolean(std::string key) {
    std::string stringResult = m_values.at(key);

    return stringResult == "true" || stringResult == "1" ? true : false;
  }

  /**
   Returns the value from the table as an array
  */
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

    for (auto val : values) {
      ltrim(val);

      result.push_back(val);
    }

    return result;
  }

  /**
   Returns a subtable with the given name
  */
  inline Table getSubtable(std::string key) {
    for (auto table : m_subtables) {
      if (table.m_name == key) {
        return table;
      }
    }

    throw std::runtime_error("Cannot find subtable: " + key);
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

/**
  Represents a single subtable document
*/
class SubTable {
public:
  SubTable();

  /**
  Load a subtable(.st) document from the given path
*/
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

class WritableTable {
public:
  inline WritableTable(std::string name) { m_tableName = name; }

  inline WritableTable *newTable(std::string name) {
    m_subtables.push_back(WritableTable(name));

    return &m_subtables.back();
  }

  inline WritableTable *setValue(std::string key, std::string value) {
    m_values.insert({key, value});
    return this;
  }

  std::string m_tableName;
  std::map<std::string, std::string> m_values;
  std::vector<WritableTable> m_subtables;
};

class SubTableWriter {
public:
  SubTableWriter(std::string filePath);

  inline WritableTable *getRoot() { return m_root; }

  void write();

private:
  std::string m_filePath;
  WritableTable *m_root;
};
