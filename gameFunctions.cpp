#include "gameFunctions.h"

char game_func::getKeystroke() {
  char in;
  std::system("stty raw");
  std::cin >> in;
  std::system("stty cooked");
  std::cout << '\n';
  return in;
}

void game_func::setFormat(int w) {
  std::cout << std::right << std::setw(w);
}

void game_func::detectGameControls(Player *p, Point &pos) {
  char input = game_func::getKeystroke();
  pos = p->pos;
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
    case 'H':
    case 'h': {
      pos = Point(-2, -2);
      break;
    }
    default:
      pos = Point(); //return -1 for illegal input
  }
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

void game_func::drawMenu(std::string address) { //draws menu
  int width, height;
  std::ifstream inFile(address);
  if (inFile.is_open()) {
    inFile >> width >> height;
    std::string s;
    getline(inFile, s);
    game_func::clrScr(20);

    game_func::setFormat(width);
    for (int k = 0; k < width + 2; k++)
      std::cout << '~';
    std::cout << '\n';

    for (int i = 0; i < height; i++) {

      getline(inFile, s);
      int bufferleft = (width - s.length()) / 2;
      game_func::setFormat(width);

      std::cout << '~';
      for (int j = 0; j < bufferleft; j++) {
        std::cout << ' ';
      }
      std::cout << s;
      for (int j = 0; j < width - s.length() - bufferleft; j++) {
        std::cout << ' ';
      }
      std::cout << "~\n";

    }

    game_func::setFormat(width);
    for (int k = 0; k < width + 2; k++)
      std::cout << '~';
    std::cout << '\n';
  } else std::cout << "Menu not found!\n";
  inFile.close();
}

void game_func::selectSlotToSave(std::vector<int> options, int &sel) {
  bool hasSelectedValid = false;
  while (!hasSelectedValid) {
    char in = game_func::getKeystroke();
    if (in == 'q' || in == 'Q')
      break;
    if (in >= '0' && in <= '9') {
      hasSelectedValid = true;
      sel = in - 48;
    }

    for (std::vector<int>::iterator it = options.begin(); it != options.end(); it++) {
      if (in - 48 == *it) {
        setFormat(40);
        std::cout << "Chosen file will be overwritten! Press c/C to confirm.";
        char confirm = game_func::getKeystroke();
        if (confirm != 'c' && confirm != 'C') {
          hasSelectedValid = false;
          sel = -1;
        }
        break;
      }
    }
  }
}

void game_func::selectSlotToLoad(std::vector<int> options, int &sel) {
  bool hasSelectedValid = false;
  while (!hasSelectedValid) {
    char in = game_func::getKeystroke();
    if (in == 'q' || in == 'Q')
      break;
    for (std::vector<int>::iterator it = options.begin(); it != options.end(); it++) {
      if (in - 48 == *it) {
        hasSelectedValid = true;
        sel = *it;
      }
    }
  }
}

void game_func::drawSaveMenu(std::vector<int> &existingSavesId) {
  std::string menuAddress = "menu/saveMenu.txt";
  std::string saveDir = "saves/";
  std::ofstream outFile(menuAddress);
  if (outFile.is_open()) {
    outFile << 30 << ' ' << 12 << '\n';
    outFile << "Save Menu\n";
    for (int i = 0; i < 10; i++) {
      std::ifstream temp(saveDir + "save" + std::to_string(i) + ".txt");
      outFile << i << ": ";
      if (temp.good()) {
        outFile << "exists!\n";//change to time stamp?
        existingSavesId.push_back(i);
      } else {
        outFile << "empty!\n";
      }
      temp.close();
    }
  }
  outFile << "Q: Exit\n";
  outFile.close();
  game_func::drawMenu(menuAddress);
}

