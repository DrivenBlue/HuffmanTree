#include "BitInputStream.hpp"

BitInputStream::~BitInputStream(){

}

/** Read the next bit from the bit buffer.
 *  If the bit buffer is currently empty,
 *  fill the bit buffer by reading a char from the istream first.
 *  Return the bit read as the least signficant bit of an int.
 *  Return -1 on EOF.
 *  This must be consistent with BitOutputStream::writeBit(), in terms
 *  of ordering of bits in the stream.
 */
int BitInputStream::readBit()
{
    int i;

    if (bufi==8)
    {
        if(this->eof())
            return -1;
        buf=in.get();
        bufi=0;
    }
    bufi++;
    i = buf>>7;
    buf=buf<<1;

    cout<<i<<endl;
    return i;

}

/** Read a byte from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading bytes.
 */
int BitInputStream::readByte()
{
    if(this->eof())
        return -1;
    return in.get();
}

/** Read a non-negative int from the ostream.
 *  Return -1 on EOF.
 *  This function doesn't touch the bit buffer.
 *  The client has to manage interaction between reading bits
 *  and reading ints.
 */
int BitInputStream::readInt()
{
    int i=0,
        temp;

    for (int j=0;j<4;j++)
    {
        if (this->eof())
            return -1;
        temp=in.get();
        temp<<=((3-j)*8);
        i|=temp;
    }
    return i;
}



int BitInputStream::next()
{
    if (index >= size) {
        return -1;
    }
    return bits[index++];
}

bool BitInputStream::eof()
{
    return in.eof();

}
