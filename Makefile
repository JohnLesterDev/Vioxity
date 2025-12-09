CC = gcc
TARGET_NAME = Vioxity.exe

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)\obj

TARGET = $(BUILD_DIR)\$(TARGET_NAME)

SOURCES = $(wildcard $(SRC_DIR)/*.c) \
          $(wildcard $(SRC_DIR)/core/*.c) \
          $(wildcard $(SRC_DIR)/scenes/*.c) \
          $(wildcard $(SRC_DIR)/systems/*.c)

OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))

COMPILER_FLAGS = -g -O2 -Wall -Wextra -std=c11 -mconsole
INCLUDE_PATHS = -I lib/include -I include
LIBRARY_PATHS = -L lib/lib

SDL_DLL = lib\SDL2.dll
OPENAL_DLL = lib\soft_oal.dll

LINKER_FLAGS = $(LIBRARY_PATHS) -lSDL2 -lOpenAL32 -lm

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET_NAME)..."
	$(CC) $(OBJECTS) $(COMPILER_FLAGS) -o $(TARGET) $(LINKER_FLAGS)
	@echo Copying DLLs...
	@if exist "$(SDL_DLL)" copy "$(SDL_DLL)" "$(BUILD_DIR)" > nul
	@if exist "$(OPENAL_DLL)" copy "$(OPENAL_DLL)" "$(BUILD_DIR)" > nul

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	@$(CC) $(COMPILER_FLAGS) $(INCLUDE_PATHS) -c $< -o $@

clean:
	@if exist "$(BUILD_DIR)" rmdir /s /q "$(BUILD_DIR)"	

run: all
	@$(TARGET)

.PHONY: all clean run