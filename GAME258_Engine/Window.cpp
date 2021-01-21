#include "Window.h"

//makes sure the important private vars are null
Window::Window() : window(nullptr), context(nullptr) {
	/*window = nullptr;
	context = nullptr;*/
}

//calls on destroy fucntion -- pack it up and go home 
Window::~Window() {
	OnDestroy();
}

bool Window::OnCreate(string name_, int width_, int height_) {
	//initalize SDL_Video -- give console error if it didnt work, return false to break out of the loop
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "Failed to initialize SDL" << endl;
		return false;
	}
	
	//save width and height of window, and set window params to that
	this->width = width_;
	this->height = height_;

	//call pre attributes func.
	SetPreAttributes();

	/*create window
		1. Set window name
		2. Center the x window pos
		3. Center the y window pos
		4. create the window using specified width and height values
		5. set any specified flags that you want
	*/
	window = SDL_CreateWindow(name_.c_str(), 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		width, height, 
		SDL_WINDOW_OPENGL);

	//if window returns null -- give console error if it didnt work, return false to break out of the loop
	if (!window) {
		cout << "Failed to create window" << endl;
		return false;
	}
	
	//create OpenGL context to use OpenGL in engine.
	//DOORWAY TO GPU COMMUNICATION
	context = SDL_GL_CreateContext(window);
	SetPostAttributes();

	//initialize glew -- library for OpenGL calls.
	GLenum err = glewInit();

	//if glew enum state does not return OK -- give console error if it didnt work, return false to break out of loop.
	if (err != GLEW_OK) {
		cout << "Failed to initialze GLEW" << endl;
		return false;
	}

	//enable depth test, used for rendering. takes z axis into account.
	glEnable(GL_DEPTH_TEST);
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	return true;
}

//shut down window and delete context // MAKE SURE OT SET WINDOW  TO NULLPTR!
void Window::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

int Window::GetWidth() const {
	return width;
}

int Window::GetHeight() const {
	return height;
}

SDL_Window* Window::GetWindow() const {
	return nullptr;
}

void Window::SetPreAttributes() {

}

void Window::SetPostAttributes() {

}

//test commit with extension
