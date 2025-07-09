#ifndef CLASS_BLOCK
#define CLASS_BLOCK
/*
This is what PU and CPU are in Lilly's version. 
Renamed to Block for clarity and because that it was they represent in a game of mastermind.
*/


class Block {
    public:
        Block(int _data, Block* _prev);
        Block(int _data);
        Block();
        ~Block(); //this will need to follow through and delete all of the blocks following it.

        int data; // The value given to the block

        //provide a pointer to the next or previous block.
        Block* traverseUp();
        Block* traverseDown();

        void setNext(Block* next);
        void setPrev(Block* prev);

    private:
        /*Pointer to the prior block.*/
        Block* prevBlock;
        /*Pointer to the next block. 
        Since this is functionally a linked list, Only the first block needs to be stored in the mastermind object, 
        and the rest will be found by navigating from this one.
        */
        Block* nextBlock; 



};


#endif