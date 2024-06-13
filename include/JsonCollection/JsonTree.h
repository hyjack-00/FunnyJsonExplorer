#ifndef JSON_TREE_H
#define JSON_TREE_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <nlohmann/json.hpp>

#include "JsonCollection.h"

using json = nlohmann::json;

class JsonNode {
public:
    JsonNode(bool isLeaf, int level) : isLeaf(isLeaf), level(level) {}
    virtual ~JsonNode() = default;
    virtual int countRows() const = 0;
    virtual int countMaxLen() const = 0;
    virtual std::string drawContent() const = 0;
    virtual std::vector<std::shared_ptr<JsonNode>> getChildren() const = 0;

    int getLevel() const { return level; }
    bool getIsLeaf() const { return isLeaf; }

private:
    const bool isLeaf;
    const int level;
};

class JsonLeaf : public JsonNode {
public:
    JsonLeaf(const std::string &name, int level, const std::string &value)
        : JsonNode(true, level), name(name), value(value) {}

    int countRows() const override;
    int countMaxLen() const override;
    std::string drawContent() const override;
    std::vector<std::shared_ptr<JsonNode>> getChildren() const override;

private:
    std::string name;
    std::string value;
};

class JsonContainer : public JsonNode {
public:
    JsonContainer(const std::string &name, int level) 
        : JsonNode(false, level), name(name) {}

    void add(std::shared_ptr<JsonNode> node);
    int countRows() const override;
    int countMaxLen() const override;
    std::string drawContent() const override;
    std::vector<std::shared_ptr<JsonNode>> getChildren() const override;

private:
    std::string name;
    std::vector<std::shared_ptr<JsonNode>> children;
};


class JsonTree : public JsonCollection {
private:
    std::shared_ptr<JsonNode> root;
    void parseJsonNode(const json &j);

public:
    JsonTree() = default;
    JsonTree(const std::string &filePath);

    void readJson(const std::string &filePath) override;
    void clearJson() override;

    std::shared_ptr<JsonNode> getRoot() const { return root; }
};

#endif // JSON_TREE_H
