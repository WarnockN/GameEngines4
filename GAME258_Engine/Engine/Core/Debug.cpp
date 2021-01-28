#include "Debug.h"

//redeclare the current severity to NONE as it is a static variable
//do the same with outputName. make sure to set it to an empty string AKA null
Debug::MessageType Debug::currSev = MessageType::TYPE_NONE;
string Debug::outputName = "";

/*OnCreate:
1. set our output name to the file name and add .txt to the end of it
2. open the file that the outputName is.
3. set it to ios::out so it is open to writing
4. close file // open and close it to create, will also overwrite if there is anything else from a previous run
5. set current severity to info type message*/
void Debug::OnCreate(const string& name_) {
	outputName = name_ + ".txt";
	ofstream out;
	out.open(outputName.c_str(), ios::out);
	out.close();
	currSev = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type_) {
	currSev = type_;
}

// ================================================================================================ //

//log message for each type of error
void Debug::Info(const string& message_, const string& fileName_, const int line_) {
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const string& message_, const string& fileName_, const int line_) {
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const string& message_, const string& fileName_, const int line_) {
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const string& message_, const string& fileName_, const int line_) {
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const string& message_, const string& fileName_, const int line_) {
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]: " + message_, fileName_, line_);
}

// ================================================================================================ //

/*access our file and write our message to log.
1. set our file to ios::out to be able to write
2. open our file -- app is append, we are now able to write to our file, and add any new logs to the end, instead of overwriting what is currently written
3. add our message
4. flush to sync the stream buffer -- makes sure buffer is empty before we close our file.
5. close the file*/
void Debug::Log(const MessageType type_, const string& message_, const string& fileName_, const int line_) {
	if (type_ <= currSev && currSev > MessageType::TYPE_NONE) {
		ofstream out;
		out.open(outputName.c_str(), ios::app | ios::out);
		out << message_ << " in: " << fileName_ << " on line: " << line_ << endl;
		out.flush();
		out.close();
	}
}
