#pragma once

#include <cassert>
#include <vector>

namespace Ñ
{
    template<typename T>
    void pop_front(std::vector<T>& vec)
    {
        assert(!vec.empty());
        vec.erase(vec.begin());
    }

    inline int64_t potencia(int64_t x, uint64_t p)
    {
        if (p == 0)
        {
            return 1;
        }
        if (p == 1)
        {
            return x;
        }

        int64_t tmp = potencia(x, p/2);

        if (p%2 == 0)
        {
            return tmp * tmp;
        }
        else
        {
            return x * tmp * tmp;
        }
    }
}