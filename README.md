# PaPiPuPePo ![icon](Visuals/PaPiPuPePoIcon.ico)

Very simple game that I build years ago when I was first toying around with C++ game creation.
I've touched up the code a wee bit and rephrased some of the comments,
the main reason I'm bothering to push this to github is to help build up a portfolio.
It was the only finished project of mine that used win32 and the stretchBlt function to draw a manually modified pixel buffer to screen (I've moved on to opengl now for a few reasons, some of the opengl projects I'm working on I plan to release later).


The game itself is named after the Japanese vowel sounds when combined with the consonant P,
no particular reason other than it sounds kind of funny (at least when I'm practicing hiragana aloud lol)

Pa ぱ, Pi ぴ, Pu ぷ, Pe ぺ, Po ぽ


---

## Gameplay

You play as the blue square and you have to reach the cyan square without being caught by any of the red squares.
Each time you reach the cyan square you gain a point and a new red square spawns in.


### Controls

All movement is grid locked, (you move from square to square and can't rest between them)

W ⇒ move up

S ⇒ move down

A ⇒ move left

D ⇒ move right

The game ends when you are either caught by a red square or you close the window


---

## Important

### Game speed and rendering

The game speed and rendering is attached to a simple timer system,
see lines 146/147 of entry.cpp.
I've uploaded the game for higher performance machines (I'd rather the game was slower on weaker machines than too fast and flashy on stronger machines).

But I've included the cbp so you can easily modify the line and recompile the project for your machine.
( hold > release + x, higher values of x make the game slower, lower values of x make the game faster).

If you really wanted you could separate the game events and the rendering or just use a more reliable timer system?
I'm not going to bother myself as I don't want to waste any more time on a game that I built years ago while testing the waters of bare-bones C++ game making.

### License

I'm releasing this project completely open source using the unlicense template: https://unlicense.org/

A grid locked square move around game isn't exactly a hard idea to come up with and implement,
so I don't see any point licensing the game with a stricter copyright/left license.

The unlicense website recommends adding some extra terms regarding major contributors and what not.
I'm not going to bother with anything like that for 2 reasons:

- Only I will be contributing to this specific repository

- It's a very basic game that anyone could come up with and create, I don't care if you make your own copy, recompile, modifiy, sell, etc. Just make sure you acknowledge the capialised part of the license file (see below)


THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.



To view the license itself see LICENSE.md, or look at the top of each .cpp, .h and .rc file where it exists as a comment!




