game: dist/main.o dist/engine.o dist/character.o dist/bullet.o dist/enemy.o
	g++ $^ -o game -lallegro -lallegro_primitives -lallegro_image

dist/main.o: main.cpp
	g++ -c main.cpp -o dist/main.o

dist/engine.o: lib/engine.h lib/engine.cpp
	g++ -c lib/engine.cpp -o dist/engine.o

dist/character.o: lib/character.h lib/character.cpp lib/engine.h
	g++ -c lib/character.cpp -o dist/character.o

dist/bullet.o: lib/bullet.h lib/bullet.cpp lib/engine.h
	g++ -c lib/bullet.cpp -o dist/bullet.o

dist/enemy.o: lib/enemy.h lib/enemy.cpp lib/engine.h
	g++ -c lib/enemy.cpp -o dist/enemy.o

run: game
	./game
