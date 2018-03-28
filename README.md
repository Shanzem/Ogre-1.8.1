# Ogre-1.81

		Notes :-
		
Laptop issues!

Backup everything, factory reset :|

If i get it sorted today, next week i will finish trying to build 1.10

Does ogre use "Y" as an up axis!? that should be "Z". :p.

I am missing Ogre OgreApplicationContext.h is this a 1.10 header? or is it a plugin? 


		Play with me guide :-
		
Download bloodshed Dev++ 5.11 or greater.
Install to its default path.
Run ogre, choose your preferred views.
close ogre. 
		
Create a new folder in your drive C:\ called "ogre" (case sensitive) LOWER CASE!
So if you open C:\ you see an ogre folder.

download pre built 1.8.1 from my google drive :-


extract OgreSDK_MinGW_v1-8-1 content to C:\ogre. so now you have C:\ogre\OgreSDK_MinGW_v1-8-1 in a folder.

download this package - top right as zip
extract to C:\ogre. so you have a directory like this :-

Directory of C:\ogre

22/07/2012  11:28         8,530,240 cg.dll
07/12/2014  18:48            14,556 libd3dcompiler_43.a
07/12/2014  18:48           212,680 libd3dx9d.a
07/12/2014  18:48           261,952 libd3dx9_43.a
07/12/2014  18:48           257,550 libole32.a
07/12/2014  18:48           313,172 liboleaut32.a
29/05/2017  23:00         1,508,122 libstdc++-6.dll
07/12/2014  18:48             3,354 libwbemuuid.a
27/03/2018  14:26             9,118 main.cpp
18/10/2012  18:00        10,169,856 OgreMain.dll
18/10/2012  18:00           174,592 OgrePaging.dll
24/03/2018  11:33             2,222 ogreproject.dev
26/03/2018  19:57         1,531,077 ogreproject.exe
26/03/2018  20:01               408 ogreproject.layout
18/10/2012  18:00            78,336 OgreProperty.dll
18/10/2012  18:00         1,007,104 OgreRTShaderSystem.dll
18/10/2012  18:00    <DIR>          OgreSDK_MinGW_v1-8-1	- Thats the SDK folder
18/10/2012  18:00           466,944 OgreTerrain.dll
18/10/2012  18:00           114,176 OIS.dll
18/10/2012  18:00           245,248 Plugin_BSPSceneManager.dll
18/10/2012  18:00           307,200 Plugin_CgProgramManager.dll
18/10/2012  18:00           135,168 Plugin_OctreeSceneManager.dll
18/10/2012  18:00            77,312 Plugin_OctreeZone.dll
18/10/2012  18:00           205,824 Plugin_ParticleFX.dll
18/10/2012  18:00           330,752 Plugin_PCZSceneManager.dll
18/10/2012  18:00           837,120 RenderSystem_Direct3D9.dll
18/10/2012  18:00         1,416,192 RenderSystem_GL.dll



open project "ogreproject.dev"

right click on ogreproject in projects tab on left hand side, click project options.

Click on parameters tab. click on "add library or object". button bottom right.

navigate to C:\ogre and add 

C:\ogre\libd3dcompiler_43.a
C:\ogre\libd3dx9d.a
C:\ogre\libd3dx9_43.a
C:\ogre\libole32.a
C:\ogre\liboleaut32.a

Do the same and add 

C:\ogre\libstdc++-6.dll

Do again add :-

C:\ogre\OgreSDK_MinGW_v1-8-1/lib\release

OgreSDK_MinGW_v1-8-1/lib/release/libOgreMain.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/libOgrePaging.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/libOgreProperty.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/libOgreRTShaderSystem.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/libOgreTerrain.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/libOIS.dll.a

Do again add :-

C:\ogre\OgreSDK_MinGW_v1-8-1/lib\release\opt and add

OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_BSPSceneManager.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_CgProgramManager.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_OctreeSceneManager.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_OctreeZone.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_ParticleFX.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libPlugin_PCZSceneManager.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libRenderSystem_Direct3D9.dll.a
OgreSDK_MinGW_v1-8-1/lib/release/opt/libRenderSystem_GL.dll.a

