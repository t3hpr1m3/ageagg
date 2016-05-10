CPP = g++

CPPFLAGS = -g -Wall -pedantic

TARGET = ageagg

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CPP) $(CPPFLAGS) -o $(TARGET) $(TARGET).cpp

clean:
	$(RM) $(TARGET)
