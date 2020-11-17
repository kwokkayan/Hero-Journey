#include "editor.h"
#include "gameFunctions.h"
void editor::createLevel(std::string levelFile, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera) {
  bool wintileExists = false;

  int width, height;
  std::cout << "Enter map (width, height): ";
  std::cin >> width >> height;
  map.createEmptyMap(width, height, 5);

  std::string name;
  int x, y;
  std::cout << "Enter player (name, x, y): ";
  std::cin >> name >> x >> y;
  player = new Player(name, x, y);
  map.insertObject(player);

  int length;
  std::cout << "Enter camera (length): ";
  std::cin >> length;
  camera = new Camera(length, player->pos);

  // commands:
  // create TYPE <TYPE ARGUMENTS> x1 y1
  // delete x1 y1
  // move x1 y1 x2 y2
  // link x1 y1 x2 y2 (where x1 y1 is pressureplate and x2 y2 is door)
  std::string command = "";
  while (!(command == "exit" && wintileExists)) {
    camera->draw(map);
    std::cout << "Player (x, y): " << '(' << player->pos.x << ", " << player->pos.y << ")\n";
    std::cout << "Enter Command (help for help): ";
    std::cin >> command;
    if (command == "help") {
      std::cout << "Commands List:\n";
      std::cout << "create TYPE <TYPE ARGUMENTS> x y\n";
      std::cout << "delete x y\n";
      std::cout << "move x1 y1 x2 y2\n";
      std::cout << "link x1 y1 x2 y2 (where x1 y1 is pressureplate and x2 y2 is door)\n";
      char temp;
      std::cout << "Press enter to continue..\n";
      std::cin >> temp;
    } else if (command == "create") {
      int x, y;
      std::string objectType;
      std::cin >> objectType;
      // objectType
      if (objectType == "void") {
        std::cin >> x >> y;
        Void *v = new Void(x, y);
        map.insertObject(v);
      } else if (objectType == "floor") {
        std::cin >> x >> y;
        Floor *f = new Floor(x, y);
        map.insertObject(f);
      } else if (objectType == "wall") {
        bool isw;
        std::cin >> isw >> x >> y;
        Wall *w = new Wall(isw, x, y);
        map.insertObject(w);
      } else if (objectType == "rock") {
        std::cin >> x >> y;
        Rock *r = new Rock(x, y);
        map.insertObject(r);
      } else if (objectType == "pressureplate") {
        std::cin >> x >> y;
        PressurePlate *pp = new PressurePlate(x, y);
        map.insertObject(pp);
      } else if (objectType == "door") {
        std::cin >> x >> y;
        Door *d = new Door(x, y);
        map.insertObject(d);
      } else if (objectType == "zombie") {
        std::cin >> x >> y;
        Zombie *z = new Zombie(x, y);
        map.insertObject(z);
        mobQueue.push_back(z);
      } else if (objectType == "snake") {
        std::cin >> x >> y;
        Snake *s = new Snake(player, x, y);
        map.insertObject(s);
        mobQueue.push_back(s);
      } else if (objectType == "wintile" && !wintileExists) {
        std::cin >> x >> y;
        wintile = new WinTile(x, y);
        map.insertObject(wintile);
        wintileExists = true;
      } else if (objectType == "infotile") {
        std::string txtaddress;
        std::cin >> txtaddress >> x >> y;
        InfoTile *infotile = new InfoTile(txtaddress, x, y);
        map.insertObject(infotile);
      }
      // end
    } else if (command == "delete") {
      int x, y;
      std::cin >> x >> y;
      if (map.getObject(x, y)->id == ObjectId::WINTILE)
        wintileExists = false;
      delete map.removeObject(x, y);
      if (map.getObject(x, y)->pos.equalsTo(-1, -1))
        map.insertObject(new Void(x, y));
    } else if (command == "move") {
      Point p = Point();
      Point q = Point();
      std::cin >> p.x >> p.y >> q.x >> q.y;
      if (map.getObject(p)->id == ObjectId::PLAYER)
        camera->camera_pos = q;
      map.getObject(p)->pos = q;
      map.moveObject(p, q);
    } else if (command == "link") {
      Point p = Point();
      Point q = Point();
      std::cin >> p.x >> p.y >> q.x >> q.y;
      PressurePlate *pp = dynamic_cast<PressurePlate*>(map.getObject(p));
      Door *d = dynamic_cast<Door*>(map.getObject(q));
      std::cout << pp << ' ' << d;
      if (pp != nullptr && d != nullptr) {
        pp->activateObj = d;
        d->activatorObj = pp;
      }
    } else if (command == "save") {
      game_func::save(levelFile, map, camera);
    } else if (command == "load") {
      std::string address;
      std::cout << "Enter address: ";
      std::cin >> address;
      game_func::load(address, map, wintile, mobQueue, player, camera);
      if (wintile != nullptr)
        wintileExists = true;
    }
  }
}
