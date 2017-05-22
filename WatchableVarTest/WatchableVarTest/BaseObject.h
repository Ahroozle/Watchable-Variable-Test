#pragma once

#include <iostream>

#include "Property.h"

class BaseObject
{
private:

protected:

public:
	BaseObject() {}
	~BaseObject() {}

	template<typename T>
	void Watch(Property<T>& p, void(__thiscall BaseObject::*selfMethod)(T)) { p.AddWatcher(this, selfMethod); }

	template<typename T>
	void StopWatching(Property<T>& p, void(__thiscall BaseObject::*selfMethod)(T) = nullptr) { p.RemoveWatcher(this, selfMethod); }

	void TestMethod(float a) { std::cout << "First!\n"; }
	void TestMethod2(float a) { std::cout << "Second!\n"; }
	void TestMethod3(float a) { std::cout << "Third!\n"; }
	void TestMethod4(float a) { std::cout << "Fourth!\n"; }
	void TestMethod5(float a) { std::cout << "Fifth!\n"; }

};