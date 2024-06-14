#include <fstream>
#include <memory>
#include <sstream>
#include <iostream>

#include "Visitor/Drawer/Drawer.h"
#include "Visitor/Drawer/DrawerFactory.h"

#include "utils.h"


// DrawerFactory
// void DrawerFactory::setLink(const std::string& branch, const std::string& vertical, const std::string& branchEnd, const std::string& verticalEnd) {
//     drawer->branch = branch;
//     drawer->vertical = vertical;
//     drawer->branchEnd = branchEnd;
//     drawer->verticalEnd = verticalEnd;
// }
void DrawerFactory::setIcon(const std::string& leafIcon, const std::string& containerIcon) {
    drawer->leafIcon = leafIcon;
    drawer->containerIcon = containerIcon;
}
void DrawerFactory::setCharLen(const int linkLen, const int iconLen) {
    drawer->iconLen = iconLen;
    drawer->indentLen = linkLen + drawer->iconLen;
}

void DrawerFactory::resetDefaultDrawer() {
    drawer = std::make_unique<Drawer>();
    drawer->reset();  // buffer
}
void DrawerFactory::resetTreeDrawer() {
    drawer = std::make_unique<TreeDrawer>();
    drawer->reset();  // buffer
}
void DrawerFactory::resetRectDrawer() {
    drawer = std::make_unique<RectDrawer>();
    drawer->reset();  // buffer
}
std::unique_ptr<Drawer> DrawerFactory::createDefaultDrawer() {
    resetDefaultDrawer();

    build();

    return std::move(drawer);
}
std::unique_ptr<Drawer> DrawerFactory::createTreeDrawer() {
    resetTreeDrawer();

    branch      = "├─";
    vertical    = "│ ";
    branchEnd   = "└─";
    verticalEnd = "  ";

    build();

    return std::move(drawer);
}
std::unique_ptr<Drawer> DrawerFactory::createRectDrawer() {
    resetRectDrawer();

    branch      = "├─";
    vertical    = "│ ";
    branchEnd   = "├─";
    verticalEnd = "│ ";

    build();

    return std::move(drawer);   
}
std::unique_ptr<Drawer> DrawerFactory::createDrawer(DrawerType drawerType) {
    switch (drawerType) {
    case DrawerType::DefaultStyle:
        return std::move(createDefaultDrawer());
    case DrawerType::TreeStyle:
        return std::move(createTreeDrawer());
    case DrawerType::RectStyle:
        return std::move(createRectDrawer());
    default:
        return nullptr;
    }
}
std::unique_ptr<Drawer> DrawerFactory::createDrawer(const std::string& drawerTypeName) {
    return std::move(createDrawer(
        DrawerRegistry::getDrawerType(drawerTypeName)));
}


ConfigDrawerFactory::ConfigDrawerFactory(const std::string& configFilePath) {
    loadConfigFile(configFilePath);
}
void ConfigDrawerFactory::loadConfigFile(const std::string& configFilePath) {
    this->configFilePath = configFilePath; 
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
            if (key == "linkIcon") {
                linkIcon = value;
            } else if (key == "leafIcon") {
                leafIcon = value;
            } else if (key == "containerIcon") {
                containerIcon = value;
            }
        }
    }
}


std::shared_ptr<DrawerFactory> DrawerFactoryRegistry::getFactory(FactoryType factoryType) {
    auto it = factoryMap.find(factoryType);
    if (it != factoryMap.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}
std::shared_ptr<DrawerFactory> DrawerFactoryRegistry::getFactory(const std::string& factoryName) {
    return getFactory(factoryNameMap[factoryName]);
}