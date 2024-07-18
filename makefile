#Ruth Massock
#07/19/2024
#Assignment 6
all: sproj6.x proj6.x

proj6.x: passserver.o proj6.o
	g++ -std=c++11 -o proj6.x proj6.o passserver.o -lcrypt 

sproj6.x: passserver.o sproj6.o
	g++ -std=c++11 -o sproj6.x sproj6.o passserver.o  -lcrypt

passserver.o: passserver.h passserver.cpp hashtable.h hashtable.hpp
	g++ -std=c++11 -c passserver.cpp

proj5.o: passserver.h hashtable.h proj6.cpp
	g++ -std=c++11 -c proj6.cpp
sproj5.o: passserver.h hashtable.h sproj6.cpp
	g++ -std=c++11 -c sproj6.cpp
base64.o: base64.h  base64.cpp
	g++ -std=c++11 -c base64.cpp
clean:
	rm -f *.o *.x
