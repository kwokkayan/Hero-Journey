#include <iostream>
#include <cstdlib>

#include "gameFunctions.h"

char game_func::getKeystroke() {
  char in;
  std::cout << "You inputted: ";
  std::system("stty raw");
  std::cin >> in;
  std::system("stty cooked");
  std::cout << '\n';
  return in;
}
void game_func::movePlayerAndCamera(Map m, Camera *c, Player *p, Point pos) {
  m.insertObject(m.removeObject(p->pos), pos);
  p->pos.changePos(pos.x, pos.y);
  c->camera_pos.changePos(pos.x, pos.y); //Change player and camera pos
}
Point game_func::detectGameControls(Player *p) {
  char input = game_func::getKeystroke();
  Point pos = p->pos;
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
      return Point();
    default:
      return Point(-2, -2); //return -1 for illegal input
  }
  return pos;
}
int game_func::processControls(Point pos, Map map, Camera *camera, Player *player) {
  if (pos.equalsTo(-1, -1))
    return -1;
  else if (pos.equalsTo(-2, -2))
    return -2;

  if (player->check(pos, map)) {
      map.updateMap(); //change
      camera->camera_pos = player->pos; //CHANGE THIS
  }
  /* switch (m.getObject(pos)->id) {
    //main checking condition... may need refactoring
    case ObjectId::FLOOR: {
      game_func::movePlayerAndCamera(m, c, p, pos);
      break;
    }
    case ObjectId::ROCK: {
      Point push_destination = Point(2 * pos.x - p->pos.x, 2 * pos.y - p->pos.y);
      Object *o = m.getObject(push_destination);
      switch (o->id) { //check destination
        case ObjectId::FLOOR: {
          m.insertObject(m.removeObject(pos), push_destination);
          game_func::movePlayerAndCamera(m, c, p, pos);
          break;
        }
        case ObjectId::PRESSUREPLATE: {
          PressurePlate *pp = static_cast<PressurePlate*>(o);
          pp->activate();
        }
      }
      break;
    }
    default:
      return -3; //return -2 for no movement
  } */

  std::cout << player->pos.x << " " << player->pos.y << "\n";

  return 0;
}
