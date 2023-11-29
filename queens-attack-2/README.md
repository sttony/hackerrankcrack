# Problem
The description is very clear, also contains several illustrations. 

# Analysis
The max cells queen can attack is n*4. The max number of obstacle is n. Checking the cell queen could attack, and 
check if it is effected by obstacle may be a good ideal. 

The basically ideal is,  trying to move queen,  stop if an obstacle is reached. 


# complexity

1. constructing hashtable for obstacles is O(n)
2. moving queen is O(4*n) 

overall  time complexity is O(n)
space complexity is O(n).