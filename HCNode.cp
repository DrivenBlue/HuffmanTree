#include "HCNode.hpp"

HCNode::~HCNode()
{
    if (c0) {
        delete c0;
    }
    if (c1) {
        delete c1;
    }
}

bool HCNode::operator<(const HCNode& other)
{
    return other.count <= this->count;
}

