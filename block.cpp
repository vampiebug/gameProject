#include "block.hpp"


//no member funcs so should just be the constructors. Look at what is done in reset for this. In fact, copy it over so we can use it in reset
/**
 * @brief Creates a new block as a member of a linked list given its data and the previous block.
 */
Block::Block(int _data, Block* _prev) : data(_data), prevBlock(_prev), nextBlock(nullptr){}

/**
 * @brief Creates a new block given just the data, not connected to anything
 */
Block::Block(int _data) : Block(_data, nullptr){}

/**
 * @brief Creates a new block with data as 0 (not valid), as the start of a linked list with no prior or following objects
 */
Block::Block() : Block(0){

}
/**
 * @brief Deletes this block object. Should probably also do some reassigning.
 */
Block::~Block(){
    
}

/**
 * @brief Getter for nextBlock
 * @return Pointer to nextBlock
 */
Block* Block::traverseDown(){
    return nextBlock;
}
/**
 * @brief Getter for prevBlock
 * @return Pointer to prevBlock
 */
Block* Block::traverseUp(){
    return prevBlock;
}

/**
 * @brief Setter for nextBlock
 * @param next The address of the next block.
 */
void Block::setNext(Block* next){
    nextBlock = next;
}

/**
 * @brief Setter for prevBlock
 * @param prev The address of the previous block.
 */
void Block::setPrev(Block* prev){
    prevBlock = prev;
}


//this is pretty scalable. Maybe we could change it so the player can choose the number they need to guess?