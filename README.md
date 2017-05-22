WatchableVars_Test

This was a small one-off I did within a few hours in my spare time because the idea had been nagging at me while working with Unreal Engine 4's UMG system. I absolutely adored the function and variable binding functionalities due to how simple and fast they made UI creation during the development of Elementum. However, I hadn't noticed any kind of system for events initiated by variable changes outside of UMG binding. The result of my curiosity is a wrapper class which can be treated as its contained type without risk as long as it is a non-pointer type. I tried to create checks for pointer types so as to fix the hole in behavior (as certain operations with encapsulated pointer types are able to be done without notifying the variable's listeners), but I was unable to figure it out and left it out.

If I were to redo this project, I would personally not put in the treat-as-contained-type functionality and instead would opt to create functions instead. I find it not only unnecessary, but also potentially problematic in the case that an end-user implement the type; It's too easy to forget that a watchable float is not a normal float. Using only explicitly-written functions would also completely eliminate the aforementioned pointer-type problems and make the class an overall more solid class to use.
