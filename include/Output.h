#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <vector>
#include "JsonTree.h"

class OutputLine {
private:
    std::vector<std::string> elements;
    std::shared_ptr<JsonNode> jsonNode;

public:
    OutputLine(const std::shared_ptr<JsonNode>& jsonNode) 
        : jsonNode(jsonNode) {}
    void addElement(const std::string& element);
    std::vector<std::string>& getElements();
    const std::shared_ptr<JsonNode>& getJsonNode() const;
};

class OutputBuffer {
private:
    std::vector<OutputLine> lines;

public:
    void addLine(const OutputLine& line);
    std::vector<OutputLine>& getLines();
    void clear();
    void print() const;
};

#endif // OUTPUT_H
