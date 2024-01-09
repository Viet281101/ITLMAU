#  Makefile 
#  Auteur : Farès BELHADJ
#  Email  : amsi@up8.edu
#  Date   : 17/10/2022
# définition des commandes utilisées
CC = gcc
CXX = g++
ECHO = echo
RM = rm -f
TAR = tar
ZIP = zip
MKDIR = mkdir
CHMOD = chmod
CP = rsync -R -r
# déclaration des options du compilateur
CFLAGS = -Wall -O2
CPPFLAGS = -I.
LDFLAGS = 
# définition des fichiers et dossiers
PACKNAME = pa
PROGNAME = home_made_bt_VS_set
VERSION = 0.5
distdir = $(PACKNAME)_$(PROGNAME)-$(VERSION)
HEADERS = bt.h my_timer.h
SOURCES = test_them.cpp my_timer.c
OBJT = $(SOURCES:.c=.o)
OBJ = $(OBJT:.cpp=.o)
DOC = documentation/html documentation/Doxyfile
EXTRAFILES = Makefile COPYING 
DISTFILES = $(SOURCES) $(HEADERS) $(DOC) $(EXTRAFILES)

all: $(PROGNAME)
$(PROGNAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(PROGNAME)
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
dist: distdir
	$(CHMOD) -R a+r $(distdir)
	$(TAR) zcvf $(distdir).tgz $(distdir)
	$(RM) -r $(distdir)
zip: distdir
	$(CHMOD) -R a+r $(distdir)
	$(ZIP) -r $(distdir).zip $(distdir)
	$(RM) -r $(distdir)
distdir: $(DISTFILES)
	$(RM) -r $(distdir)
	$(MKDIR) $(distdir)
	$(CHMOD) 777 $(distdir)
	$(CP) $(DISTFILES) $(distdir)
documentation/html: documentation/Doxyfile $(SOURCES) $(HEADERS)
	cat $< | sed -e "s/PROJECT_NAME *=.*/PROJECT_NAME = $(PROGNAME)/" |\
	  sed -e "s/PROJECT_NUMBER *=.*/PROJECT_NUMBER = $(VERSION)/" >> $<.new
	mv -f $<.new $<
	cd documentation && doxygen && cd ..
doc: documentation/html
clean:
	@$(RM) -r $(PROGNAME) $(OBJ) *~ $(distdir).tgz $(distdir).zip gmon.out	\
	  core.* documentation/*~ documentation/html
