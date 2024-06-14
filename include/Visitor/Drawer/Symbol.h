#ifndef SYMBOL_H
#define SYMBOL_H

#include <cstddef>
#include <string>
#include <vector>

#include "utils.h"


struct LinkType {
    enum T {
        Branch,     // 00
        Vertical,   // 01 
        BranchEnd,  // 10
        VerticalEnd,// 11
        other
    };

    static bool isVerticalLink(LinkType::T linkType) {
        return (int)linkType & 1;
    }
    static bool isEndLink(LinkType::T linkType) {
        return (int)linkType & 2;
    }
    static T toBranch(LinkType::T linkType)   { return (T)((int)linkType & 2); }
    static T toVertical(LinkType::T linkType) { return (T)((int)linkType | 1); }
    static T toEnd(LinkType::T linkType)      { return (T)((int)linkType | 2); }
    static T toNoEnd(LinkType::T linkType)    { return (T)((int)linkType & 1); }
};


struct Link {
private:
    // 4: branch, vertical, branchEnd, verticalEnd
    std::vector<std::string> links;
    // 非实际长度
    int linkLen;

public:
    Link() = default;
    Link(std::string& branch, std::string& vertical, 
         std::string& branchEnd, std::string& verticalEnd, int linkLen) 
         : linkLen(linkLen), 
           links{branch, vertical, branchEnd, verticalEnd} {}

    std::string getLink(LinkType::T linkType) const {
        return links[(int)linkType];
    }
    int getLinkLen() const {
        return linkLen;
    }

    /* 
        逐个匹配几个 link，从右侧匹配逐个字符匹配
    */
    LinkType::T getLastLinkType(std::string &indent) {
        for (int ty = 0; ty < links.size(); ty++) {
            std::string& link = links[ty];
            if (indent.size() < link.size()) continue; 

            for (int i = 0; i < linkLen; i++) {
                if (indent[indent.size() - linkLen + i] != link[i]) {
                    break;
                }
            }
            return (LinkType::T)ty;
        }
        return LinkType::other;
    }

    /* 如果 level 增加：
        替换最外一级 branch* -> vertical*，
        增加一级 branch*
    */
    void stepIn(std::string &indent, bool isEnd) {
        // 替换
        if (indent.size() > 0) {
            auto lastLinkType = getLastLinkType(indent);
            int actualLen = getLink(lastLinkType).size();
            indent = indent.substr(0, indent.size() - actualLen);

            // bool islastLinkEnd = LinkType::isEndLink(lastLinkType);
            // if (islastLinkEnd) indent += getLink(LinkType::VerticalEnd);
            // else               indent += getLink(LinkType::Vertical);
            indent += getLink(LinkType::toVertical(lastLinkType));
        }

        // 增加
        indent += getLink(
            isEnd ? LinkType::BranchEnd : LinkType::Branch
        );
        DEBUG_PRINT("New indent = '%s'", indent.c_str());
    } 

    /* 如果 level 减小：
        减少一级 branch*，
        替换最外一级 vertical* -> branch*
    */
    void stepOut(std::string &indent) {
        DEBUG_PRINT("indent-0 '%s'", indent.c_str());
        // 减少
        if (indent.size() > 0) {
            auto lastLinkType = getLastLinkType(indent);
            int actualLinkLen = getLink(lastLinkType).size();
            indent = indent.substr(0, indent.size() - actualLinkLen);
        }
        DEBUG_PRINT("indent-1 '%s'", indent.c_str());
        
        // 替换
        if (indent.size() > 0) {
            auto lastLinkType = getLastLinkType(indent);
            int actualLinkLen = getLink(lastLinkType).size();
            indent = indent.substr(0, indent.size() - actualLinkLen);

            // bool islastLinkEnd = LinkType::isEndLink(lastLinkType);
            // if (islastLinkEnd) indent += getLink(LinkType::BranchEnd);
            // else               indent += getLink(LinkType::Branch);
            indent += getLink(LinkType::toBranch(lastLinkType));
        }
        DEBUG_PRINT("New indent = '%s'", indent.c_str());
    }
};


#endif // SYMBOL_H