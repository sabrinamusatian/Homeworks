#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s, s1;
    cout << "Print the first line" << endl;
    getline(cin, s);
    cout << "Print the second line" << endl;
    getline(cin, s1);
    int number = 0; // counter for number of substrings
    for (int i = 0; i < s.length() - s1.length() + 1; i++)
    {
        if (s[i] == s1[0])
        {
            if (s.substr(i, s1.length()) == s1)
            {
                number++;
            }
        }
    }
    cout << "Number of substrings is " << number;
    return 0;
}
