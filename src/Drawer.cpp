#include "Drawer.h"
#include <iostream>

// int getActualLen(std::string utf8Str) {
//     int length = 0;
//     for (size_t i = 0; i < utf8Str.length(); ++i) {
//         if ((utf8Str[i] & 0xC0) != 0x80) {
//             // This is the start of a new UTF-8 character
//             ++length;
//         }
//     }
//     return length;
// }

// Drawer builder 默认实现
std::shared_ptr<OutputBuffer> Drawer::getOutput(const std::shared_ptr<JsonNode>& rootNode) {
    reset();
    drawNode(rootNode, "", "");
    drawDecorate();
    drawIcon();
    return outputBuffer; 
}
std::shared_ptr<OutputBuffer> Drawer::getOutput() {
    return outputBuffer;
}

void Drawer::reset() {
    outputBuffer = std::make_shared<OutputBuffer>();
    outputBuffer->clear();
}
void Drawer::drawNode(const std::shared_ptr<JsonNode>& jsonNode, 
                      const std::string& selfLink, 
                      const std::string& childLink) 
{
    OutputLine line(jsonNode);
    line.addElement(selfLink);
    line.addElement(defaultIcon);
    line.addElement(jsonNode->drawContent());
    outputBuffer->addLine(line);

    for (const auto& child : jsonNode->getChildren()) {
        if (child == jsonNode->getChildren().back())
            drawNode(child, childLink + branchEnd, childLink + verticalEnd + defaultIcon);
        else
            drawNode(child, childLink + branch, childLink + vertical + defaultIcon);
    }
}
void Drawer::drawDecorate() {
    // Default implementation: no special decoration
}
void Drawer::drawIcon() {
    // Default implementation: leafIcon, ContainerIcon
    for (auto &line : outputBuffer->getLines()) {
        auto &jsonNode = line.getJsonNode();

        // if (jsonNode->getLevel() == 0) { // unexpected
        //     throw std::runtime_error("Root node should not be drawn.");
        // }

        if (jsonNode->getIsLeaf()) {
            line.getElements()[1] = leafIcon;
        } else {
            line.getElements()[1] = ContainerIcon;
        }
    }
}


// TreeDrawer
void TreeDrawer::drawDecorate() {
    // Remove the root line
    if (!outputBuffer->getLines().empty()) {
        outputBuffer->getLines().erase(outputBuffer->getLines().begin());
    }
}


// RectDrawer
void RectDrawer::drawNode(const std::shared_ptr<JsonNode>& jsonNode, 
                          const std::string& selfLink, 
                          const std::string& childLink) 
{
    OutputLine line(jsonNode);
    line.addElement(selfLink);
    line.addElement(defaultIcon);
    auto content = jsonNode->drawContent();
    line.addElement(content);

    // Add horizontal lines to match the maximum line length
    int maxLen = 60; // TODO 实现
    int sumLen = jsonNode->getLevel() * indentLen + content.length();
    std::string rightIndent = " ";
    if (maxLen > sumLen) {
        for (int i = 0; i < maxLen - sumLen; i += 1)
            rightIndent += "─"; // 可提取为成员变量
    }
    line.addElement(rightIndent);

    line.addElement("┤"); // 可提取为成员变量
    outputBuffer->addLine(line);

    for (const auto& child : jsonNode->getChildren()) {
        if (child == jsonNode->getChildren().back())
            drawNode(child, childLink + branchEnd, childLink + verticalEnd + defaultIcon);
        else
            drawNode(child, childLink + branch, childLink + vertical + defaultIcon);
    }
}
void RectDrawer::drawDecorate() {
    // Remove the root line
    if (!outputBuffer->getLines().empty()) {
        outputBuffer->getLines().erase(outputBuffer->getLines().begin());
    }
    // 替换首行末行的字符
    if (!outputBuffer->getLines().empty()) {
        auto &firstLine = outputBuffer->getLines().front();
        firstLine.getElements()[0] = "┌─";
        firstLine.getElements().back() = "┐";
    }
    if (outputBuffer->getLines().size() > 1) {
        auto &lastLine = outputBuffer->getLines().back();
        lastLine.getElements().back() = "┘";

        // 第二个元素是 icon，替换为 "✩"
        lastLine.getElements()[1] = "✩";
        
        // 全部替换为封闭字符
        auto &jsonNode = lastLine.getJsonNode();
        std::string indents = "└─";
        int numIndent = jsonNode->getLevel();
        for (int i = 0; i < numIndent - 1; i += 1) {
            indents += "─┴─";
        }
        lastLine.getElements()[0] = indents;
    }
}
