GTKMM = #gtkmm-3.0
CFLAGS = `pkg-config --cflags gtk+-3.0 $(GTKMM)`
LIBS = `pkg-config --libs gtk+-3.0 $(GTKMM)`
SOURCE_FILES = $(wildcard *.cpp)

simple :
	gcc $(CFLAGS) -o simple $(SOURCE_FILES) $(LIBS) -rdynamic -lstdc++ -std=c++11 -lm

clean :
	rm simple

exec :
	make simple
	./simple
	rm simple