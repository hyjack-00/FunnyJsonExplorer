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
        drawLine(node);
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
    DEBUG_PRINT("TO DRAW NODE %s", jsonNode->getName().c_str());

    int level = jsonNode->getLevel();
    if (level == currentLevel) {
        DEBUG_PRINT("level == %s", "");
    } 
    else if (level == currentLevel + 1) {
        DEBUG_PRINT("level += %d", 1);
        // bool isLastChild = JsonTree::isLastChild(jsonNode);
        // DEBUG_PRINT("isLastChild 1.fromFather = %d, 2.fromIter = %d", isLastChild, currentIsLastChild);
        link.stepIn(currentIndent, currentIsLastChild);
        currentLevel = level;
    } 
    else if (level < currentLevel) {
        int skipLevel = currentLevel - level;
        DEBUG_PRINT("level -= %d", skipLevel);
        while (skipLevel-- > 0)
            link.stepOut(currentIndent);
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

    outputBuffer->addLine(currentLine);
}

void Drawer::drawIcon(const std::shared_ptr<JsonNode> jsonNode) {
    jsonNode->accept(*this);
}
void Drawer::drawDecorate() {
    // Default implementation: no special decoration
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




// // TreeDrawer
// void TreeDrawer::drawDecorate() {
//     // Remove the root line
//     if (!outputBuffer->getLines().empty()) {
//         outputBuffer->getLines().erase(outputBuffer->getLines().begin());
//     }
// }


// // RectDrawer
// void RectDrawer::drawNode(const std::shared_ptr<JsonNode>& jsonNode, 
//                           const std::string& selfLink, 
//                           const std::string& childLink) 
// {
//     OutputLine line(jsonNode);
//     line.addElement(selfLink);
//     line.addElement(linkIcon);
//     auto content = jsonNode->drawContent();
//     line.addElement(content);

//     // Add horizontal lines to match the maximum line length
//     int maxLen = 60; // TODO 实现
//     int sumLen = jsonNode->getLevel() * indentLen + content.length();
//     std::string rightIndent = " ";
//     if (maxLen > sumLen) {
//         for (int i = 0; i < maxLen - sumLen; i += 1)
//             rightIndent += "─"; // 可提取为成员变量
//     }
//     line.addElement(rightIndent);

//     line.addElement("┤"); // 可提取为成员变量
//     outputBuffer->addLine(line);

//     for (const auto& child : jsonNode->getChildren()) {
//         if (child == jsonNode->getChildren().back())
//             drawNode(child, childLink + branchEnd, childLink + verticalEnd + linkIcon);
//         else
//             drawNode(child, childLink + branch, childLink + vertical + linkIcon);
//     }
// }
// void RectDrawer::drawDecorate() {
//     // Remove the root line
//     if (!outputBuffer->getLines().empty()) {
//         outputBuffer->getLines().erase(outputBuffer->getLines().begin());
//     }
//     // 替换首行末行的字符
//     if (!outputBuffer->getLines().empty()) {
//         auto &firstLine = outputBuffer->getLines().front();
//         firstLine.getElements()[0] = "┌─";
//         firstLine.getElements().back() = "┐";
//     }
//     if (outputBuffer->getLines().size() > 1) {
//         auto &lastLine = outputBuffer->getLines().back();
//         lastLine.getElements().back() = "┘";

//         // // 第二个元素是 icon，替换为 "✩"
//         // lastLine.getElements()[1] = "✩";
        
//         // 全部替换为封闭字符
//         auto &jsonNode = lastLine.getJsonNode();
//         std::string indents = "└─";
//         int numIndent = jsonNode->getLevel();
//         for (int i = 0; i < numIndent - 1; i += 1) {
//             indents += "─┴─";
//         }
//         lastLine.getElements()[0] = indents;
//     }
// }
// void RectDrawer::drawIcon() {
//     for (auto &line : outputBuffer->getLines()) {
//         auto &jsonNode = line.getJsonNode();

//         if (jsonNode->getIsLeaf()) {
//             line.getElements()[1] = leafIcon;
//         } else {
//             line.getElements()[1] = containerIcon;
//         }
//     }

//     auto &lastLine = outputBuffer->getLines().back();
//     if (lastLine.getElements()[1] == " ")
//         lastLine.getElements()[1] = "✩";
// }