#include "BitOutputStream.hpp"

void BitOutputStream::writeBit(int bit){
    buf[bufi++] = bit;
    if(bufi & 8) {
        flush();
    }
}

void BitOutputStream::writeByte(int b) {
    int count = 8;
    while(count--) {
        writeBit(b & 1);
        b >>= 1;
    }
}

void BitOutputStream::writeInt(int i) {

}

void BitOutputStream::flush(){
    int cursor = 0;
    while(cursor < bufi)
        out << buf[cursor++];
    bufi = 0;
    buf ^= buf;	// zero the byte
}


