#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@up8.edu
#  Date   : 21/09/2021

# définition des commandes utilisées
CC = gcc
ECHO = echo
RM = rm -f
TAR = tar
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R

# déclaration des options du compilateur
CFLAGS = -Wall -O3
CPPFLAGS = -I.
LDFLAGS = -lm

# définition des fichiers et dossiers
PROGNAME = static_2d_array
VERSION = 1.1
distdir = $(PROGNAME)-$(VERSION)
HEADERS = 
SOURCES = static_2d_array.c
OBJ = $(SOURCES:.c=.o)
DISTFILES = $(SOURCES) Makefile $(HEADERS)

# Traitements automatiques des dépendances
all: $(PROGNAME)
$(PROGNAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)
distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz gmon.out core.*
