#ifndef JSON_TREE_H
#define JSON_TREE_H

#include <string>
#include <vector>
#include <stack>
#include <memory>
#include <iostream>
#include <nlohmann/json.hpp>

#include "JsonCollection.h"
#include "Visitor/Visitor.h"

using json = nlohmann::json;


class JsonNode {
public:
    JsonNode(const std::string name, int level, std::shared_ptr<JsonNode> father)
        : level(level), name(name) {}
    virtual ~JsonNode() = default;

    virtual void accept(TreeVisitor &visitor) = 0;

    virtual std::vector<std::shared_ptr<JsonNode>> getChildren() const = 0;

    int getLevel() const { return level; }
    const std::string& getName() const { return name; }
    const std::shared_ptr<JsonNode> getFather() const { return father; }

private:
    std::shared_ptr<JsonNode> father;
    const std::string name;
    const int level;
};


class JsonLeaf : public JsonNode {
public:
    JsonLeaf(const std::string &name, int level, 
        const std::string &value, std::shared_ptr<JsonNode> father)
        : JsonNode(name, level, father), value(value) {}

    void accept(TreeVisitor &v) override { v.visit(this); }

    const std::string& getValue() const { return value; }
    std::vector<std::shared_ptr<JsonNode>> getChildren() const override;

private:
    std::string value;
};


class JsonContainer : public JsonNode {
public:
    JsonContainer(const std::string &name, int level,
        std::shared_ptr<JsonNode> father)
        : JsonNode(name, level, father) {}
    void add(std::shared_ptr<JsonNode> node);

    void accept(TreeVisitor &v) override { v.visit(this); }

    std::vector<std::shared_ptr<JsonNode>> getChildren() const override;

private:
    std::vector<std::shared_ptr<JsonNode>> children;
};


class JsonTreeIterator : public JsonIterator<JsonNode> {
private:
    // DFS
    std::stack<std::shared_ptr<JsonNode>> nodeStack; 
    // Track parent and child index
    std::stack<std::pair<std::shared_ptr<JsonNode>, size_t>> parentStack; 

    std::shared_ptr<JsonNode> currentNode;
    std::pair<std::shared_ptr<JsonNode>, size_t> currentInfo;

public:
    JsonTreeIterator(std::shared_ptr<JsonNode> root);

    bool hasMore() const override;
    const std::shared_ptr<JsonNode> getNext() override;

    bool isLastChild() const;
};


class JsonTree : public JsonCollection<JsonNode> {
private:
    std::shared_ptr<JsonNode> root;

    void parseJsonNode(const json &j);
    void parseHelper(const json &j, std::shared_ptr<JsonContainer> parent);

public:
    JsonTree() = default;
    JsonTree(const std::string &filePath);

    void readJson(const std::string &filePath) override;
    void clearJson() override;

    std::unique_ptr<JsonIterator<JsonNode>> createIterator() const override;

    static bool isLastChild(std::shared_ptr<JsonNode> jsonNode);
};

#endif // JSON_TREE_H
