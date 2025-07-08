#include "block.hpp"


//no member funcs so should just be the constructors. Look at what is done in reset for this. In fact, copy it over so we can use it in reset
/**
 * @brief Creates a new block as a member of a linked list given its first member and the data for the new block.
 */
Block::Block(int _data) : data(_data), nextBlock(nullptr){}

/**
 * @brief Creates a new block with data as 0 (not valid), as the start of a linked list.
 */
Block::Block() : Block(0){

}
/**
 * @brief Deletes this block object and all the ones following it.
 */
Block::~Block(){
    
}

//this is pretty scalable. Maybe we could change it so the player can choose the number they need to guess?