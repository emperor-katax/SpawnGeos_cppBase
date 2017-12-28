
# SpawnGeos_cppBase

Developed by Unreal Engine 4.18.1

by: Katax

Katax.emperor@gmail.com

www.linkedin.com/in/cliff-sharif/

This application spawned number of static meshes into the stage and, when character collisions with them, each send unique message to game mode class and destroy themselves. This message appears on “Output log” in editor at the moment but can be used for Spawn other static objects or maybe time-based particle system to present destruction effect.

All classes purely developed and are functional under C++. 
StageOrginiser class, is responsible for spawn static meshes in number.It has UPROPERTY for change maximum mesh number and an identical name. Meshes which are spawned by organiser class, will send their coordination, id and organiser identical name to, game mode class as an event when they are destroyed.
GeoUnit class are container of each static mesh. They will respond to collision which catch from “Character” and destroy themselves by sending a delegate event through game mode. This event contains id, coordination and organiser identical name of that mesh. 

note:
This sample of application shows 3 walls made from number of static meshes which are made by 3 organiser classes. Total number of meshes are 320 spheres and they respond to player character movement. On collision with character, they will show message in output log and destroy.
For make new wall, drag an “StageOrginiser” class into the scene, change its “Frame Box” scale and positions, set up “Maximum Element To Spawn” and finally set “Orginiser Ident” to your preferred name. Click play and run through the new wall, also check output log for details.


Cheers … ; ] ,, 
