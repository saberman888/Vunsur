GCC := g++ -std=c++11
INC := -I .  -IC:\MinGW\include -L . -LC:\MinGW\lib -L .\bin

STATIC_LIB := ar rcs 
SHARED_LIB := $(GCC) -shared

LINK_LIB :=  -lcurl -lcurldll 
FLAGS := -w -Wall -Wextra -Wfatal-errors 
SRC := source/Script.cpp source/Info.cpp source/selfaccount.cpp source/condition.cpp source/user.cpp source/gold.cpp source/Error.cpp source/Flair.cpp source/UserAccount.cpp
OBJ := Info.o Script.o selfaccount.o condition.o user.o gold.o Error.o Flair.o UserAccount.o



all:

	$(GCC) $(FLAGS) $(INC) -c $(SRC) $(LINK_LIB)
	$(STATIC_LIB) bin/libvunsur.a $(OBJ) 
	
	$(GCC) $(FLAGS) $(INC) -DDEBUG=1 -DOUTJSON=1 -c $(SRC) $(LINK_LIB)
	$(STATIC_LIB) bin/libvunsur_debug.a $(OBJ) 
	
	$(GCC) $(FLAGS) $(INC) -c examples/example1.cpp $(LINK_LIB)
	$(GCC) $(FLAGS) $(INC) -o examples/example1 examples/example1.cpp $(LINK_LIB) -lvunsur_debug
	del .\*.o 
	

	

	copy .\libcurl.dll .\examples
