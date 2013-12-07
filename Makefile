

NAME	=	cam

CXX	=	clang++

SRC	=	main.cpp \
		Window.cpp \
		Camera.cpp \
		Matrices.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -std=c++11 -O3

LDFLAGS	=	-lglut -lGLU -lGL  -lXext -lX11 -lm

$(NAME):	$(OBJ)
		$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
		rm -rf $(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean $(NAME)

ex:		$(NAME)
		./$(NAME)

cex:		re
		./$(NAME)

%.o:%.cpp	$(CXX) $(CXXFLAGS) -c $< -o $@