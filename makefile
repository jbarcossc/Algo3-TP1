all:
	g++ -o main main.cpp numeroMagico.cpp auxiliares.cpp numerosMagicos.h auxiliares.h -O3 -std=c++14

clean:
	rm -rf main