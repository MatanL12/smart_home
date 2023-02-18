#main_client makefile
CXX = g++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INC_INL_DIR) -I$(INC_SERVER_DIR) -I$(INC_TCP_DIR)
CPPFLAGS += -I$(INC_SENSORS_DIR) -I$(INC_PROTOCOL_DIR) -I$(INC_THREAD_SAFE_DIR) -I$(INC_MISCELL_DIR) -I$(INC_INL_MISCELL_DIR) -I$(INC_INL_TCP_DIR) -I$(INC_INL_THREAD_SAFE_DIR)
CPPFLAGS += -MMD -MP
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3

LDFLAGS =
LDLIBS = -pthread

# Header files directory
INC_DIR = ../../inc
INC_SERVER_DIR = ../../inc/server
INC_TCP_DIR = ../../inc/server/tcp
INC_SENSORS_DIR = ../../inc/sensors
INC_THREAD_SAFE_DIR = ../../inc/thread_safe
INC_PROTOCOL_DIR = ../../inc/protocol
INC_MISCELL_DIR = ../../inc/miscellaneous
INC_INL_DIR = ../../inc/inl
INC_INL_MISCELL_DIR = ../../inc/inl/miscellaneous
INC_INL_TCP_DIR = ../../inc/inl/tcp
INC_INL_THREAD_SAFE_DIR = ../../inc/inl/thread_safe


# Source files directory
SRC_TCP_DIR = ../../src/server/tcp
SRC_PROTOCOL_DIR = ../../src/protocol
SRC_SENSORS_DIR = ../../src/sensors
SRC_THREAD_SAFE_DIR = ../../src/thread_safe


TARGET = main_client
OBJS = main_client.o $(SRC_SENSORS_DIR)/sensor_base.o $(SRC_SENSORS_DIR)/sensor_temperature.o $(SRC_SENSORS_DIR)/sensor_fire_detector.o $(SRC_SENSORS_DIR)/sensor_badge.o $(SRC_TCP_DIR)/tcp_client_socket.o $(SRC_THREAD_SAFE_DIR)/threads_semaphore.o $(SRC_PROTOCOL_DIR)/smart_home_protocol.o

all: $(TARGET)

check: $(TARGET)
	./$(TARGET) -v

$(TARGET): $(OBJS)

vala: all
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean

DEPENDS = $(OBJS:%.o=%.d)

-include $(DEPENDS)