CXXFLAGS +=  -g -Wall
LDFLAGS += -L./crypto/
LIBRARY += -lcrypto

# build helloworld executable when user executes "make"
fileCrypto: fileCrypto.o libcrypto.a
	$(CXX) $(CXXFLAGS) $(LDFLAGS) fileCrypto.o $(LIBRARY) -o fileCrypto
fileCrypto.o: fileCrypto.cc
	$(CXX) $(CXXFLAGS) -c fileCrypto.cc

libcrypto.a:
	(cd crypto; make)

# remove object files and executable when user executes "make clean"
clean:
	rm -f *.o testCrypto fileCrypto


