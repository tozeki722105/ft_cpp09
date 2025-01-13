CXX		:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -Wconversion -std=c++98
RM		:=	rm -f

PMERGE_PATH := ./PM/
NODE_PATH := $(PMERGE_PATH)

TARGET	:=	PmergeMe
SRCS    :=	$(NODE_PATH)Node.cpp \
			$(PMERGE_PATH)MISList.cpp \
			$(PMERGE_PATH)MISUtils.cpp \
			$(PMERGE_PATH)PmergeMe.cpp \
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
