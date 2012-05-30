# C++ compiler
CXX = g++

# paths
SRCPATH = src
OBJPATH = obj
RESPATH = res
RCFILE = osdkeys.rc
RESOURCES = osdkeys.ico
TARGET = osdkeys.exe

# flags
CXXFLAGS = -O0 -Wall -DUNICODE -D_WIN32_WINNT=0x0600 -std=gnu++0x
LDFLAGS = -mwindows -static-libgcc -static-libstdc++ -lwinmm -lole32

SRCS = $(wildcard $(SRCPATH)/*.cpp)
OBJS = $(patsubst $(SRCPATH)/%.cpp,$(OBJPATH)/%.o,$(SRCS))
RES = $(patsubst %.rc,$(RESPATH)/%.o,$(RCFILE))

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(RES)
	$(CXX) -o $@ $^ $(LDFLAGS)
	strip $(TARGET)

$(OBJPATH)/%.o: $(SRCPATH)/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

-include $(wildcard $(OBJPATH)/*.d)

$(RES): $(RESPATH)/$(RCFILE) $(addprefix $(RESPATH)/,$(RESOURCES))
	windres $(RESPATH)/$(RCFILE) $(RES)

clean:
	rm -f $(TARGET)
	rm -f $(OBJPATH)/*.o
	rm -f $(OBJPATH)/*.d
	rm -f $(RES)