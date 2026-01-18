all: main.o generator.o
	g++ build/main.o build/generator.o -o build/fractal -lSDL2

prepare:
	mkdir build

generator.o: src/generator.cpp
	g++ -c src/generator.cpp -o build/generator.o

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

clean:
	rm build/*.o build/fractal

run:
	./build/fractal