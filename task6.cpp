#include <iostream>
#include <string>
#include <ctype.h>

using namespace std;

int main()
{
    string s;
    cout << "Print the whole line" << endl;
    getline(cin, s); // read the whole line with spaces
    char c[s.length()]; // making an array for line without spaces

    int m = 0; // counter of elements;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != ' '){
            c[m] = toupper(s[i]);
            m++;
        }
    }
    for (int i = 0; i < m / 2; i++)
    {
        if (c[i] != c[m - 1 - i]){
            cout << "Line is not a palindrome";
            return 0;
        }
    }
    cout << "Line is a palindrome";
    return 0;
}
