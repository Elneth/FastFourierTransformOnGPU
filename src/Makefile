###############################################################################
# Makefile pour la compilation des programmes 
###############################################################################

#### variables ####
CC = g++
BIN = g++
OPT = -std=c++11
CFLAGS = -Wall -Werror
OBJS = main.o fft.o
LIBS = -lboost_iostreams -lboost_system -lboost_filesystem

INCLUDES_DIR = ../include
INSTALL_DIR = ../bin

EXECUTABLES = parallel_fft.exe

###############################################################################
# compilation separee des packages (modules)
###############################################################################

%.o: %.cpp
	$(CC) $(CFLAGS) $(OPT) $(INCLUDES_DIR) -fopenmp -o $@ -c $<

###############################################################################
# edition de lien des modules separes 
# pour la creation des programmes executables 
###############################################################################

$(EXECUTABLES) : $(OBJS)
	$(BIN) $^ -o $@ $(LIBS) -fopenmp


###############################################################################
# run, clean, install, docs
###############################################################################
all : $(EXECUTABLES)
	mv $(EXECUTABLES) $(INSTALL_DIR)
	rm -rf ./*.o

run : $(EXECUTABLES)
	mv $(EXECUTABLES) $(INSTALL_DIR)
	rm -rf ./*.o
	$(INSTALL_DIR)/$(EXECUTABLES)

clean :
	rm -rf *.o *.o
	rm -f $(INSTALL_DIR)/$(EXECUTABLES)

cleanpy :
	rm fft.py
	rm fft_wrap.cxx
	rm *.so
	rm -rf __pycache__


install : $(EXECUTABLES)
	mv $(EXECUTABLES) $(INSTALL_DIR)
	rm -rf ./*.o
	g++ -c -fPIC fft.cpp
	swig -c++ -python fft.i
	g++ -c -fPIC fft_wrap.cxx -I/usr/include/python3.8
	g++ -shared -Wl,-soname,_fft.so -o _fft.so fft.o fft_wrap.o