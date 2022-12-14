#pragma once

#include<string>
#include<fstream>
#include<chrono>

using namespace std;

class Logger {
	public:
		enum class Severity {
			Verbose,
			Debug,
			Event,
			Error,
		};

		Logger(Severity severity, bool useConsole);
		~Logger();

		void LogError(string text) { Log(Severity::Error, text); }
		void LogEvent(string text) { Log(Severity::Event, text); }
		void LogDebug(string text) { Log(Severity::Debug, text); }
		void LogVerbose(string text) { Log(Severity::Verbose, text); }

	private:
		void Log(Severity, string displayText);
		double GetSecondsSinceStart()
		{
			return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
		}

		ofstream outStream;
		Severity minLevel;
		std::chrono::system_clock::time_point startTime;
};
