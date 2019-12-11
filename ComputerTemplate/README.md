# WARNING: This folder, this readme, and the files are spoilers. 

# Intcode templates for C++

... because several of the intcode challenges fucking suck and failing one makes the rest impossible. 

You can use these as a reference for your own intcode implementation, or just copy it and skip some days. I highly recommend building off the last intcode challenge instead of skipping, entirely because it's very likely there's going to be more... (day 2, 5, 7, 9, and 11 are intcode challenges)

Also note that I made sure all the implementations are backwards compatible. It was the only way to make sure I got enough tests on basic features.  

## Structure 

The headers here are self-contained. Day5.hpp corresponds to the computer I had at the _end_ of day 5, Day7.hpp to the one at the _end_ of day 7, and so on. 

If you're looking to crack day 11, grab day 9 and build on the code to get the right answer for day 11. If you just want the answer, just add the input and run it the normal way (compile and run). The templates are here for people who want to try, but who found one or more days undoable. 

This doesn't cover day 2. Day 2 is extremely straight forward. Little to implement, decent examples that cover the things that need to be covered. That being said, if you're struggling with day 2, see src/Day2.hpp. Day 2 for me was done in 16 lines and it's fairly easy to understand and implement. 

Day 5 is where the difficulty, at least for me, skyrocketed. Day 7 wasn't too bad (medium-hard, but not _bad_ as some of the other intcode challenges were). I barely managed to do day 9 because of a resize issue. Lacking examples of any quality made it a pain in the ass to implement. 


