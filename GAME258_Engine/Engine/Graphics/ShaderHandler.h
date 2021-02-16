#ifndef SHADERHANDLER_H
#define SHADLERHANDLER_H

#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../Core/Debug.h"

using namespace std;

class ShaderHandler {
public:
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();

	void CreateProgram(const string& shaderName_,
					   const string& vertexShaderFileName_,
					   const string& fragmentShaderFileName_);

	GLuint GetShader(const string& shaderName_);
	
	void OnDestroy();

private:
	ShaderHandler();
	~ShaderHandler();

	static unique_ptr<ShaderHandler> shaderInstance;
	friend default_delete <ShaderHandler>;

	string ReadShader(const string& filePath_);
	GLuint CreateShader(GLenum shaderType_, const string& source_, const string& shaderName_);
	
	static unordered_map<string, GLuint> programs;
};
#endif

