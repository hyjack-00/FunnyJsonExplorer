#include <fstream>
#include <sstream>
#include <iostream>

#include "DrawerFactory.h"


// DrawerFactory
void DrawerFactory::resetTreeDrawer() {
    drawer = std::make_unique<TreeDrawer>();
    drawer->reset();  // buffer
}
void DrawerFactory::resetRectDrawer() {
    drawer = std::make_unique<RectDrawer>();
    drawer->reset();  // buffer
}
void DrawerFactory::setLink(const std::string& branch, const std::string& vertical, const std::string& branchEnd, const std::string& verticalEnd) {
    drawer->branch = branch;
    drawer->vertical = vertical;
    drawer->branchEnd = branchEnd;
    drawer->verticalEnd = verticalEnd;
}
void DrawerFactory::setIcon(const std::string& defaultIcon, const std::string& leafIcon, const std::string& containerIcon) {
    drawer->defaultIcon = defaultIcon;
    drawer->leafIcon = leafIcon;
    drawer->ContainerIcon = containerIcon;
}
void DrawerFactory::setCharLen(const int linkLen, const int iconLen) {
    drawer->linkLen = linkLen;
    drawer->iconLen = iconLen;
    drawer->indentLen = drawer->linkLen + drawer->iconLen;
}

std::unique_ptr<Drawer> DrawerFactory::createTreeDrawer() {
    resetTreeDrawer();

    branch      = "├─";
    vertical    = "│ ";
    branchEnd   = "└─";
    verticalEnd = "  ";

    setAll();

    return std::move(drawer);
}
std::unique_ptr<Drawer> DrawerFactory::createRectDrawer() {
    resetRectDrawer();

    branch      = "├─";
    vertical    = "│ ";
    branchEnd   = "├─";
    verticalEnd = "│ ";

    setAll();

    return std::move(drawer);   
}


ConfigDrawerFactory::ConfigDrawerFactory(const std::string& configFilePath) 
    : configFilePath(configFilePath) 
{
    std::ifstream configFile(configFilePath);
    if (!configFile) {
        std::cerr << "Failed to open config file: " << configFilePath << std::endl;
        return;
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            if (key == "defaultIcon") {
                defaultIcon = value;
            } else if (key == "leafIcon") {
                leafIcon = value;
            } else if (key == "ContainerIcon") {
                containerIcon = value;
            }
        }
    }
}