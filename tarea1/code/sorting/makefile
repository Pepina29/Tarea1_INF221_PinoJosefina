CXX = g++
CXXFLAGS = -std=c++11 -O2
CXXFLAGS = -std=c++17 -O2
OBJS =  algorithms/sort.o algorithms/quicksort.o algorithms/mergesort.o sorting.o

all: sorting

sorting: $(OBJS)
	$(CXX) $(CXXFLAGS) -o sorting $(OBJS)

algorithms/sort.o: algorithms/sort.cpp
	$(CXX) $(CXXFLAGS) -c algorithms/sort.cpp -o algorithms/sort.o

algorithms/quicksort.o: algorithms/quicksort.cpp
	$(CXX) $(CXXFLAGS) -c algorithms/quicksort.cpp -o algorithms/quicksort.o

algorithms/mergesort.o: algorithms/mergesort.cpp
	$(CXX) $(CXXFLAGS) -c algorithms/mergesort.cpp -o algorithms/mergesort.o

sorting.o: sorting.cpp
	$(CXX) $(CXXFLAGS) -c sorting.cpp -o sorting.o

clean:
	rm -f algorithms/*.o sorting.o sorting

#medir memoria
PROGRAMS =  merge quick sort 
INPUTS = data/matrix_input/*.txt
MEASURE_DIR = data/measurements

medir_memoria:
	@for in1 in $(INPUTS); do \
		base=$$(basename $$in1); \
		outfile=$(MEASURE_DIR)/$$base; \
		for prog in $(PROGRAMS); do \
			echo "Ejecutando $$prog con $$base..."; \
			valgrind --tool=massif --massif-out-file=massif.out ./$$prog $$in1 >/dev/null 2>&1; \
			peak=$$(grep "mem_heap_B=" massif.out | sort -n | tail -1 | cut -d= -f2); \
			peak_kb=$$((peak/1024)); \
			rm -f massif.out; \
			tmpfile=$$(mktemp); \
			awk -v alg=$$prog -v mem=$$peak_kb 'BEGIN{OFS=" | "} $$2==alg {$$4=mem " KB"} {print}' $$outfile > $$tmpfile; \
			mv $$tmpfile $$outfile; \
		done; \
	done