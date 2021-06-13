Final project, Team memeber: Zhenwei Liu, A16169244 ; Siyuan Zhang, A16059936

There are four buttons on our board. The first button is standard fire, when pressed, the ship will fire at standard rate. The second button is rapid fire,
when pressed, the ship will fire at a higher rate. The third button is pause, when pressed, the game will pause until you press the
fourth button which is continue. 

When the game starts, simply tilt the board left or right to move around. Use the first and second button to fire, 
and use third and fourth button to pause and continue the game.

We did several imporvement to our ship. First we decouple the fire and move, we can now use button to shoot and use accelerometer to move. Then we 
adjust the x,y,z zero values to make the shit move smooth. Then we added few functionalities to it.

During the game, the first row of OLED will show the state of the controller, the second row will show the reamining lives of the ship
and the third row will show the current score. When our ship got hit, our motor will buzz, LED will flash and OLED will update the lives.

When the game is over, the motor and LED will buzz and flash for a longer time, and 'game over' will print on the OLED. After a few seconds,
The controller will reset and ready for the next rounds with 4 lives and 0 scores.
