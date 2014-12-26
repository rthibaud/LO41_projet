all : executable

executable : main.o chaineDeProduction.o
	gcc -o executable main.o chaineDeProduction.o -pthread

main.o : main.c chaineDeProduction.h
	gcc -c main.c -pthread

chaineDeProduction.o : chaineDeProduction.c chaineDeProduction.h 
	gcc -c chaineDeProduction.c -pthread

clean :
	rm main.o chaineDeProduction.o executable 