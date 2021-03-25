CXXFLAGS +=  -g -Wall
INC += -I./crypto
DYNAMIC_LIB_DIRS +=
DYNAMIC_LIBS += -lssl -lcrypto
STATIC_LIB_DIRS += -L./crypto/
STATIC_LIBS += -lsimplecrypto

PROGRAM = xmlPackager


# build helloworld executable when user executes "make"
$(PROGRAM): fileCrypto.o libcrypto.a
	$(CXX) fileCrypto.o -Wl,-Bstatic $(STATIC_LIBS) $(STATIC_LIB_DIRS) -Wl,-Bdynamic $(DYNAMIC_LIBS) $(DYNAMIC_LIB_DIRS) -o $(PROGRAM)
fileCrypto.o: fileCrypto.cc
	$(CXX) $(CXXFLAGS) $(INC) -c fileCrypto.cc

libcrypto.a:
	(cd crypto; make)

# remove object files and executable when user executes "make clean"
clean:
	(cd crypto; make clean)
	rm -f *.o testCrypto $(PROGRAM)


