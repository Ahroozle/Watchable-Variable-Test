#pragma once

#include "WatcherList.h"

//#include <assert.h>
//#include <type_traits>

#define PROPERTY_MAXNUM_WATCHERS 100

template<typename T>
class Property final
{
private:

	T data;

	//bool isPointer = false;

	WatcherList<T> watchers;

	//void CheckIfPointer() { isPointer = std::is_pointer<T>(); }

public:

	Property() { /*CheckIfPointer();*/ }
	Property(const T value) : data(value) { /*CheckIfPointer();*/ }
	~Property() {}

	const T& Get() { return &data; }
	void Set(const T value);

	void AddWatcher(BaseObject* newWatcher, void(__thiscall BaseObject::*method)(T));
	void RemoveWatcher(BaseObject* leavingWatcher, void(__thiscall BaseObject::*method)(T));

	Property& operator=(const T& other) { Set(other); return *this; }

	// HOW DOES THIS MAGICAL JESUS FUNCTION EVEN WORK :O
	// This is literally the function which allows me to treat this class almost exactly like its internal type
	operator T() const { return data; }
};


#include "Property.hpp"

#define PROPERTY(type, name) Property<type> name