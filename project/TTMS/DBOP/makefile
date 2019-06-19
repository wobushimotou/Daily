XX=g++
SOURCE=-g -Wall 
main:main.o 	
	$(XX) $^ $(SOURCE) -o main -lmysqlpp
main.o:main.cpp DbOperation.h GetParameter.h
	$(XX) -c -g main.cpp -Wall -I/usr/include/mysql/ -I/usr/local/include/mysql++

clean:
	rm *.o
