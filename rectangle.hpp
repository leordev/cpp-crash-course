#include <iostream>  // for std::cout, std::cin

// this is a simple guard notation that prevents the header
// file to be rewritten multiple times on the compilation
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

// a well-known separation should be class definition on
// header file and class implementation on cpp file
class Rectangle {

// set public accessors -- never forget this because by default
// everything is private in a class
public:

    // empty constructor, initialize members with default vals
    Rectangle(){}; // or Rectangle() = default;

    // constructor with parameters
    Rectangle(int width, int height);

    // in c++ we don't need to handle anything about the
    // resources releases... but if you want to do anything
    // special when the object is destroyed, the destructor
    // method is exactly like a constructor with a tilde prefix
    ~Rectangle() {
        std::cout << "\nReleasing rectangle " << _width << "x" << _height;
    }

    // public accessors
    int Width()  const;
    int Height() const;

    // methods that don't change data members
    // flagged with const
    int Area() const;

    // it changes data members, so not `const`
    void Scale(int factor);

private:

    // member data, convention to name it with
    // underscore + lowercase, ex: _width, _my_width, _myWidth
    // never do _Upper, because of standard cpp naming conflicts
    int _width{1};
    int _height{1};

};

// inline functions are small functions that should
// stay in the header file (usually less than 10 lines)

// constructor with parameters implementation
inline Rectangle::Rectangle(int width, int height)
    : _width{width}, _height{height} {}

inline int Rectangle::Width()  const  { return _width; }
inline int Rectangle::Height() const  { return _height; }


#endif
