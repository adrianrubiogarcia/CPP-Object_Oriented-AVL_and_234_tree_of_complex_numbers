OBJ=tad.o tcomplejo.o tlistacom.o tavlcom.o ta234com.o
OPC=-g
COMP=g++

tad: $(OBJ)
	$(COMP) $(OPC) $(OBJ) -o tad
tad.o: tad.cc 
	$(COMP) $(OPC) -c tad.cc
tcomplejo.o: tcomplejo.cc tcomplejo.h
	$(COMP) $(OPC) -c tcomplejo.cc
tlistacom.o: tlistacom.cc tlistacom.h
	$(COMP) $(OPC) -c tlistacom.cc
tavlcom.o: tavlcom.cc tavlcom.h
	$(COMP) $(OPC) -c tavlcom.cc
ta234com.o: ta234com.cc ta234com.h
	$(COMP) $(OPC) -c ta234com.cc

