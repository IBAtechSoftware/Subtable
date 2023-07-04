#include <Subtable/subtable.hpp>
#include <iostream>

int main() {
  SubTable table = SubTable();
  table.loadDocument("example.st");

  auto configTable = table.getTable("ROOT").getSubtable("Config");
  auto authTable = configTable.getSubtable("Auth");

  std::cout << configTable.getString("Username") << std::endl;
  std::cout << authTable.getString("Token") << std::endl;

  SubTableWriter writer = SubTableWriter("example.st");
  writer.getRoot()
      ->newTable("Config")
      ->setValue("Username", "Interfiber")
      ->newTable("Auth")
      ->setValue("Issuer", "multiplayer_auth")
      ->setValue("Token", "001012mdi3o234jknerdjhnw34");

  writer.write();
}
