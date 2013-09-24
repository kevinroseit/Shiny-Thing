**Please Note**

---Focus:

We are focusing on the Windows portion first and then we can por to other systems.
Each folder has all the same folders.
The window event for linux will be based either on x11 or what ever else they use.
We may or may not be able to support all graphical interfaces for Linux (I need to do some more research into that).
Do not worry about updating the code to all folders, again we will work on ports later.

---Libraries:

I have included DLL's and Static-Libraries in Windows.
I will compile certain SDK's with my 8.4 edition of MinGW GCC, mainly because I have to in order to use the SDK properly.
The two folder Libraries may end up not being used in the long run.

---SFML Libraries:
As of now the program will use Standard libraries (iostream, thread, mutex, etc.) and **SFML**.
SFML is an SDK that makes graphics audio and the like easier integrate with. 
SFML works on top of Open-GL and directX9. 
When we use SFML we may also directly use Open-GL and directX9 classes systems methods etc. (in case there are performance issues in areas where access to directX9 or OPen-GL may prove beneficial).
You must acquire SFML yourself it's really easy.
url: www.sfml-dev.org/download/sfml/2.1/
We must all use the same version of SFML which is 2.1.
We may have different compilers so I suggest building it from source, especially if you don't find one compatible with the programming environment you are using.
SFML has brain dead easy walk throughs on how to install and set up IDE's, at the top Resources->Tutorials SFML2.1 -> and the tutorial that best fits your needs.

---Formating code UTF-8 a problem?
For ultimate portability we should look into this UTF-8 source formatting. 
Not too important although something to keep in the bakc of our minds.
Also, should we include all project files (if I use Code::Blocks should I just upload the sources, inludes and libraries?).
I feel we should only include sources and the like to project files like Code::Blocks .cbj files.


---Let me know your thoughts I am not a mind reader!