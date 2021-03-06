# Makefile pour TP2.
# Adaptez ce fichier au besoin (si vous ajouter des fichiers).


# Choisir l'une des deux configurations (-g: Debug | -O2: Release)
#OPTIONS = -g -O0 -Wall
OPTIONS = -O2 -Wall 

all : tp2 

tp2 : tp2.cpp date.o epicerie.o pointst.o
	g++ ${OPTIONS} -o tp2 tp2.cpp date.o epicerie.o pointst.o
	
pointst.o : pointst.cpp pointst.h
	g++ ${OPTIONS} -c -o pointst.o pointst.cpp 

date.o : date.cpp date.h
	g++ ${OPTIONS} -c -o date.o date.cpp

epicerie.o : epicerie.cpp epicerie.h pointst.h arbreavl.h tableau.h 
	g++ ${OPTIONS} -c -o epicerie.o epicerie.cpp

clean:
	rm -rf tp2 testdate *~ *.o log*.txt rapport*.txt *+.txt

