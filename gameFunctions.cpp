#include "gameFunctions.h"
// getKeystroke() detects keyboard input (one character) without needing to press enter
// by use of system()
// the character is returned
char game_func::getKeystroke() {
  char in;
  std::system("stty raw"); //seting the console not require ending input with enter
  std::cin >> in;
  std::system("stty cooked"); //reseting the console to default
  std::cout << '\n';
  return in;
}
// setFormat(int w) right aligns the line of output
// w is the number of characters that are right aligned
void game_func::setFormat(int w) {
  std::cout << std::right << std::setw(w);
}

// This detects the game input for the player and modifies pos,
// which is the potential new position of the player,
// unless H/h is pressed. If so, the menu is instead opened.
void game_func::detectGameControls(Player *p, Point &pos) {
  char input = game_func::getKeystroke(); // getting the input
  pos = p->pos; // pos is set to player position
  // W A S D is the movement keys of the player
  //  -W is up
  //  -A is left
  //  -S is down
  //  -D is right
  // H opens the menu and therefore pos is set to an invalid value
  // the switch statement defines the changes of pos according to input.
  // If invalid input, a different invalid value is set.
  switch (input) {
    case 'W':
    case 'w': {
      --pos.y; //above player
      break;
    }
    case 'A':
    case 'a': {
      --pos.x; //left to player
      break;
    }
    case 'S':
    case 's': {
      ++pos.y; //below player
      break;
    }
    case 'D':
    case 'd': {
      ++pos.x; //right to player
      break;
    }
    case 'H':
    case 'h': {
      pos = Point(-2, -2); //open menu
      break;
    }
    default:
      pos = Point(); //return -1, -1 for illegal input
  }
}
// This clears the screen by printing \n for t times.
void game_func::clrScr(int t) {
  for (int i = 0; i < t; i++) {
    std::cout << '\n';
  }
}
// This erase the data of all object, mobQueue, and camera
void game_func::clearObjects(Map &map, std::vector<Moveable*> &mobQueue, Camera *&camera) {
  map.deleteMap();
  mobQueue.clear();
  delete camera;
}
// This prints game information for the player and other information
void game_func::drawUI(Player* player) {
  player->printName();
  player->printHP();
  player->printXY();
  std::cout << "Press H/h for the game menu\n";
}
// This draws the different menus of the game defined by the txt address of the menus,
// which is stored by the parameter address.
// With the address, data of the menu is inputted via file I/O.
// ==========================================
// Sample menu txt (comments are in brackets):
// 30 3 (30 is the right align width of the menu, 3 is the lines of text in the menu)
// Sample Menu (1st line)
// Text 1 (2nd line)
// Text 2 (3rd line)
void game_func::drawMenu(std::string address) { //draws menu
  int width, height; //these store the first 2 file inputs
  std::ifstream inFile(address);
  if (inFile.is_open()) {
    inFile >> width >> height;
    std::string s;
    getline(inFile, s);
    game_func::clrScr(20);

    game_func::setFormat(width);
    for (int k = 0; k < width + 2; k++) // Prints the top box container of the menu
      std::cout << '~';
    std::cout << '\n';

    // This prints each line of output according to the txt
    // The output is centered by printing spaces before and after the text.
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
    for (int k = 0; k < width + 2; k++) // Prints the bottom box container of the menu
      std::cout << '~';
    std::cout << '\n';
  } else std::cout << "Menu not found!\n";
  inFile.close();
}
// This handles the inputs for the save menu
// options stores the save id for existing saves.
// When the player selects those saves, they will be prompted to confirm the selection,
// since they new save would overwrite the existing one.
// sel stores the selection of the save.
// if q is inputted the operation would be aborted.
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

    for (std::vector<int>::iterator it = options.begin(); it != options.end(); it++) { // linear search for checking existing saves
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
// This handles the inputs for the load menu
// options stores the save id for existing saves, which can only be chosen.
// sel stores the selection of the existing save.
// if q is inputted the operation would be aborted.
void game_func::selectSlotToLoad(std::vector<int> options, int &sel) {
  bool hasSelectedValid = false;
  while (!hasSelectedValid) {
    char in = game_func::getKeystroke();
    if (in == 'q' || in == 'Q')
      break;
    for (std::vector<int>::iterator it = options.begin(); it != options.end(); it++) { // linear search for checking existing saves
      if (in - 48 == *it) {
        hasSelectedValid = true;
        sel = *it;
      }
    }
  }
}
// This draws the save menu.
// First, the saveMenu.txt is opened and being overwritten.
// Then, By checking the existance of save files, it writes the correct state into the txt.
// I.e. 1: exists! if save1.txt exists
//      0: empty! otherwise
// existingSavesId is updated accordingly.
// After the saveMenu.txt is overwritten, drawMenu is called with the correct address
void game_func::drawSaveMenu(std::vector<int> &existingSavesId) {
  std::string menuAddress = "menu/saveMenu.txt";
  std::string saveDir = "saves/";
  std::ofstream outFile(menuAddress);
  if (outFile.is_open()) {
    outFile << 30 << ' ' << 12 << '\n';
    outFile << "Save Menu\n";
    for (int i = 0; i < 10; i++) { // linear search for existance of save files
      std::ifstream temp(saveDir + "save" + std::to_string(i) + ".txt");
      outFile << i << ": ";
      if (temp.good()) { // checks if the file exists (by opening it)
        outFile << "exists!\n";
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
// This draws the load menu.
// First, the loadMenu.txt is opened and being overwritten.
// Then, By checking the existance of save files, it writes the correct state into the txt.
// I.e. 1: exists! if save1.txt exists, and empty otherwise
// existingSavesId is updated accordingly.
// After the loadMenu.txt is overwritten, drawMenu is called with the correct address
void game_func::drawLoadMenu(std::vector<int> &existingSavesId) {
  std::string menuAddress = "menu/loadMenu.txt";
  std::string saveDir = "saves/";
  std::ofstream outFile(menuAddress);
  if (outFile.is_open()) {
    outFile << 30 << ' ' << 12 << '\n';
    outFile << "Load Menu\n";
    for (int i = 0; i < 10; i++) { // linear search for existance of save files
      std::ifstream temp(saveDir + "save" + std::to_string(i) + ".txt");
      if (temp.good()) { // checks if the file exists (by opening it)
        outFile << i << ": ";
        outFile << "exists!\n";
        existingSavesId.push_back(i);
      }
      temp.close();
    }
  }
  outFile << "Q: Exit\n";
  outFile.close();
  game_func::drawMenu(menuAddress);
}
// This draws the main menu by calling drawMenu with the corresponding address.
void game_func::drawMainMenu() {
  game_func::drawMenu("menu/mainMenu.txt");
}
// This handles the operations of the main menu.
// There are four functions:
//  1. Story mode: starts the game in story mode, with cutscenes and sequential play
//  2. Level Selection: lets players to play individual levels separately
//  3. Load save: lets players to play previous saves
//  4. Leave Game: quits the game
// For functions 1 to 3, the corresponding levels will be loaded,
// which would alter map, wintile, mobQueue, player, camera and isStoryMode.
void game_func::handleMainMenu(int levels, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera, bool &isStoryMode) {
  // functionFlag stores the inputed function's enum for use in switch cases
  // loadedLevel is true when a level is stored
  // hasQuitted is true when the player quits the game
  game_func::mainMenuFunctions functionFlag;
  bool loadedLevel = false;
  bool hasQuitted = false;
  while (!(loadedLevel || hasQuitted || isStoryMode)) { // By use of De Morgan's law, the loop continues until a level is loaded, the player quits the game, or story mode is enabled.
    game_func::drawMainMenu();
    game_func::mainMenuLoop(functionFlag);
    switch (functionFlag) { // switch case to execute the correct functions
      case game_func::mainMenuFunctions::STORY: {
        game_func::readScriptLevel("level1/level1m.txt", map, wintile, mobQueue, player, camera);
        game_func::selectDifficulty(player);
        game_func::printCutScene(1);
        isStoryMode = true;
        break;
      }
      case game_func::mainMenuFunctions::SELECT: {
        std::vector<int> existingSavesId;
        std::vector<int> scriptSavesId;
        bool isScriptFile = false;

        game_func::drawLevelSelectMenu(levels, scriptSavesId, existingSavesId);

        int sel = -1;
        game_func::selectSlotToLoad(existingSavesId, sel);
        if (sel != -1) { // checks whether a valid level is selected
          game_func::setFormat(55);
          std::cout << "You have chosen level " << std::to_string(sel) <<"!\n";
          for (std::vector<int>::iterator it = scriptSavesId.begin(); it != scriptSavesId.end(); it++) {
            if (*it == sel) {
              isScriptFile = true;
              break;
            }
          }
          if (!isScriptFile) {
            std::string address = "level" + std::to_string(sel) + "/level" + std::to_string(sel) + ".txt";
            game_func::load(address, map, wintile, mobQueue, player, camera);
          } else {
            std::string address = "level" + std::to_string(sel) + "/level" + std::to_string(sel) + "m.txt";
            game_func::readScriptLevel(address, map, wintile, mobQueue, player, camera);
          }
          game_func::setFormat(75);
          std::cout << "Load completed! Press any key to continue...";
          char c = getKeystroke();
          game_func::selectDifficulty(player);
          loadedLevel = true;
        }
        break;
      }
      case game_func::mainMenuFunctions::LOAD: {
        std::vector<int> existingSavesId;
        game_func::drawLoadMenu(existingSavesId);

        int sel = -1;
        selectSlotToLoad(existingSavesId, sel);
        if (sel != -1) {
          game_func::setFormat(55);
          std::cout << "You have chosen save " << std::to_string(sel) <<"!\n";
          game_func::load("saves/save" + std::to_string(sel) + ".txt", map, wintile, mobQueue, player, camera);
          game_func::setFormat(75);
          std::cout << "Load completed! Press any key to continue...";
          char c = getKeystroke();
          loadedLevel = true;
        }
        break;
      }
      case game_func::mainMenuFunctions::LEAVEGAME: {
        hasQuitted = true;
        player = nullptr; //for use in loop
        break;
      }
    }
  }
}
// This draws the level select menu.
// Level stores the number of levels (from 1 to level)
// scriptSavesId stores the levels that are written in script format
// existingLevelsId stores levels that exist
// The menu is constructed in a similar way to save and load menus.
// First, the txt is opened.
// Then by checking whether the file exists (in script format or save format),
// the addresses are pushed into the corresponding vectors.
// After the menu txt is written, it is passed to drawMenu.
void game_func::drawLevelSelectMenu(int level, std::vector<int> &scriptSavesId, std::vector<int> &existingLevelsId) {
  std::string menuAddress = "menu/levelSelectMenu.txt";
  std::ofstream outFile(menuAddress);
  if (outFile.is_open()) {
    outFile << 30 << ' ' << level + 2 << '\n';
    outFile << "Level Select Menu\n";
    for (int i = 1; i <= level; i++) { // linear search to check whether the files exist
      std::string address = "level" + std::to_string(i) + "/level" + std::to_string(i) + ".txt";
      outFile << "Level " << i << " : ";
      std::ifstream temp(address);
      if (temp.good()) { // this checks whether the file exists (in script format or save format)
        outFile << "exists!\n";
        existingLevelsId.push_back(i);
      } else {
        std::string scriptAddress = "level" + std::to_string(i) + "/level" + std::to_string(i) + "m.txt";
        std::ifstream temptwo(scriptAddress);
        if (temptwo.good()) {
          outFile << "exists!\n";
          existingLevelsId.push_back(i);
          scriptSavesId.push_back(i);
        } else {
          outFile << "empty!\n";
        }
      }
      temp.close();
    }
  }
  outFile << "Q: Exit\n";
  outFile.close();
  game_func::drawMenu(menuAddress);
}
// This handles the input for the main menu.
// When the user inputs the corresponding key, the corresponding function enum will be set,
// where it is stored in f.
void game_func::mainMenuLoop(game_func::mainMenuFunctions &f) {
  char input = ' ';
  bool hasChosen = false;
  while (!hasChosen) {
    input = game_func::getKeystroke();
    hasChosen = true;
    switch (input) {
      case 'S':
      case 's': {
        f = game_func::mainMenuFunctions::STORY;
        break;
      }
      case 'E':
      case 'e': {
        f = game_func::mainMenuFunctions::SELECT;
        break;
      }
      case 'L':
      case 'l': {
        f = game_func::mainMenuFunctions::LOAD;
        break;
      }
      case 'Q':
      case 'q': {
        f = game_func::mainMenuFunctions::LEAVEGAME;
        break;
      }
      default:
        hasChosen = false;
    }
  }
}
// This handles the input for the in-game menu.
// When the user inputs the corresponding key, the corresponding function enum will be set,
// where it is stored in f.
void game_func::menuLoop(game_func::menuFunctions &f) {
  char input = ' ';
  bool hasChosen = false;
  while (!hasChosen) {
    input = game_func::getKeystroke();
    hasChosen = true;
    switch (input) {
      case 'R':
      case 'r': {
        f = game_func::menuFunctions::RESTART;
        break;
      }
      case 'S':
      case 's': {
        f = game_func::menuFunctions::SAVE;
        break;
      }
      case 'L':
      case 'l': {
        f = game_func::menuFunctions::LOAD;
        break;
      }
      case 'Q':
      case 'q': {
        f = game_func::menuFunctions::LEAVEGAME;
        break;
      }
      case 'H':
      case 'h': {
        f = game_func::menuFunctions::LEAVEMENU;
        break;
      }
      case 'M':
      case 'm': {
        f = game_func::menuFunctions::MAINMENU;
        break;
      }
      default:
        hasChosen = false;
    }
  }
}
// This prints the lose screen, when the lose condition is met
void game_func::printLoseScreen() {
  std::cout << "You have died! :(\n";
  std::cout << "Press any button to return to main menu!";
  char temp = game_func::getKeystroke();
}
// This prints the win screen, when the win conditions are met
void game_func::printWinScreen() {
  std::cout << "You win!\n";
  std::cout << "Press any button to return to main menu!";
  char temp = game_func::getKeystroke();
}
// This reads the level in scripted format
// The file is formated in this way:
// ...
// <Object Type> <Object Parameters> <x position> <y position>
// ...
// ==========================================================
// One special case is linking the pressureplate to a door.
// Then, the following order must be observed.
// ...
// link
// pressureplate <x position> <y position>
// door <x position> <y position>
// ...
// ==========================================================
// the game variables will be set accordingly.
void game_func::readScriptLevel(std::string levelFile, Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&p, Camera *&c) {

  std::ifstream fin;
  fin.open(levelFile.c_str());
  std::string objectType;

  while (fin >> objectType) {
    if (objectType == "map") {
      int width, height, depth = 5;
      fin >> width >> height;
      map.createEmptyMap(width, height, depth);
    } else if (objectType == "player") {
      std::string n;
      int px, py;
      fin >> n >> px >> py;
      p = new Player(n, px, py);
      map.insertObject(p);
    } else if (objectType == "camera") {
      int l;
      fin >> l;
      c = new Camera(l, p->pos);
    } else if (objectType == "link") { //The special case!
      std::string n;
      int px, py;

      fin >> n >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      map.insertObject(pp);

      fin >> n >> px >> py;
      Door *d = new Door(px, py);
      map.insertObject(d);

      pp->activateObj = d;
      d->activatorObj = pp;
    } else if (objectType == "door") {
      int px, py;
      fin >> px >> py;
      Door *d = new Door(px, py);
      map.insertObject(d);
    } else if (objectType == "pressureplate") {
      int px, py;
      fin >> px >> py;
      PressurePlate *pp = new PressurePlate(px, py);
      map.insertObject(pp);
    } else if (objectType == "rock") {
      int px, py;
      fin >> px >> py;
      Rock *r = new Rock(px, py);
      map.insertObject(r);
    } else if (objectType == "wall") {
      bool isSideWall;
      int px, py;
      fin >> isSideWall >> px >> py;
      Wall *w = new Wall(isSideWall, px, py);
      map.insertObject(w);
    } else if (objectType == "zombie") {
      int px, py;
      fin >> px >> py;
      Zombie *z = new Zombie(px, py);
      mobQueue.push_back(z);
      map.insertObject(z);
    } else if (objectType == "snake") {
      int px, py;
      fin >> px >> py;
      Snake *s = new Snake(p, px, py);
      mobQueue.push_back(s);
      map.insertObject(s);
    } else if (objectType == "wintile") {
      int px, py;
      fin >> px >> py;
      wintile = new WinTile(px, py);
      map.insertObject(wintile);
    } else if (objectType == "infotile") {
      std::string address;
      int px, py;
      fin >> address >> px >> py;
      InfoTile *infotile = new InfoTile(address, px, py);
      map.insertObject(infotile);
    }
  }
}
// This is the mainloop of the program. Handles the game, most menus and executing menu functions.
// in each iteration, the following will be executed:
//   1. Game information like health is displayed
//   2. The camera is displayed
//   3. The winning conditions will be checked
//     3.1. If winning conditions met, then execute the corresponding functions according to gamemode and levels
//   4. The losing codition will be checked
//     4.1. If losing conditions met, the game will be aborted and return to main menu
//   5. The game inputs are detected (W A S D H)
//   6. If H is inputted, open the menu and start the menu loop.
//     6.1 Detect menu input and execute the corresponding functions
//        (Restart, Save, Load, Quit Game, Quit Menu, Return to Main Menu)
//   7. Movement is checked and the gamestate is updated if it is valid
//   8. MobQueue, which stores all mobs, is processed:
//     8.1 if the mob is flagged for destruction, it is removed from the game, and the loop moves to the next
//     8.2 Mob moves and the gamestate is updated
//   9. The console is cleared for the next iteration
void game_func::gameLoop(Map &map, WinTile *&wintile, std::vector<Moveable*> &mobQueue, Player *&player, Camera *&camera, bool &isStoryMode, bool &returnMainMenu) {
  Point newP = Point();
  //initial load here
  int currentlevel = 1; //for storymode
  bool hasQuitted = false;
  bool noUpdate = false;
  int currentHealth = player->hp;

  game_func::save("saves/autosave.txt", map, camera);
  while (true) {
    game_func::drawUI(player);
    camera->draw(map);
    if (wintile->hasWon) { //Wining condition
      if (!isStoryMode) {
        game_func::printWinScreen();
        returnMainMenu = true;
        break;
      } else if (currentlevel == 5) {
        game_func::printCutScene(6);
        returnMainMenu = true;
        break;
      } else {
        ++currentlevel;
        std::string currlevelFile = "level" + std::to_string(currentlevel) + "/level" + std::to_string(currentlevel) + "m.txt";
        game_func::clearObjects(map, mobQueue, camera);
        game_func::readScriptLevel(currlevelFile, map, wintile, mobQueue, player, camera);
        player->hp = currentHealth;
        game_func::save("saves/autosave.txt", map, camera);
        game_func::printCutScene(currentlevel);
        continue;
      }
    }
    if (player->hp <= 0) { // Losing condition
      game_func::printLoseScreen();
      returnMainMenu = true;
      break;
    }

    game_func::detectGameControls(player, newP);
    if (newP.equalsTo(-2, -2)) { // Opening the menu
      game_func::drawMenu("menu/menu.txt");
      game_func::menuFunctions selection;
      game_func::menuLoop(selection);
      switch (selection) {
        case game_func::menuFunctions::RESTART: {
          game_func::setFormat(55);
          std::cout << "Restarting...\n";
          map.deleteMap();
          mobQueue.clear();
          delete camera;
          game_func::load("saves/autosave.txt", map, wintile, mobQueue, player, camera);
          game_func::setFormat(75);
          std::cout << "Restart completed! Press any key to continue...";
          char c = getKeystroke();
          break;
        }
        case game_func::menuFunctions::SAVE: {
          std::vector<int> existingSavesId;
          game_func::drawSaveMenu(existingSavesId);;
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
        case game_func::menuFunctions::LOAD: {
          std::vector<int> existingSavesId;
          game_func::drawLoadMenu(existingSavesId);
          int sel = -1;
          selectSlotToLoad(existingSavesId, sel);
          if (sel != -1) {
            game_func::setFormat(55);
            std::cout << "You have chosen save " << std::to_string(sel) <<"!\n";
            game_func::clearObjects(map, mobQueue, camera);
            game_func::load("saves/save" + std::to_string(sel) + ".txt", map, wintile, mobQueue, player, camera);
            game_func::setFormat(75);
            std::cout << "Load completed! Press any key to continue...";
            char c = getKeystroke();
          }
          break;
        }
        case game_func::menuFunctions::LEAVEGAME: {
          hasQuitted = true;
          break;
        }
        case game_func::menuFunctions::LEAVEMENU: {
          break;
        }
        case game_func::menuFunctions::MAINMENU: {
          returnMainMenu = true;
          break;
        }
      }
      if (hasQuitted || returnMainMenu)
        break;
      continue;
    }

    if (!newP.equalsTo(-1, -1) && player->check(newP, map)) {
      camera->camera_pos = player->pos;
      map.updateMap(player->pos, 3);
    }
    for (std::vector<Moveable*>::iterator it = mobQueue.begin(); it != mobQueue.end(); it++) {
      if ((*it)->destroyFlag) {
        Object *target = map.removeObject((*it)->pos);
        if (target->id != (*it)->id) {
          Object *realTarget = map.removeObject((*it)->pos);
          map.insertObject(target);
          target = realTarget;
        }
        mobQueue.erase(it);
        delete target;
        break;
      }
      (*it)->move(map);
      (*it)->dealDmg(player);
      map.updateMap((*it)->pos, 3);
      currentHealth = player->hp;
    }
    game_func::clrScr(30); //clear the screen
  }
}
// This saves the gamestate to the a save file with the address.
// The save file starts from 0, 0 to mapwidth - 1, mapheight -1
// The save file is formatted as follows:
// <map width> <map height> <map depth>
// <camera length>
// <Object id> <Object parameters>
// end
// ...
// =====================================
// For pressureplates and doors, the line will be as follows:
// <Object id> <Object parameters> <door/pressureplate x pos> <door/pressureplate y pos>
// end
void game_func::save(std::string address, Map map, Camera *c) {
  std::ofstream outFile(address);
  if (outFile.is_open()) {
    outFile << map.getWidth() << ' ' << map.getHeight() << ' ' << map.getDepth() << '\n';
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
              outFile << static_cast<int>(p->id) << ' ' << p->name  << ' ' << p->hp << ' ' << p->justTookDmg << ' ' << p->justHealed << '\n';
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
// This loads the gamestate from a save file
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
        //std::cout << "x, y: " << j << ' ' << i << '\n';
        while (true) {
          std::string s;
          getline(inFile, s);
          if (s == "end")
            break;
          std::istringstream stringIn(s);
          int numId;
          stringIn >> numId;
          ObjectId id = static_cast<ObjectId>(numId);
          //std::cout << s << '\n';
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
              bool jtd, jh;
              stringIn >> n >> hp >> jtd >> jh;
              p->name = n; //so ugly, but snakeeee
              p->hp = hp;
              p->justTookDmg = jtd;
              p->justHealed = jh;
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
              //std::cout << activator.x << " " << activator.y << " door\n";
              Door *d = new Door(io, j, i);
              if (activator.equalsTo(-1, -1) || (activator.y > i || (activator.y == i && activator.x > j))) {
                d->activatorObj = nullptr;
              } else {
                PressurePlate *ob = dynamic_cast<PressurePlate*>(map.getObject(activator));
                //std::cout << ob << " door\n";
                if (ob == nullptr) {
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

void game_func::printCutScene(int num) {
  std::string address = "cutscenes/" + std::to_string(num) + ".txt";
  std::ifstream inFile(address);
  game_func::clrScr(6);
  std::cout << "Cutscene " << num << "\n\n";
  if (inFile.is_open()) {
    std::string s;
    while (getline(inFile, s))
      std::cout << s << '\n';
  } else {
    std::cout << "cutscene " << num << " not created yet!";
  }
  if (num == 6)
    std::cout <<"\nPress any button to return to main menu...";
  else
    std::cout << "\nPress any button to start...";
  char temp = game_func::getKeystroke();
  inFile.close();
}
void game_func::selectDifficulty(Player *&player) {
  game_func::drawMenu("menu/difficultyMenu.txt");
  bool selectedValid = false;
  while (!selectedValid) {
    selectedValid = true;
    char sel = game_func::getKeystroke();
    switch (sel) {
      case '0': {
        player->hp = 50;
        break;
      }
      case '1': {
        player->hp = 25;
        break;
      }
      case '2': {
        player->hp = 10;
        break;
      }
      case '3': {
        player->hp = 1;
        break;
      }
      case '4': {
        player->hp = rand() % 50 + 1;
        break;
      }
      default : {
        selectedValid = false;
      }
    }
  }
}
