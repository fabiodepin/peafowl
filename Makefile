CC                   = gcc
CXX 		     = g++ 
LINK_OPT             = 
VERSION              = 
OPTIMIZE_FLAGS       = -O3 -finline-functions
CXXFLAGS             = -Wall -g 
CFLAGS               =
LDFLAGS              = 
INCS                 = -I ./ 
LIBS                 = 
INCLUDES             =
TARGET               = utils.o ipv4_reassembly.o ipv6_reassembly.o reassembly.o tcp_stream_management.o hash_functions.o flow_table.o api.o 

.PHONY: clean cleanall install uninstall test
.SUFFIXES: .cpp .o

all: $(TARGET)
tcp_stream_management.o: tcp_stream_management.c
	$(CC) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c tcp_stream_management.c -o tcp_stream_management.o
utils.o: utils.cpp
	$(CXX) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c utils.cpp -o utils.o
reassembly.o: reassembly.cpp
	$(CXX) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c reassembly.cpp -o reassembly.o
ipv4_reassembly.o: ipv4_reassembly.cpp
	$(CXX) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c ipv4_reassembly.cpp -o ipv4_reassembly.o
ipv6_reassembly.o: ipv6_reassembly.cpp
	$(CXX) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c ipv6_reassembly.cpp -o ipv6_reassembly.o
hash_functions.o: hash_functions.cpp
	$(CXX) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c hash_functions.cpp -o hash_functions.o
flow_table.o: flow_table.c
	$(CC) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c flow_table.c -o flow_table.o
api.o: api.c *.h 
	make -C ./inspectors
	$(CC) $(INCS) $(CXXFLAGS) $(OPTIMIZE_FLAGS) -c api.c -o api.o 
test:
	make -C ./test
	make -C ./test test
clean: 
	make -C ./inspectors clean
	make -C ./test clean
	-rm -fr *.o *~ *.so* libdpi.a
cleanall:
	make -C ./inspectors cleanall
	make -C ./test cleanall
	-rm -fr *.o *~ 
	-rm -fr $(TARGET)
lib:
	ar rs libdpi.a *.o inspectors/*.o