If you done this correctly hitting compile and run in Dev++ will show a blank screen called.

"Hello Ogre World From Luke :)"

and should create a "First-Ogre.LOG" in C:\ogre

FIN :).


		System requirements / My constraints :-
		
Windows / Linux	/ Raspberry PI
		
1Ghz 			Intel/Atom/Amd	- Empty frame with plugins uses 24.88% cpu a second.

500(+20?)MB		Ram				- Empty frame with plugins so far uses 10MB ram.

64MB 			Graphics card supporting GL/DX9 integrated or better.


		What i have in the box currently :-
		
Ogre 1.8.1							Running in Dev++
ogreproject.exe						Test window, produces .log contain all loads
OPENGL								Tested and works	-	Enabled
DX9									Tested and works	-	Enabled
FreeImage 							version: 3.15.3
ParticleFX							Need documentation
BSPSceneManager
CgProgramManager
PCZSceneManager						Need documentation
OctreeZone							Need documentation
OctreeSceneManager					Need documentation




		Still needed :-

Quake 3 map editor for .bsp maps	Q3Radiant 197 by Id Software or open source equivalent. 
									Hopefully its like half life or half life 2 map editor. or natural selection 2 map editor.
									I have experience in these editors.
									
Resource manager .pk3				Internal way for Q3Radiant to handle data compression. appears as an archive.
									Should contain a map. Should be able to pack .mesh .tga(other image formats).bsp
									Less HDD space.
									
									
Navmap plugin	 					Identify scenes changes / loads for player. A.I movement, patrols route to player without
									getting stuck.

MySql lite plugin					Database, items, saves, NPC stats, the bread and butter at the fancy restaurant.
(Open source equivalent) 			Always wanted to learn SQL, now is my chance!						
									
																		
LUA plugin							A.I Scripting, camera events,tutorial,cut scene.
									Like jass from warcraft 3 map editor :)
									Bet that is its origins.

Sound plugin(raw)					Not researched much, OpenAL is one option.

Movie plugin						Ogre forums mentioned "A" plugin, plays video. no sound played, but file must contain sound!.
									Hopefully this is cured/altered made sane :).

Mesh viewer							I have vowed to make this myself as a side project.
									Using imgui and ogre engine to load and render a mesh in GL/DX9 and include textures/wireframe
									to test defects and check mesh bones and animation work.
									Without the hassle of coding it in to test.
									
Blender2ogre						Not built, downloaded

IMGUI raw binding 					(not .dll :D )	Needs porting in, Todo once a laptop is sorted.	

							
									
		Oddities :-
		
Multi-player mode 1~3 players? 		LAN (Wifi,Cat5)and VPN only. Could be implemented, Internet play? 
									iffy on a good idea as it means exposing a port. Should be interesting on PIs.
									Gamepad usb support, easy to code implement. open source OS. cheap hardware.
									Nifty little games console. :)
									
		
Multi-player plugin					It exists no idea if it supports 1.8.1 though.

		Undecided :-
		
Tempted to make this like diablo 2,torchlight 2.
Heavy use of 2d images, with only 3d characters / mobs / pawns / (buildings - possibly)
Scenery can be 2d, due to the camera locking in locked z/y/x with isometric view, while still looking like it has a 3d model.

		Example :-

Light source without shadows. 

Prop candle (light source) in an empty room. attach a small .png picture to all faces in the room.
the closer to the light the higher the transparency until full (see through) further away transparency becomes dark.
add multiple pictures that cycle every 30 fps, but slightly altered to give the effect the candle is flickering.

This effect is seen in the fresnel demo, for the roman bath. giving the illusion of the waters reflection on shiny tiles.
Even though its just a collection of small (30kb) 30 images played in a loop.

This saves costly calculations on static items, detailed shadows on player and NPC Pawns only.

I do have tight constraints. But nav nodes to different locations and loading will help with that.

As well as my coding ability. Going to look for some OGRE .Pdf books. 

All goes well you should be able to play this on a raspberry PI (Have one to test!! running debian) and i can play on my laptop :).

