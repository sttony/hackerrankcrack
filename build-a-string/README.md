# Problem
You can execute two operations
1. Add a char, cost A
2. copy a substring and attach it to the end, cost B

Obviously, the key step is 2. You always can execute n operation 1, and cost A*len. 

# Approach
DP sounds like a good start. Let's create a  ```values[n]``` to store minCost to generate ```input[n]```, we will use 
example 1 aabaacaba to go through the process. 

For 1st char,  we have to use Op1,  so ```value[0] = A```, 

For "aa", we have two choice,  op1 append a,  or op2, copy substring "a".  However A=4,  B=5. So we should choose op1.

For "aab", no choice, ```values=[4, 4+4, 4+4+4]```, 

For "aaba", same for 2nd a,  ```values=[4, 4+4, 4+4+4, 4+4+4+4 ]```

For "aabaa", at this point. we can choose,  duplicate substring "aa",  then  ```values=[4, 4+4, 4+4+4, 4+4+4+4,  values[2] + 5]```
...

So the next question is, how can we find out the matched substring, in above example, how can we quickly find out 
```input.substr(0, 2) == input.substr(3,2) ```

I will use a char index to help to do the backtrace. This is a very common tricky to process string kind of problem. 

```cpp
vector<int> char_to_index[26]; 
// because aabaa

char_to_index[0] = [0, 1, 3, ];  // 0 ->a
char_to_index[1] = [2];  // 1 ->b 
```

When we get ```input[4]```,  we can know the possible matched substring starts at 3, 1, 0.  For index=3. the possible longest
substring is "a",  ```values[3]+ 5>  4+4+4+4+4```. But For index =1, the possible longest substring is "aa",  
```values[2]+ 5<  4+4+4+4+4``` so we need to set the new value to 17

# Complexity
For each backtrace,  it could be back len=1, len=2, len=3...  len = i/2=  (x^2/8 + x/4), for ```i=1-->n``` over all big 
O is O(n^3)/24.

Char index could store every char, so it is O(n). 
