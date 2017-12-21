#include "crc.h"
#include "md5.h"
#include "sha1.h"
//OOPS- TODO
//#include "sha256.h"
#include "sha512.h"
#include "sha512-256.h"
#include <iostream>
#include <sstream>

using namespace std;

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>

#pragma pack(0)

class TestSHA1 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestSHA1 );
  CPPUNIT_TEST( testString );
  CPPUNIT_TEST( testBinary );
  CPPUNIT_TEST( testFile );
  CPPUNIT_TEST( testStream );
  CPPUNIT_TEST_SUITE_END();

  struct {
    char bytes[12];
    int32_t something;
    uint64_t whatever;
  } data;

  const char *filename = "./testfile.bin";

public:
  void setUp() {
    memset(data.bytes, sizeof(data), 0);
    strncpy(data.bytes, "astring", sizeof(data.bytes));
    data.something = -1;
    data.whatever = 0xdeadbeefdeadbeef;
  }
  void tearDown() {}

  void testString() {
    std::string sum = sw::sha1::calculate("SHA of std::string");
    CPPUNIT_ASSERT_EQUAL(std::string("170047a4105993814a3f8be7d81c4e8b32b04fac"), sum);
  }

  void testBinary() {
    // sha1sum of unsigned char * data = "astring\0\0\0\xff\xff\xff\xff\xef\xbe\xad\xde"
    // see
    std::string sum = sw::sha1::calculate(&data, sizeof(data));
    CPPUNIT_ASSERT(sizeof(data) == 24); // if not, it put some padding in which will break our shit
    CPPUNIT_ASSERT_EQUAL(std::string("0c84741e541483554d37836c5af3df1e00ef8e3a"), sum);
  }

  void testFile() {
    std::string sum = sw::sha1::file(filename);
    CPPUNIT_ASSERT_EQUAL(std::string("0c84741e541483554d37836c5af3df1e00ef8e3a"), sum);
  }

  void testStream() {
    std::stringstream ss("SHA of std::stringstream");
    std::string sum = sw::sha1::calculate(ss);
    CPPUNIT_ASSERT_EQUAL(std::string("4358fb61f10b4fb308e2573eac6c262b06506c8f"), sum);
  }
};

class TestMD5 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestMD5 );
  CPPUNIT_TEST( testString );
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp() {}
  void tearDown() {}

  void testString() {
    std::string sum = sw::md5::calculate("MD5 of std::string");
    CPPUNIT_ASSERT_EQUAL(std::string("bd8c5c60bd9ec82e38aec2112d661a59"), sum);
  }
};

/**
 *
 * TODO - FIGURE OUT THE ANSWERS TO THIS
 *
class TestCRC : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestCRC );
  CPPUNIT_TEST( testCRC );
  CPPUNIT_TEST( testString16 );
  CPPUNIT_TEST( testString32 );
  CPPUNIT_TEST_SUITE_END();

  struct {
    char bytes[10];
    int something;
    unsigned long whatever;
  } data;

public:
  void setUp() {
    memset(data.bytes, sizeof(data), 0);
    strncpy(data.bytes, "astring", sizeof(data.bytes));
    data.something = -1;
    data.whatever = 0xdeadbeef;
  }
  void tearDown() {}
 
  void testCRC() {
    /////////////////////////////////////////////////////////////
    // CRC returns a number, not a hex string
    // crc16: uint16_t, crc32: uint32_t
    // `stream` function and `file` function are not exported.
    uint16_t crc16 = sw::crc16::calculate("CRC16 of std::string");
    uint32_t crc32 = sw::crc32::calculate("CRC32 of std::string");
    crc16 = sw::crc16::calculate(&data, sizeof(data));
    crc32 = sw::crc32::calculate(&data, sizeof(data));
  }

  void testString16() {
    uint16_t sum = sw::crc16::calculate("CRC16 of std::string");
    CPPUNIT_ASSERT_EQUAL((uint16_t)0xfefe, sum);
  }

  void testString32() {
    uint32_t sum = sw::crc32::calculate("CRC32 of std::string");
    CPPUNIT_ASSERT_EQUAL(0xfefefefe, sum);
  }
};
 *
 *
 **/

