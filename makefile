CXX = g++
RM = rm

DEFFLAGS =
CFLAGS = -DNDEBUG

TARGETS1 = test21.1.o
TARGETS2 = test21.2.o
TARGETS3 = test21.1
TARGETS4 = test21.2
TARGETS = $(TARGETS1) $(TARGETS2) $(TARGETS3) $(TARGETS4)

all:$(TARGETS)

$(TARGETS1):test21-define-make.cpp
	@echo "Compiling with define \t$<\t ===>\t $@"
	$(CXX) $(DEFFLAGS) -c $^ -o $@

$(TARGETS2):test21-define-make.cpp
	@echo "Compiling without define \t$<\t ===>\t $@"
	$(CXX)  -c $^ -o $@

$(TARGETS3):$(TARGETS1)
	@echo "Linking \t$<\t ===>\t $@"
	$(CXX) $^ -o $@

$(TARGETS4):$(TARGETS2)
	@echo "Linking \t$<\t ===>\t $@"
	$(CXX) $^ -o $@

clean:
	$(RM) -f *.o
	$(RM) -f $(TARGETS) 

