CXX = g++
CFLAGS = -Wall -pedantic -std=c++11

all : 
	$(CXX) $(CFLAGS) -o task2.exe task2/prodcon.cpp
	$(CXX) $(CFLAGS) -o task3.exe task3/threads.cpp
	$(CXX) $(CFLAGS) -o task4.exe task4/thr1.cpp
	$(CXX) $(CFLAGS) -o dispatch.exe task5/dispatcher_challenge.cpp
