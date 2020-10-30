#include <iostream>

#include "thingsClasses.h"
#include "map.h"
#include "camera.h"
#include "gameFunctions.h"
int main() {
  Map map = Map();
  Player player = Player("Derek", 4, 4);
  Object void_obj = Object();
  Rock rock = Rock(2, 2);
  Camera camera = Camera(12, player.pos);

  map.createEmptyMap(20, 20, 5);
  map.insertObject(player, player.pos);
  map.insertObject(rock, rock.pos);

  //Player movement
  do {
    camera.draw(map);
  } while (game_func::detectGameControls(map, camera, player) != -1);
}
