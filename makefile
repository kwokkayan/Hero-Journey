FLAGS = -std=c++11 -pedantic-errors
OBJECTCODES = testmain.o thingsClasses.o map.o camera.o
TARGET = testmain
thingsClasses.o: thingsClasses.cpp thingsClasses.h
	g++ $(FLAGS) -c $<
map.o: map.cpp map.h
	g++ $(FLAGS) -c $<
camera.o: camera.cpp camera.h
	g++ $(FLAGS) -c $<
testmain.o: testmain.cpp
	g++ $(FLAGS) -c $<
$(TARGET): $(OBJECTCODES)
	g++ $(FLAGS) $(OBJECTCODES) -o $@
clean:
	rm $(OBJECTCODES) $(TARGET)
all: $(OBJECTCODES) $(TARGET)
.PHONY: clean all
