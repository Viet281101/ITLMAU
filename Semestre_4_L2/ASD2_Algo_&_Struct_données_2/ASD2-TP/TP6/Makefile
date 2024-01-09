


all: tp6

COURS = ASD2
DEVOIR = TP6
PROGRAMMER = Viet_NGUYEN-20006303

CC = gcc
CFLAGS = -Wall -Wextra
C11 = -std=c11
CMZONE = -g -fsanitize=address
RM = rm -f
DELPROGNAME = a.out [$(COURS)]_$(DEVOIR)_$(PROGRAMMER).zip
DELFILE = tp6 test_variables exam1
DISTDIRNAME = $(COURS)_$(DEVOIR)_$(PROGRAMMER) #nom du dossier pour la création de l'archive



tp6: tp6.c
	$(CC) $(CFLAGS) test_variables.c -o test_variables
	$(CC) $(CFLAGS) question2.4.c -o exam1
	$(CC) $(CFLAGS) $(CMZONE) tp6.c -o tp6

run:
	./tp6


distdir: tp6.c ASD2_TD6.pdf Makefile dijkstra.c dijkstra.h test_variables.c question2.4.c
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
	@$(RM) -r $(DELFILE)
	@$(RM) -rf $(DISTDIRNAME)




