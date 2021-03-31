# AmongThem 
A 2D game in c++ using openGL inspired by amongus

## How to run
```
    > mkdir build 
    > cd build
    > cmake ..
    > make
    > ./AmongThem
```
## Features
+ Random maze genreation
+ Two tasks on completion of each get 150 points
    + PowerStick : Red : vaporize imposter
    + PowerStick : Blue : make obstacles and powerup visible for more points collection
+ Bucket : Water : Adds 100 points
+ Bucket : Lava : Dexreases 100 points
+ exit open on 300+ points

## Keys
+ arrow keys for movement
+ q for quit window

## Lacks
+ HUD : see in terminal
+ Light : Always on

## Bonus
+ powerups and obstacles are inspired from minecraft
+ used bfs for choosing next step for imposter or shortes path in real time
+ win and lose icons 
