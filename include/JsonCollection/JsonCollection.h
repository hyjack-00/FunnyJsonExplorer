#ifndef JSON_COLLECTION_H
#define JSON_COLLECTION_H

#include <string>
#include <memory>

// 抽象元素
class JsonElement {

};

// 抽象迭代器
class JsonIterator {
private:
    // 子类自行定义对应的 collection 及其遍历方法

public:
    virtual ~JsonIterator() = default;

    virtual bool hasMore() const = 0;
    virtual const JsonElement* getNext() = 0;
};

// 抽象集合
class JsonCollection {
private:
    // 子类自行定义存放 JsonElement 的数据结构

public:
    virtual ~JsonCollection() = default;

    virtual void readJson(const std::string &filePath) = 0;
    virtual void clearJson() = 0;

    virtual JsonIterator* createIterator() = 0;
};

#endif // JSON_COLLECTION_H