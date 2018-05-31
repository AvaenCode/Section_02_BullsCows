# Section_02_BullsCows

The following project is a console game that will ask the user to guess an isogram. Depending on the user input which can only be lowercase and have no repeating letters (definition of an isogram), the game will either return Bull(s) or a Cow(s). 

The definition of a bull and cow can be found below:

Bull - The letter is in the right place and is correct.
Cow - The letter is not in the right place but is correct.

I.e: Assume our hidden isogram is "plane", the user name do one of the following:

- If the user input the word "apend" the user will get the following feedback:
Bull = 0 |  Cow = 3, this is because the letters 'a', 'e', and 'p' are found in the target word "plane" but are not in the right place. Despite the spelling of "append" being wrong, the game will not check for spelling.

- If the user input the word "pleas" the user will get the following feedback:
Bull = 2 | Cow = 2, this is because the letters 'p', & 'l' are in the right place and are correct. However 'a', & 'e' while being correct aren't in the right place.

The hidden word will be random every time the game is reset or reopened. No input files are needed, the hidden isograms are pulled from an array of strings that have it's indexed randomly generated.
