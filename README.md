# Hey there!

This Repo includes a simple express server to provide yourself an API to get your TikTok followers.
Also there is code for a MAX7219 LED Matrix and a Wemos, to call this API and display your followers.
STL files can be found on Thingiverse: https://www.thingiverse.com/thing:5317413

If you have 10k Follower or more, the code will not work anymore (Count is rounded on TikToks server). 

## Setup
### Server
Just install dependencies and run the script local or deploy somewhere (e.g. Heroku).
### Wemos
I'm using this lib for controlling the matrix: https://github.com/squix78/MAX7219LedMatrix
Look at this PR for rotating: https://github.com/squix78/MAX7219LedMatrix/pull/8

Enter your Server and Wifi credentials and start flashing the code.
