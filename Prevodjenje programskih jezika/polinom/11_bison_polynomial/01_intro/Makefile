GOAL = polinomial
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14

$(GOAL): polinomial.o main.o
	$(CXX) -o $@ $^

polinomial.o: polinomial.cpp polinomial.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


.PHONY: clean

clean:
	rm $(TARGET) *.o $(GOAL)
