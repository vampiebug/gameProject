#ifndef CLASS_BLOCK
#define CLASS_BLOCK
/*
This is what PU and CPU are in Lilly's version. 
Renamed to Block for clarity and because that it was they represent in a game of mastermind.
*/
class Block {
    public:
        Block(int _data);
        Block();
        ~Block(); //this will need to follow through and delete all of the blocks following it.

        int data; // The value given to the block
        /*Pointer to the next block. 
        Since this is functionally a linked list, Only the first block needs to be stored in the mastermind object, 
        and the rest will be found by navigating from this one.
        */
        Block* nextBlock; 
        /*Pointer to the block that is currently being pointed at. 
        Used for traversing the list. I don't think this is necessary--The player and CPU lists should have their pwn separate Block* trackers, but not every node should need a tracker
        */
        //Block* trackerPU = nullptr;
};


#endif