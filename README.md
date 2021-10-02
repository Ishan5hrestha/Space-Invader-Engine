# Space Invader Engine  
Simple game engine customised for **Retro Scroller Shooter** type of game. It can easily be customised for other type of game.  
Initially made for running in DOS-Box within limited RAM of 64KB.
# Files
.txt files are the sprites of in game objects like ship, bullet, asteroids, backgrounds, etc. These files are created by PDRAWB2.cpp. Following are the descriptions of the code files.
## PDRAWB2.cpp
This is sprite drawing program that eases the process of drawing line between pixels and filling colors. The sprites can have maximum of 5 frames of different images like in a gif type file.  
Instructions for use:  
- To create new file goto line 145 and change the "ship" there to your desired object name.
```
fp=fopen("ship","w");
```
- Run the code.
  - Use *WASD* keys to move the cursor
  - plus(+) or minus(-) to magnify the image
  - *Space* to draw line
  - *X* to change color
  - *F* to fill in the color selected (Due to limit of DOS-Box, using this command can cause unusual bugs and problems)
  - . or , to increase the FPS of the screen. Higher fps gave flickering effect on DOS-Box. So this feature was added for ease.
  - press console (~) to open console:
    - type "save" to save your file
    - type "next" to create next frame
  - Status of cursor and color is displayed on the top
## PMUSIC.cpp
It demonstrates how the music works. It was created first to test music playing of the compiler and to clear out confusion.
The music is stored in **music.txt** which unfortunately got lost.  
Music was stored in similarly as in old Nokia phone's midi editor. Length of note, note name(C,C#,D,D#,E,F,F#,G,G#,A,A#,B,C) followed by duration of pause(ie. no sound).
## SINVADER.cpp
sinvader.cpp is the bulk of game engine. There are unused parts like rotate which can be useful in other projects. All of the objects on screen are member of class *object* which has initialise part and processing part on main body. This structure of objects was inspired by GameMaker 8.2's object concept of:
- Initialise: Actions to perform when room starts
- Step: Actions to perform on each run frame
- End: When object is destroyed, what actions to do
Currently this engine uses only the first two. The third isn't required because objects aren't destroyed. When bullets vanish from screen they goto position outside the screen. There are only 7 instances of bullets at any time. No more bullets are created due to limited memory limit. Same thing lies for the asteroid.  
Controls:
- WASD movement ie. "A" to move left, "D" to move right
- SPACE to shoot   
Code can be modified to become an entirely new game  
