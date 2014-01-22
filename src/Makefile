CXX=g++
RM=rm -f
CPPFLAGS=-g -I include/
SRCS=main.cpp lib/partition.cpp lib/candidate.cpp lib/candidateset.cpp lib/fun.cpp lib/utils.cpp lib/hashtree.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	g++ $(LDFLAGS) -o fun $(OBJS)

clean:
	$(RM) $(OBJS)