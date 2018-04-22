#include "rectangle.hpp"

// these implementations should be inline functions on
// header file... but they are here only for a demonstration

int Rectangle::Area() const {
    return _width * _height;
}

// it changes data members, so not `const`
void Rectangle::Scale(int factor) {
    _width *= factor;
    _height *= factor;
}
