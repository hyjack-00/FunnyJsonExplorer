#include "Output/TreeOutput.h"
#include <iostream>

// OutputLine 方法实现
void OutputLine::addElement(const std::string& element) {
    elements.push_back(element);
}
std::vector<std::string>& OutputLine::getElements() {
    return elements;
}
const std::shared_ptr<JsonNode>& OutputLine::getJsonNode() const {
    return jsonNode;
}


// OutputBuffer 方法实现
void OutputBuffer::addLine(const OutputLine& line) {
    lines.push_back(line);
}
void OutputBuffer::clear() {
    lines.clear();
}
std::vector<OutputLine>& OutputBuffer::getLines() {
    return lines;
}
void OutputBuffer::print() const {
    for (auto line : lines) {
        for (auto elem : line.getElements()) {
            std::cout << elem;
        }
        std::cout << std::endl;
    }
}
