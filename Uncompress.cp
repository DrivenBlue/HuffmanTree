#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "HCTree.hpp"

// get the size of the compressed file in bits
int getSize(HCTree &hct, std::vector<int> freqs)
{
    /*int result = 0;
    for (size_t i = 0; i < freqs.size(); ++i) {
        if (freqs[i]) {
            result += freqs[i] * hct.getCode(i).size();
        }
    }
    return result; */
}

int main(int argc, char* argv[])
{
    // read the file into a buffer
    std::ifstream ifs(argv[1], std::ios::binary);
    std::string buffer((std::istreambuf_iterator<char>(ifs)),
                (std::istreambuf_iterator<char>()));

    // create an empty file if we're trying to uncompress an empty file
    if (!buffer.size()) {
        std::ofstream ofs(argv[2], std::ios::binary);
        exit(0);
    }

    // create a BitInputStream
    std::stringstream ss(buffer);
    BitInputStream bis(ss);

    // build the tree
    //HCTree hct;
    //hct.build(bis.freqs);
    //bis.size = getSize(hct, bis.freqs);

    std::ofstream ofs(argv[2], std::ios::binary);

    // decode each byte into the uncompressed file
    //int c = hct.decode(bis);
    //int i = 0;
    //while (c >= 0) {
      //  ofs << (byte)c;
        //c = hct.decode(bis);
  //  }

    return 0;
}

