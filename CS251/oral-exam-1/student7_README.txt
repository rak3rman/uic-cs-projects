
DISCLAIMER: This live coding prompt is purposely ambiguous.
We aren’t going to tell you exactly how to cout, exactly how to handle edge cases, etc.
There is no autograder and auto grading would defeat the purpose of the exercise.
Instead, you should talk through all of your thoughts and state any assumptions as you are solving the problem.

You got this.  :D  

PROMPT:

**********************
About - Spotify charts the Top 200 streamed songs daily. The file contains a list variation of 
        that, except that it does not include the song, only the artist. The other difference 
        is this list pertains to the days of 9/18/20 and 9/19/20. 26 totals songs,
        13 of the tops songs were considered for each day.
        The first row in the file contains the header for the file: (Artist | # of streams the song got)
        Each remaining row contains the name of an artist followed by the # of streams, separated by a space.
        As you work through the problem state any assumptions.
        
File reading - read data in. Store the header in a string (will not be needed). 
            Store the rest of the data in a map. Where the artist is the key and # of streams the value.

Process/Calculations: 
    (1) Write a script that allows the user to type in an Artist’s name and lookup how many streams that Artist had.
        Also print out if the Artist had above average streams (as compared to the rest of the Artists in the list).
    (2) After the lookup, print out useful information based on the results (if lookup failed, if user should try again,
	    what the result is, etc.). You can choose this.
        ** These calculations must be done after the container has been filled, and the file has been closed.

Creative component (if time permits) - create one cin and one cout for this problem.  Make sure your code uses the cin.  
****************