#ifndef GLOBAL_H
#define GLOBAL_H

#include <bits/stdc++.h>

template <typename T> std::string printId (T begin, T end, std::string separator = ", ") {
    std::stringstream ss;
    for(T tmp = begin; tmp != end; ++tmp) {
        if(tmp != begin) ss << separator;
        ss << (*tmp).getId();
    }
    if (begin == end)
        ss << "Kosong";
    return ss.str();
}

template <typename T> std::string print (T begin, T end, std::string separator = "\n") {
    std::stringstream ss;
    for(T tmp = begin; tmp != end; ++tmp) {
        if(tmp != begin) ss << separator;
        ss << (*tmp);
    }
    if (begin == end)
        ss << "Kosong";
    return ss.str();
}

template <typename T> std::string printIdPtr (T begin, T end, std::string separator = ", ") {
    std::stringstream ss;
    for(T tmp = begin; tmp != end; ++tmp) {
        if(tmp != begin) ss << separator;
        ss << (*tmp)->getId();
    }
    if (begin == end)
        ss << "Kosong";
    return ss.str();
}

template <typename T> std::string printPtr (T begin, T end, std::string separator = "\n") {
    std::stringstream ss;
    for(T tmp = begin; tmp != end; ++tmp) {
        if(tmp != begin) ss << separator;
        ss << *(*tmp);
    }
    if (begin == end)
        ss << "Kosong";
    return ss.str();
}

#endif // GLOBAL_H