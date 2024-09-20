/********************************
The following mySwap works like the swap function in the library.

Your name: JJ Hoffmann
Your programmer number: 16
Hours spent: .25
Any difficulties?: No
********************************/

/**
 * Prints the elements of an array.
 * 
 * This function outputs all elements of an integer array, separated by spaces, followed by a newline.
 * 
 * @param ar[] The array to be printed.
 * @param s The size of the array.
 *
 */
template <class T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
