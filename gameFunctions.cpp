#include <iostream>
#include <cstdlib>

#include "gameFunctions.h"

char game_func::getKeystroke() {
  char in;
  std::cout << "You inputted: ";
  std::system("stty raw");
  std::cin >> in;
  std::system("stty cooked");
  std::cout << "\n\n\n\n\n\n\n\n\n\n";
  return in;
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
void game_func::drawUI(Player* player) {
  player->printName();
  player->printHP();
  player->printXY();
}
void game_func::printLoseScreen() {
  std::cout << "You have died! :(\n";
}
void game_func::gameLoop(Map map, std::vector<Moveable*> mobQueue, Player *player, Camera *camera) {
  Point newP = Point();
  while (true) {
    game_func::drawUI(player);
    camera->draw(map);

    if (player->hp <= 0) {   //Losing condition
      game_func::printLoseScreen();
      break;
    }

    newP = game_func::detectGameControls(player);
    if (newP.equalsTo(-1, -1))
      break;

    if (!newP.equalsTo(-2, -2) && player->check(newP, map)) {
      camera->camera_pos = player->pos; //CHANGE THIS
      map.updateMap(player->pos, 3);
    }

    for (std::vector<Moveable*>::iterator it = mobQueue.begin(); it != mobQueue.end(); it++) {
      if ((*it)->destroyFlag) {
        //do some crazy shit
        Object *target = map.removeObject((*it)->pos);
        if (target->id != (*it)->id) {
          Object *realTarget = map.removeObject((*it)->pos); //only one layer?
          map.insertObject(target);
          target = realTarget;
        }

        //camera->draw(map);
        //std::cout << target <<'\n';

        mobQueue.erase(it);
        delete target; //delete second obj
        //std::cout << target;
        break;
      }
      (*it)->move(map);
      (*it)->dealDmg(player);

      map.updateMap((*it)->pos, 3);
    }
  }
}
