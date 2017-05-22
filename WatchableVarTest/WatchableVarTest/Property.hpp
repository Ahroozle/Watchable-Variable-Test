#pragma once

#include "Property.h"

template<typename T>
void Property<T>::Set(const T value)
{
	data = value;
	watchers.Broadcast(value);
}

template<typename T>
void Property<T>::AddWatcher(BaseObject* newWatcher, void(__thiscall BaseObject::*method)(T))
{
	watchers.Add(newWatcher, method);
}

template<typename T>
void Property<T>::RemoveWatcher(BaseObject* leavingWatcher, void(__thiscall BaseObject::*method)(T))
{
	if (method != nullptr)
		watchers.Remove(leavingWatcher, method);
	else
		watchers.RemoveAllFrom(leavingWatcher);
}
