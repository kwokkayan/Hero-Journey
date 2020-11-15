 // Filename: testmain.cpp
// Description: Program that tests the classes and functions
// Last Changed: 5 Nov, 2020
#include <iostream>


#include "baseClasses.h"
#include "colorIO.h"
#include "objectStack.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"

int main() {
  Map map = Map();

  Player *player = new Player("Derek", 2, 4);
  Camera *camera = new Camera(10, player->pos);

  Rock *rock = new Rock(2, 2);
  Rock *rockk = new Rock(2, 3);


  Door *door = new Door(5, 5);
  Door *door2 = new Door(10, 10);
  PressurePlate *pp = new PressurePlate(3, 3);

  pp->activateObj = door; //These lines link the pressurePlate to the door
  door->activatorObj = pp;

  std::cout << "Creating map...\n";
  map.createEmptyMap(100, 100, 5); //Creates an empty map with walled borders
  map.insertObject(player); //inserts player into the map

  map.insertObject(rock);
  map.insertObject(rockk);

  map.insertObject(door);
  map.insertObject(pp);

  map.insertObject(door2);

  std::cout << "Map created!\n";
  //Player movement
  Point p = Point();
  do {
    camera->draw(map);
    p = game_func::detectGameControls(player);
  } while (game_func::processControls(p, map, camera, player) != -1);
}
