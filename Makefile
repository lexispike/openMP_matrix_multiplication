# compile Q4.cpp
Q4: Q4.cpp
	g++ -fopenmp Q4.cpp -o Q4

# run Q4
run_Q4: Q4
	./Q4

# clean the directory
clean:
	rm -f Q4