void game_func::drawLoadMenu(std::vector<int> &existingSavesId) {
  std::string menuAddress = "menu/loadMenu.txt";
  std::string saveDir = "saves/";
  std::ofstream outFile(menuAddress);
  if (outFile.is_open()) {
    outFile << 30 << ' ' << 12 << '\n';
    outFile << "Load Menu\n";
    for (int i = 0; i < 10; i++) {
      std::ifstream temp(saveDir + "save" + std::to_string(i) + ".txt");
      if (temp.good()) {
        outFile << i << ": ";
        outFile << "exists!\n";//change to time stamp?
        existingSavesId.push_back(i);
      }
      temp.close();
    }
  }
  outFile << "Q: Exit\n";
  outFile.close();
  game_func::drawMenu(menuAddress);
}

void game_func::menuLoop(game_func::menuFuncions &f) {
  char input = ' ';
  bool hasChosen = false;
  while (!hasChosen) {
    input = game_func::getKeystroke();
    hasChosen = true;
    switch (input) {
      case 'R':
      case 'r': {
        f = game_func::menuFuncions::RESTART;
        break;
      }
      case 'S':
      case 's': {
        f = game_func::menuFuncions::SAVE;
        break;
      }
      case 'L':
      case 'l': {
        f = game_func::menuFuncions::LOAD;
        break;
      }
      case 'Q':
      case 'q': {
        f = game_func::menuFuncions::LEAVEGAME;
        break;
      }
      case 'H':
      case 'h': {
        f = game_func::menuFuncions::LEAVEMENU;
        break;
      }
      default:
        hasChosen = false;
    }
  }
}

