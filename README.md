Qixiang (David) Zhang  
Nai-Jack Li

## Distinct Longest Common Subsequences

### Problem Statement
Let ```bstring(n, x)``` be the length-n character string consisting of 0's and 1's which, when interpreted as a number expressed in binary, has value x.

Implement and analyze the time complexity of an algorithm CountLCS that, given n in the range, and two integers x and y that are each in the range, determines the number of distinct strings that are LCS's of ```bstring(n, y)``` and ```bstring(n, y)``` and displays them.


### Algorithm Description
Our algorithm (CountLCS) for this project consists of 2 major parts:
 - Count the size of LCS (LCS)
 - Print out the longest common subsequences (findLCS).

Details see [here](report.pdf)
