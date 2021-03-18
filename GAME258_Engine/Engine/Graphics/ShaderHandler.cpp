#include "ShaderHandler.h"

unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;
unordered_map<string, GLuint> ShaderHandler::programs = unordered_map<string, GLuint>();

ShaderHandler::ShaderHandler() {}

ShaderHandler::~ShaderHandler() { OnDestroy(); }


ShaderHandler* ShaderHandler::GetInstance()
{
    if (shaderInstance.get() == nullptr) shaderInstance.reset(new ShaderHandler);
    return shaderInstance.get();
}

void ShaderHandler::CreateProgram(const string& shaderName_, const string& vertexShaderFileName_, const string& fragmentShaderFileName_) {
    //read the 2 files for the vert and frag shaders
    string vertexShaderCode = ReadShader(vertexShaderFileName_);
    string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

    //check if empty -- dont need to throw error message because we did it in CreateShader
    if (vertexShaderCode == "" || fragmentShaderCode == "") return;

    //create the vert and frag shaders
    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

    //check if empty
    if (vertexShader == 0 || fragmentShader == 0) return;

    //create the linkResult var and create the program
    GLint linkResult = 0;
    GLuint program = glCreateProgram();

    //attach the vert and frag shaders in the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    //link the program
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

    //error checking 
    if (!linkResult) {
        GLint infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

        //create a vec wit the size of that log length 
        //then input that information into the log    <<the place we want OpenGL to put it is the address of the first element of this vector>>
        vector<char> programLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);

        //convert it to a string and throw a debug error message.
        string programString(programLog.begin(), programLog.end());
        Debug::Error("Erorr linking shader " + shaderName_ + ". Error: \n" + programString, "ShaderHandler.cpp", __LINE__);

        //delete the shdaers and the program
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        return;
    }

    programs[shaderName_] = program;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint ShaderHandler::GetShader(const string& shaderName_) {
    if (programs.find(shaderName_) != programs.end()) return programs[shaderName_];
    return 0;
}

void ShaderHandler::OnDestroy() {
    if (programs.size() > 0) {
        for (auto p : programs) {
            glDeleteProgram(p.second);
        }
        programs.clear();
    }
}


/*pass in the shader file, and outputs the string that the file contains.
1. create a string to rep the content of the file
2. create the ifstring which is obj we use to read the file
3. check to see if there is badbit exception -- is there something wrong with the file?
========================== INSIDE TRY/CATCH ==========================
TRY:
1. open the file
2. create a string stream
3. take whatever is in the file and pass it to the string stream
4. close the file
5. set the string to equal whatever is in the string stream

CATCH:
1. if anything goes wrong, print to the debug file that something that has gone wrong
2. return an empty string if it did go wrong, if not return our shaderCode string (the stuff inside the file)
*/
string ShaderHandler::ReadShader(const string& filePath_) {
    string shaderCode = "";
    ifstream file;
    file.exceptions(ifstream::badbit);
    try {
        file.open(filePath_);
        stringstream tmpStream;
        tmpStream << file.rdbuf();
        file.close();
        shaderCode = tmpStream.str();
    }
    catch (ifstream::failure error_) {
        Debug::Error("Could not read the shader: " + filePath_, "ShaderHandler.cpp", __LINE__);
        return "";
    }

    return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const string& source_, const string& shaderName_) {
    //create our shader and the compileResult var. 0 = did nto compile 1 = compiled properly -- useful for the glCompileShader func.
    GLint compileResult = 0;
    GLuint shader = glCreateShader(shaderType_);
    
    //convert our string into a chat* object and get the size of the shader
    const char* shaderCodePtr = source_.c_str();
    const int shaderCodeSize = source_.size();

    //set our shader source and compile our shader
    glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
    glCompileShader(shader);

    //get the compile status and set the compileResult to what the current status is -- see top comment
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    //error checking if the shader did not compile.
    if (!compileResult) {
        //get the legnth of the info that the shader will give us on what went wrong
        //pass in the address of this int and full in the value of that int
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        
        //create a vec wit the size of that log length 
        //then input that information into the log    <<the place we want OpenGL to put it is the address of the first element of this vector>>
        vector<char> shaderLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
        
        //convert it to a string and throw a debug error message.
        string shaderString(shaderLog.begin(), shaderLog.end());
        Debug::Error("Erorr compiling shader" + shaderName_ + ". Error: \n" + shaderString, "ShaderHandler.cpp", __LINE__);
        
        return 0;
    }

    return shader;
}
