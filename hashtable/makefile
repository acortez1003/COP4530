proj5.x: proj5.o passserver.o
	g++ -o proj5.x proj5.o passserver.o -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -c passserver.cpp

proj5.o: proj5.cpp passserver.h hashtable.h
	g++ -c proj5.cpp

clean:
	rm -f *.o