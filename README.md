# A SDL Project for Forsbergsskola GP22
## Summary of the project
This is a little endurance game used with SDL framework. The player will click through three stages; main menu, main game and the end credits. The main menu will give instructions how to enter the game or exit the game. In the main game, a background image with a fox will be displayed. In the upper left corner the player will see the instructions to start the game. As soon as the player presses on the fox, a timer and music will go off as long the player keeps the mouse pointer pressed. When the player stop pressing the timer will stop and the end credits will show the amount of seconds the player endured the game. 
## Information about the code
The code includes class definitions for the application, states, and textures, as well as implementation code for handling events, updating the game state, rendering the game, and managing the lifecycle of the application.
### Application Class
The Application class is where to manages the game. It includes functions for initializing and closing the game, handling events, updating the game state, and rendering the game. It also includes member variables for managing the game window, the game renderer, the current state of the game, and the font used to render text in the game. The Application class inherits from the CSingleton class, which is a template class for implementing the singleton pattern.
### State Class
The State class is an abstract base class for different states of the game, such as the menu state, game state, and end state. Each state class inherits from the State class and implements its own update(), render(), onMouseButtonDown(), and onMouseButtonUp() functions for updating the state, rendering the state, and handling mouse button events.
### Texture Class
The Texture class is a class for managing textures in the game. It includes functions for loading textures from files, rendering textures to the game screen, and freeing textures when they are no longer needed.
### External Libarys 
The code uses third-party libraries such as SDL and SDL_image for handling graphics and input events, and SDL_mixer for playing music in the game.
## Media
### Screenshots
![Main Menu](https://user-images.githubusercontent.com/112477585/232328850-10eb952d-0871-43f2-b286-0d7192c7e7ab.png)
![Main Game)](https://user-images.githubusercontent.com/112477585/232328881-0b6bf5be-1593-4268-a539-4496c2af7b5c.png)
![End Credit](https://user-images.githubusercontent.com/112477585/232328905-2e1e5452-f8e8-4e3c-a9dd-54a35225e748.png)
### Game Video
https://user-images.githubusercontent.com/112477585/232329875-fc376e43-d3ae-4586-a224-32416b8a9f79.mp4 

(Unfortunatley the recorder couldn't configurate the SDL window correctly, so the player is pressing on the fox.)
## Download the game
Click on the zip file that you want to download, after the download you open the zip and chose PopUpClicker.exe

Have fun!


