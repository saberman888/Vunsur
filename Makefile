

CPP      := g++.exe
CC       := gcc.exe
OBJ      := vunsur_basic.o Script.o 
SRC  := source/vunsur_basic.cxx source/Script.cxx
LIBS     := -lcurl -lcurl.dll
INCS     := -I"C:/MinGW/include" -I"G:/Projects/VunsurDev"
CXXINCS  := -I"C:/MinGW/include" -I"G:/Projects/VunsurDev"
BIN      := libVunsur.a
CXXFLAGS := $(CXXINCS) -w -pedantic -fsyntax-only -Werror -Wfatal-errors
CFLAGS   := $(INCS) -w -pedantic -fsyntax-only -Werror -Wfatal-errors

all:
	$(CPP) -c $(SRC) $(CFLAGS) -DDDEBUG=1 $(LIBS)
	ar rcs $(BIN) $(OBJ) 
	$(CPP) -o Example example.cxx $(CFLAGS) $(LIBS) -lVunsur