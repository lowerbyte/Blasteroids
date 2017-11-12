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

![Screen one.](/images/blasteroids_git.png)

![Screen two.](/images/blasteroids2_git.png)

![Game over.](/images/blasteroids3_git.png)

Hope you will have fun with it!


