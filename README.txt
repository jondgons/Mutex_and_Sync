--Program Information--
  Name: Cody Gonsowski
  Date: 02/18/2020
  Assignment: Assignment #3
  Program Title: Multithreaded Mutex & Synchronization
  Files required: main.c, makefile
  	
--Design Overview--
  This program is essentially a bank demonstration that utilizes multithreading to perform a series of deposits and withdrawls. There are THREAD_COUNT (4) threads in total, half for deposits, half for withdrawls. The output shows at what time the action was performed, and the balance before and after the action.

--Known Bugs/Problems--
  - -no-pie used in makefile as a workaround for -lpthread issues with linking
  
--External Sources--
  - lec4-1.pdf - utilized for mutex management
