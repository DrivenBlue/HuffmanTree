#include <algorithm>
#include <bitset>
#include "HCTree.hpp"
#include "iostream"

HCTree::~HCTree()
{
    delete root;
}

void HCTree::build(const std::vector<int> &freqs)
{
    //Construct forest

    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;

    // add leaves to priority_queue
        for (size_t i = 0; i < freqs.size(); ++i) {
            if (freqs[i]) {
                HCNode *node = new HCNode(freqs[i], i);
                leaves[i] = node;
                forest.push(node);
            }
        }

        HCNode *node;
        // BASE CASE:
        // add a "node" if only single node
        if (forest.size() == 1) {
            forest.push(new HCNode(0, 0));
        }

        //internal nodes
        while (forest.size() > 1) {
            node = new HCNode(0, 0);

            node->c0 = forest.top();
            node->c0->p = node;
            forest.pop();

            node->c1 = forest.top();
            node->c1->p = node;
            forest.pop();

            node->count += node->c0->count;
            node->count += node->c1->count;

            forest.push(node);
        }

        root = forest.top();
}

void HCTree::encode(byte symbol, BitOutputStream& out) const {

    HCNode* walker = leaves[symbol];
    bitset<8> temp;
    int count = 0;

    while(walker != root) {
        if(walker == walker->p->c0)
            temp[count++] = 0;
        else
            temp[count++] = 1;
        walker = walker->p;
    }

    while(count)
        out.writeBit(temp[--count]);
    if(leaves[++symbol] == *leaves.end())
        out.flush();
}


/*
 *
 *
 */

int HCTree::decode(BitInputStream &in) const
{
    HCNode *curr = root;
    int bit;

    // traverse tree until leaf or out of bits
    while (curr->c0 || curr->c1) {
        bit = in.next();
        if (bit < 0) {
            return -1;
        }
        if (bit) {
            curr = curr->c1;
        } else {
            curr = curr->c0;
        }
    }
    return curr->symbol;
}

