#include "tower.hpp"

Tower::Tower() : startBlock(new Block()), lastBlock(nullptr){}

Tower::Tower(int data) : startBlock(new Block(data)), lastBlock(nullptr){}

Tower::~Tower(){
    //idk what to do here, probably traverse and delete everything
}

/**
 * @brief Return the pointer to the next block in the tower.
 * @param current A pointer to block you want the next block for.
 * @return A pointer to the next block, which may be nullptr. Maybe make these private?
 */

/**
 * @brief Return the pointer to the previous block in the tower.
 * @param current A pointer to block you want the previous block for.
 * @return A pointer to the previous block, which may be nullptr. Maybe make these private?
 */


/**
 * @brief adds a new block to the end of the tower
 * @param newBlock A pointer to block you want to add. Should already have data defined (enforce this?)
 */
void Tower::addToEnd(Block* newBlock){
    Block* tracker = startBlock;
    while (tracker->traverseDown() != nullptr){
        tracker = tracker->traverseDown();
    }
    //this is very important! Not only do we set the next address to the newBlock, but we also let newBlock link back to the previous last block.
    tracker->setNext(newBlock);
    newBlock->setPrev(tracker);
}