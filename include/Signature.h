#ifndef SIGNATURE_H_
#define SIGNATURE_H_

#include <string_view>
#include <fstream>

#include <libFlatBuf/packfile_generated.h>

#include "Checksum.h"



namespace tardis
{

template<ChecksumType checksumType>
inline uint32_t sig_calculate(const std::string& buffer)
{
    CheckSum<checksumType> cs;
    return cs.calculate(buffer);
}

constexpr inline auto weak_sig_calculate = sig_calculate<ChecksumType::WEAK>;
constexpr inline auto strong_sig_calculate = sig_calculate<ChecksumType::STRONG>;

/// @brief sign each block of a file
std::vector<uint32_t> sign_file(const std::string& path);

}

#endif