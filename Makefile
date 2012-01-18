# C++ compiler
CXX = g++

# paths
SRCPATH = src
OBJPATH = obj
TARGET = OSDKeys.exe

# flags
CXXFLAGS = -O0 -Wall -DUNICODE -D_WIN32_WINNT=0x0600 -std=gnu++0x
LDFLAGS = -mwindows -static-libgcc -static-libstdc++ -lwinmm -lole32

SRCS = $(wildcard $(SRCPATH)/*.cpp)
OBJS = $(patsubst $(SRCPATH)/%.cpp,$(OBJPATH)/%.o,$(SRCS))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	strip $(TARGET)

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(wildcard $(OBJPATH)/*.d)

clean:
	rm -f $(TARGET)
	rm -f $(OBJPATH)/*.o
	rm -f $(OBJPATH)/*.d