.PHONY: \
	all \
	build \
	build_mkdirs \
	clean \
	clean_mode \
	debug \
	release \
	test \
	default

# Build by default
default: build
all: debug release
test: build

# Defaults
mode ?= debug
ifeq ($(filter $(mode), debug release), )
$(error Mode must either be debug or release)
endif

# Parameters
THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))
PROJECT_DIR := $(dir $(abspath $(THIS_MAKEFILE)))
PROJECT_NAME := $(shell basename $(PROJECT_DIR))
TARGET_NAME := lib$(PROJECT_NAME).so
LINK_TYPE := shared-lib
TARGET_TYPES := $(LINK_TYPE) test
OUTPUT_DIRECTORY_NAME := bin
TEST_UTIL_DIR := 
INCLUDE_PROJECTS := ../../ds/stack
STATIC_LIBRARIES :=
SHARED_LIBRARIES := ../../ds/stack/$(OUTPUT_DIRECTORY_NAME)/$(mode)/libstack.so
INCLUDE_DIRECTORIES := include $(patsubst %, %/include, $(INCLUDE_PROJECTS))
SOURCE_FILES := $(shell find src -type f -name "*.c")
OUTPUT_DIRECTORY = $(OUTPUT_DIRECTORY_NAME)
OBJECT_DIRECTORY = obj

ifeq ($(TARGET_TYPE), test)
	ifeq ($(LINK_TYPE), static-lib)
		STATIC_LIBRARIES := $(OUTPUT_DIRECTORY)/$(mode)/$(TARGET_NAME) $(STATIC_LIBRARIES)
	else ifeq ($(LINK_TYPE), shared-lib)
		SHARED_LIBRARIES := $(OUTPUT_DIRECTORY)/$(mode)/$(TARGET_NAME) $(SHARED_LIBRARIES)
	endif


	LINK_TYPE := executable
	INCLUDE_PROJECTS := $(INCLUDE_PROJECTS) $(TEST_UTIL_DIR)
	TARGET_NAME := $(PROJECT_NAME)_test
	SOURCE_FILES := $(shell find test -type f -name "*.c")
	INCLUDE_DIRECTORIES := $(INCLUDE_DIRECTORIES) $(TEST_UTIL_DIR)/include
endif

# Toolchain
CC := gcc
AR := gcc-ar

# Flags
FLAGS := $(FLAGS) -pedantic-errors -Wall -Wextra \
	$(patsubst %, -I%, $(INCLUDE_DIRECTORIES))
FLAGS_DEBUG := $(FLAGS_DEBUG) -g
FLAGS_RELEASE := $(FLAGS_RELEASE) -O3 -DNDEBUG
ifeq ($(LINK_TYPE), executable)
	FLAGS := $(FLAGS) -fPIE
else
	FLAGS := $(FLAGS) -fPIC
endif

# C Specific Flags
CFLAGS := $(CFLAGS) $(FLAGS) -ansi
CFLAGS_DEBUG := $(CFLAGS_DEBUG) $(FLAGS_DEBUG)
CFLAGS_RELEASE := $(CFLAGS_RELEASE) $(FLAGS_RELEASE)

# Linker Flags
LFLAGS := $(LFLAGS) $(FLAGS)
LFLAGS_DEBUG := $(LFLAGS_DEBUG) $(FLAGS_DEBUG)
LFLAGS_RELEASE := $(LFLAGS_RELEASE) $(FLAGS_RELEASE)

# Implementation

ifneq ($(LINK_TYPE), static-lib)
	COMMA := ,
	LFLAGS := $(LFLAGS) \
			  $(patsubst %, -L%, $(dir $(SHARED_LIBRARIES))) \
			  $(patsubst %, -Wl$(COMMA)-rpath=%, $(abspath $(dir $(SHARED_LIBRARIES)))) \
			  $(patsubst %, -l:%, $(notdir $(SHARED_LIBRARIES))) \
			  $(STATIC_LIBRARIES)
endif

DEPENDENCY_LIBRARIES := $(STATIC_LIBRARIES) $(SHARED_LIBRARIES)

PROJECTS_DIRECTORIES := $(INCLUDE_PROJECTS)

ifneq ($(PROJECTS_DIRECTORIES), )

build:
	@set -e ; \
	for project in $(PROJECTS_DIRECTORIES); do \
		echo "Entering '$$project'." ; \
		$(MAKE) TARGET_TYPE= -s -C $$project; \
		echo "Leaving '$$project'." ; \
	done ; \
	$(MAKE) PROJECTS_DIRECTORIES= build

