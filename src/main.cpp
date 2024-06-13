#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cxxopts/cxxopts.hpp> 

#include "JsonCollection/JsonTree.h"
#include "Output/TreeOutput.h"
#include "Visitor/Drawer/Drawer.h"
#include "Visitor/Drawer/DrawerFactory.h"

DrawerFactoryRegistry registry;

// Function to print the JSON tree structure
void printJsonTree(const std::shared_ptr<JsonNode>& node, int indent = 0) {
    if (!node) return;

    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }
    std::cout << node->drawContent() << std::endl;

    for (const auto& child : node->getChildren()) {
        printJsonTree(child, indent + 1);
    }
}

int main(int argc, char* argv[]) {
    // Parse command-line arguments
    cxxopts::Options options("FJE", "A command-line JSON file visualization tool");
    options.add_options()
        ("f,file", "JSON file path", cxxopts::value<std::string>())
        ("s,style", "Style of visualization (tree/rect)", cxxopts::value<std::string>()->default_value("tree"))
        ("i,icon", "Icon family to use", cxxopts::value<std::string>()->default_value("default"))
        ("c,config", "Configuration file path (required if -i config is used)", cxxopts::value<std::string>())
        ("h,help", "Print usage");
    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return 0;
    }
    if (!result.count("file")) {
        std::cerr << "Error: JSON file path not provided." << std::endl;
        return 1;
    }

    std::string filename = result["file"].as<std::string>();
    std::string style = result["style"].as<std::string>();
    std::string iconFamily = result["icon"].as<std::string>();

    JsonTree jsonTree;
    try {
        jsonTree.readJson(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error reading JSON file: " << e.what() << std::endl;
        return 1;
    }

    // build drawer
    auto factory = registry.getFactory(iconFamily);
    if (iconFamily == "config") {
        if (!result.count("config")) {
            std::cerr << "Error: Configuration file path must be provided when using -i config." << std::endl;
            return 1;
        }
        std::string configFilePath = result["config"].as<std::string>();

        auto configFactory = std::dynamic_pointer_cast<ConfigDrawerFactory>(factory);
        configFactory->loadConfigFile(configFilePath);
    }

    auto drawer = factory->createDrawer(style);

    // build output
    auto root = jsonTree.getRoot();
    auto output = drawer->getOutput(root);
    output->print();

    return 0;
}
