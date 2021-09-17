COMPILER := g++
SRC := $(wildcard src/source/*.cpp)
FLAGS := -Wall -Wextra -ggdb3
RELEASEFLAGS := -O2

all: debug

debug: clean makeDirs
	@echo Building for debug ...
	$(COMPILER) $(SRC) -Isrc/headers/ -o build/debug/server -lrestbed $(FLAGS)

release: clean makeDirs
	@echo Building for release ...
	$(COMPILER) $(SRC) -o build/release/server -lrestbed $(RELEASEFLAGS)

makeDirs:
	@mkdir -p build/release
	@mkdir -p build/debug

clean:
	@echo Cleaning ...
	@rm -rf build
	@rm -f server