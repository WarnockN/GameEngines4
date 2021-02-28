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
		Debug::FatalError("Failed to initialize SDL.", "Window.cpp", __LINE__);
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
		Debug::FatalError("Failed to create window.", "Window.cpp", __LINE__);
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
		Debug::FatalError("Failed to initalize GLEW.", "Window.cpp", __LINE__);
		return false;
	}

	

	//Debug openGL Version
	Debug::Info("OpenGL version: " + string((char*)glGetString(GL_VERSION)), "Window.cpp", __LINE__);
	//print OpenGL version, just to check
	//cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

	glViewport(0, 0, width, height);

	return true;
}

//shut down window and delete context // MAKE SURE OT SET WINDOW  TO NULLPTR!
void Window::OnDestroy() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	window = nullptr;
}

/*set all of our OpenGL window attributes
	1. Gets rid of any depricated functions -- set profile mask to core
	2. set OpenGL major version 4
	3. set OpenGL minor version 5
	-- THIS MEANS WE ARE USING OPENGL VERSION 4.5 --
	4. enable double buffering -- safety to prevent graphical tears or stutters.
	5. set the swap interval to be equal to the vertical retrace. //I assume this is similar to the V-Sync setting to prevent screen tear?//
	6. set glewExperimental to true, allows for us to track erros for experimental GPU extensions
*/
void Window::SetPreAttributes() {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);
	glewExperimental = GL_TRUE;
}

//set our depth size to 32, we are doing this after we set our context to prevent OpenGL from reverting to v1.1, in case it didnt understand what our context was.
void Window::SetPostAttributes() {
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
}
