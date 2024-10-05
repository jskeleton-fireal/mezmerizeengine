# mezmerize engine - by the goat jskeleton
will leave you mezmerise!!d

## NOT FINISHED!! like its not even operational at this stage


### what is this? 
its an attempt to merge quake engine/source engine styled programming with modern component based systems, while still being LEGIBLE and READABLE (UNLIKE UNREAL. yeah i said it.)

### what is this not
this is not an engine to replace unity or unreal or whatever use those engines if you wanna make real games this is just a project im working on for FUN.

### should i use this engine for my next project?
no. only i can use this engine muhahaha cause im EVIL!!!!!


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
the mez folder is where some general config and stuff is, the merize folder is where the actual code of the engine is. in YOUR main.cpp you need to call Engine::RunEngine() to run the engine. (THIS IS A LOOP). If you need more control you can create an instance of the engine (on the heap would be nice) and calling some stuff before finally calling run. You do not need to inherit the engine. (todo: more docs! for the people!)
