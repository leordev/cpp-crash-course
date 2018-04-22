/**
 * #include is a preprocessor operator that works
 * literally like a "smart" copy and paste
 */
#include <iostream>  // for std::cout, std::cin
#include <string>    // for std::string, std::getline
#include <random>    // for std::random_device, std::mt19937
#include <algorithm> // for std::sort, std::uniform_int_distribution
#include <vector>    // for std::vector
#include <map>       // for std::map
#include <fstream>   // for std::ifstream
#include <memory>    // for std::make_unique
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

template <typename T>
constexpr T maxValue = T(1000);

template <>
constexpr double maxValue<double> = 2000;

template <>
constexpr double maxValue<std::string> = 5000;

void ex_templates() {
    std::cout << " maxValue<int>          : " << maxValue<int> << "\n";
    std::cout << " maxValue<double>       : " << maxValue<double> << "\n";
    std::cout << " maxValue<std::string>  : " << maxValue<std::string> << "\n";
}

// raw pointers are very dangerous and there's no reason to utilize
// it on C++14... if you really need to use it YOU MUST NOT FORGET
// TO DELETE IT!!! the declaration syntax is: type * p_name
// the destruction syntax is delete p_name; followed by
// p_name = nullptr; as a good convention
void ex_raw_pointer() {
    Rectangle * p_rec = new Rectangle(10, 15);
    p_rec->Scale(2);

    // try to comment below and you will
    // find out that the rectangle destructor
    // will never be called
    delete p_rec;
    p_rec = nullptr;
}

// for smart pointers you don't need to worry about the destruction
// from c++14 use it and be happy :)
// no matter what the Rectangle will run destructor.
void ex_smart_pointer() {
    std::unique_ptr<Rectangle> p_rec = std::make_unique<Rectangle>(10,15);
    p_rec->Scale(2);
}

void ex_lambdas() {
    std::vector<std::string> names{"Leo", "John", "Ana", "Robert", "Lucca", "Martin"};


    // lambdas are anonymous functions declared by the syntax []
    // in the below example I'm changing the default sort behavior
    // to order by the size of a string instead of alphabetical
    std::sort(begin(names), end(names),
        [](std::string const& a, std::string const& b) {
            return a.length() < b.length();
        }
    );

    for(std::string name : names) {
        std::cout << "\nname: " << name;
    }

    // if you need to use pointer inside lambdas you must
    // use the std::move on the lambda init-capture statement
    auto p_rec = std::make_unique<Rectangle>(10,15);

    std::cout << "\n\nOutside and before the move rectangle area: " << p_rec->Area() << '\n';

    auto lambda = [ptr = std::move(p_rec)](){
        std::cout << "\nInside the lambda rectangle area: " << ptr->Area() << '\n';
    };

    lambda();
}

// a iterator is a pointer. if you want to change a value from that pointer
// you must use * on the pointer name... otherwise you would be trying to
// change the pointer, not the value inside
void ex_iterators() {
    std::vector<std::string> names{ "Leo", "Ana", "Flavia", "Scott", "John"};

    // find and rename Flavia for ***
    // if it found any value, the iterator will never be
    // the same pointer of the end iterator... remember, end
    // iterator always points to the last index of the vector + 1
    if (const auto it = find(begin(names), end(names), "Flavia");
        it != end(names)) {
        *it = "***";
    }

    // as you saw above, with c++17 we have a new feature that
    // we can declare variables inside it and limit the scope
    // of the variable into it so we cant access it variable
    // here - try to uncomment below code
    // std::cout << *it;

    for(auto n : names) {
        std::cout << "\n Name: " << n;
    }
}

void ex_map_with_structured_bindings() {
    // this is a regular map structure like any other language
    // nothing new here... unless `get` method is `.at`
    std::map<std::string, std::string> portugueseDictionary{
            {"casa", "gatto"},
            {"gato", "cat"},
            {"macarrao", "pasta"},
            {"lasanha", "lasagna"}
    };
    std::cout << "The portuguese word 'macarrao' means ";
    std::cout << portugueseDictionary.at("macarrao");

    // this is an example of Structured Binding
    // the result of a insert is a pair structure
    // so we can use brackets to get the first and second
    // value and name it the way we want. it's very like
    // Pattern Matching from Functional Programming Languages!
    // we use it a lot in elixir and elm :D
    auto [it, success] = portugueseDictionary.insert({"cadeira", "chair"});

    if(success) {
        std::cout << "\n\nThe word cadeira was added successfully!";
    } else {
        auto const& [key, value] = *it;
        std::cout << "\n\nThe word " << key << " already exists and means " << value;
    }

    for (auto const& [portuguese, english] : portugueseDictionary) {
        std::cout << '\n' << portuguese << ": " << english;
    }
}

int main() {

    // uncomment each function to play with examples :)
    // ex_basic_calc();
    // ex_string();
    // gen_random_numbers();
    // ex_swap();
    // ex_vectors();
    // ex_read_file();
    // ex_rectangle();
    // ex_templates();
    // ex_raw_pointer();
    // ex_smart_pointer();
    // ex_lambdas();
    // ex_iterators();
    ex_map_with_structured_bindings();

    return 0;
}
