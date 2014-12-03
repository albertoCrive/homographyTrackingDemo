UNAME=$(shell uname)

CC=g++
LDFLAGS = `pkg-config opencv --libs`
CFLAGS = `pkg-config --cflags eigen3` `pkg-config opencv --cflags` -Iinclude -std=c++11
CFLAGS_RELEASE= -O3 -DNDEBUG -DEIGEN_NO_DEBUG -ffast-math
CFLAGS_DEBUG= -g -O0
ifeq ($(UNAME),Linux)
	CFLAGS +=  -fopenmp -fPIC
	LDFLAGS += -fopenmp 
endif
