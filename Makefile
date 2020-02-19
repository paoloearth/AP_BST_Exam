TEST = main
CXX = c++
TESTSRC = test/main.cpp 
CXXFLAGS = -std=c++14 -Wall -Wextra -O3
IFLAGS = -I include


all: $(TEST)  docs

docs: 
	doxygen documentation/Doxyfile
$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS)

clean: 
	@rm -fr main docs/html docs/latex

.PHONY: all docs clean
