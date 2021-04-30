#include "Window.h"
#include "Debug.h"
Window::Window()
{
	window = nullptr;
	context = nullptr;
}

Window::~Window()
{
	OnDestroy();
}

bool Window::OnCreate(std::string name_, int width_, int height_)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Debug::FatalError("Failed to initialize SDL", __FILE__, __LINE__);
		return false;
	}
	this->width = width_;
	this->height = height_;
	setPreAttributes();

	window = SDL_CreateWindow(name_.c_str(),
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED,
		width, height, SDL_WINDOW_OPENGL);
	if (!window) {
		Debug::FatalError("Window Failed to Create", __FILE__, __LINE__);
		return false;
	}
	context = SDL_GL_CreateContext(window);
	setPostAtrributes();

	GLenum error = glewInit();
	if (error != GLEW_OK) {
		Debug::FatalError("Failed to initalize GLEW", __FILE__, __LINE__);
		return false;
	}
	Debug::Info("OpenGL Version: " + std::string((char*)glGetString(GL_VERSION)), "Window.cpp", __LINE__);
	
	glViewport(0, 0, width, height);
	
	return true;
}

void Window::OnDestroy()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth()
{
	return width;
}

int Window::GetHeight()
{
	return height;
}

SDL_Window* Window::GetWindow() const
{
	return window;
}

void Window::setPreAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

void Window::setPostAtrributes()
{
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}


