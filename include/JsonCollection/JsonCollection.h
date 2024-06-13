#ifndef JSON_COLLECTION_H
#define JSON_COLLECTION_H

#include <string>

class JsonCollection {
private:

public:
    JsonCollection() = default;
    ~JsonCollection() = default;

    virtual void readJson(const std::string &filePath) = 0;
    virtual void clearJson() = 0;
};

#endif // JSON_COLLECTION_H