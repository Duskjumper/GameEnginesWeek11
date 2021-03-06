#include "Debug.h"

Debug::MessageType Debug::currentSev = MessageType::TYPE_NONE;
std::string Debug::outputName = "";

void Debug::OnCreate(const std::string& name_)
{
	outputName = name_ + ".txt"; 
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	currentSev = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type_)
{
	currentSev = type_;
}

void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	log(MessageType::TYPE_FATAL_ERROR, "[FATALERROR]: " + message_, fileName_, line_);
}

void Debug::log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message_ << " in: " << fileName_ << " on line " << line_ << std::endl;
		out.flush();
		out.close();
	}
}
