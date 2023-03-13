#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <map>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>

// Functions
static inline void ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
                                    { return !std::isspace(ch); }));
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

class Table
{
public:
    std::string Name;
    std::vector<Table> Subtables;
    std::map<std::string, std::string> Values;

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &BOOST_SERIALIZATION_NVP(Name);
        ar &BOOST_SERIALIZATION_NVP(Subtables);
        ar &BOOST_SERIALIZATION_NVP(Values);
    }
};

int main()
{
    Table RootTable = Table{};
    RootTable.Name = "ROOT";

    std::vector<Table *> Tables;
    Tables.push_back(&RootTable);

    Table *CurrentTable = Tables.back();

    int TableIndex = 0;

    std::ifstream ifs("example.st");
    std::string Line;

    while (std::getline(ifs, Line))
    {

        ltrim(Line);

        if (Line[0] == '?')
        {
            Line.erase(0, 1); // Remove ?
            ltrim(Line);

            // Split by space
            auto LineParsed = split(Line, " ");

            if (LineParsed.size() < 2){
                throw std::runtime_error("Invalid create table syntax");
            }

            if (LineParsed[1] != "{"){
                throw std::runtime_error("Expected {");
            }

            std::cout << "Open table: " << LineParsed[0] << std::endl;

            Table NewTable{};
            NewTable.Name = LineParsed[0];

            // Insert a pointer to the subtable into the global Tables vector

            CurrentTable->Subtables.push_back(NewTable);

            Tables.push_back(&CurrentTable->Subtables.back());

            CurrentTable = &CurrentTable->Subtables.back();
            TableIndex++;
        }

        if (Line[0] == '@'){
            Line.erase(0, 1); // Remove the first character(@)
            ltrim(Line);

            std::vector<std::string> TableInsertSplit = split(Line, "=");
        
            if (TableInsertSplit.size() < 2){
                throw std::runtime_error("Invalid syntax for table insert, example: @Test=123");
            }

            std::string TableKey = TableInsertSplit[0];
            std::string TableValue = TableInsertSplit[1];

            TableKey.pop_back();
            ltrim(TableValue);

            CurrentTable->Values.insert(std::pair<std::string, std::string>(TableKey, TableValue));
        }

        if (Line[0] == '}')
        {
            std::cout << "Close table: " << CurrentTable->Name << std::endl;

            TableIndex--;
            CurrentTable = Tables[TableIndex];
        }
    }

    std::ofstream ofs("out.xml");
    // save data to archive
    {
        unsigned int flags = boost::archive::no_header;
        boost::archive::xml_oarchive oa(ofs, flags);
        // write class instance to archive
        oa << BOOST_SERIALIZATION_NVP(RootTable);
        // archive and stream closed when destructors are called
    }
}
