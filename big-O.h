/************************************************************************
CS311 Kazumi Slott

Your name: JJ Hoffmann
Your program number: 16
Hours spent:
Describe any difficulties here: 

Experiment:                             (in milliseconds)
                                        AlgoA       AlgoB      AlgoC
------------------------------------------------------------------------
Actual Runtimes with 1000 elements   |           |           |
(Record the 3 runtimes obtained      |           |           |
when you run big-O_file.cpp)         |           |           |
------------------------------------------------------------------------
Expected Runtimes with 2000 elements |           |           |
(Guess how long each algo would take |           |           |
before you run big-O_file.cpp)       |           |           |
------------------------------------------------------------------------
Actual Runtimes with 2000 elements   |           |           |
------------------------------------------------------------------------
Expected Runtimes with 3000 elements |           |           |
------------------------------------------------------------------------
Actual Runtimes with 3000 elements   |           |           |
------------------------------------------------------------------------

<Question> Did the actual runtimes for 2000 and 3000 match what you expected?
Please explain.
<Your answer here>

************************************************************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runtime complexity of this algorithm? O(n^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
int algoA(const int a[], int sz)//Don't change the function headers
{   
    // Initialize max_sum to 0
    int max_sum = 0;

    // Check to make sure the array has elements
    if (sz == 0) return 0;

    // i == length of subarray
    for (int i = 1; i <= sz; i++) {

        // j == starting index of subarray
        for (int j = 0; j <= sz - i; j++) {
            int sum = 0;
            
            // k == index of subarray within array a[]
            for (int k = j; k < j + i; k++) {
                sum += a[k]; // sum of subarray
            }

            // Set the max_sum to the greater of the current sum or the max_sum 
            max_sum = (sum > max_sum) ? sum : max_sum;
        }
    }
}

//What is the runtime complexity of this algorithm? O(????)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
    // Initialize max_sum to 0
    int max_sum = 0;

    // Check to make sure the array has elements
    if (sz == 0) return 0;

    // i == starting position
    for (int i = 0; i < sz; i++) {

        // Initialize sum to 0 on each iteration of i
        int sum = 0;

        // j == len of subarray
        for (int j = i; j < sz; j++) {

            // Add every j element to the array
            sum += a[j];

             // Set the max_sum to the greater of the current sum or the max_sum 
            max_sum = (sum > max_sum) ? sum : max_sum;
        }
    }
}

//What is the runtime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{
    // Initialize max_sum to 0
    int max_sum = 0;

    // Check to make sure the array has elements
    if (sz == 0) return 0;

    // Initialize the sum to the value of the first array element 
    int sum = a[0];

    // Loop through the array
    for (int i = 0; i < sz; i++) {

        // If the current element is greater than the sum plus the current element, set the sum to the current element
        if (a[i] > sum + a[i]) 
            sum = a[i];
        else 
        // Otherwise, add the current element to the sum
            sum = sum + a[i];
    
        // Set the max_sum to the greater of the current sum or the max_sum 
        max_sum = (sum > max_sum) ? sum : max_sum;
    }

    return max_sum;

}