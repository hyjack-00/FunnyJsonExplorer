#ifndef JSON_COLLECTION_H
#define JSON_COLLECTION_H

#include <string>
#include <memory>


// 抽象只读迭代器，必须返回 const 元素
template<typename ElementType>
class JsonIterator {
private:
    // 子类自行定义对应的 collection 及其遍历方法

public:
    virtual ~JsonIterator() = default;

    virtual bool hasMore() const = 0;
    virtual const std::shared_ptr<ElementType> getNext() = 0;
};

// 抽象集合
template<typename ElementType>
class JsonCollection {
private:
    // 子类自行定义存放 JsonElement 的数据结构

public:
    virtual ~JsonCollection() = default;

    virtual void readJson(const std::string &filePath) = 0;
    virtual void clearJson() = 0;

    virtual std::unique_ptr<JsonIterator<ElementType>> createIterator() const = 0;
};

#endif // JSON_COLLECTION_H