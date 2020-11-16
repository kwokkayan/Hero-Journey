#include <iostream>
#include <fstream>
#include <vector>

#include "baseClasses.h"
#include "colorIO.h"
#include "moveable.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"
#include "player.h"
#include "door.h"
#include "floor.h"
#include "pressurePlate.h"
#include "zombie.h"
#include "rock.h"
#include "wall.h"

void levelObject(std::string levelFile, Map &map, std::vector<Moveable*> &mobQueue, Player* p, Camera* c) {

  std::ifstream fin;
  fin.open(levelFile.c_str());
  std::cout << "opened file\n";
  std::string objectType;

  while (fin >> objectType) {
    if (objectType == "player") {
      std::cout << "if player begin\n";
      std::string n;
      int px, py;
      fin >> n >> px >> py;
      p = new Player(n, px, py);
      map.insertObject(p);
      std::cout << "if player end\n";
    }
    else if (objectType == "camera") {
      int l;
      fin >> l;
      c = new Camera(l, p->pos);
    }
    else if (objectType == "door") {
      int px, py;
      fin >> px >> py;
      Door *d = new Door(px, py);
      map.insertObject(d);
    }
    else if (objectType == "pressureplate") {
      int px, py;
      fin >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      map.insertObject(pp);
    }
    else if (objectType == "rock") {
      int px, py;
      fin >> px >> py;
      Rock *r = new Rock(px, py);
      map.insertObject(r);
    }
    else if (objectType == "wall") {
      bool isSideWall;
      int px, py;
      fin >> isSideWall >> px >> py;
      Wall *w = new Wall(isSideWall, px, py);
      map.insertObject(w);
    }
    else if (objectType == "zombie") {
      int px, py;
      fin >> px >> py;
      Zombie *z = new Zombie(px, py);
      mobQueue.push_back(z);
      map.insertObject(z);
    }
  }
  std::cout << "Finished reading objects\n";
}
