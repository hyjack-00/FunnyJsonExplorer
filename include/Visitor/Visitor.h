#ifndef VISITOR_H
#define VISITOR_H

#include "JsonCollection/JsonTree.h"

class TreeVisitor {
private:

public:
    virtual void visit(JsonLeaf *leaf) = 0;
    virtual void visit(JsonContainer *cont) = 0; 
};

#endif // VISITOR_H