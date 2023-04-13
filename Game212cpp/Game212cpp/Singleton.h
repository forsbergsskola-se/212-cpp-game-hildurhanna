#pragma once

#include <assert.h>
#include <stdio.h>

/**
* Singleton class
* CSingleton is a template class for implementing the singleton pattern
* The singleton pattern guarantees that only 1 instance of an object is constructed
*/
template <class T>
class CSingleton
{
protected:

			 CSingleton			(void) {s_pInstance = (T*)this;}
	virtual ~CSingleton			(void) {s_pInstance = nullptr;}

public:

	/**
	* Initializes the singleton by constructing an instance of the given data type
	* Asserting if the instance is already initialized
	*/
	static void	Initialize		(void)
	{
	#ifdef _DEBUG
		assert(!s_pInstance);
	#endif

		new T;
	}

	/**
	* Deinitializes the singleton by destroying the instance
	* Asserting if the instance is not valid (i.e not initialized)
	*/
	static void	Deinitialize	(void)
	{
	#ifdef _DEBUG
		assert(s_pInstance);
	#endif

		delete s_pInstance;
	}

	/**
	* Retrieves a reference to the instance
	* Asserting if the instance is not valid (i.e not initialized)
	* \return A reference to the instance
	*/
	static T&	GetInstance		(void)
	{
	#ifdef _DEBUG
		assert(s_pInstance);
	#endif

		return *s_pInstance;
	}

private:

	static T* s_pInstance;

};

template <class T> T* CSingleton<T>::s_pInstance = nullptr;