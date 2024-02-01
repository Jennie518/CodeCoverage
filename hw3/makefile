#Target: all checks if prereq executable is up to date
#
#Target: run checks if the executable file named executable is up to date
	#runs the executable file
#
#Target: clean
	#removes all .o file and the executable file named executable
#
#Target: .PHONY explicitely tells make that these targets are not associated with files
#
#Target: make checks if the .cpp and .h files are up to date
	#Creates .o files and executable
#
#Target: printM
	#prints out values of macros


CXX = c++
CFLAGS = -std=c++11
CXXSOURCE = cmdline.cpp main.cpp  expr.cpp Test.cpp
HEADERS = cmdline.h catch.h expr.h
CXXOBJECT = cmdline.o main.o expr.o Test.o

msdscript: $(CXXSOURCE) $(HEADERS)
	$(CXX) $(CFLAGS) -c $(CXXSOURCE)
	$(CXX) $(CFLAGS) -o msdscript $(CXXOBJECT)

run: msdscript
	./msdscript

.PHONY: test
test: msdscript
	./msdscript --test

.PHONY: clean
clean:
	rm -rf *.o msdscript

.PHONY: printM
printM:
	echo $(CXXSOURCE) $(CXX) $(CFLAGS) $(HEADERS) $(CXXOBJECT)













