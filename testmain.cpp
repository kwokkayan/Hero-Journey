#include <iostream>

#include "thingsClasses.h"
#include "map.h"
#include "camera.h" 
int main() {
  Map map = Map();
  Player player = Player("Derek", 1, 1);
  Object void_obj = Object();
  Rock rock = Rock(2, 2);
  Camera camera = Camera(5, player.pos);

  map.createEmptyMap(10, 10);
  map.insertObject(player, player.pos);
  map.insertObject(rock, rock.pos);

  camera.draw(map);
} 