driver: driver.o
	g++ -o driver.x driver.o

driver.o: driver.cpp tvector.h tvector.hpp
	g++ -c driver.cpp

mydriver: mydriver.o
	g++ -o mydriver.x mydriver.o

mydriver.o: mydriver.cpp tvector.h tvector.hpp
	g++ -c mydriver.cpp

clean:
	rm *.o driver.x mydriver.x