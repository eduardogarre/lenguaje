#pragma once

#include <cassert>

namespace Ñ
{
    template<typename T>
    void pop_front(std::vector<T>& vec)
    {
        assert(!vec.empty());
        vec.erase(vec.begin());
    }
}