CXX		:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -Wconversion -std=c++98
RM		:=	rm -f

PMERGE_PATH := ./PMM/
NODE_PATH := $(PMERGE_PATH)Node/

TARGET	:=	PMergeMe
SRCS    :=	$(NODE_PATH)LNode.cpp \
			$(NODE_PATH)Node.cpp \
			$(NODE_PATH)VNode.cpp \
			$(PMERGE_PATH)MISList.cpp \
			$(PMERGE_PATH)MISUtils.cpp \
			$(PMERGE_PATH)MISVec.cpp \
			$(PMERGE_PATH)PMergeMe.cpp \
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
