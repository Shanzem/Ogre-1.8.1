# Ogre-1.8.1

		Notes :-
		
CLICK ON PROGRAM RESOURCES.TXT FOR FULL DETAILS
		
Download 
https://drive.google.com/open?id=1YFPHCwl2J7vrGQKkfEuu7OY33_fFL_L7


18/04/2018

EXE WORKS! 

Added DLLs and changed the way they are looked for.

Pictures added date 11/04/18.

Learned a lot this weekend, 

Material scripts and how render passes work. 

- Included check "Scene.material" open with notepad! -

Game resource loading and grouping said resources for levels

Adding, setting positions of meshs. added lights, setup camera.
Moved camera for screen shots.

And setup GTK Radiant, and began making a map WITHOUT tutorials
or help resources on using the mapping program :D.

Cut all non needed faces, leak protection box.

Been using krita to create needed .tga textures for mapping.

Blender work. Just discovered blender2ogre does not work! ARGH!

New things to ponder :-

Physics and maths

Ray casting.

A vector drawn from point A to point B. Think i found a new friend!.

Used in object collision to FPS shooters to check if a shot fired is a hit or miss
on a hitbox. Also used to prevent models from falling through other meshs.


The use of BSP.

BSP,isn't very efficient but quick to setup. 
Octrees are more efficient but would require me to build my entire game scenery
in blender or another 3D modeling software.

For an example lets say i have  4x4  flat plane. i place that plane at 0x,0y,0z in ogre.
Which would mean 2 meters in y, and -2 meters in y. As 0,0,0 would be the center point of the plane.
I then add another 4x4 plane at 0x,0y,4z meters up and i would build my
geometry up by stitching it together.

That sounds painful but for the generic RPG it wouldn't be to hard.

Few templates, and thats it. Would actually make my life easier :).

Would just mean me making some form of grid with naming convention with locations on my part
to keep a track of the stitching.

------------------------------------------------------------------------

Me in ogre checking texture script. 

Ogre uses Painting passes like
Photoshop/Krita, LAYERS!. 

Mesh(s) has a texture from file applied to it on its first pass. via a script.

Check Scene.material for further details. (Right click open with notepad)

LOADS of scripts for pass`s different techniques,
ambient,diffuse,specular,emissive,texture,anim_texture,

Bottom of the pictures just a simple plane with again texture applied.

Check code for details.

<a href="https://imgur.com/Ubp9pGu"><img src="https://i.imgur.com/Ubp9pGu.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/t4ELlVs"><img src="https://i.imgur.com/t4ELlVs.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/l0Aa63E"><img src="https://i.imgur.com/l0Aa63E.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/8AmW2eb"><img src="https://i.imgur.com/8AmW2eb.jpg" title="source: imgur.com" /></a>


-------------------------------------------------------------------

Me in GTK Radiant.

Never used this map editor before :) but its just like the half life map editor.
In-terms of functionality and ease of use. What you see in the pic is a leak
prevention box and a "shelf" for the players camera. Then in the basin is the
beginning of a test cave map. 

Last pictures is textured black leaving only rock texture seen.

This will be what the player sees with the camera in +20y above and pitched/yawed

<a href="https://imgur.com/a4f5grr"><img src="https://i.imgur.com/a4f5grr.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/ankOkyC"><img src="https://i.imgur.com/ankOkyC.jpg" title="source: imgur.com" /></a>

----------------------------------------------------------------

Me in blender. 

Modeling a candle, to then place in a modeled room in blender.
To insert into Ogre so then i can try material script animation passes.

Unfortunately blender2ogre is throwing me an error :( or i would have a demo! :|.

Going to sort this by downloading blender 2.75 and hope my 2.79 models will import :|.

<a href="https://imgur.com/izbiKYw"><img src="https://i.imgur.com/izbiKYw.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/SAWY1Mq"><img src="https://i.imgur.com/SAWY1Mq.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/RAJKY0j"><img src="https://i.imgur.com/RAJKY0j.jpg" title="source: imgur.com" /></a>
<a href="https://imgur.com/sO6EGj4"><img src="https://i.imgur.com/sO6EGj4.jpg" title="source: imgur.com" /></a>
