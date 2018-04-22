/**
 * #include is a prepocessor operator that works
 * literally like a "smart" copy and paste
 */
#include <iostream>  // for std::cout, std::cin
#include <string>    // for std::string, std::getline
#include <random>    // for std::random_device, std::mt19937
#include <algorithm> // for std::sort, std::uniform_int_distribution
#include <vector>    // for std::vector
#include <fstream>   // for std::ifstream
#include "rectangle.hpp" // for use of the Rectangle class

// if you dont want to keep writing std:: every time
// you need to access the std library, just uncomment
// below. it can cause naming conflict therefore not
// recommended for production usage
//using namespace std;

/**
 * Initializations:
 * int a{}; // brace-init, scalar types will init with 0
 * int a = 0;
 *
 * int a{5};
 * int a = 5;
 *
 * never ever use this initialization:
 * int a; // lead to crazy numbers, ??garbage from memory??
 *
 */
void ex_basic_calc() {
    std::cout << "value of a\n";
    int a{};
    std::cin >> a;

    std::cout << "\nvalue of b\n";
    int b{};
    std::cin >> b;

    std::cout << "\ncalculations";
    std::cout << "\nsum: a + b >>> " << (a + b);
    std::cout << "\nsubtraction: a - b >>> " << (a - b);
    std::cout << "\nmultiplication: a * b >>> " << (a * b);
    std::cout << "\ndivision: a / b >>> " << (a / b);
    std::cout << "\nrest: a % b >>> " << (a % b);
}

void ex_string() {
    std::cout << "Tell me a phrase: ";
    std::string phrase{};
    getline(std::cin, phrase);

    int separators = phrase.length() + 4;
    std::string separator(separators, '#');
    std::string second_line{"\n# " + phrase + " #\n"};

    std::cout << separator;
    std::cout << second_line;
    std::cout << separator;
}

void gen_random_numbers() {
    std::random_device seed{};
    std::mt19937 engine{seed()};
    std::uniform_int_distribution<> dis{1, 10};

    int x{ dis(engine) };

    std::cout << x << '\n';
}

/*
 * type x -> value copy (memory waste?)
 * type& x -> reference
 * type const& x -> constant reference, safe: you can't modify
 */
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void ex_swap() {
    int a = 5;
    int b = 10;

    std::cout << "\na value before swap >>> " << (a);
    std::cout << "\nb value before swap >>> " << (b);
    swap(a, b);
    std::cout << "\na value after swap >>> " << (a);
    std::cout << "\nb value after swap >>> " << (b);

}

void ex_vectors() {

    // initializes vector with the zero-index value of 3
    std::vector<int> my_num{3};

    // initializes a vector of 3 positions with
    // each positon having a int = 0
    std::vector<int> zero_nums(3);

    std::cout << "\nmy_num size >>> " << my_num.size();
    std::cout << "\nzero_nums size >>> " << zero_nums.size();

    std::cout << "\nmy_nums is >>> " << my_num[0];

}

void ex_read_file() {
    // open file
    std::ifstream file{"CMakeLists.txt"};

    // read lines from the file to a vector
    std::vector<std::string> lines{};
    std::string line{};
    while (std::getline(file, line)) {
        // push_back - wtf? appends to the end of the vector
        // like .add, .append, .push in another languages LOL
        lines.push_back(line);
    }

    // iterators types, but you will want to simply use `auto`
    // std::vector<int>::iterator it;
    // std::vector<int>::const_iterator const_it;
    auto it_begin = begin(lines);
    auto it_end = end(lines);
    std::sort(it_begin, it_end);

    // print file lines
    // again, as in the swap function, always prefer to use
    // references (&) to eliminate expensive copies...
    // for basic types like int is cheap, but imagine complex classes as images...
    // auto const& - if you want to keep it safe with the same value
    // auto & - if you want to modify elements values
    for(std::string const& line : lines) {
        std::cout << line << std::endl;
    }

}

void print_rectangle_info(Rectangle const& r) {
    std::cout << "\n\nRectangle of ";
    std::cout << r.Width() << "x" << r.Height();
    std::cout << " area is " << r.Area();
}

void ex_rectangle() {
    Rectangle r_default{};
    print_rectangle_info(r_default);

    Rectangle r{3,4};
    print_rectangle_info(r);

    std::cout << "\n\n>>>> Scaling by 5...";
    r.Scale(5);
    print_rectangle_info(r);
}

int main() {

    // uncomment each function to play with examples :)
    //ex_basic_calc();
    //ex_string();
    //gen_random_numbers();
    //ex_swap();
    //ex_vectors();
    //ex_read_file();
    ex_rectangle();

    return 0;
}
