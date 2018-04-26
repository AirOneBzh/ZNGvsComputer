#exemple de Makefile avec une version debug
#rajouter l'option -DTOTO signifie que l'on rajoute un #define TOTO au programme
#la constante toto sera connue de tout le programme

CC = gcc
#compilateur
CFLAGS = -Wall -std=c11 `pkg-config --cflags MLV`
#option  -DTOTO   ->  = #define
LDFLAGS =`pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`
#-lm  #librairies par math rajouter - lm
DEBUG = -Wall -std=c11 -g
# -DDEBUG

LISTEPROG = src/allocation.o src/mon_erreur.o src/interface.o src/jeu.o src/main.o
SRC= $(wildcard src/*.c)
OBJ= $(SRC:.c=.o)

all:clean prog propre

PATH_SRC=../src/
LISTETEST=  $(PATH_SRC)allocation.o $(PATH_SRC)mon_erreur.o $(PATH_SRC)interface.o $(PATH_SRC)jeu.o test_jeu.o
test: clean prog_test propre

prog_test: $(LISTETEST)
	@$(CC) $^ -o $@ $(lDFLAGS) $(CFLAGS) $(LDLIBS)

cd:
	cd tests

prog : $(LISTEPROG)
	@$(CC) $^ -o $@ $(lDFLAGS) $(CFLAGS) $(LDLIBS)
	#
	# Lancer bin/prog pour lancer le programme
	#     make debug     pour trouver segfault
	#
#dans la ligne du dessus il y a une tabulation en debut ligne !!


%.o: %.c
	@$(CC) -o $@ -c $< $(lDFLAGS) $(CFLAGS) $(LDLIBS)

obj/%do:src/%c
	$(CC) $(DEBUG) -o obj/$@ -c $<


clean :
	@rm -f src/*.o src/*.do prog progdebug

propre :
	@rm -f src/*.o
