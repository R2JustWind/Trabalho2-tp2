all: testa_backup.cpp   backup.cpp backup.hpp backup.o
	g++ -std=c++11 -Wall backup.o testa_backup.cpp -o testa_backup
	./testa_backup
	#use comentario se necessario

compile: testa_backup.cpp   backup.cpp backup.hpp backup.o
	g++ -std=c++11 -Wall backup.o testa_backup.cpp -o testa_backup

backup.o : backup.cpp backup.hpp
	g++ -std=c++11 -Wall -c backup.cpp
	
testa_backup: 	testa_backup.cpp   backup.cpp backup.hpp backup.o
	g++ -std=c++11 -Wall backup.o testa_backup.cpp -o testa_backup
	
test: testa_backup	
	./testa_backup
	
cpplint: testa_backup.cpp   backup.cpp backup.hpp
	cpplint   --exclude=catch.hpp  *.*
	
gcov: testa_backup.cpp   backup.cpp backup.hpp 
	g++ -std=c++11 -Wall -fprofile-arcs -ftest-coverage -c backup.cpp
	g++ -std=c++11 -Wall -fprofile-arcs -ftest-coverage backup.o testa_backup.cpp -o testa_backup
	./testa_backup
	gcov *.cpp	
	 
debug: testa_backup.cpp   backup.cpp backup.hpp 
	g++ -std=c++11 -Wall -g -c backup.cpp
	g++ -std=c++11 -Wall  -g backup.o testa_backup.cpp -o testa_backup
	gdb testa_backup
	
	
cppcheck: testa_backup.cpp   backup.cpp backup.hpp
	cppcheck  --enable=warning .

valgrind: testa_backup
	valgrind --leak-check=yes --log-file=valgrind.rpt ./testa_backup


clean:
	rm -rf *.o *.exe *.gc* testa_backup 
	
	
