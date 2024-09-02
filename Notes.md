# BattleSips Notes
*For quicker startup and a central place for "planning"*

The notes will be divided into 3 sections:
- Implementation notes
- Planning
- General

## Implementation
- Having problem compiling with "Serial" from other filetypes than ".ino"
- Main: Starting from Neonodes "Simple" sketch.

## Planning
- [ ] test and verify button library
- [ ] Include button library

### Matrix Library
- Create Library

### Initial sketch
- [ ] Make it fun to start up board
  - [ ] Add startup animation
  - [x] Low light intensity
- [x] Start from scratch with a simple and maintainable base: building from a Neopixel sample (since that is the main thing on the board.)

## General notes
### 2/9/2024
Fideling w/ trying to include ``Serial`` seems to be a bit more complex, with numerous library dependencies which are automatically in ``.ino`` files. The solution is to point to a "print"-function in .ino file.

Focusing today on a fun startup animation. 

Thinking of a wave... Maybe have a pixel width which is continually moving.
1) One pixel line which is moving across the board.
   - [ ] Create a matrix class
   - [ ] Create animation class 
2) Fill pixel behind w/ blue

How do we want to set the color of a pixel?

i: 0     1   -   99  100	101	-	199	200	201 -	299
R: 100   99  -   1   0   0   -   0   0   1   -   99  
G: 0     1   -   99  100 99  -   1   0   0   -   0   
B: 0     0   -   0   0   1   -   99  100 99  -   1  

i = 0 ->       RED
0 < i < 99 ->  RED/GREEN
i = 100 ->     GREEN
101 < i < 199 ->  GREEN/BLUE
i = 200 ->     BLUE
201 < i < 299 ->  BLUE/RED

colorCounter

one loop to sequentially light colors
  colorCounter++
  check color value

one loop to sequentially tur lights off

color is    0 - 100
strength is 0 - 255

strength = 0 - 10 -> 0 - 255
10*25.5



### 22/8/2024
Starting these notes as jumping into programming today it was quite hard to know what is the next step. Hoping this document will ease with both implementation notes on what is being designed, and also gather tought on what is needed in teh future.

Found out that Arduino for VS Code i "deprecated", and that they are pointign to the new 2.3.2 version of the Arduino IDE to be used instead. Thus my thought of keeping everyting within VS Code is probably faulty. Instead VS Code should be used for...  you guessed it, code! 
