#pragma once

template<typename T>
WatcherList<T>::WatcherList()
{
	watcherArray = new Watcher[capacity];
}

template<typename T>
WatcherList<T>::~WatcherList()
{
	delete[] watcherArray;
}

template<typename T>
void WatcherList<T>::Watcher::Ping(T val)
{
	(watcherObject->*watcherFunc)(val);
}

template<typename T>
void WatcherList<T>::Broadcast(T newValue)
{
	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (watcherArray[currentWatcher].valid)
			watcherArray[currentWatcher].Ping(newValue);
	}
}

template<typename T>
void WatcherList<T>::Resize(int newCapacity)
{
	Watcher* newArr = new Watcher[newCapacity];

	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (watcherArray[currentWatcher].valid)
		{
			newArr[currentWatcher] = watcherArray[currentWatcher];
		}
	}

	capacity = newCapacity;

	delete[] watcherArray;
	watcherArray = newArr;
}

template<typename T>
void WatcherList<T>::Add(BaseObject* newWatcher, void(__thiscall BaseObject::*newFunc)(T))
{
	if (numValid + 1 >= capacity)
		Resize(capacity * 2);

	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (!watcherArray[currentWatcher].valid)
		{
			watcherArray[currentWatcher].watcherObject = newWatcher;
			watcherArray[currentWatcher].watcherFunc = newFunc;
			watcherArray[currentWatcher].valid = true;
			break;
		}
	}

	++numValid;
}

template<typename T>
void WatcherList<T>::Clear()
{
	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (numValid <= 0)
			break;
		
		if (watcherArray[currentWatcher].valid)
		{
			watcherArray[currentWatcher].valid = false;
			--numValid;
		}
	}

	numValid = 0;
}

template<typename T>
void WatcherList<T>::RemoveAllFrom(BaseObject* leavingWatcher)
{
	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (watcherArray[currentWatcher].valid)
		{
			if (watcherArray[currentWatcher].watcherObject == leavingWatcher)
			{
				watcherArray[currentWatcher].valid = false;
				--numValid;
			}
		}
	}
}

template<typename T>
void WatcherList<T>::Remove(BaseObject* focusWatcher, void(__thiscall BaseObject::*leavingFunc)(T))
{
	for (int currentWatcher = 0; currentWatcher < capacity; ++currentWatcher)
	{
		if (watcherArray[currentWatcher].valid)
		{
			if (watcherArray[currentWatcher].watcherObject == focusWatcher && watcherArray[currentWatcher].watcherFunc == leavingFunc)
			{
				watcherArray[currentWatcher].valid = false;
				--numValid;
				break;
			}
		}
	}
}
