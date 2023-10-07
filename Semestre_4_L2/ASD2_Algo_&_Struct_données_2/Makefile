# définition des constantes 
CC= gcc
CPPFLAGS= -I. # ici chercher des includes dans le dossier "." en priorité
CFLAGS= -Wall -Wextra -g 

DISTDIR=rendu
# cible principale (par défaut)
all: foobar

# phase de link : gcc -flags dépendances -o executable
foobar: foobar.o foo.o bar.o
	$(CC) $(CPPFLAGS) $(CFLAGS) foobar.o foo.o bar.o -o foobar
	
# assemblage : gcc -flags -c source.c
foobar.o: foobar.c foo.h bar.h
	$(CC) $(CPPFLAGS) $(CFLAGS) -c foobar.c 
	
# cible clean
clean: 
	rm *.o foobar
	
distdir: foobar.c foo.h bar.h foo.c bar.c Makefile
	rm -r $(DISTDIR)
	mkdir $(DISTDIR) && cp -rf $^ $(DISTDIR) 

# ici on veut que make dist déclenche distdir
dist: distdir
	tar zcvf $(DISTDIR).tgz $(DISTDIR)
	rm -rf $(DISTDIR)

	
