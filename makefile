
build_tests:
	clang++ -std=c++17 -lpthread src/testing.cpp -o tests
	clang++ -std=c++17 -lpthread src/benchmark_1_thread.cpp -o b2
	clang++ -std=c++17 -lpthread src/benchmark_10_threads.cpp -o b1
	./tests
	time ./b1
	time ./b2