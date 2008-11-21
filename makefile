CC=g++
CFLAGS=-c -w -g
LDFLAGS=-w -g ../../GUI.o ../../Window.o ../../Graph.o -lfltk -lXft -lfltk_images
SOURCES=Gamelan_Window.h Gamelan_Window.cpp Gamelan.cpp Gam_String.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=game
	 
all: $(EXECUTABLE)
	  
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
		 
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
		 
clean:
	rm -f *.o game
