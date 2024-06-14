#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

#include "JsonCollection/JsonTree.h"

// JsonLeaf method implementations
std::vector<std::shared_ptr<JsonNode>> JsonLeaf::getChildren() const {
    return {};
}


// JsonContainer method implementations
void JsonContainer::add(std::shared_ptr<JsonNode> node) {
    children.push_back(node);
}
std::vector<std::shared_ptr<JsonNode>> JsonContainer::getChildren() const {
    return children;
}


// JsonTreeIterator method implementations
JsonTreeIterator::JsonTreeIterator(std::shared_ptr<JsonNode> root) {
    nodeStack.push(root);
    parentStack.push({nullptr, 0}); // Root has no parent

    currentNode = 0;
    currentInfo = {nullptr, -1};
}
bool JsonTreeIterator::hasMore() const {
    return !nodeStack.empty();
}

const std::shared_ptr<JsonNode> JsonTreeIterator::getNext() {  // DFS
    if (nodeStack.empty()) {
        return nullptr;
    }

    currentNode = nodeStack.top();
    nodeStack.pop();

    currentInfo = parentStack.top();
    parentStack.pop();

    // 获取子节点并按逆序压入栈中
    const auto& children = currentNode->getChildren();
    for (size_t i = 0; i < children.size(); ++i) {
        nodeStack.push(children[i]);
        parentStack.push({currentNode, i});
    }

    return currentNode;
}

bool JsonTreeIterator::isLastChild() const {
    if (currentInfo.second == -1) {
        return true; // init case
    }

    auto parent = currentInfo.first;
    size_t index = currentInfo.second;

    if (!parent) {
        return true; // Root node case
    }
    const auto& siblings = parent->getChildren();
    return index == siblings.size() - 1;
}


// JsonTree method implementations
JsonTree::JsonTree(const std::string &filePath) {
    readJson(filePath);
}

std::unique_ptr<JsonIterator<JsonNode>> JsonTree::createIterator() const {
    return std::make_unique<JsonTreeIterator>(root);
}

void JsonTree::readJson(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    json j;
    file >> j;
    parseJsonNode(j);
}

void JsonTree::parseJsonNode(const json &j) {
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

bool JsonTree::isLastChild(std::unique_ptr<JsonIterator<JsonNode>>& iter) {
    auto treeIter = dynamic_cast<JsonTreeIterator*>(iter.get());
    if (!treeIter) {
        throw std::runtime_error("Invalid iterator type.");
    }
    return treeIter->isLastChild();
}
