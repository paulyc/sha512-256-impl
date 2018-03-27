//
//  types.hpp
//  sha512-256-impl
//
//  Created by Paul Ciarlo on 3/21/18.
//  Copyright © 2018 Paul Ciarlo. All rights reserved.
//

#ifndef types_hpp
#define types_hpp

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

namespace sw { namespace detail {

typedef uint64_t binary_512_t[8];
typedef uint64_t binary_256_t[4];
typedef std::basic_string<uint8_t> binary_string;

class HexStringOutput {
public:
    static std::string format(const uint8_t *const in_, unsigned len_bytes) {
        std::ostringstream ss; // hex string
        ss << std::hex << std::setfill('0') << std::setw(2);
        for (unsigned i = 0; i < len_bytes; ++i) {
          ss << in_[i];
        }
        return ss.str();
    }
    static std::string truncate(std::string in_, unsigned out_bytes) {
        return in_.substr(0, out_bytes*2);
    }
};

class BinaryStringOutput {
public:
    static binary_string format(const uint8_t *const in_, unsigned len_bytes) {
        binary_string out;
        out.resize(len_bytes);
        for (unsigned i = 0; i < len_bytes; ++i) {
            out[i] = in_[i];
        }
        return out;
    }
    static binary_string truncate(binary_string in_, unsigned out_bytes) {
        return in_.substr(0, out_bytes);
    }
};

} }

#include "types.cpp"

#endif /* types_hpp */
