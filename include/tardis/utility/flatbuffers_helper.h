/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_UTILITY_FLATBUFFERS_HELPER_H_
#define INCLUDE_TARDIS_UTILITY_FLATBUFFERS_HELPER_H_


#include <libFlatBuf/packfile_generated.h>

namespace tardis::flatbuf
{

using FlatBufferBuilder = flatbuffers::FlatBufferBuilder;

template<typename T>
using FlatBufferType = flatbuffers::Offset<T>;

/**
 * @brief Every class that can convert to flatbuffers class should implement this interface.
 * 
 * @tparam T Flatbuffers type
 */
template<typename T>
struct Convertible
{
    using FlatType = T;
    /**
     * @brief Serialized a class which has implemened @c Convertible interface
     * 
     * @param builder flatbuffers::FlatBufferBuilder
     * 
     * @return Returns flatbuffers::Offset<T>
     */
    virtual inline FlatBufferType<FlatType> to_flatbuffer(FlatBufferBuilder& builder) const noexcept = 0;
};


}  // namespace tardis::flatbuf


#endif  // INCLUDE_TARDIS_UTILITY_FLATBUFFERS_HELPER_H_
