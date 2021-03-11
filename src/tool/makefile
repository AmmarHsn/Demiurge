CPPFLAG=g++
EXEC=NodeEdgeGenerator

all: $(EXEC)

NodeEdgeGenerator: NodeEdgeGenerator.o
	$(CPPFLAG) -o $@ $^ -ljsoncpp
%.o: %.cpp
	$(CPPFLAG) -o $@ -c $^ -ljsoncpp
clean:
	rm -rf *.o
mrproper: clean
	rm -rf find