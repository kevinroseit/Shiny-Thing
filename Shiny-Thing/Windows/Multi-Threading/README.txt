---Hello, welcome and g'day!---

Today we have a delicious multi threading program utilizing Posix.  
This code should be pretty portable using threads and multiple muti (mutex's?). 

---The main idea for the program is this:

main waits till int i = 100 then quits. 
main will not add to i.
There are two threads that loop simultaneously one adds 1 to i and another adds 3 to i.
You can see the output of the threads as they work in parallel!
It works.. about as well as a rusty pair of pliers....
Hopefully for large scale applicatoins, like games, threading will increase the performance.
I have not yet measured the difference between this parallel thread program and a single thread program incrementing i by 3 the whole time.
Though It would be cool to see the speed and performance differences.


---Problems (Dates and Time lines available on Git!):

**ImportanceLevel = 10** Can't figure out this 'returns 3' problem.
Researched some of it and found maybe it's because I don't catch any of the exceptions that try_lock throws?

---Todo (Dates and Time lines available on Git!):

**ImportanceLevel = 5** Next I would like to get passing objects to threads. 
I have not researched this at all.

**ImportanceLevel = 3** I don't like global variables just hanging around. 
I would like to keep everythign neat and organized in headers and in main etc.
This is more of like an up keep to make sure lazy code and bad code does not stick around.

**ImportanceLevel = 6** Reminds me, what is Ian upto? See if he would like to help out.
I also may have some one else helping, his name is Joe. 
I believe he will be helping more on the game side though.


**ImportanceLevel = 1** Start work on some better documentation, not just for this program but for the game as well.
Maybe come up with a .pdf, examples and ooh pretty pictures, (making this stuff easier and friendlier to deal with, pretty much).



---Other:

Ignore what the pre-amble says in main.cpp. 
Right now I am working on very basic threading experiments. 
