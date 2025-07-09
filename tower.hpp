#ifndef CLASS_TOWER
#define CLASS_TOWER
#include "block.hpp"

//basically just a pointer of blocks with methods for adding and removing.
//https://www.geeksforgeeks.org/cpp/doubly-linked-list-in-cpp/
//idk if we need all of those insert at end and at beginning funcs. I think we're only using insert at end.
class Tower{
    public:
        //needs ctors and dtors
        //can't initialize new list from existing Blocks.
        //creates an empty new tower
        Tower();
        //creates a new tower with a startBlock with a new block
        Tower(int data);
        ~Tower();
        //needs first and last block
        Block* startBlock;
        Block* lastBlock;
        //needs insert function to add to end
        void addToEnd(Block* newBlock);

};


#endif