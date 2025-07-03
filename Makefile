#specify compiler

CC = g++

#Define name of obj file that will be created post-compilation
PROJECT = invisibility_cloak

# Includes directories that can be added to include path of main.cpp
CFLAGS = -std=c++11 $(shell pkg-config --cflags opencv4) -Iinclude/
#Imported libs
LIBS = $(shell pkg-config --libs opencv4)


.PHONY: build
ifeq ($(SRC), $(link),)
build:
	$(error "No SRC set")
else
build:
	@echo "Building..."
	@$(CC) $(SRC) $(link) -o $(PROJECT) $(CFLAGS) $(LIBS)
endif

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -rf $(PROJECT)
