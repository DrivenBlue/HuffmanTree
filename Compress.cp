#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "HCTree.hpp"

/*Open the input file for reading.
 * counting the number of occurrences of each byte value; then close the file.
Use these byte counts to construct a Huffman coding tree.
Open the output file for writing.
Write enough information (a "file header") to the output file to enable the coding tree to be
reconstructed when the file is read by your uncompress program.
Open the input file for reading, again.
Using the Huffman coding tree, translate each byte from the input file into its code,
and append these codes as a sequence of bits to the output file, after the header.
Close the input and output files.*/

// creates the header used to rebuild the tree with the following format:
/*
    char freq char freq ... char freq
*/
void makeFormat(std::ostream &out, std::vector<int> freqs)
{
    for (size_t i = 0; i < freqs.size(); ++i) {
        if (freqs[i]) {
            out << i << " " << freqs[i] << " ";
        }
    }
    out << std::endl;
}

int main(int argc, char* argv[])
{
    // Read bytes from the file
    // read the file into a buffer
    std::ifstream ifs(argv[1], std::ios::binary); //reads from stream in binary
    std::string buffer((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

    // create a new file if we're trying to compress an empty file
    if (!buffer.size()) {
        std::ofstream ofs(argv[2], std::ios::binary);
        exit(0);
    }

    // count the occurences of each char
    std::vector<int> freqs(256, 0);
    for (size_t i = 0; i < buffer.size(); ++i) {
        byte byt = buffer[i];
        ++freqs[byt];
    }

    // build HCTree
    HCTree huff;
    huff.build(freqs);

    // output the compressed file
    std::ofstream ofs(argv[2], std::ios::binary);
    BitOutputStream bos(ofs);
    makeFormat(ofs, freqs);
    for (size_t i = 0; i < buffer.size(); ++i) {
        huff.encode(buffer[i], bos);
    }

    return 0;
}

