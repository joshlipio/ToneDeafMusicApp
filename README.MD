#Tone Deaf Music Application
Final project for CS 3505 at the University of Utah. Tone Deaf is a program that teaches users the basics on how to play piano as well as how to read sheet music through several lessons and playing tests.

TO GET THIS WORKING ON YOUR END:

In the directory you pulled to (The same one with the include and ToneDeaf folders) create two new folders, libs and bin (exact names).

1. Choose which kit you want to use, the current ones I have supported are MinGW 32bit, MSVC2015 32bit, and MSVC2015 64bit.

2. Once you've chosen that, open up the DLL files zip folder, then open the folder corresponding to the kit you chose.

3. Copy the files in that folder (all of them might not be necessary, but I left them in to be safe) and move them to an empty "bin" folder.

4. Next, open up the Lib files zip folder, then open the folder corresponding to the kit you chose.

5. Copy the files in that folder to the empty "libs" folder you created.

6. Make sure when you open the project in Qt you select the kit corresponding with what you chose.

Then, it should compile just fine when referencing SFML and Box2D.

Hope that works!


