#include <iostream>

#include "JsonTree.h"
#include "Drawer.h"

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

    std::cout << "DefaultDrawer:" << std::endl;
    Drawer drawer;
    auto output0 = drawer.getOutput(root);
    output0->print();

    std::cout << "TreeDrawer:" << std::endl;
    TreeDrawer treeDrawer;
    auto output1 = treeDrawer.getOutput(root);
    output1->print();

    std::cout << "RectDrawer:" << std::endl;
    RectDrawer rectDrawer;
    auto output2 = rectDrawer.getOutput(root);
    output2->print();

    return 0;
}
