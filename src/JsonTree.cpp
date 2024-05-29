#include "JsonTree.h"
#include <fstream>
#include <iostream>

// JsonLeaf method implementations
int JsonLeaf::countRows() const {
    return 1;
}

int JsonLeaf::countMaxLen() const {
    return name.size() + (value.empty() ? 0 : (value.size() + 2));
}

std::string JsonLeaf::drawContent() const {
    return value.empty() ? name : name + ": " + value;
}

std::vector<std::shared_ptr<JsonNode>> JsonLeaf::getChildren() const {
    return {};
}

// JsonContainer method implementations
void JsonContainer::add(std::shared_ptr<JsonNode> node) {
    children.push_back(node);
}

int JsonContainer::countRows() const {
    int rows = 1; // include self
    for (const auto &child : children) {
        rows += child->countRows();
    }
    return rows;
}

int JsonContainer::countMaxLen() const {
    int maxLen = name.size();
    for (const auto &child : children) {
        int childMaxLen = child->countMaxLen();
        if (childMaxLen > maxLen) {
            maxLen = childMaxLen;
        }
    }
    return maxLen;
}

std::string JsonContainer::drawContent() const {
    return name;
}

std::vector<std::shared_ptr<JsonNode>> JsonContainer::getChildren() const {
    return children;
}

// JsonTree method implementations
JsonTree::JsonTree(const std::string &filePath) {
    readJson(filePath);
}

void JsonTree::readJson(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    json j;
    file >> j;
    parseJson(j);
}

void JsonTree::parseJson(const json &j) {
    root = std::make_shared<JsonContainer>("root", 0);

    // 格式定义
    std::function<void(const json &, std::shared_ptr<JsonContainer>)> parseHelper = 
    [&](const json &j, std::shared_ptr<JsonContainer> parent) {
        if (j.is_object()) {
            for (auto it = j.begin(); it != j.end(); ++it) {
                if (it->is_object()) {
                    auto container = std::make_shared<JsonContainer>(
                        it.key(), parent->getLevel() + 1);
                    parent->add(container);
                    parseHelper(it.value(), container);
                } 
                else if (it->is_array()) {
                    throw std::runtime_error("Unsupported JSON format: array");
                }
                else {
                    auto value = it->dump();
                    if (value == "null") value = "";
                    else                 value = value.substr(1, value.size() - 2);
                    auto leaf = std::make_shared<JsonLeaf>(
                        it.key(), parent->getLevel() + 1, value);
                    parent->add(leaf);
                }
            }
        } 
        else {
            throw std::runtime_error("Unsupported JSON format: array / straight value");
        }
    };

    parseHelper(j, std::dynamic_pointer_cast<JsonContainer>(root));
}

void JsonTree::clearJson() {
    root.reset();
}
