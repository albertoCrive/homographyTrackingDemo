SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=homographyDemo
LIB_CPP = libHomographyEstimation.so

include Makefile.inc

help:           ## Show this help.
	@echo "——————— Available Targets  ——————— \n\n"
	@fgrep -h "##" $(MAKEFILE_LIST) | fgrep -v fgrep | sed -e 's/\\$$//' | sed -e 's/##//'
	@echo "\n\n"


all: ## 		build all in release mode
all: libCppRelease demoRelease unittestsRelease cleanObj

release: ## 	build all in release mode
release: libCppRelease demoRelease unittestsRelease cleanObj

debug: ## 	build all in debug mode
debug: libCppDebug demoDebug unittestsDebug cleanObj 


libCppRelease: ## 	C++ lib - release mode
libCppRelease: CFLAGS += $(CFLAGS_RELEASE)
libCppRelease:	$(LIB_CPP)

libCppDebug: ##		C++ lib - release mode
libCppDebug: CFLAGS += $(CFLAGS_DEBUG)
libCppDebug:	$(LIB_CPP)

$(LIB_CPP): $(SOURCES) $(OBJECTS)
	@echo ——————— compiling the Homography library  ——————— 
	$(CC) -shared $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

demoRelease: ##		executable - release mode 
demoRelease: CFLAGS += $(CFLAGS_RELEASE)
demoRelease: libCppRelease $(EXECUTABLE)

demoDebug: ##		executable - debug mode 
demoDebug: CFLAGS += $(CFLAGS_DEBUG)
demoDebug: libCppDebug $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES) $(OBJECTS)
	@echo ——————— compiling the demo  ——————— 
	$(CC) ISMAR_Demo/main.cpp $(CFLAGS) $(LDFLAGS) -L. -lHomographyEstimation -o ISMAR_Demo/$@
	cd ISMAR_Demo && ln -sf ../libHomographyEstimation.so libHomographyEstimation.so

unittestsRelease: ##		unit tests - release mode 
unittestsRelease: CFLAGS += $(CFLAGS_RELEASE)
unittestsRelease: libCppRelease unittests

unittestsDebug: ##		unit tests - debug mode 
unittestsDebug: CFLAGS += $(CFLAGS_DEBUG)
unittestsDebug: libCppDebug unittests

unittests: $(SOURCES) $(OBJECTS)
	@echo ——————— compiling the test  ——————— 
	$(CC) unit/UnitTests.cpp $(CFLAGS) $(LDFLAGS) -L. -lHomographyEstimation -o unit/$@ 
	cd unit && ln -sf ../libHomographyEstimation.so libHomographyEstimation.so
.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@


.PHONY: clean all help

cleanObj:
	@echo ——————— Cleaning the objects .o  ——————— 
	rm -rf ISMAR_Demo/main.o unit/UnitTests.o $(OBJECTS)

clean:
	@echo ——————— Cleaning the project   ——————— 
	rm -rf ISMAR_Demo/main.o ISMAR_Demo/libHomographyEstimation.so unit/UnitTests.o unit/libHomographyEstimation.so $(OBJECTS) libHomographyEstimation.so unit/unittests ISMAR_Demo/$(EXECUTABLE)

