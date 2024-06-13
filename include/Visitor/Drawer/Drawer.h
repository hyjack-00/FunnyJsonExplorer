#ifndef DRAWER_H
#define DRAWER_H

#include "JsonCollection/JsonTree.h"
#include "Output/TreeOutput.h"

enum DrawerType {
    DefaultStyle,
    TreeStyle,
    RectStyle
};


class Drawer {
friend class DrawerFactory;

protected:
    std::shared_ptr<OutputBuffer> outputBuffer;

    // link strings
    std::string branch;
    std::string vertical;
    std::string branchEnd;
    std::string verticalEnd;
    int linkLen;

    // icons between links
    std::string defaultIcon;
    std::string leafIcon;
    std::string ContainerIcon;
    int iconLen;

    // indention = link + icon
    int indentLen;

public:
    Drawer() = default;
    virtual ~Drawer() = default;

    void reset();
    virtual std::shared_ptr<OutputBuffer> getOutput(const std::shared_ptr<JsonNode>& rootNode);
    virtual std::shared_ptr<OutputBuffer> getOutput();
    virtual void drawNode(
        const std::shared_ptr<JsonNode>& jsonNode, 
        const std::string& selfLink, 
        const std::string& childLink);
    virtual void drawDecorate();
    virtual void drawIcon();
};

class TreeDrawer : public Drawer {
private:

public:
    TreeDrawer() = default;

    void drawDecorate() override;
};

class RectDrawer : public Drawer {
private:

public:
    RectDrawer() = default;

    void drawNode(
        const std::shared_ptr<JsonNode>& jsonNode, 
        const std::string& selfLink, 
        const std::string& childLink) override;
    void drawDecorate() override;
    void drawIcon() override;
};

#endif // DRAWER_H
