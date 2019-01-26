# Jetpack Joyride

## Instructions

mkdir build
cd build
cmake ../
make all -j 4

Note - In case of Experimental Error for GLM.
add "#define GLM_ENABLE_EXPERIMENTAL" in the files main.h nonedit.cpp other_handlers.cpp and input.cpp, before you include glm.

## Controls

- Up Arrow Key        : Going Up
- Down Arrow Key      : Going Down
- Right Arrow Key     : Going Right
- Left Arrow Key      : Going Left
- S/s                 : Shooting Water Balloons

## Bonus
- Dragon
- Magnet Power Up
- Immunity Power Up
- Seven Segment Score Display
- Ice Balls
- Good Representation of Characters

## About

- The world consists of a wall,score display,platform and the player.The player
will have a Jetpack attached to him with which he can move up. Note : we do
not expect the player to look same as the player in the picture, make use of
primitives to construct your player in the best creative way possible.

- Coins of different colours (each corresponding to certain points) should
appear above the ground at various heights (random).

- Magnets,should appear and disappear randomly which will cause the player’s
motion to be influenced.

- Special flying objects(moving in a projectile) at least 2, should appear
randomly and should give player certain bonus(Like speed ups, more
coins,etc) .You are free to use or own creativity and imagination.

- Circular ring: A semi circular horizontal ring should appear after a certain
distance, if the player goes inside this ring he should follow the semi circular
path and will be protected from the enemies.


- Enemy 1( Fire Lines) :Two circular or small cylindrical objects
appear and a “Fire” like line is created between them.The Lines can be at any angle with the platform.
- Enemy 2( Fire Beams): Two pairs of circular or small cylindrical objects
 appear and a “Fire” like beam is created between each
pair.The beams are parallel to platform and can move along Y
axis.
- Enemy 3( Boomerangs): A boomerang appears randomly and
move somewhat in a horizontal ‘U’ direction or a flattened ‘C’ direction
,i.e. the boomerang should start ahead of the player, go behind it and
then come back and cross the player.If the player comes in contact
with the boomerang ,a penalty should be incurred.
- Enemy 4( Viserion ) ( BONUS): A flying dragon should appear
randomly ,adjust its position according to player(movement along Y
axis) and should throw Ice balls (Need not look like an exact dragon :p
, but certainly better representations would fetch you extra bonus
marks)



