
all: compile link run

compile:
	g++ -c Main.cpp -I"C:\Users\Arina1\Documents\mylibraries\SFML-2.5.1\include" -DSFML_STATIC

link:
	g++ Main.o -o Main -L"C:\Users\Arina1\Documents\mylibraries\SFML-2.5.1\lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main

clean:
	rm -f  Main *.o

run:
	 .\Main
