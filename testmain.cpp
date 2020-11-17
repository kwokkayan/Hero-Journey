 // Filename: testmain.cpp
// Description: Program that tests the classes and functions
// Last Changed: 5 Nov, 2020
#include <iostream>
#include <vector>

#include "baseClasses.h"
#include "moveable.h"
#include "colorIO.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "zombie.h"
#include "snake.h"
#include "winTile.h"
#include "infoTile.h"
#include "gameFunctions.h"

int main() {
  Map map;
  WinTile *wintile = nullptr;
  std::vector<Moveable*> mobQueue;
  Player *player = nullptr;
  Camera *camera = nullptr;
  if (false) {
    map = Map();
    //Always remember to create an empty map before inserting objects!
    map.createEmptyMap(20, 20, 3);

    player = new Player("Derek", 2, 4);
    camera = new Camera(18, player->pos);

    //NEW: wintile and infotile
    wintile = new WinTile(10, 6);
    InfoTile *infotile = new InfoTile("sample_text/sample.txt", 10, 8);

    Rock *rock = new Rock(10, 1);
    Rock *rockk = new Rock(9, 2);
    Rock *rockkk = new Rock(11, 2);
    Rock *rockkkk = new Rock(10, 3);

    Door *door = new Door(5, 5);
    Door *door2 = new Door(10, 10);
    PressurePlate *pp = new PressurePlate(3, 3);

    // These lines link the pressurePlate to the door
    pp->activateObj = door;
    door->activatorObj = pp;

    // Sample declaration of multiple mobs
    // Remember to use a vector to store them!
    // So that I may process them!
    Snake *s = nullptr;
    for (int j = 0; j < 1; j++) {
      for (int i = 1; i <= 2; i++) {
        s = new Snake(player, i, 10 + j);
        mobQueue.push_back(s);
        map.insertObject(s);
      }
    }
    s = new Snake(player, 1, 1);
    mobQueue.push_back(s);
    map.insertObject(s);

    Zombie *z = new Zombie(10, 2);
    map.insertObject(z);
    mobQueue.push_back(z);

    // Don't forget to insert the declared objects!
    map.insertObject(player);
    map.insertObject(wintile);
    map.insertObject(infotile);

    map.insertObject(rock);
    map.insertObject(rockk);
    map.insertObject(rockkk);
    map.insertObject(rockkkk);
    map.insertObject(door);
    map.insertObject(pp);
    map.insertObject(door2);

    // Pass through the initialised map, mobQueue, player and camera
    // To start the game
    game_func::save("saves/save1.txt", map, camera);
  } else {
    game_func::load("saves/save1.txt", map, wintile, mobQueue, player, camera);
  }
  game_func::gameLoop(map, wintile, mobQueue, player, camera);
}
