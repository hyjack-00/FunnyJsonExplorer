#include <iostream>
#include <memory>
#include "JsonCollection/JsonTree.h"
#include "Output/TreeOutput.h"
#include "Visitor/Drawer/Drawer.h"

#include "utils.h"

// Drawer builder 默认实现
std::shared_ptr<OutputBuffer> Drawer::getOutput(const JsonTree& tree) {
    DEBUG_PRINT("Draw with branch '%s', vertical '%s', branchEnd '%s', verticalEnd '%s'",
                link.getLink(LinkType::Branch).c_str(),
                link.getLink(LinkType::Vertical).c_str(),
                link.getLink(LinkType::BranchEnd).c_str(),
                link.getLink(LinkType::VerticalEnd).c_str());
    DEBUG_PRINT("Draw with leafIcon '%s', containerIcon '%s'", 
                leafIcon.c_str(), containerIcon.c_str());
    DEBUG_PRINT("Draw with linkLen %d, iconLen %d", 
                link.getLinkLen(), iconLen);

    reset();
    auto iter = tree.createIterator();
    while (iter->hasMore()) {
        auto node = iter->getNext();
        currentIsLastChild = ((JsonTreeIterator*) iter.get())->isLastChild();

        DEBUG_PRINT("TO DRAW NODE %s", node->getName().c_str());
        drawLine(node);
        outputBuffer->addLine(currentLine);
    }
    drawDecorate();
    return outputBuffer; 
}
std::shared_ptr<OutputBuffer> Drawer::getOutput() {
    return outputBuffer;
}

void Drawer::reset() {
    outputBuffer = std::make_shared<OutputBuffer>();
    outputBuffer->clear();

    currentIndent = "";
    currentLevel = 0;
}

// DFS
void Drawer::drawLine(const std::shared_ptr<JsonNode> jsonNode) {
    int level = jsonNode->getLevel();
    if (level == currentLevel) {
        DEBUG_PRINT("level == %s", "");
        link.stepStay(currentIndent, currentIsLastChild);
    } 
    else if (level == currentLevel + 1) {
        DEBUG_PRINT("level += %d", 1);
        link.stepIn(currentIndent, currentIsLastChild);
        currentLevel = level;
    } 
    else if (level < currentLevel) {
        int skipLevel = currentLevel - level;
        DEBUG_PRINT("level -= %d", skipLevel);
        while (skipLevel-- > 0)
            link.stepOut(currentIndent, currentIsLastChild);
        currentLevel = level;
    }
    else {
        throw std::runtime_error("Invalid level skip.");
    }

    DEBUG_PRINT("Current level %d, indent '%s'", 
                currentLevel, currentIndent.c_str());

    currentLine = std::make_shared<OutputLine>(jsonNode);
    currentLine->addElement(currentIndent);
    drawIcon(jsonNode);

    currentLine->addElement(
        printer.getContent(jsonNode)
    );
}

void Drawer::drawIcon(const std::shared_ptr<JsonNode> jsonNode) {
    jsonNode->accept(*this);
}
void Drawer::drawDecorate() {
    // 去掉首行
    if (!outputBuffer->getLines().empty()) {
        outputBuffer->getLines().erase(outputBuffer->getLines().begin());
    }
    // 每行去掉首字符空格
    for (auto &line : outputBuffer->getLines()) {
        auto &elements = line->getElements();
        if (elements.empty()) continue;

        auto &indent = elements.front();
        if (!indent.empty() && indent[0] == ' ') {
            indent.erase(0, 1);
        }
    }    
}

void Drawer::drawLeafIcon() {
    currentLine->addElement(leafIcon);
}
void Drawer::drawContainerIcon() {  
    currentLine->addElement(containerIcon);
}
void Drawer::visit(const JsonLeaf *leaf) {
    drawLeafIcon();
}
void Drawer::visit(const JsonContainer *container) {
    drawContainerIcon();
}


// TreeDrawer



// RectDrawer
void RectDrawer::drawLine(const std::shared_ptr<JsonNode> jsonNode) 
{
    Drawer::drawLine(jsonNode);

    // 填充右侧横线
    int indentLen = jsonNode->getLevel() * link.getLinkLen();
    int contentLen = currentLine->getElements().back().size();
    int fillLen = 50 - indentLen - iconLen - contentLen;

    std::string fillStr = "";
    for (int i = 0; i < fillLen; i += 1) {
        fillStr += "─";
    }
    currentLine->addElement(fillStr);

    // 添加右侧边框
    currentLine->addElement("┤");
}

void RectDrawer::drawDecorate() {
    Drawer::drawDecorate();

    // 首行处理
    if (!outputBuffer->getLines().empty()) {
        auto &firstLine = outputBuffer->getLines().front();
        firstLine->getElements()[0] = "┌─";
        firstLine->getElements().back() = "┐";
    }
    // 末行处理
    if (outputBuffer->getLines().size() > 1) {
        auto &lastLine = outputBuffer->getLines().back();
        lastLine->getElements().back() = "┘";
        
        // 全部替换为封闭字符
        auto &jsonNode = lastLine->getJsonNode();
        std::string indents = "└─";
        int numIndent = jsonNode->getLevel();
        for (int i = 0; i < numIndent - 1; i += 1) {
            indents += "─┴─";
        }
        lastLine->getElements()[0] = indents;

        // 第二个元素是 icon，替换为 "✩"
        auto &icon = lastLine->getElements()[1];
        if (icon == " ")
            icon = "✩";
    }
}
