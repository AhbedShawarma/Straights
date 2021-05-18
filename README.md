# Straights Design Document

## Overview
The project follows the model-view-controller design pattern and structure. Due to the controller and view being tightly coupled, I chose to only create one class that implements both of their roles in a class called Interface. This leads to the structure resembling an observer pattern more. Interface is a concrete object of the observer class and the model (StraightsModel) is a concrete object of the subject class.  StraightsModel stores all of the data of the game including each player’s data, the deck, the piles of cards on the table, the basic rules of which card needs to be played first and the score total that will lead the game to end. The Interface contains a StraightsModel and is attached to it in an observer pattern. The Interface also contains the main game loop.

PlayerData and Card are separate classes that are included in StraightsModel and Interface. PlayerData stores a player’s hand, discard pile, total score, and current round score. The final class is the computer class which only stores the functions for what the computer can do.

## Design
### Game Loop
Initially, I planned my game loop to be a recursive call of functions between update, playeTurn, and a model function which then calls update. However, this became complicated quickly and I realized that for my simple text based view, I do not need to update anything after a player makes a move since it is not a real time changing display. So I simplified the design of my game loop to be a while loop that breaks when the game ends. This loop relies only on functions in the model class to decide when a round ends and when the game ends and does not handle any logic itself. It handles user input and calls functions in the model that handle the logic for that input. 

### Play and Discard
These functions are implemented in model and only handle removing cards player hands to either a pile on the table or the discard pile. Initially, I was also going to handle whether the play or discard is legal here but decided to create separate functions for those instead since they need to be accessed by other functions and the interface as well. These functions use std::remove to remove cards which is most of the logic.

### Cards
I initially was not going to have a Card class because I thought I didn’t need one. However, I kept finding that it would be easier to break up the suit and rank of a card and also store the rank as an integer from 1 to 13 to handle the logic in the model class. I would later create a dictionary in Interface to map each integer to the associated letter for outputting. I also realized I needed to sort vectors of cards, find cards in vectors, and remove cards from them so I decided to create a dedicated card class that handles equality operators such as ==, !=, >, >=, <, <= so that I can use functions from algorithms on a vector of cards.

### Computers and ragequit
I decided to create a computer class only to include functions that return the card the computer has chosen to play or discard. I stored the list of players in model and had an indicator that tells the program which players are computers and which are humans. The computer functions took in parameters of PlayerData so that they can decide which card to remove from player hands, or if they need to play a card, a list of valid moves was passed to the function. This resulted in me handling the difference between computers and humans easily, a simple char to indicate the difference. This structure also made it easy for a player to ragequit as only the indicator needed to change as a result of them quitting.

### Deck and Shuffle
As a result of the overloaded operators I created for Card, it was easy to shuffle them and store the deck as a vector of cards.


## Resilience
### A change to the GUI:
I chose to implement a MVC design pattern so that changes in the display of the game can be easily implemented. All of the game’s data and functions that change the data are implemented in a model class called straights model. This class can attach different views that are concrete observer classes. So if you want to change the game to use a better GUI instead of the simple text that is currently implemented, you can do so easily. You will not need to change anything from the model class or other classes being used and only have to create the new view itself. This is achieved by the functions in the model that handle the logic of a player turn end with calling a notify function to notify it’s observers (any view) to update. So once the view calls the model to run game logic, the view’s update method will be called to update the display.

### A change to the rules and basic mechanics:
In my model class, I store variables for the starting card that should be played first and the score needed to end the game. Changes in these rules can be easily made. Furthermore, it is also easy to change how a winner is decided as it is handled in it’s own function. The same goes with a change to how a round ends and when a game ends. These are all functions in model and if they are modified, no other class needs to be changed. The interface class calls on these functions to output the results of turns and what is occurring in the game but does not handle any logic itself. So changing these functions in the model will not require the interface to change.

### A new feature
If a new feature is required to be added to the game, there could be a lot more changes required as compared to changing the GUI. This of course, depends on the feature. If the feature is simply a new command a player can make then all I would need to add is an extra input in my interface which would then call a new function in my model class.
