GTKMM = #gtkmm-3.0
CFLAGS = `pkg-config --cflags gtk+-3.0 $(GTKMM)`
LIBS = `pkg-config --libs gtk+-3.0 $(GTKMM)`
SOURCE_FILES = main.cpp \
	line.cpp \
	object.cpp \
	coordinates.cpp \
	point.cpp \
	wireframe.cpp \
	color.cpp \
	ui.cpp \
	world.cpp \
	window.cpp \
	transformations.cpp \
	matriz1x3.cpp \
	matriz3x3.cpp \
	polygon.cpp \
	#ddata.cpp

simple :
	gcc $(CFLAGS) -o simple $(SOURCE_FILES) $(LIBS) -rdynamic -lstdc++ -std=c++11 -lm

clean :
	rm simple

exec :
	rm simple
	make simple
	./simple
