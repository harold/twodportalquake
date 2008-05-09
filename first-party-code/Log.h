#pragma once

class CLog
{
	// NO! Ctor
		private:
			CLog();

	// Methods
		private:
		public:
			static void Print( char* inFormat, ... );
};