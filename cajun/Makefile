


CC = mpicxx
#CC = g++

# NOTE: Because I fail at linux development, there is an absolute path to the boost libraries installation wired into the executable's 
# library search path. 
# This avoids the use of LD_LIBRARY_FLAGS when libboost* tries to load its SOs. Statically linking boost appeared to be 
# nontrivial and so was not thoroughly explored.
#
BOOST_PATH=/home/dmacdonald/EMOD/boost/boost_1_43_0
#BOOST_PATH=/home/jbloedow/EMOD/boost/boost_1_43_0
BOOST_INCLUDES=$(BOOST_PATH)
BOOST_LIBS=$(BOOST_PATH)/stage/lib
#BOOST_LIBS=
UNIT_TEST_INCLUDES=UnitTest++/src
#MPI_INCLUDE=/usr/include/openmpi-i386/
MPI_INCLUDE=
ROOT = $(PWD)/../
#CFLAGS = -Wall -g -fpermissive -I $(BOOST_INCLUDES) -I $(UNIT_TEST_INCLUDES) -I $(MPI_INCLUDE) -ffloat-store  -std=c++0x -Wno-unknown-pragmas
INCS = -I $(UNIT_TEST_INCLUDES) -I$(ROOT) -I$(ROOT)/Eradication -I$(ROOT)/utils/ -I$(ROOT)/cajun/include -I$(ROOT)/campaign -I$(ROOT)/jsonspirit -I$(ROOT)/unittest/UnitTest++/src  -I $(BOOST_PATH)
CFLAGS = -w -O3 -fpermissive $(INCS) -ffloat-store  -std=c++0x -Wno-unknown-pragmas -I $(BOOST_PATH) -save-temps -D_new_=new
CFLAGS_DBG = -Wall -g -fpermissive -I $(UNIT_TEST_INCLUDES) -I $(MPI_INCLUDE) -ffloat-store  -std=c++0x -Wno-unknown-pragmas -I $(BOOST_PATH) -D_new_=new $(INCS)
COMPILE = $(CC) $(CFLAGS) -c
DBG_COMPILE = $(CC) $(CFLAGS_DBG) -c
#LDFLAGS=-L/usr/local/lib -L/usr/local/lib -L/usr/lib/mpich2/lib/ -L /usr/lib/mpich2/lib/ -lmpichcxx -L$(BOOST_LIBS) -Wl,-R$(BOOST_LIBS) -L libs/ -ljson_spirit -lboost_program_options -lboost_mpi -lboost_serialization -lboost_filesystem -lboost_system #-lmpich #-lopa -lpthread -lrt -lstdc++ -pthreads
LDFLAGS=-L/usr/local/lib -L/usr/local/lib -L/usr/lib/mpich2/lib/ -L /usr/lib/mpich2/lib/ -lmpichcxx -L$(BOOST_LIBS) -Wl,-R$(BOOST_LIBS) -L libs/ -lboost_program_options -lboost_filesystem -lboost_system #-lmpich #-lopa -lpthread -lrt -lstdc++ -pthreads
SOURCES=$(wildcard *.cpp) $(wildcard src/*.cpp) $(wildcard UnitTest++/src/*.cpp) $(wildcard UnitTest++/src/Posix/*.cpp) $(wildcard json_spirit/*.cpp)
#SOURCES=$(wildcard *.cpp) $(wildcard cajun/src/*.cpp) $(wildcard UnitTest++/src/*.cpp) $(wildcard UnitTest++/src/Posix/*.cpp)
OBJFILES := $(patsubst %.cpp,%.o,$(SOURCES))
OBJFILES.dbg := $(patsubst %.cpp,obj/dbg/%.o,$(SOURCES))
OBJFILES.rls := $(patsubst %.cpp,obj/rls/%.o,$(SOURCES))
EXECUTABLE=Eradication


all: $(OBJFILES) $(EXECUTABLE)

clean:
	rm $(OBJFILES)

clean.rls:
	rm $(OBJFILES.rls)

clean.dbg:
	rm $(OBJFILES.dbg)

$(EXECUTABLE): $(OBJFILES)
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) $(OBJFILES)

bin/dbg/$(EXECUTABLE): $(OBJFILES.dbg)

bin/rls/$(EXECUTABLE): $(OBJFILES.rls)

debug: bin/dbg/$(EXECUTABLE)
	#$(CC) $(LDFLAGS) -o bin/dbg/$(EXECUTABLE) $(OBJFILES.dbg)

release: bin/rls/$(EXECUTABLE)
	#$(CC) $(LDFLAGS) -o bin/rls/$(EXECUTABLE) $(OBJFILES.rls) ../cajun/obj/rls/src/*.o ../jsonspirit/obj/rls/*.o ../utils/obj/rls/*.o ../campaign/obj/rls/*.o ../unittest/obj/rls/*.o ../unittest/obj/rls/UnitTest++/src/*.o ../unittest/obj/rls/UnitTest++/src/Posix/*.o

%.o: %.cpp
	$(COMPILE) -o $@ $<

obj/dbg/%.o: %.cpp
	mkdir -p obj/dbg/src
	$(DBG_COMPILE) -o $@ $<

obj/rls/%.o: %.cpp
	mkdir -p obj/rls/src
	$(COMPILE) -o $@ $<

