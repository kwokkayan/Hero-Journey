#include <iostream>
#include <cstdlib>
#include "gameFunctions.h"
char game_func::getKeystroke() {
  char in;
  std::system("stty raw");
  std::cin >> in;
  std::system("stty cooked");
  return in;
}
void game_func::movePlayerAndCamera(Map &m, Camera &c, Player &p, Point pos) {
  m.insertObject(m.removeObject(p.pos.x, p.pos.y), pos.x, pos.y);
  p.pos.changePos(pos.x, pos.y);
  c.camera_pos.changePos(pos.x, pos.y); //Change player and camera pos
}
int game_func::detectGameControls(Map &m, Camera &c, Player &p) {
  char input = game_func::getKeystroke();
  Point pos = p.pos;
  switch (input) {
    case 'W':
    case 'w': {
      --pos.y;
      break;
    }
    case 'A':
    case 'a': {
      --pos.x;
      break;
    }
    case 'S':
    case 's': {
      ++pos.y;
      break;
    }
    case 'D':
    case 'd': {
      ++pos.x;
      break;
    }
    case 'Q':
    case 'q':
      return -1;
    default:
      return -2; //return -1 for illegal input
  }
  std::cout << pos.x << " " << pos.y << "\n";
  switch (m.getObject(pos.x, pos.y).id) {
    case ObjectId::FLOOR: {
      game_func::movePlayerAndCamera(m, c, p, pos);
      break;
    }
    case ObjectId::ROCK: {
      Point push_destination = Point(2 * pos.x - p.pos.x, 2 * pos.y - p.pos.y);
      if (m.getObject(push_destination.x, push_destination.y).id == ObjectId::FLOOR) {
        m.insertObject(m.removeObject(pos.x, pos.y), push_destination.x, push_destination.y);
        game_func::movePlayerAndCamera(m, c, p, pos);
      }
      break;
    }
    default:
      return -3; //return -2 for no movement
  }



  return 0;
}
