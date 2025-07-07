#include <sstream>
#include <iostream>

#ifndef CLASS_PLAYER
#define CLASS_PLAYER

class Player {
  private:
  const std::string name;

  public:
  Player();
  Player(const std::string _name);
  const std::string getName() const;
}; //end of Class Player

#endif
