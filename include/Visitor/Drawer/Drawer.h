#ifndef DRAWER_H
#define DRAWER_H

#include <memory>

#include "JsonCollection/JsonTree.h"
#include "Output/TreeOutput.h"
#include "Visitor/Visitor.h"
#include "Visitor/Printer/Printer.h"
#include "Symbol.h"

#include "utils.h"

enum DrawerType {
    DefaultStyle,
    TreeStyle,
    RectStyle
};

class DrawerRegistry {
public:
    static DrawerType getDrawerType(const std::string& typeStr) {
        static std::map<std::string, DrawerType> drawerTypeMap = {
            {"default", DrawerType::DefaultStyle},
            {"tree", DrawerType::TreeStyle},
            {"rect", DrawerType::RectStyle}
        };
        
        DEBUG_PRINT("type = %s, %d", typeStr.c_str(), drawerTypeMap[typeStr]);

        return drawerTypeMap[typeStr];
    }
};

class Drawer : public TreeVisitor {
friend class DrawerFactory;

protected:
    // modified by drawXX();
    std::shared_ptr<OutputBuffer> outputBuffer;

    std::shared_ptr<OutputLine> currentLine;
    std::string currentIndent;
    int currentLevel;
    bool currentIsLastChild;

    Printer printer;

    Link link;

    std::string leafIcon;
    std::string containerIcon;
    int iconLen;
    void drawLeafIcon();
    void drawContainerIcon();


public:
    Drawer() = default;
    virtual ~Drawer() = default;

    virtual void reset();
    virtual std::shared_ptr<OutputBuffer> getOutput(const JsonTree& tree);
    virtual std::shared_ptr<OutputBuffer> getOutput();

    virtual void drawLine(const std::shared_ptr<JsonNode> jsonNode);
    virtual void drawIcon(const std::shared_ptr<JsonNode> jsonNode);
    virtual void drawDecorate();


    void visit(const JsonLeaf *leaf) override;
    void visit(const JsonContainer *container) override;
};


class TreeDrawer : public Drawer {
private:

public:
    TreeDrawer() = default;

};


class RectDrawer : public Drawer {
private:

public:
    RectDrawer() = default;

    void drawLine(const std::shared_ptr<JsonNode> jsonNode) override;
    void drawDecorate() override;
};

#endif // DRAWER_H
