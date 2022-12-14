#include<iostream>
#include"Logger.h"


 Logger::Logger(Severity severity, bool useConsole) : minLevel(severity), outStream("Log.log"), startTime(std::chrono::system_clock::now())
{
	if (useConsole == true)
	{
		outStream.set_rdbuf(std::cout.rdbuf());
	}
}

 Logger::~Logger()
{
	outStream.flush();
	outStream.close();
}

void  Logger::Log(Logger::Severity severity, string message)
{
	int max = static_cast<int>(severity);
	int min = static_cast<int>(minLevel);
	if (max >= min)
	{

		outStream.precision(4);
		outStream << '[' << std::fixed << GetSecondsSinceStart() << "]\t";

		switch (severity)
		{
		case Severity::Verbose: outStream << "Verb" << '\t' << message << '\n'; break;
		case Severity::Debug:	outStream << "Debug" << '\t' << message << '\n'; break;
		case Severity::Event:	outStream << "Event" << '\t' << message << '\n'; break;
		case Severity::Error:	outStream << "Error" << '\t' << message << '\n'; break;
		}
	}
	else
	{
		return;
	}
}