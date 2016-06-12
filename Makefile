CXX := g++
CC  := g++
CXXFLAGS :=
CXXFLAGS += -Weffc++
CXXFLAGS += -std=c++11
TARGET := snewschecker
SRCS :=
SRCS += $(wildcard *.cc)
OBJS :=
OBJS += $(patsubst %.cc,%.o,$(SRCS))
LIBS :=
LIBS += -lmrss
INSTALLROOTPATH := /usr/local
INSTALLBINPATH  := $(INSTALLROOTPATH)/bin
INSTALLMAN1PATH := $(INSTALLROOTPATH)/man/man1

.PHONY : release debug clean install uninstall

release : CXXFLAGS += -DNDEBUG
release : $(TARGET)

debug : CXXFLAGS += -g -O0
debug : CXXFLAGS += -DPRIVATE_DEBUG
debug : $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

clean:
	$(RM) -v $(TARGET) $(OBJS)

install:
	cp $(TARGET) $(INSTALLBINPATH)
	cp $(TARGET).1 $(INSTALLMAN1PATH)

uninstall:
	$(RM) -v $(INSTALLBINPATH)/$(TARGET)
	$(RM) -v  $(INSTALLMAN1PATH)/$(TARGET).1

