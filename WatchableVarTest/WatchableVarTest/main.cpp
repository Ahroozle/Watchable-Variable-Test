
#include "Property.h"
#include "BaseObject.h"

#include <iostream>
#include <crtdbg.h>

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Behold the magic of the Property<T>::operator T() const

	// This is completely valid and yields the correct result (setting the internal short to 50)
	Property<short> shortProperty = 50;

	//*shortProperty;

	// This confuses intellisense, but is still completely valid.
	Property<float> floatProperty = shortProperty;
	// The only operator= overload in the class is 'Property& operator=(const T& other)'

	// This is completely valid and yields the correct result (setting realInt to floatProperty's internal float's value), too.
	int realInt = floatProperty;
	// (also it gives you warnings as if it were an intrinsic type)

	// So is this.
	std::cout << floatProperty << std::endl;

	// You can new into it...
	Property<float*> floatptrProperty = new float(10);

	// ... dereference it...
	*floatptrProperty = 100;
	std::cout << *floatptrProperty << std::endl;

	// ... AND delete from it...
	delete floatptrProperty;

	// ... without ever knowing it's a wrapper class!

	// HOW DOES ANY OF THIS EVEN BEGIN TO WORK?!


	std::cout << std::endl;

	BaseObject test;

	test.Watch(floatProperty, &BaseObject::TestMethod);
	test.Watch(floatProperty, &BaseObject::TestMethod2);
	test.Watch(floatProperty, &BaseObject::TestMethod3);

	floatProperty = 10;

	std::cout << std::endl;

	test.StopWatching(floatProperty, &BaseObject::TestMethod2);

	floatProperty = 10;

	std::cout << std::endl;

	test.Watch(floatProperty, &BaseObject::TestMethod4);
	test.Watch(floatProperty, &BaseObject::TestMethod5);

	floatProperty = 10;

	std::cout << std::endl;

	test.StopWatching(floatProperty);

	floatProperty = 10;

	std::cout << std::endl;

	float lel = 1;

	//float* derpy = dynamic_cast<float*>(lel);

	system("pause");

	return 0;
}
