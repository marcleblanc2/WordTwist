CCC= g++
CCCFLAGS = -Wall -O3

all: wo rem res

wo : wordtwist.cc 
	$(CCC) $(CCCFLAGS) $^ -o $@

%.o : %.cc 
	$(CCC) -c $(CCCFLAGS) $<

rem : remove.cc 
	$(CCC) $(CCCFLAGS) $^ -o $@

%.o : %.cc 
	$(CCC) -c $(CCCFLAGS) $<

res : resolve.cc 
	$(CCC) $(CCCFLAGS) $^ -o $@

%.o : %.cc 
	$(CCC) -c $(CCCFLAGS) $<

clean:
	rm -f *.o *~ *% *# .#*
