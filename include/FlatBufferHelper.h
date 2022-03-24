#ifndef FLAT_BUFFER_HELPER_H_
#define FLAT_BUFFER_HELPER_H_


#include <libFlatBuf/packfile_generated.h>

namespace tardis::flatbuf
{

using FlatBufferBuilder = flatbuffers::FlatBufferBuilder;

template<typename T>
using FlatBufferType = flatbuffers::Offset<T>;

template<typename T>
struct Convertible 
{
    using FlatType = T;
    virtual inline FlatBufferType<FlatType> to_flatbuffer(FlatBufferBuilder& builder) const noexcept = 0;
};


struct Serializer
{
    FlatBufferBuilder& serialize() const noexcept;
};


}

#endif