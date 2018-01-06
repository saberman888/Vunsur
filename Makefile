GCC := g++ -std=c++11
STATIC_LIB := ar rcs
INC := -IC:\MinGW\include -LC:\MinGW\lib -I .\include\Vunsur
INC_EXAMPLE := -I .\include\Vunsur -L .\lib
DEBUG_MACROS := -DDEBUG=1 -DOUTJSON=1
FLAGS := -w -Wall -Wextra -Wfatal-errors -march=native

BIN := lib/libvunsur.a
BIN_DEBUG := lib/libvunsur_debug.a
OBJS := Error.o Flair.o Info.o Script.o Types.o UserAccount.o account.o condition.o gold.o linkncomms.o other.o selfaccount.o subreddit.o user.o 

SRC := source/Error.cpp source/Flair.cpp source/Info.cpp source/Script.cpp source/Types.cpp source/UserAccount.cpp source/account.cpp source/condition.cpp source/gold.cpp source/linkncomms.cpp source/other.cpp source/selfaccount.cpp source/subreddit.cpp source/subreddit.cpp source/user.cpp
SRC_EXAMPLE := ./example/example.cpp

LINK_LIB := -lcurl -lcurldll

all:
	$(GCC) $(INC) $(FLAGS) -c $(SRC) $(LINK_LIB)
	$(STATIC_LIB) $(BIN) $(OBJS)
	
	del *.o
	
	$(GCC) $(INC) $(FLAGS) $(DEBUG_MACROS) -c $(SRC) $(LINK_LIB)
	$(STATIC_LIB) $(BIN_DEBUG) $(OBJS) 
	
	del *.o
	
	$(GCC) $(INC) $(INC_EXAMPLE) $(FLAGS) -c examples\example.cpp $(LINK_LIB) -lvunsur
	$(GCC) $(INC) $(INC_EXAMPLE) -o examples\Example example.o -lvunsur $(LINK_LIB)
	
	$(GCC) $(INC) $(INC_EXAMPLE) $(FLAGS) -c examples\example.cpp $(LINK_LIB) -lvunsur_debug
	$(GCC) $(INC) $(INC_EXAMPLE) -o examples\Example_debug example.o -lvunsur_debug $(LINK_LIB)
	
	del *.o

