CFLAGS+=-I/opt/hpvt/include
LDFLAGS= -lopencv_core -lopencv_highgui -lopencv_imgproc
OBJS= sample4-1.o
TARGET=plugin4-1.so
all:: $(TARGET)
%.o: %.c
        @rm -f $@
        gcc $(CFLAGS) -c $< -o $@
%.o: %.cpp
        @rm -f $@
        g++ $(CFLAGS) -c $< -o $@
$(TARGET): $(OBJS)
        g++ -shared $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
clean::
        rm -f $(OBJS) $(TARGET)
