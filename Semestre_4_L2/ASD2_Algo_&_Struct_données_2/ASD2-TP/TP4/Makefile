
all: tp4

COURS = ASD2
DEVOIR = TP4
PROGRAMMER = Viet_NGUYEN-20006303

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
DELPROGNAME = a.out [$(COURS)]_$(DEVOIR)_$(PROGRAMMER).zip

DISTDIRNAME = $(COURS)_$(DEVOIR)_$(PROGRAMMER) #nom du dossier pour la création de l'archive



tp4: tp4.c
	$(CC) tp4.c

winrun: 
	a.out tp4_db.csv
run: 
	./a.out tp4_db.csv

distdir: tp4.c tp4_db.csv ASD2_TD4.pdf Makefile README.md
#supprime le dossier dans lequel on met les copies de se qu'on va zip
#on recréer le dossier
#on y met les copies des fichiers à mettre dans le zip
	rm -rf $(DISTDIRNAME)
	mkdir $(DISTDIRNAME) && cp -rf $^ $(DISTDIRNAME) 

dist: clean distdir
#on zip le dossier qu'on a remplit dans la cible distdir
#on supprime le dossier
	zip -r [$(COURS)]_$(DEVOIR)_$(PROGRAMMER).zip $(DISTDIRNAME)
	rm -rf $(DISTDIRNAME)

clean: 
	find . -name "*.o" -delete
	find . -name "*.a" -delete
	@$(RM) -r $(DELPROGNAME)
	@$(RM) -rf $(DISTDIRNAME)


