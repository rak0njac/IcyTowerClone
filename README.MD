## To be added:

- "floors.bmp" asset details (meanwhile you can figure it out yourself from FloorTypes.cpp)
- Sound asset details (meanwhile you can figure it out yourself by searching for sf::Sound occurences)
- Build instructions for Windows

## About
Demo: https://www.youtube.com/watch?v=Oedn3MMslG8

This is a clone of Icy Tower written in C++ using SFML. 

You need to provide your own assets - read below on how to do this.
Accuracy and faithfulness to the original game was very important, and I think it turned out great, keeping in mind that this is my first real C++ project.

Special thanks to the original creators and legends of Icy Tower and its legacy - Johan Peitz and Anders Svensson!

Things I may add in the future:
- sign sprites behind the number of a platform
- main menu
- launcher with config options
- replays

There will be no features which do not exist in the original games as that would not make sense for a clone. The clone may be extended to an all new project at one point.

## Assets

The game at it's current state does not support stretching or other means of properly displaying variably sized GFX assets. All GFX assets must be pixel-perfect unless noted different below each mentioned asset. 
The GFX assets must be located in ROOT/assets folder. Make sure to include the following GFX assets:

"Bkg2.png" represents the general background - the farthermost layer to render (blue bricks in original Icy Tower):<br />
Resolution: 505 (or higher) x 544<br />
Note: Make sure that the picture consists of 17 rows with 32px height. If desired, the rows can alternate between two designs, like in the original Icy Tower.

"Wallz3.png" represents the walls on the left and right side (white bricks in original Icy Tower):<br />
Resolution: 640 x 768<br />
Note: Make sure that the picture consists of 12 rows with 64px height. If desired, the rows can alternate between two designs, like in the original Icy Tower. Make sure that the area between the left and right wall is PNG alpha transparent.

"Clock.png" represents the timer clock background:<br />
Resolution: 73 x 84

"ClockHandle.png" represents the clock handle:<br />
Resolution: 73 x 84<br />
Note: The rotational pivot point of the handle is between the pixels at 36,47 and 37,47

"ComboMeter.png" represents the empty combo meter:<br />
Resolution: 40 x 131<br />
Note: The bar will be filled at the following rectangle of this picture: top-left at 11,19; bottom-right at 26,118; both values inclusive

"ComboMeterBar.png" represents the full bar of the combo meter:<br />
Resolution: 40 x 131<br />
Note: The bar should be at the following rectangle of this picture: top-left at 11,19; bottom-right at 26,118; both values inclusive. In the original game, the bar consists of 100 rows with 1px height and 16px width. It is not required to be this way in IcyTowerClone. You can fill the rectangle with anything as long as you stick to the right dimensions and positions.

"freshmarker.ttf" represents the default font. You can put any TTF font here and just change it's name to "freshmarker.ttf", or, alternatively, you can change the name in DefaultFont.cpp.

"harold.bmp" represents the character. IcyTowerClone supports original Icy Tower bmp character files. These are publicly available. For example, you can download http://hzik.com/vzkazy/icy/harold_the_underboy.rar and just use that as the asset, or you can create your own frames based on that asset (don't forget that it needs to be pixel-perfect).

"floors.bmp" represents the floor frames.

## Build instructions for Linux (special thanks to Arkanosis)

Using your package manager, install SFML, sed and gcc (g++). Run the following commands in their respective order in your terminal:

```
git clone git@github.com:rak0njac/IcyTowerClone.git
cd IcyTowerClone
sed -i 's@include <SFML\\@include <SFML/@' *.h
sed -i 's@static enum@enum@' *.h
g++ -std=c++11 -I. -I/usr/include *.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o icytower
```

Starting the game then is as simple as:

```
./icytower
```

The game is still playable without the assets; it's just all white rectangles on a black background. You can provide the assets by following the Assets section having IcyTowerClone as your root folder.