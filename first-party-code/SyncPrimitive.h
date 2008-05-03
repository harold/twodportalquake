#pragma once
#include "WindowsIncludes.h"

class CSyncPrimitive
{
	// Members
		private:
			HANDLE m_Mutex;

	// Ctor
		public:
			CSyncPrimitive( );
			~CSyncPrimitive();

	// Methods
		private:
		public:
			void Grab();
			void Drop();
};