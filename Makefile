#exemple de Makefile avec une version debug
#rajouter l'option -DTOTO signifie que l'on rajoute un #define TOTO au programme
#la constante toto sera connue de tout le programme

CC = gcc
#compilateur
CFLAGS = -Wall -std=c11 -ansi `pkg-config --cflags MLV`
#option  -DTOTO   ->  = #define
LDFLAGS =`pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`
#-lm  #librairies par math rajouter - lm
DEBUG = -Wall -std=c11 -g
# -DDEBUG

LISTEPROG = include/allocation.o include/mon_erreur.o include/interface.o include/jeu.o include/pile.o include/liste.o include/IA.o include/main.o
SRC= $(wildcard include/*.c)
OBJ= $(SRC:.c=.o)

all:clean prog propre

PATH_SRC=../include/
debug: clean prog propre
	gdb prog

prog_test: $(LISTETEST)
	@$(CC) $^ -o $@ $(lDFLAGS) $(CFLAGS) $(LDLIBS)

cd:
	cd tests

prog : $(LISTEPROG)
	@$(CC) $^ -o $@ $(lDFLAGS) $(CFLAGS) $(LDLIBS)
	#
	# Lancer prog pour lancer le programme
	#     make debug   et run  pour trouver segfault
	#
#dans la ligne du dessus il y a une tabulation en debut ligne !!


%.o: %.c
	@$(CC) -o $@ -c $< $(lDFLAGS) $(CFLAGS) $(LDLIBS)

obj/%do:include/%c
	$(CC) $(DEBUG) -o obj/$@ -c $<


clean :
	@rm -f include/*.o include/*.do prog progdebug

propre :
	@rm -f include/*.o include/*.do 
