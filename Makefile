all : executable

executable : main.o chaineDeProduction.o
	gcc -o executable main.o chaineDeProduction.o -pthread -lpthread

main.o : main.c chaineDeProduction.h
	gcc -c main.c -pthread -lpthread

chaineDeProduction.o : chaineDeProduction.c 
	gcc -c chaineDeProduction.c -pthread -lpthread

clean :
	rm main.o chaineDeProduction.o executable 