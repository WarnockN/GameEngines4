#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Debug {
public:
	/*this is our enumeration for the types of debug messages this class is going to be sending.
	  making sure the enum is the same size as an unsigned short, just for the sake of memory management
	*/
	enum class MessageType : unsigned short {
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	/*singleton. prevents copying of the debug class.*/
	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug&& operator=(Debug&&) = delete;

	static void OnCreate(const string& name_ = "GAME258 Engine Debug Message Log");
	static void SetSeverity(MessageType type_);
	
	//create functions for each type of debug message 
	static void Info(const string& message_, const string& fileName_, const int line_);
	static void Trace(const string& message_, const string& fileName_, const int line_);
	static void Warning(const string& message_, const string& fileName_, const int line_);
	static void Error(const string& message_, const string& fileName_, const int line_);
	static void FatalError(const string& message_, const string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const string& message_, const string& fileName_, const int line_);
	static MessageType currSev;
	static string outputName;

};
#endif

