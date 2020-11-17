#include "gameFunctions.h"

char game_func::getKeystroke() {
  char in;
  std::cout << "You inputted: ";
  std::system("stty raw");
  std::cin >> in;
  std::system("stty cooked");
  //std::cout << "\n\n\n\n\n\n\n\n\n\n";
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
void game_func::clrScr(int t) {
  for (int i = 0; i < t; i++) {
    std::cout << '\n';
  }
}
void game_func::drawUI(Player* player) {
  player->printName();
  player->printHP();
  player->printXY();
}
void game_func::printLoseScreen() {
  std::cout << "You have died! :(\n";
}
void game_func::printWinScreen() {
  std::cout << "You win!\n";
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
    else if (objectType == "snake") {
      int px, py;
      fin >> px >> py;
      Snake *s = new Snake(p, px, py);
      std::cout << "Snake created\n";
      mobQueue.push_back(s);
      map.insertObject(s);
    }
    else if (objectType == "wintile") {
      int px, py;
      fin >> px >> py;
      WinTile *wintile = new WinTile(px, py);
      std::cout << "WinTile created\n";
      map.insertObject(wintile);
    }
    else if (objectType == "infotile") {
      std::string address;
      int px, py;
      fin >> address >> px >> py;
      InfoTile *infotile = new InfoTile(address, px, py);
      std::cout << "InfoTile created\n";
      map.insertObject(infotile);
    }
  }
  std::cout << "Finished reading objects\n";
}
void game_func::gameLoop(Map map, WinTile *wintile, std::vector<Moveable*> mobQueue, Player *player, Camera *camera) {
  Point newP = Point();
  while (true) {
    game_func::drawUI(player);
    camera->draw(map);

    if (player->hp <= 0) {   //Losing condition
      game_func::printLoseScreen();
      break;
    }
    if (wintile->hasWon) {
      game_func::printWinScreen();
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
    game_func::clrScr(30); //clear the screen
  }
}

void game_func::save(std::string address, Map map, Camera *c) {
  std::ofstream outFile(address);
  if (outFile.is_open()) {
    outFile << map.getHeight() << ' ' << map.getWidth() << ' ' << map.getDepth() << '\n';
    outFile << c->length << '\n';
    for (int i = 0; i < map.getHeight(); i++) {
      for (int j = 0; j < map.getWidth(); j++) {
        ObjectStack stack = ObjectStack(map.getDepth());
        while (map.numOfObject(j, i) > 0) { //invert the stack to get right order
          stack.push(map.removeObject(j, i));
        }
        while (stack.size() > 0) {
          Object *o = stack.pop();
          switch (o->id) {
            case ObjectId::VOID: {
              //Void *v = static_cast<Void*>(o);
              outFile << static_cast<int>(o->id) << '\n';
              break;
            }
            case ObjectId::FLOOR: {
              outFile << static_cast<int>(o->id) << '\n';
              break;
            }
            case ObjectId::TOPWALL:
            case ObjectId::SIDEWALL: {
              Wall *w = static_cast<Wall*>(o);
              outFile << static_cast<int>(w->id) << ' ' << w->isSideWall << '\n';
              break;
            }
            case ObjectId::PLAYER: {
              Player *p = static_cast<Player*>(o);
              outFile << static_cast<int>(p->id) << ' ' << p->name  << ' ' << p->hp << ' ' << p->justTookDmg << '\n';
              break;
            }
            case ObjectId::ROCK: {
              outFile << static_cast<int>(o->id) << '\n';
              break;
            }
            case ObjectId::PRESSUREPLATE: {
              PressurePlate *pp = static_cast<PressurePlate*>(o);
              outFile << static_cast<int>(pp->id) << ' ' << pp->isPressed << ' ';
              // XY OF THE OBJECT IS KEPT
              if (pp->activateObj != nullptr) // If nullptr then record invalid object
                outFile << pp->activateObj->pos.x << ' ' << pp->activateObj->pos.y << '\n';
              else
                outFile << "-1 -1\n";
              break;
            }
            case ObjectId::DOOR: {
              Door *d = static_cast<Door*>(o);
              outFile << static_cast<int>(d->id) << ' ' << d->isOpened << ' ';
              if (d->activatorObj != nullptr) // If nullptr then record invalid object
                outFile << d->activatorObj->pos.x << ' ' << d->activatorObj->pos.y << '\n';
              else
                outFile << "-1 -1\n";
              break;
            }
            case ObjectId::ZOMBIE: {
              outFile << static_cast<int>(o->id) << '\n';
              break;
            }
            case ObjectId::SNAKE: {
              Snake *s = static_cast<Snake*>(o);
              outFile << static_cast<int>(s->id) << ' ' << s->viewDistance << ' ';
              if (s->player != nullptr)
                outFile << s->player->pos.x << ' ' << s->player->pos.y << '\n';
              else
                outFile << "-1 -1\n";
              break;
            }
            case ObjectId::WINTILE: {
              WinTile *w = static_cast<WinTile*>(o);
              outFile << static_cast<int>(w->id) << ' ' << w->hasWon << '\n';
              break;
            }
            case ObjectId::INFOTILE: {
              InfoTile *i = static_cast<InfoTile*>(o);
              outFile << static_cast<int>(i->id) << ' ' << i->address << '\n';
              break;
            }
          }
          map.insertObject(o);
        }
        outFile << "end\n";
      }
    }
    outFile.close();
  } else std::cout << "Failed to open!";
}
void game_func::load(std::string address, Map &map, WinTile *&win, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c) {
  std::ifstream inFile(address);

  p = new Player("empty", 0, 0); //so ugly :(

  if (inFile.is_open()) {
    int w, h, d, l;
    inFile >> w >> h >> d >> l;
    map = Map(w, h, d);
    c = new Camera(l, Point());
    for (int i = 0; i < map.getHeight(); i++) {
      for (int j = 0; j < map.getWidth(); j++) {
        while (true) {
          std::string s;
          getline(inFile, s);
          if (s == "end")
            break;
          std::istringstream stringIn(s);
          int numId;
          stringIn >> numId;
          ObjectId id = static_cast<ObjectId>(numId);
          switch (id) {
            case ObjectId::VOID: {
              Void *v = new Void(j, i);
              map.insertObject(v);
              break;
            }
            case ObjectId::FLOOR: {
              Floor *f = new Floor(j, i);
              map.insertObject(f);
              break;
            }
            case ObjectId::TOPWALL:
            case ObjectId::SIDEWALL: {
              bool isw;
              stringIn >> isw;
              Wall *w = new Wall(isw, j, i);
              map.insertObject(w);
              break;
            }
            case ObjectId::PLAYER: {
              std::string n;
              int hp;
              bool jtd;
              stringIn >> n >> hp >> jtd;
              p->name = n; //so ugly, but snakeeee
              p->hp = hp;
              p->justTookDmg = jtd;
              p->pos.x = j;
              p->pos.y = i;
              c->camera_pos = p->pos;
              map.insertObject(p);
              break;
            }
            case ObjectId::ROCK: {
              Rock *r = new Rock(j, i);
              map.insertObject(r);
              break;
            }
            case ObjectId::PRESSUREPLATE: {
              bool ip;
              Point activate = Point();
              stringIn >> ip >> activate.x >> activate.y;
              PressurePlate *pp = new PressurePlate(ip, j, i);
              if (activate.equalsTo(-1, -1) || (activate.y > i || (activate.y == i && activate.x > j))) {
                pp->activateObj = nullptr;
              } else {
                Openable *op = static_cast<Openable*>(map.getObject(activate));
                pp->activateObj = op;
                op->activatorObj = pp;
              }
              map.insertObject(pp);
              break;
            }
            case ObjectId::DOOR: {
              bool io;
              Point activator;
              stringIn >> io >> activator.x >> activator.y;
              Door *d = new Door(io, j, i);
              if (activator.equalsTo(-1, -1) || (activator.y > i || (activator.y == i && activator.x > j))) {
                d->activatorObj = nullptr;
              } else {
                PressurePlate *ob = static_cast<PressurePlate*>(map.getObject(activator));
                d->activatorObj = ob;
                ob->activateObj = d;
              }
              map.insertObject(d);
              break;
            }
            case ObjectId::ZOMBIE: {
              Zombie *z = new Zombie(j, i);
              map.insertObject(z);
              mobQueue.push_back(z);
              break;
            }
            case ObjectId::SNAKE: {
              int vd;
              Point playerpos;
              stringIn >> vd >> playerpos.x >> playerpos.y;
              Snake *s = new Snake(vd, j, i);
              if (playerpos.equalsTo(-1, -1)) {
                s->player = nullptr;
              } else {
                s->player = p;
              }
              map.insertObject(s);
              mobQueue.push_back(s);
              break;
            }
            case ObjectId::WINTILE: {
              bool hw;
              stringIn >> hw;
              win = new WinTile(hw, j, i);
              map.insertObject(win);
              break;
            }
            case ObjectId::INFOTILE: {
              std::string address;
              stringIn >> address;
              InfoTile *infotile = new InfoTile(address, j, i);
              map.insertObject(infotile);
              break;
            }
          }
        }
      }
    }
  }
}
