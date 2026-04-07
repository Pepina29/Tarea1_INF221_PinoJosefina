CXX = g++
CXXFLAGS = -std=c++17 -O2
OBJS = algorithms/naive.o algorithms/strassen.o matrix_multiplication.o

all: matrix_multiplication

matrix_multiplication: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

algorithms/naive.o: algorithms/naive.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

algorithms/strassen.o: algorithms/strassen.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

matrix_multiplication.o: matrix_multiplication.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f algorithms/*.o matrix_multiplication.o matrix_multiplication

run: matrix_multiplication
	./matrix_multiplication