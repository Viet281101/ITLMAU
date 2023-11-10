#Compilation générique avec makefile 

CC=gcc

main:		main.o matriceadj.o listeadj.o affichage.o fifo.o heap.o matriceadj.h listeadj.h affichage.h fifo.h heap.h
		$(CC) main.o matriceadj.o listeadj.o affichage.o heap.o fifo.o -o main


#matriceadj:	matriceadj.o affichage.o fifo.o matriceadj.h fifo.h affichage.h
#		$(CC) matriceadj.o affichage.o fifo.o -o matriceadj
		
#listeadj:	listeadj.o affichage.o heap.o listeadj.h heap.h affichage.h
#		$(CC) listeadj.o affichage.o fifo.o -o listeadj

clean:
	@rm -f *.o
	@rm -f core
	@rm -f *~
	@rm -r main


