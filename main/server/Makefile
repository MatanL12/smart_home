#main_server makefile
CXX = g++ -static-libstdc++
CC = $(CXX)

CPPFLAGS = -I$(INC_DIR) -I$(INC_INL_DIR) -I$(INC_SERVER_DIR) -I$(INC_AGENT_DIR) -I$(INC_AGENTS_MANAGER_DIR) -I$(INC_TCP_DIR)
CPPFLAGS += -I$(INC_THREAD_SAFE_DIR) -I$(INC_SAVE_EVENTS_DIR) -I$(INC_EVENTS_PUBLISHER_DIR) -I$(INC_PROTOCOL_DIR) -I$(INC_EVENT_DIR) -I$(INC_MISCELL_DIR)
CPPFLAGS += -I$(INC_INL_AGENT_DIR) -I$(INC_INL_EVENT_DIR) -I$(INC_INL_TCP_DIR) -I$(INC_INL_THREAD_SAFE_DIR) -I$(INC_INL_MISCELL_DIR)
CPPFLAGS += -MMD -MP 
# c language
CFLAGS = -g3

# c++ language
CXXFLAGS = -std=c++17 
CXXFLAGS+= -Wall -pedantic
CXXFLAGS+= -Werror
CXXFLAGS+= -g3 

# LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../../library/ 
# export LD_LIBRARY_PATH 

LDFLAGS =
LDLIBS = -pthread -L../../library -lagents

# Header files directory
INC_DIR = ../../inc
INC_SERVER_DIR = ../../inc/server
INC_TCP_DIR = ../../inc/server/tcp
INC_AGENT_DIR = ../../inc/agents
INC_AGENTS_MANAGER_DIR = ../../inc/agents_manager
INC_THREAD_SAFE_DIR = ../../inc/thread_safe
INC_SAVE_EVENTS_DIR = ../../inc/save_events
INC_EVENTS_PUBLISHER_DIR = ../../inc/events_publisher
INC_PROTOCOL_DIR = ../../inc/protocol
INC_EVENT_DIR = ../../inc/event
INC_MISCELL_DIR = ../../inc/miscellaneous
INC_INL_DIR = ../../inc/inl
INC_INL_AGENT_DIR = ../../inc/inl/agents
INC_INL_EVENT_DIR = ../../inc/inl/event
INC_INL_TCP_DIR = ../../inc/inl/tcp
INC_INL_THREAD_SAFE_DIR = ../../inc/inl/thread_safe
INC_INL_MISCELL_DIR = ../../inc/inl/miscellaneous

# Source files directory
SRC_SERVER_DIR = ../../src/server
SRC_PROTOCOL_DIR = ../../src/protocol
SRC_AGENT_MANAGER_DIR = ../../src/agents_manager
SRC_SAVE_EVENTS_DIR = ../../src/save_events
SRC_EVENTS_PUBLISHER_DIR = ../../src/events_publisher
SRC_TCP_DIR = ../../src/server/tcp
SRC_THREAD_SAFE_DIR = ../../src/thread_safe


TARGET = main_server 
OBJS = main_server.o $(SRC_THREAD_SAFE_DIR)/threads_semaphore.o $(SRC_THREAD_SAFE_DIR)/threads_thread_pool.o $(SRC_AGENT_MANAGER_DIR)/agent_manager.o $(SRC_EVENTS_PUBLISHER_DIR)/events_publisher.o $(SRC_SERVER_DIR)/server_app.o $(SRC_TCP_DIR)/tcp_client_socket.o $(SRC_EVENTS_PUBLISHER_DIR)/notifier_events.o 
OBJS += $(SRC_SERVER_DIR)/tcp_event_handler.o $(SRC_TCP_DIR)/tcp_selector.o $(SRC_TCP_DIR)/tcp_server_socket.o $(SRC_SERVER_DIR)/threads_act_event_handler.o $(SRC_AGENT_MANAGER_DIR)/agent_loader.o $(SRC_EVENTS_PUBLISHER_DIR)/proxy_events_publisher.o $(SRC_PROTOCOL_DIR)/smart_home_protocol.o $(SRC_SAVE_EVENTS_DIR)/save_events_ostream.o $(SRC_SAVE_EVENTS_DIR)/save_events_db.o
all: $(TARGET) 

check: $(TARGET)
	./$(TARGET) -v
$(TARGET): $(OBJS) 

vala: all
	valgrind --leak-check=yes --track-origins=yes ./$(TARGET)

clean: 
	@$(RM) $(TARGET) $(OBJS) $(DEPENDS)

.PHONY: all check clean DEPENDS = $(OBJS:%.o=%.d)

DEPENDS = $(OBJS:%.o=%.d)
 
-include $(DEPENDS) 
