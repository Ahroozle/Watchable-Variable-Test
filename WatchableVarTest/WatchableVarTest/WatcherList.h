#pragma once

class BaseObject;

template<typename T>
class WatcherList final
{
private:

	class Watcher
	{
	public:
		bool valid = false;
		BaseObject* watcherObject = nullptr;
		void(__thiscall BaseObject::*watcherFunc)(T) = nullptr;

		void Ping(T val);
	};

	// NOTE: When watchers are removed, their validity bool is simply switched to false.
	Watcher* watcherArray;

	int numValid = 0;
	int capacity = 2;

	void Resize(int newCapacity);

public:

	WatcherList();
	~WatcherList();

	void Broadcast(T newValue);
	void Add(BaseObject* newWatcher, void(__thiscall BaseObject::*newFunc)(T));
	void Clear();
	void RemoveAllFrom(BaseObject* leavingWatcher);
	void Remove(BaseObject* focusWatcher, void(__thiscall BaseObject::*leavingFunc)(T));
};

#include "WatcherList.hpp"