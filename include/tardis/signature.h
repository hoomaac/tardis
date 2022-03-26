/**
* @author humac (hoomaac@gmail.com)
* @date 2022-03-25
*
* @copyright Copyright (c) 2022 by humac <hoomaac@gmail.com>
*/

#ifndef INCLUDE_TARDIS_SIGNATURE_H_
#define INCLUDE_TARDIS_SIGNATURE_H_


#include <string>
#include <vector>
#include <fstream>

#include <libFlatBuf/packfile_generated.h>

#include "tardis/checksum.h"


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

}  // namespace tardis


#endif  // INCLUDE_TARDIS_SIGNATURE_H_
