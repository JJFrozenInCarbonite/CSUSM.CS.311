/********************************
The following mySwap works like the swap function in the library.

Your name: Jj Hoffmann
Your programmer number: 16
Hours spent: .25
Any difficulties?: No
********************************/

template <class T>
void mySwap(T& a, T& b)
{
    T temp = a;
    a = b;
    b = temp;
}
