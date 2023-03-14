#include "subtable.hpp"
#include <iostream>

int main(){
    SubTable table = SubTable();
    table.loadDocument("example.st");

    auto testTable = table.getTable("ROOT").getSubtable("Test");
    auto usersArray = testTable.getArray("Users");
}