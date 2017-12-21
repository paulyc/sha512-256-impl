# sha512-256-impl

Code borrowed from http://www.atwillys.de/content/cc/cpp-hash-algorithms-class-templates-crc-sha1-sha256-md5/

Implementation of SHA512/256 algorithm described in https://eprint.iacr.org/2010/548.pdf

## Abstract
With the emergence of pervasive 64 bit computing we observe 
that it is more cost effective to compute a SHA-512 than it is 
to compute a SHA-256 over a given size of data. We propose a 
standard way to use SHA-512 and truncate its output to 256 bits. 
For 64 bit architectures, this would yield a more efficient 256 bit 
hashing algorithm, than the current SHA-256. We call this method 
SHA-512/256. We also provide a method for reducing the size of the 
SHA-512 constants table that an implementation will need to store.
