#ifndef VECTOR_TO_MAP_WITH_ID_H
#define VECTOR_TO_MAP_WITH_ID_H

#include "helpers/id_counter.h"

#include <unordered_map>
#include <vector>

template<class T>
concept has_getId = requires(T t) {
    { t->getId() } -> std::same_as<ID>;
};

namespace helpers
{

template<has_getId T>
std::unordered_map<ID, T> vector_to_map_with_id(const std::vector<T> &v)
{
    std::unordered_map<ID, T> m;
    for (auto& el : v)
    {
        m.insert(std::make_pair(el->getId(), el));
    }
    return m;
}


template<has_getId T>
std::vector<T> map_with_id_to_vector(const std::unordered_map<ID, T> &m)
{
    std::vector<ID, T> v;
    for (auto& it = m.begin(); it < m.end(); it++)
    {
        v.push_back(it->second);
    }
    return v;
}

}


#endif // VECTOR_TO_MAP_WITH_ID_H
