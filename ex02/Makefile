CXX		:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -Wconversion -std=c++98
RM		:=	rm -f

PMERGE_PATH := ./
NODE_PATH := $(PMERGE_PATH)Node/

TARGET	:=	PMergeMe
SRCS    :=	$(NODE_PATH)LNode.cpp \
			$(NODE_PATH)Node.cpp \
			$(NODE_PATH)VNode.cpp \
			MISList.cpp \
			MISUtils.cpp \
			MISVec.cpp \
			PMergeMe.cpp \
			main.cpp 
OBJS    :=	$(patsubst %.cpp, %.o, $(SRCS))

.PHONY: all clean flean re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all
