# Space Invader Engine  
Simple game engine customised for ** Retro Scroller Shooter ** type of game. It can easily be customised for other type of game.  
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
  - + or - to magnify the image
  - *Space* to draw line
  - *X* to change color
  - *F* to fill in the color selected
  - . or , to increase the FPS of the screen. Higher fps gave flickering effect on DOS-Box. So this feature was added for ease.
  - press console (~) to open console:
    - type "save" to save your file
    - type "next" to create next frame
  - Status of cursor and color is displayed on the top
pmusic.cpp is to demonstrate how the music works.  
sinvader.cpp is the game{  
  WASD movement ie. "A" to move left, "D" to move right  
  SPACE to shoot  
}  
Code can be modified to become an entirely new game  
