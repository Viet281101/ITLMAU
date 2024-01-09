
all: tp5

COURS = ASD2
DEVOIR = TP5
PROGRAMMER = Viet_NGUYEN-20006303

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
DELPROGNAME = a.out [$(COURS)]_$(DEVOIR)_$(PROGRAMMER).zip

DISTDIRNAME = $(COURS)_$(DEVOIR)_$(PROGRAMMER) #nom du dossier pour la création de l'archive



tp5: tp5.c
	$(CC) $(CFLAGS) tp5.c -o tp5

run:
	./tp5

distdir: tp5.c ASD2_TD5.pdf Makefile test
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


