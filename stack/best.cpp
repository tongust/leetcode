/*
We want to search for a subsequence (s1,s2,s3)

INTUITION: The problem would be simpler if we want to find sequence with s1 > s2 > s3, we just need to find s1, followed by s2 and s3. Now if we want to find a 132 sequence, we need to switch up the order of searching. we want to first find s2, followed by s3, then s1.

IDEA: We can start from either side but I think starting from the end allow us to finish in a single pass. The idea is to start from end and search for a candidate for s2 and s3. A number becomes a candidate for s3 if there is any number on the left of s2 that is bigger than it.

DETECTION: Keep track of the largest candidate of s3 and once we encounter any number smaller than s3, we know we found a valid sequence since s1 < s3 implies s1 < s2.

IMPLEMENTATION:

Have a stack, each time we store a new number, we first pop out all numbers that are smaller than that number. The numbers that are popped out becomes candidate for s3.
We keep track of the maximum of such s3 (which is always the most recently popped number from the stack).
Once we encounter any number smaller than s3, we know we found a valid sequence since s1 < s3 implies s1 < s2.
RUNTIME: Each item is pushed and popped once at most, the time complexity is therefore O(n).

EXAMPLE:
i = 6, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 9, S3 candidate = None, Stack = Empty
i = 5, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 7, S3 candidate = None, Stack = [9]
i = 4, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 10, S3 candidate = None, Stack = [9,7]
i = 3, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 9, S3 candidate = 9, Stack = [10]
i = 2, nums = [ 9, 11, 8, 9, 10, 7, 9 ], S1 candidate = 8, S3 candidate = 9, Stack = [10,9] We have 8<9, sequence found!

EDIT: Thanks @Pumpkin78 and @dalwise for pointing out that the maximum candidate for s3 is always the recently popped number from the stack, because if we encounter any entry smaller than the current candidate, the function would already have returned.
*/
bool find132pattern(vector<int>& nums) {
    int s3 = INT_MIN;
    stack<int> st;
    for( int i = nums.size()-1; i >= 0; i -- ){
        if( nums[i] < s3 ) return true;
        else while( !st.empty() && nums[i] > st.top() ){ 
          s3 = st.top(); st.pop(); 
        }
        st.push(nums[i]);
    }
    return false;
}
