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
//Long's function
void game_func::readLevel(std::string levelFile, Map &map, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c) {

  std::ifstream fin;
  fin.open(levelFile.c_str());
  std::cout << "opened file\n";
  std::string objectType;

  while (fin >> objectType) {
    //bool linking = false;
    if (objectType == "player") {
      std::string n;
      int px, py;
      fin >> n >> px >> py;
      p = new Player(n, px, py);
      std::cout << "Player " << p << " created at " << p->pos.x << " " << p->pos.y << '\n';
      map.insertObject(p);
    }
    else if (objectType == "camera") {
      int l;
      fin >> l;
      c = new Camera(l, p->pos);
      std::cout << "Camera with length " << l << " created at " << c->camera_pos.x << " " << c->camera_pos.y << '\n';
    }
    else if (objectType == "door") {
      int px, py;
      fin >> px >> py;
      Door *d = new Door(px, py);
      std::cout << "Door created at " << d->pos.x << " " << d->pos.y << '\n';
      map.insertObject(d);
    }
    else if (objectType == "pressureplate") {
      int px, py;
      fin >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      std::cout << "PressurePlate created at " << pp->pos.x << " " << pp->pos.y << '\n';
      map.insertObject(pp);
    }
    else if (objectType == "rock") {
      int px, py;
      fin >> px >> py;
      Rock *r = new Rock(px, py);
      std::cout << "Rock created at " << r->pos.x << " " << r->pos.y << '\n';
      map.insertObject(r);
    }
    else if (objectType == "wall") {
      bool isSideWall;
      int px, py;
      fin >> isSideWall >> px >> py;
      Wall *w = new Wall(isSideWall, px, py);
      std::cout << "Wall created at " << w->pos.x << " " << w->pos.y << '\n';
      map.insertObject(w);
    }
    else if (objectType == "zombie") {
      int px, py;
      fin >> px >> py;
      Zombie *z = new Zombie(px, py);
      std::cout << "Zombie created at " << z->pos.x << " " << z->pos.y << '\n';
      mobQueue.push_back(z);
      map.insertObject(z);
    }
  }
  std::cout << "Finished reading objects\n";
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
