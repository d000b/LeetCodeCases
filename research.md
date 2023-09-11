Iteration: 6  
Version: 18c0aa94cbeca78b1230ae500076f03bc0fcd039  
Runtime: 7ms  
Memory: 10.2Mb  
Message: Removing re-capture of previous values from stl\vector via indices. Using the values saved after the previous code block has been run. Possible cause: Cache miss, Branching.  

Iteration: 5  
Version: 8e0593e5459a01e63f346102e39daabf21301423  
Runtime: 0ms  
Memory: 10.2Mb  
Message: Using stl\Container methods (front(), end()) instead of indexes. Access to stl\vector read values in the boundary case has been changed from copying values to access by constant left reference.  

Iteration: 4  
Version: 166f41af4db2ba563da6b709c609b33b964d0479  
Runtime: 5ms  
Memory: 10.2Mb  
Message: Creating a boundary case with read-optimization. Splitting code into methods.

Iteration: 3  
Version: efb15c27d4562da446f3f5e386b62184f43c386e  
Runtime: 7ms  
Memory: 10.4Mb  
Message: Keeping locally close previous values did not allow us to get a speed gain relative to the previous version of the code. There was a memory loss of 0.2Mb   

Iteration: 2  
Version: 2c6c98079e458666811bc3996b169901d8da447d  
Runtime: 7ms  
Memory: 10.2Mb  
Message: According to the [LeetCode](https://leetcode.com/) website and their [compiler](./setting.cpp.md), the optimization using local saving and reusing previous (column) values was 3ms (30%). Possible Cause: Fixed the cache miss issue.   

Iteration: 1  
Version: 9ef09b805b25dd683a5f788b39fa361832a5e7a7  
Runtime: 10ms  
Memory: 10.3Mb  
Message: First workable code. All logic is mixed in a single method. Extreme cases are not worked out.  
