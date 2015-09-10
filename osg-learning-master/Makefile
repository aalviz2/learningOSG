all: learn1 cubeman 2cubes 2cubesMove 2dtextures 3dtextures

learn1: learn1.cpp
	g++ -o learn1 learn1.cpp -losg -losgViewer -losgGA

2cubes: 2cubes.cpp
	g++ -o 2cubes 2cubes.cpp -losg -losgViewer -losgGA

2cubesMove: 2cubesMove.cpp
	g++ -o 2cubesMove 2cubesMove.cpp -losg -losgViewer -losgGA

cubeman: cubeman.cpp
	g++ -o cubeman cubeman.cpp -losg -losgViewer -losgGA

2dtextures: 2dtextures.cpp
	g++ -o 2dtextures 2dtextures.cpp -losg -losgViewer -losgGA -losgDB

3dtextures: 3dtextures.cpp
	g++ -o 3dtextures 3dtextures.cpp -losg -losgViewer -losgGA -losgDB

clean:
	rm -f learn1 2cubes 2cubesMove cubeman 2dtextures 3dtextures
