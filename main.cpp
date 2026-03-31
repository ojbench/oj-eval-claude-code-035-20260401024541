#include "MyString.hpp"
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    // Test default constructor
    MyString s1;
    assert(s1.size() == 0);
    assert(s1.capacity() == 15);

    // Test const char* constructor with SSO
    MyString s2("hello");
    assert(s2.size() == 5);
    assert(s2.capacity() == 15);

    // Test const char* constructor without SSO
    MyString s3("this is a long string");
    assert(s3.size() == 21);
    assert(s3.capacity() >= 21);

    // Test copy constructor
    MyString s4(s2);
    assert(s4.size() == 5);

    // Test operator+
    MyString s5 = s2 + s2;
    assert(s5.size() == 10);

    // Test append
    MyString s6("test");
    s6.append(" append");
    assert(s6.size() == 11);

    // Test operator[]
    MyString s7("abc");
    assert(s7[0] == 'a');
    assert(s7[1] == 'b');
    assert(s7[2] == 'c');

    // Test at
    try {
        s7.at(10);
        assert(false); // Should not reach here
    } catch (const out_of_range& e) {
        // Expected
    }

    // Test reserve
    MyString s8("short");
    s8.reserve(100);
    assert(s8.capacity() >= 100);
    assert(s8.size() == 5);

    // Test resize
    MyString s9("test");
    s9.resize(10);
    assert(s9.size() == 10);

    // Test iterators
    MyString s10("hello");
    int count = 0;
    for (auto it = s10.begin(); it != s10.end(); ++it) {
        count++;
    }
    assert(count == 5);

    // Test const iterators
    const MyString s11("world");
    count = 0;
    for (auto it = s11.cbegin(); it != s11.cend(); ++it) {
        count++;
    }
    assert(count == 5);

    cout << "All tests passed!" << endl;

    return 0;
}
