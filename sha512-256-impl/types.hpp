//Copyright (C) 2018 Paul Ciarlo
//
//Redistribution and use in source and binary forms, with or without
//modification, are permitted provided that the following conditions are met:
//
//* Redistributions of source code must retain the above copyright notice, this
//  list of conditions and the following disclaimer.
//
//* Redistributions in binary form must reproduce the above copyright notice,
//  this list of conditions and the following disclaimer in the documentation
//  and/or other materials provided with the distribution.
//
//* Neither the name of the copyright holder nor the names of its
//  contributors may be used to endorse or promote products derived from
//  this software without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
//FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
//DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
//CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
//OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

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
