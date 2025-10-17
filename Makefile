CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -g -Wall
LDFLAGS = -lstdc++fs
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
TARGET = testa_backup
SOURCES = backup.cpp testa_backup.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "LN -> Linkando o executável final: $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	@echo "CXX -> Compilando $< para $@"
	$(CXX) $(CXXFLAGS) -c -o $@ $<

test: $(TARGET)
	./$(TARGET)

cpplint:
	cpplint --exclude=include/catch.hpp *.cpp include/*.hpp

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem .

valgrind: $(TARGET)
	@echo "Atenção: O relatório do Valgrind será salvo em valgrind.rpt"
	valgrind --leak-check=full --log-file=valgrind.rpt ./$(TARGET)

gcov:
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c backup.cpp -o backup.o
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -c testa_backup.cpp -o testa_backup.o
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) backup.o testa_backup.o -o $(TARGET) $(LDFLAGS)
	./$(TARGET)
	gcov -r backup.cpp

debug: $(TARGET)
	gdb $(TARGET)

clean:
	@echo "Limpando arquivos gerados..."
	rm -f $(TARGET) $(OBJECTS) *.gcno *.gcda *.gcov valgrind.rpt

.PHONY: all test cpplint cppcheck valgrind gcov debug clean