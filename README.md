# mezmerize engine - by the goat jskeleton
will leave you mezmerise!!d

## NOT FINISHED!! like its not even operational at this stage


### what is this? 
its an attempt to merge quake engine/source engine styled programming with modern component based systems, while still being LEGIBLE and READABLE (UNLIKE UNREAL. yeah i said it.)

### what is this not
this is not an engine to replace unity or unreal or whatever use those engines if you wanna make real games this is just a project im working on for FUN.

### should i use this engine for my next project?
no. only i can use this engine muhahaha cause im EVIL!!!!!
<br>
okay i just found out that if you dont put a license on some github stuff its automatically like "You cannot use this" or something for your stuff so i need to put a license no this i want all yall to use this but i gotta figure a thang out so DONT USE this just yet i dont want yall to get in trubs


## ! dependencies !
I didn't include any deps in here since im not sure if you can even do that but imma just list the deps now you gota go on a quest to find them. Put them in the deps folder and you should be fine.
you only have to compile assimp the rest have pre-built binaries

> sfml - (window stuff and some misc rendering stuff real good use it)<br>
> glew - (various opengl extensions)<br>
> glm - (opengl math stuff. amazing library use it) <br>
> assimp - (of course assimp is here its the goat)<br>

### how to setup
alright i kind of set it up weird so heres the general structure
<br>
the mez folder is where some general config and stuff is, the merize folder is where the actual code of the engine is. in YOUR program you need to make your engine class that inherits BaseEngine, and in main main.cpp you need to call (your engine)->run() to run the engine. (THIS IS A LOOP). 

# How to setup a project in MSVC
the easiest way is to just clone the repo. get the deps and put them where they need to be get the dlls put them where they need to go and boom you have it working. This should work
<br>
## How to setup as a multi project solution in MSVC
okay this kind of sucks but i'll break it down for you. You need mez and your project in the same solution, and you need to change mez to compile as a static library (.lib) instead of an executable. note: on msvc2022 this breaks library settings so set those back. and then on your project go to linker -> general and set Additional Library Dependencies to $(OutDir), and add "mezmerizeengine.lib" to Additional Dependencies in the input tab. this is how i got it to work i'll drop a better guide to set this up soon since this is how i want yall to use this