/**
 *
 * OOPS - TODO
 *
class TestSHA256 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestSHA256 );
  CPPUNIT_TEST( testString );
  CPPUNIT_TEST( testBinary );
  CPPUNIT_TEST( testFile );
  CPPUNIT_TEST( testStream );
  CPPUNIT_TEST_SUITE_END();

  struct {
    char bytes[10];
    int something;
    unsigned long whatever;
  } data;

  const char *filename = "./testfile.bin";

public:
  void setUp() {
    memset(data.bytes, sizeof(data), 0);
    strncpy(data.bytes, "astring", sizeof(data.bytes));
    data.something = -1;
    data.whatever = 0xdeadbeef;
  }
  void tearDown() {}

  void testString() {
    std::string sum = sw::sha256::calculate("SHA256 of std::string");
    CPPUNIT_ASSERT_EQUAL(std::string("4d2eaa413f7a5e4a870601d27f16419c209bd3a642b5b78bab6d68bf9d907b66"), sum);
  }

  void testBinary() {
    // sha256sum of unsigned char * data = "astring\0\0\0\xff\xff\xff\xff\xef\xbe\xad\xde"
    // see
    std::string sum = sw::sha256::calculate(&data, sizeof(data));
    CPPUNIT_ASSERT_EQUAL(std::string("86c7f81ded0020d8bae286d39bd664bcd173521719c273519643b956c98535e8"), sum);
  }

  void testFile() {
    std::string sum = sw::sha256::file(filename);
    CPPUNIT_ASSERT_EQUAL(std::string("86c7f81ded0020d8bae286d39bd664bcd173521719c273519643b956c98535e8"), sum);
  }

  void testStream() {
    std::stringstream ss("SHA256 of std::stringstream");
    std::string sum = sw::sha256::calculate(ss);
    CPPUNIT_ASSERT_EQUAL(std::string("f3d5b027a0c6fdd68e27ba5d7a450f6fcb593e96a88c674cc3bf7a837c908cb3"), sum)
  }
};
 *
 *
 **/

class TestSHA512 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestSHA512 );
  CPPUNIT_TEST( testString );
  CPPUNIT_TEST( testVoid );
  CPPUNIT_TEST( testFile );
  CPPUNIT_TEST( testData );
  CPPUNIT_TEST_SUITE_END();

  struct {
    char bytes[12];
    int32_t something;
    uint64_t whatever;
  } data;

  const char *filename = "testfile.bin";

public:
  void setUp() {}
  void tearDown() {}

  void testString() {
    std::string sum = sw::sha512::calculate("SHA512 of std::string");
    CPPUNIT_ASSERT_EQUAL(std::string("\
d588fe53e3ffa4e6\
365f5b71b1574c18\
b834bf8bbc2d3d9d\
511c087a583cba23\
112bb3b400faf2f5\
711766542f48330e\
037fba3c9c9ee7d5\
9f9012aba83f9522"), sum);
  }

  void testVoid() {
    std::string sum = sw::sha512::calculate();
    CPPUNIT_ASSERT_EQUAL(std::string("\
cf83e1357eefb8bd\
f1542850d66d8007\
d620e4050b5715dc\
83f4a921d36ce9ce\
47d0d13c5d85f2b0\
ff8318d2877eec2f\
63b931bd47417a81\
a538327af927da3e"), sum);
  }

  void testFile() {
    std::string sum = sw::sha512::file(filename);
    CPPUNIT_ASSERT_EQUAL(std::string("\
8fce2b5e6fabf6c8\
6a31f9573d50c44e\
ed24ece314153421\
a1c369e31ed68f46\
9ed45cc753850e2b\
b482fd07ea36e35c\
60a6ba2863b840bb\
7af20b2a32df85d8"), sum);
  }

  void testData() {
    std::string sum = sw::sha512::calculate(&data, sizeof(data));
    CPPUNIT_ASSERT_EQUAL(std::string("\
8fce2b5e6fabf6c8\
6a31f9573d50c44e\
ed24ece314153421\
a1c369e31ed68f46\
9ed45cc753850e2b\
b482fd07ea36e35c\
60a6ba2863b840bb\
7af20b2a32df85d8"), sum);
  }
};

