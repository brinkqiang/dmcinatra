#ifndef __DMSTL_H_INCLUDE__
#define __DMSTL_H_INCLUDE__

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <functional>

template<typename container>
inline void
    dm_print_container(const container& c)
{
    std::copy(c.begin(), c.end(), std::ostream_iterator<typename container::value_type>(std::cout, std::endl));
}

template<typename DataType, typename FieldType>
inline
    std::vector<DataType*>
    dm_match(FieldType& (DataType::*poField)(), FieldType oValue, std::vector<DataType>& RawData)
{
    std::vector<DataType*> vecData;

    for (int i=0; i < static_cast<int>(RawData.size()); ++i)
    {
        DataType*poDataType = &RawData[i];
        if ((poDataType->*poField)() == oValue)
        {
            vecData.push_back(poDataType);
        }
    }

    return vecData;
}

template<typename T>
size_t dm_size(T* start, T* end)
{
    return std::distance(start, end) + 1;
}

template<typename T>
inline void dm_resize(T& in)
{
    T tmp(in);
    std::swap(in, tmp);
}

#endif // __DMSTL_H_INCLUDE__