void game_func::printLoseScreen() {
  std::cout << "You have died! :(\n";
}
void game_func::printWinScreen() {
  std::cout << "You win!\n";
}
//Long's function
void game_func::readLevel(std::string levelFile, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c) {

  std::ifstream fin;
  fin.open(levelFile.c_str());
  std::cout << "opened file\n";
  std::string objectType;

  while (fin >> objectType) {
    //bool linking = false;
    if (objectType == "map") {
      int width, height, depth = 5;
      fin >> width >> height;
      map.createEmptyMap(width, height, depth);
    } else if (objectType == "player") {
      std::string n;
      int px, py;
      fin >> n >> px >> py;
      p = new Player(n, px, py);
      std::cout << "Player " << p << " created at " << p->pos.x << " " << p->pos.y << '\n';
      map.insertObject(p);
    } else if (objectType == "camera") {
      int l;
      fin >> l;
      c = new Camera(l, p->pos);
      std::cout << "Camera with length " << l << " created at " << c->camera_pos.x << " " << c->camera_pos.y << '\n';
    } else if (objectType == "link") {
      // How to use link
      // in txt
      // ...
      // link
      // *PressurePlate Declaration*
      // *Door Declaration* //change to declare openable
      // ...
      std::string n;
      int px, py;

      fin >> n >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      std::cout << "PressurePlate created at " << pp->pos.x << " " << pp->pos.y << '\n';
      map.insertObject(pp);

      fin >> n >> px >> py;
      Door *d = new Door(px, py);
      std::cout << "Door created at " << d->pos.x << " " << d->pos.y << '\n';
      map.insertObject(d);

      pp->activateObj = d;
      d->activatorObj = pp;
    } else if (objectType == "door") {
      int px, py;
      fin >> px >> py;
      Door *d = new Door(px, py);
      std::cout << "Door created at " << d->pos.x << " " << d->pos.y << '\n';
      map.insertObject(d);
    } else if (objectType == "pressureplate") {
      int px, py;
      fin >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      std::cout << "PressurePlate created at " << pp->pos.x << " " << pp->pos.y << '\n';
      map.insertObject(pp);
    } else if (objectType == "rock") {
      int px, py;
      fin >> px >> py;
      Rock *r = new Rock(px, py);
      std::cout << "Rock created at " << r->pos.x << " " << r->pos.y << '\n';
      map.insertObject(r);
    } else if (objectType == "wall") {
      bool isSideWall;
      int px, py;
      fin >> isSideWall >> px >> py;
      Wall *w = new Wall(isSideWall, px, py);
      std::cout << "Wall created at " << w->pos.x << " " << w->pos.y << '\n';
      map.insertObject(w);
    } else if (objectType == "zombie") {
      int px, py;
      fin >> px >> py;
      Zombie *z = new Zombie(px, py);
      std::cout << "Zombie created at " << z->pos.x << " " << z->pos.y << '\n';
      mobQueue.push_back(z);
      map.insertObject(z);
    } else if (objectType == "snake") {
      int px, py;
      fin >> px >> py;
      Snake *s = new Snake(p, px, py);
      std::cout << "Snake created\n";
      mobQueue.push_back(s);
      map.insertObject(s);
    } else if (objectType == "wintile") {
      int px, py;
      fin >> px >> py;
      wintile = new WinTile(px, py);
      std::cout << "WinTile created\n";
      map.insertObject(wintile);
    } else if (objectType == "infotile") {
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

void game_func::gameLoop(Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera) {
  Point newP = Point();
  //initial load here
  bool hasQuitted = false;
  bool noUpdate = false;

  while (true) {
    game_func::drawUI(player);
    camera->draw(map);
    if (wintile->hasWon) {
      game_func::printWinScreen();
      break;
    }
    if (player->hp <= 0) {   //Losing condition
      game_func::printLoseScreen();
      break;
    }

    game_func::detectGameControls(player, newP); //change to pass by reference
    std::cout << "dsd\n";
    std::cout << newP.x << ' ' << newP.y << '\n';
    if (newP.equalsTo(-2, -2)) { //open menu
      game_func::drawMenu("menu/menu.txt");
      game_func::menuFuncions selection;
      game_func::menuLoop(selection);
      switch (selection) {
        case game_func::menuFuncions::RESTART: {
          std::string n;
          std::cout << "Nothing yet! :(";
          char c = getKeystroke();
          break;
        }
        case game_func::menuFuncions::SAVE: {
          std::vector<int> existingSavesId;
          game_func::drawSaveMenu(existingSavesId);

          //std::cout << "Please input savefile name (if exists it will be overwritten!): ";
          //std::cin >> address;
          int sel = -1;
          selectSlotToSave(existingSavesId, sel);
          if (sel != -1) {
            game_func::setFormat(55);
            std::cout << "You have chosen save " << std::to_string(sel) <<"!\n";
            game_func::save("saves/save" + std::to_string(sel) + ".txt", map, camera);
            game_func::setFormat(75);
            std::cout << "Save completed! Press any key to continue...";
            char c = getKeystroke();
          }
          break;
        }
        case game_func::menuFuncions::LOAD: {
          std::vector<int> existingSavesId;
          game_func::drawLoadMenu(existingSavesId);

          int sel = -1;
          selectSlotToLoad(existingSavesId, sel);
          if (sel != -1) {
            game_func::setFormat(55);
            std::cout << "You have chosen save " << std::to_string(sel) <<"!\n";
            map.deleteMap();
            mobQueue.clear();
            delete camera;
            game_func::load("saves/save" + std::to_string(sel) + ".txt", map, wintile, mobQueue, player, camera);
            game_func::setFormat(75);
            std::cout << "Load completed! Press any key to continue...";
            char c = getKeystroke();
          }
          break;
        }
        case game_func::menuFuncions::LEAVEGAME: {
          hasQuitted = true;
          break;
        }
        case game_func::menuFuncions::LEAVEMENU: {
          break;
        }
      }
      if (hasQuitted)
        break;
      continue;
    }

    if (!newP.equalsTo(-1, -1) && player->check(newP, map)) {
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
                Openable *op = dynamic_cast<Openable*>(map.getObject(activate));
                if (op == nullptr) {
                  Object *topObj = map.removeObject(activate);
                  op = static_cast<Openable*>(map.getObject(activate));
                  map.insertObject(topObj);
                }
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
                PressurePlate *ob = dynamic_cast<PressurePlate*>(map.getObject(activator));
                if (ob ==nullptr) {
                  Object *topObj = map.removeObject(activator);
                  ob = static_cast<PressurePlate*>(map.getObject(activator));
                  map.insertObject(topObj);
                }
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
