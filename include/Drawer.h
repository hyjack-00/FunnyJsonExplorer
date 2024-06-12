#ifndef DRAWER_H
#define DRAWER_H

#include "JsonTree.h"
#include "Output.h"

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
    // // TODO 删除默认构造函数，使用工厂方法
    // Drawer() : linkLen(2), iconLen(1) {
    //     indentLen = linkLen + iconLen;
    //     defaultIcon = leafIcon = ContainerIcon = " ";
    //     branch      = "  ";
    //     vertical    = "  ";
    //     branchEnd   = "  ";
    //     verticalEnd = "  ";
    //     reset();
    // }

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
    // // TODO 删除默认构造函数，使用工厂方法
    // TreeDrawer() : Drawer() {
    //     branch      = "├─";
    //     vertical    = "│ ";
    //     branchEnd   = "└─";
    //     verticalEnd = "  ";
    // }

    void drawDecorate() override;
};

class RectDrawer : public Drawer {
private:

public:
    // // TODO 删除默认构造函数，使用工厂方法
    // RectDrawer() : Drawer() {
    //     branch      = "├─";
    //     vertical    = "│ ";
    //     branchEnd   = "├─";
    //     verticalEnd = "│ ";
    // }

    void drawNode(
        const std::shared_ptr<JsonNode>& jsonNode, 
        const std::string& selfLink, 
        const std::string& childLink) override;
    void drawDecorate() override;
};

#endif // DRAWER_H
