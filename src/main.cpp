#include <iostream>

#include "JsonTree.h"

// test
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
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <json file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    JsonTree jsonTree;

    try {
        jsonTree.readJson(filename);
    } catch (const std::exception& e) {
        std::cerr << "Error reading JSON file: " << e.what() << std::endl;
        return 1;
    }

    std::shared_ptr<JsonNode> root = jsonTree.getRoot();
    printJsonTree(root);

    return 0;
}
