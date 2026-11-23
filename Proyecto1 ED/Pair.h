#pragma once
#include <iostream>


template <typename K, typename V>
class Pair;

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Pair<K, V>& p);

template <typename K, typename V>
class Pair {
public:
    K key;
    V value;

    Pair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    Pair(K key) {
        this->key = key;
    }

    Pair() {}

    bool operator==(const Pair<K, V>& other) const {
        return key == other.key;
    }

    bool operator<(const Pair<K, V>& other) const {
        return key < other.key;
    }

    bool operator<=(const Pair<K, V>& other) const {
        return key <= other.key;
    }

    bool operator>(const Pair<K, V>& other) const {
        return key > other.key;
    }

    bool operator>=(const Pair<K, V>& other) const {
        return key >= other.key;
    }

    bool operator!=(const Pair<K, V>& other) const {
        return key != other.key;
    }


    friend std::ostream& operator<< <K, V>(std::ostream& os, const Pair<K, V>& other);
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Pair<K, V>& other) {
    os << "(" << other.key << ", " << other.value << ")";
    return os;
}