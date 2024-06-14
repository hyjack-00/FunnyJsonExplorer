#ifndef VISITOR_H
#define VISITOR_H


class JsonLeaf;
class JsonContainer;

class TreeVisitor {
private:

public:
    virtual void visit(const JsonLeaf *leaf) = 0;
    virtual void visit(const JsonContainer *cont) = 0; 
};

#endif // VISITOR_H