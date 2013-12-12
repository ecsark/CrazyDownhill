NAME	=	cam

CXX	=	clang++

SRC	=	main.cpp \
		Window.cpp \
		Camera.cpp \
		Matrices.cpp \
		Node.cpp \
		Terrain.cpp \
		GLSLShader.cpp \
		loadShader.cpp \
		objreader.cpp \
		Car.cpp \
		Skybox.cpp \
		BmpLoader.cpp \
		ParticleSystem.cpp

OBJ	=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -std=c++11  -ggdb



#LDFLAGS	=	-lglut -lGLU -lGL  -lXext -lX11 -lm
#CFLAGS 	=


OS := $(shell uname)

ifeq ($(OS),Linux)
	LDFLAGS= -lglut -lGLU -lGL -lGLEW -lXext -lX11 -lm
endif
ifeq ($(OS),Darwin)
	LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa -L/opt/local/lib -lglew
	CFLAGS= -I/opt/local/include/GL/h
endif


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