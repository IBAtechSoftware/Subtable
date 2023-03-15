#include <Subtable/subtable.hpp>
#include <iostream>

int main(){
    SubTable table = SubTable();
    table.loadDocument("examples/launcherConfig.st");

    auto launcherConfig = table.getTable("ROOT").getSubtable("LauncherConfig");
    auto userConfig = launcherConfig.getSubtable("User");
    auto localUserConfig = userConfig.getSubtable("LocalSettings");
    auto developerModeEnabled = localUserConfig.getBoolean("DeveloperModeEnabled");

    std::cout << developerModeEnabled << std::endl;
}