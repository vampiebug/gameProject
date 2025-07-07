all: release

release:
	g++ -Wall -std=gnu++17 -o arcade *.cpp 

debug:
	g++ -g -Wall -std=gnu++17 -o arcade *.cpp 
