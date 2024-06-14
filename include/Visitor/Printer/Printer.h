#ifndef PRINTER_H
#define PRINTER_H

#include <memory>

#include "Visitor/Visitor.h"
#include "JsonCollection/JsonTree.h"

class Printer : public TreeVisitor {
private:
    std::string content;

public:
    Printer() = default;
    virtual ~Printer() = default;

    std::string getContent(const std::shared_ptr<JsonNode> jsonNode) { 
        jsonNode->accept(*this);
        return content;
    }

    void visit(const JsonLeaf *leaf) override {
        content = leaf->getName() + ": " + leaf->getValue();
    }
    void visit(const JsonContainer *container) override {
        content = container->getName();
    }
};

#endif // PRINTER_H