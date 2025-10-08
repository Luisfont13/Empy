# ========================================
# Configuración general
# ========================================

# Directorios
SRC_DIR = src
BUILD_DIR = build
LIBS_DIR = libs
CORE_DIR = $(SRC_DIR)/core

#Variables
VERSION_RES = versions/version.res

# Archivos fuente
SOURCES = $(SRC_DIR)/main.cpp \
          $(CORE_DIR)/renderer/renderer.cpp \
          $(LIBS_DIR)/glad/glad.c \
		  $(CORE_DIR)/buffer/*.cpp \
		  $(CORE_DIR)/shader/*.cpp \
		  $(CORE_DIR)/texture/*.cpp \

# Includes
INCLUDES = -I$(LIBS_DIR)/glad \
           -I$(LIBS_DIR)/glfw \
           -I$(LIBS_DIR)/stb \
           -I.

# ========================================
# Compilador para Windows (MinGW)
# ========================================

CC_MINGW = x86_64-w64-mingw32-g++

# Bibliotecas para Windows
LIBS_MINGW = -L$(LIBS_DIR)/glfw -lglfw3 -lopengl32 -lgdi32 -lshell32

# Archivo de salida para Windows
TARGET_MINGW = $(BUILD_DIR)/motor.exe

# ========================================
# Flags de compilación para MinGW
# ========================================

CXXFLAGS_MINGW = -std=c++20 -O2 -Wall -mwindows
MINGW_FLAGS = -static 

# ========================================
# Objetivos
# ========================================

.PHONY: mingw clean

# Compilar para Windows (MinGW) - TODO EN UNA SOLA LÍNEA
mingw: $(BUILD_DIR)
	$(CC_MINGW) $(SOURCES) $(VERSION_RES) $(INCLUDES) -o $(TARGET_MINGW) $(LIBS_MINGW) $(CXXFLAGS_MINGW) $(MINGW_FLAGS)

# Crear directorio de build si no existe
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# ========================================
# Limpiar archivos compilados
# ========================================

clean:
	rm -rf $(BUILD_DIR)

# ========================================
# Mensajes
# ========================================

help:
	@echo "Usos del Makefile:"
	@echo "  make mingw          - Compilar para Windows (motor.exe)"
	@echo "  make clean          - Limpiar archivos compilados"
	@echo "  make help           - Mostrar este mensaje"