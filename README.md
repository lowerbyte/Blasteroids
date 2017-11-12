#Blasteroids

Hello! I'm sure you know this game. Very old, very simple and veery good.  
My friend asked me to help him with his project which ge got from the book _Head First C_.  
Don't know how good this book is, but this challenge was really great, so I thought I will write one myself.  
In the book we only have few things done and those are structures for spaceship, blast and the asteroids and how game should react and behave. The rest (which is the impelemtation) is your pure imagination.

So let me introduce you to my impelentation. It is very simple, but works very well. I tried to comment the code, so it would help you to understand it.  
To compile the code you have to have the Allegro5 library download which you can get from [here](http://liballeg.org/download.html).  
After that and closing my repository you have to compile it with linked libraries (I did not a make file :C). This command should help you:  
`gcc spaceship.c blast.c asteroid.c collision.c main.c -lm -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -Wall -Wextra -o blasteroids`

Sample screenshots:
![Screen one.](https://drive.google.com/file/d/1ibdsNdQdhiEFF3EAEcuNu2m3dJGOvYcK/view?usp=sharing)

![Screen two.](https://drive.google.com/file/d/10KI2YHShm6nIQC5zHwQkeHzmtph7ax7J/view?usp=sharing)

![Game over.](https://drive.google.com/file/d/1_Qv7DChpszHv3v4AjgWcMmf8-rViMRTz/view?usp=sharing)

Hope you will have fun with it!


