#pragma once

#include <random>
#include <type_traits>

namespace math
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type
        rand(T min, T max)
    {
        assert(max >= min && "Maximum value cannot be less than minimum value.");
        std::uniform_int_distribution<T> dist(min, max);
        return dist(gen);
    }

    template<typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type
        rand(T min, T max)
    {
        assert(max >= min && "Maximum value cannot be less than minimum value.");
        std::uniform_real_distribution<T> dist(min, max);
        return dist(gen);
    }
}