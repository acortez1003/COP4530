proj4.x: BET.o proj4_driver.o
	g++ -o proj4.x BET.o proj4_driver.o

BET.o: BET.cpp BET.h
	g++ -c BET.cpp

proj4_driver.o: proj4_driver.cpp BET.h
	g++ -c proj4_driver.cpp

clean:
	rm *.o proj4.x