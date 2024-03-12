//
// Created by Zhang Fan on 2022-12-21.
//

#ifndef BONUS_QUEMAP_H
#define BONUS_QUEMAP_H
#include <queue>
#include <map>
#include <utility>

template <typename keyType, typename valueType>
class QueMap {
private:
    std::queue<keyType> queue;
    std::map<keyType, valueType> map;

public:
    bool empty();
    std::pair<keyType, valueType> front();
    std::pair<keyType, valueType> pop();
    void push(keyType, valueType);
    bool isKeyNew(keyType key);
    void update(keyType key, valueType value);
    unsigned int size();
    QueMap();
};

template<typename keyType, typename valueType>
std::pair<keyType, valueType> QueMap<keyType, valueType>::front() {
    keyType key = queue.front();
    std::pair<keyType, valueType> keyValuePair = std::pair<keyType, valueType>{key, map[key]};
    return  keyValuePair;
}

template<typename keyType, typename valueType>
QueMap<keyType, valueType>::QueMap() {
    this->queue = std::queue<keyType>();
    this->map = std::map<keyType, valueType>();
}

template<typename keyType, typename valueType>
void QueMap<keyType, valueType>::push(keyType key, valueType value) {
    queue.push(key);
    map[key] = value;
}

template<typename keyType, typename valueType>
std::pair<keyType, valueType> QueMap<keyType, valueType>::pop() {
    keyType key = queue.front();
    queue.pop();
    std::pair<keyType, valueType> keyValuePair = std::pair<keyType, valueType>{key, map[key]};
    map.erase(key);
    return  keyValuePair;
}

template<typename keyType, typename valueType>
bool QueMap<keyType, valueType>::empty() {
    return queue.empty();
}

template<typename keyType, typename valueType>
bool QueMap<keyType, valueType>::isKeyNew(keyType key) {
    return (map.find(key) == map.end());
}

template<typename keyType, typename valueType>
void QueMap<keyType, valueType>::update(keyType key, valueType value) {
    map[key] = value;
}

template<typename keyType, typename valueType>
unsigned int QueMap<keyType, valueType>::size() {
    return queue.size();
}


#endif //BONUS_QUEMAP_H