clean:
	@set -e ; \
	for project in $(PROJECTS_DIRECTORIES); do \
		echo "Entering '$$project'." ; \
		$(MAKE) TARGET_TYPE= -s -C $$project clean; \
		echo "Leaving '$$project'." ; \
	done ; \
	$(MAKE) PROJECTS_DIRECTORIES= clean

debug:
	@set -e ; \
	for project in $(PROJECTS_DIRECTORIES); do \
		echo "Entering '$$project'." ; \
		$(MAKE) TARGET_TYPE= -s -C $$project debug; \
		echo "Leaving '$$project'." ; \
	done ; \
	$(MAKE) PROJECTS_DIRECTORIES= debug

release:
	@set -e ; \
	for project in $(PROJECTS_DIRECTORIES); do \
		echo "Entering '$$project'." ; \
		$(MAKE) TARGET_TYPE= -s -C $$project release; \
		echo "Leaving '$$project'." ; \
	done ; \
	$(MAKE) PROJECTS_DIRECTORIES= release

else
ifeq ($(TARGET_TYPE), )

build:
	@set -e ; \
	for target_type in $(TARGET_TYPES); do \
		$(MAKE) -s -f $(THIS_MAKEFILE) build TARGET_TYPE=$$target_type; \
	done
clean:
	@set -e ; \
		$(MAKE) -s -f $(THIS_MAKEFILE) clean TARGET_TYPE=$$target_type; \
	done
debug:
	@set -e ; \
	for target_type in $(TARGET_TYPES); do \
		$(MAKE) -s -f $(THIS_MAKEFILE) debug TARGET_TYPE=$$target_type; \
	done
release:
	@set -e ; \
	for target_type in $(TARGET_TYPES); do \
		$(MAKE) -s -f $(THIS_MAKEFILE) release TARGET_TYPE=$$target_type; \
	done

else

ifeq ($(SOURCE_FILES), )
$(error No source files)
endif

ifeq ($(mode), debug)
	FLAGS := $(FLAGS) $(FLAGS_DEBUG)
	CFLAGS := $(CFLAGS) $(CFLAGS_DEBUG)
	LFLAGS := $(LFLAGS) $(LFLAGS_DEBUG)
else ifeq ($(mode), release)
	FLAGS := $(FLAGS) $(FLAGS_RELEASE)
	CFLAGS := $(CFLAGS) $(CFLAGS_RELEASE)
	LFLAGS := $(LFLAGS) $(LFLAGS_RELEASE)
else
$(error Mode must either be debug or release)
endif

OBJECT_FILES := $(patsubst %.c, $(OBJECT_DIRECTORY)/$(mode)/%.o, $(filter %.c, $(SOURCE_FILES)))
DEPENDENCY_FILES := $(patsubst %, %.d, $(OBJECT_FILES))
OBJECT_FILES_DIRECTORIES := $(dir $(OBJECT_FILES))

TARGET_FILE := $(OUTPUT_DIRECTORY)/$(mode)/$(TARGET_NAME)

ifeq ($(LINK_TYPE), executable)
	LINK_COMMAND := $(CC) -o $(TARGET_FILE) $(OBJECT_FILES) $(LFLAGS)
else ifeq ($(LINK_TYPE), shared-lib)
	LINK_COMMAND := $(CC) -o $(TARGET_FILE) $(OBJECT_FILES) $(LFLAGS) -shared
else ifeq ($(LINK_TYPE), static-lib)
	LINK_COMMAND := $(AR) rcs $(TARGET_FILE) $(OBJECT_FILES)
else
$(error LINK_TYPE must either be executable, static-lib, shared-lib)
endif

build: $(TARGET_FILE)
	@echo 'Done!'

build_mkdirs:
	@mkdir -p $(dir $(TARGET_FILE)) $(OBJECT_FILES_DIRECTORIES)

$(TARGET_FILE): $(OBJECT_FILES) $(DEPENDENCY_LIBRARIES)
	@echo "Linking '$@'..."; \
	$(LINK_COMMAND)

$(OBJECT_FILES): $(OBJECT_DIRECTORY)/$(mode)/%.o: %.c | build_mkdirs
	@echo "Compiling '$<'..."; \
	$(CC) -c $(CFLAGS) -o $@ $< -MD -MP -MF $@.d

-include $(DEPENDENCY_FILES)

clean:
	@$(MAKE) -s clean_mode mode=debug; \
	$(MAKE) -s clean_mode mode=release; \
	echo "Done!"

clean_mode:
	@echo "Cleaning $(OBJECT_FILES) $(DEPENDENCY_FILES) $(TARGET_FILE)"; \
	rm -rf $(OBJECT_FILES) $(DEPENDENCY_FILES) $(TARGET_FILE)

debug:
	@$(MAKE) -s mode=debug

release:
	@$(MAKE) -s mode=release

endif
endif
