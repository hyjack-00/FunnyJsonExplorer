#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

#include "utils.h"


struct Link {
    std::string branch;
    std::string vertical;
    std::string branchEnd;
    std::string verticalEnd; 
    // 2字符展示，但是实际 utf-8 长度更长
    int actualLinkLen;
    int linkLen;

    std::string linkIcon;
    int actualIconLen;
    int iconLen;

public:
    Link() {}

    void setLink(
        std::string& branch, std::string& vertical, 
        std::string& branchEnd, std::string& verticalEnd, 
        std::string& linkIcon, int linkLen, int iconLen) 
    {
        this->branch = branch;
        this->vertical = vertical;
        this->branchEnd = branchEnd;
        this->verticalEnd = verticalEnd;
        this->linkIcon = linkIcon;
        this->linkLen = linkLen;
        this->iconLen = iconLen;

        actualLinkLen = branch.size();

        actualIconLen = linkIcon.size();
    }

    /* 判断 indent 末尾是：
        branch 还是 branchEnd
        vertical 还是 verticalEnd 
    */
    bool isEndLink(std::string &link) {
        return link == branchEnd || link == verticalEnd;
    } 

    /* 如果 level 增加：
        替换 indent 最右侧的 branch* -> vertical*，
        增加一级 linkIcon + branch*
    */
    void stepIn(std::string &indent, bool isEnd) {
        // 替换
        if (indent.size() > 0) {
            std::string lastLink = indent.substr(indent.size() - actualLinkLen);
            bool isFormerEnd = isEndLink(lastLink);

            indent = indent.substr(0, indent.size() - actualLinkLen);
            if (isFormerEnd) indent += verticalEnd;
            else             indent += vertical;
        }

        // 增加
        indent += linkIcon;
        if (isEnd) indent += branchEnd;
        else       indent += branch;
        DEBUG_PRINT("New indent = '%s'", indent.c_str());
    } 

    /* 如果 level 减小：
        减少一级 linkIcon + branch*，
        替换 indent 最右侧的 vertical* -> branch*
    */
    void stepOut(std::string &indent) {
        // 减少
        indent = indent.substr(0, indent.size() - actualLinkLen - actualIconLen);
        
        // 替换
        if (indent.size() > 0) {
            std::string lastLink = indent.substr(indent.size() - actualLinkLen);
            bool isEnd = isEndLink(lastLink);

            indent = indent.substr(0, indent.size() - actualLinkLen);
            if (isEnd) indent += branchEnd;
            else       indent += branch;
        }
        DEBUG_PRINT("New indent = '%s'", indent.c_str());
    }
};


#endif // SYMBOL_H