class TestSHA512_256 : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE( TestSHA512_256 );
  CPPUNIT_TEST( testMessage512 );
  CPPUNIT_TEST( testMessage512_256_full );
  CPPUNIT_TEST( testMessage512_256 );
  CPPUNIT_TEST_SUITE_END();

  char message[256];

public:
  void setUp() {
    for (int i = 0; i <= 255; ++i) {
      message[i] = (char)i;
    }
  }
  void tearDown() {}
  
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
  void testMessage512() {
    sw::sha512::str_t sha512hash = sw::sha512::calculate(message, 256);
    CPPUNIT_ASSERT_EQUAL(std::string("\
1e7b80bc8edc552c\
8feeb2780e111477\
e5bc70465fac1a77\
b29b35980c3f0ce4\
a036a6c946203682\
4bd56801e62af7e9\
feba5c22ed8a5af8\
77bf7de117dcac6d"), sha512hash);
}

void testMessage512_256_full() {
  sw::sha512_256::str_t hash512 = sw::sha512_256::calculate<512>(message, 256);
  CPPUNIT_ASSERT_EQUAL(std::string("\
4ff7ecb3e7c23b55\
9974eba17a3d1a62\
0504f18be2e472ea\
c5c5cbf75b3b7550\
27a8af7dc7dc9845\
8cfc76997dc50cfd\
f4f500cc1830f561\
bf2abd3732fdf66a"), hash512);
  CPPUNIT_ASSERT_EQUAL(std::string("4ff7ecb3e7c23b55"), hash512.substr(0*16,16));
  CPPUNIT_ASSERT_EQUAL(std::string("9974eba17a3d1a62"), hash512.substr(1*16,16));
  CPPUNIT_ASSERT_EQUAL(std::string("0504f18be2e472ea"), hash512.substr(2*16,16));
  CPPUNIT_ASSERT_EQUAL(std::string("c5c5cbf75b3b7550"), hash512.substr(3*16,16));
}

void testMessage512_256() {
  sw::sha512_256::str_t hash512_256 = sw::sha512_256::calculate(message, 256);
  CPPUNIT_ASSERT_EQUAL(std::string("\
4ff7ecb3e7c23b55\
9974eba17a3d1a62\
0504f18be2e472ea\
c5c5cbf75b3b7550"), hash512_256);

  hash512_256 = sw::sha512_256::calculate<256>(message, 256);
  CPPUNIT_ASSERT_EQUAL(std::string("\
4ff7ecb3e7c23b55\
9974eba17a3d1a62\
0504f18be2e472ea\
c5c5cbf75b3b7550"), hash512_256);
  }
};

CPPUNIT_TEST_SUITE_REGISTRATION( TestSHA1 );
CPPUNIT_TEST_SUITE_REGISTRATION( TestMD5 );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestCRC );
//CPPUNIT_TEST_SUITE_REGISTRATION( TestSHA256 );
CPPUNIT_TEST_SUITE_REGISTRATION( TestSHA512_256 );

int main(int argc, const char* argv[])
{
  CppUnit::TestResult controller;
  CppUnit::TestResultCollector collectedresults;
  controller.addListener (&collectedresults);

  CppUnit::TestRunner runner;
  runner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
  runner.run(controller);
  
  CppUnit::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
  compileroutputter.write();
  
  return collectedresults.wasSuccessful() ? 0 : 1;

}
