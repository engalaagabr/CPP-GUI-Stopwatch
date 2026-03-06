CXX = g++

SRC = main.cpp \
imgui/imgui.cpp \
imgui/imgui_draw.cpp \
imgui/imgui_widgets.cpp \
imgui/imgui_tables.cpp \
imgui/backends/imgui_impl_glfw.cpp \
imgui/backends/imgui_impl_opengl3.cpp

INCLUDES = -Iimgui -Iimgui/backends
LIBS = -lglfw -lGL -ldl

TARGET = stopwatch

all:
	$(CXX) $(SRC) $(INCLUDES) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)
