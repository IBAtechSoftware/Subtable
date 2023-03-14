#include "subtable.hpp"
#include <iostream>

int main(){
    SubTable table = SubTable();
    table.loadDocument("example.st");

    std::cout << table.getTable("ROOT").getSubtable("Test").getString("Port") << std::endl;
}