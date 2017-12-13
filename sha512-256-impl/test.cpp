#include "crc.h"
#include "md5.h"
#include "sha1.h"
#include "sha512-256.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, const char* argv[])
{
  // Any kind of data example data types
  struct {
    char bytes[100];
    int something;
    unsigned long whatever;
  } data;
 
  string path = "/home/me/a-file";
 
  /////////////////////////////////////////////////////////////
  // SHA1, SHA512 and MD5 static functions return the checksum
  // as hex string.
 
  // String
  cout << sw::sha1::calculate("SHA of std::string") << endl;
 
  // Binary data (void*, size_t)
  cout << sw::sha1::calculate(&data, sizeof(data)) << endl;
 
  // File checksum
  cout << sw::sha1::file(path) << endl;
 
  // Streams (std::istream &) aer possible, too
  std::stringstream ss("SHA of std::stringstream");
  cout << sw::sha1::calculate(ss) << endl;
 
  // The same with md5 and sha512
  cout << sw::md5::calculate("MD5 of std::string") << endl;
  cout << sw::sha512::calculate("SHA512 of std::string") << endl;
  cout << sw::sha512::file(path) << endl;
  cout << sw::sha512::calculate(&data, sizeof(data)) << endl;
  // etc, etc.
  
  /*
The 256 bytes message (represented as
a sequence of bytes; byte 0 is first,
byte 255 is last):
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f
10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f
20 21 22 23 24 25 26 27 28 29 2a 2b 2c 2d 2e 2f
30 31 32 33 34 35 36 37 38 39 3a 3b 3c 3d 3e 3f
40 41 42 43 44 45 46 47 48 49 4a 4b 4c 4d 4e 4f
50 51 52 53 54 55 56 57 58 59 5a 5b 5c 5d 5e 5f
60 61 62 63 64 65 66 67 68 69 6a 6b 6c 6d 6e 6f
70 71 72 73 74 75 76 77 78 79 7a 7b 7c 7d 7e 7f
80 81 82 83 84 85 86 87 88 89 8a 8b 8c 8d 8e 8f
90 91 92 93 94 95 96 97 98 99 9a 9b 9c 9d 9e 9f
a0 a1 a2 a3 a4 a5 a6 a7 a8 a9 aa ab ac ad ae af
b0 b1 b2 b3 b4 b5 b6 b7 b8 b9 ba bb bc bd be bf
c0 c1 c2 c3 c4 c5 c6 c7 c8 c9 ca cb cc cd ce cf
d0 d1 d2 d3 d4 d5 d6 d7 d8 d9 da db dc dd de df
e0 e1 e2 e3 e4 e5 e6 e7 e8 e9 ea eb ec ed ee ef
f0 f1 f2 f3 f4 f5 f6 f7 f8 f9 fa fb fc fd fe ff
The SHA-512/256 hash value (before
truncation):
h0 = 4ff7ecb3e7c23b55
h1 = 9974eba17a3d1a62
h2 = 0504f18be2e472ea
h3 = c5c5cbf75b3b7550
h4 = 27a8af7dc7dc9845
h5 = 8cfc76997dc50cfd
h6 = f4f500cc1830f561
h7 = bf2abd3732fdf66a
The SHA512/256 hash value (256 bits):
h0 = 4ff7ecb3e7c23b55
h1 = 9974eba17a3d1a62
h2 = 0504f18be2e472ea
h3 = c5c5cbf75b3b7550
For comparison, the SHA-512 hash value
of the same message is:
h0 = 1e7b80bc8edc552c
h1 = 8feeb2780e111477
h2 = e5bc70465fac1a77
h3 = b29b35980c3f0ce4
h4 = a036a6c946203682
h5 = 4bd56801e62af7e9
h6 = feba5c22ed8a5af8
h7 = 77bf7de117dcac6d
*/
  char message[256];
  for (int i = 0; i <= 255; ++i) {
    message[i] = (char)i;
  }
  
  sw::sha512::str_t hash = sw::sha512_256::calculate(message, 256);
  cout << "welp this is the whole sha512-256: " << hash << endl;
  for (int h = 0; h < 4; ++h) {
    cout << "so h" << h << " = " << hash.substr(h*16,16) << endl;
  }
  
  /////////////////////////////////////////////////////////////
  // CRC returns a number, not a hex string
  // crc16: uint16_t, crc32: uint32_t
  // `stream` function and `file` function are not exported.
  cout << sw::crc16::calculate("CRC16 of std::string") << endl;
  cout << sw::crc32::calculate("CRC32 of std::string") << endl;
  cout << sw::crc16::calculate(&data, sizeof(data)) << endl;
  cout << sw::crc32::calculate(&data, sizeof(data)) << endl;
  return 0;
}
