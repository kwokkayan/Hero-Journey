CC = g++
CPPFLAGS = -std=c++11 -pedantic-errors
TARGET = testmain
OBJECTCODES = baseClasses.o moveable.o openable.o camera.o colorIO.o door.o void.o wall.o floor.o gameFunctions.o map.o objectStack.o zombie.o snake.o player.o pressurePlate.o rock.o testmain.o
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<
$(TARGET): $(OBJECTCODES)
	$(CC) $(CPPFLAGS) $(OBJECTCODES) -o $@
clean:
	rm $(OBJECTCODES) $(TARGET)
all:
	$(TARGET)
.PHONY: clean all
