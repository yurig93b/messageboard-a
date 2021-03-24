

#include "doctest.h"
#include "Board.hpp"
#include <limits>
#include <stdexcept>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <regex>


// Yanked from Stackoverflow
template<typename Char, typename Traits, typename Allocator>
std::basic_string<Char, Traits, Allocator> operator *
        (const std::basic_string<Char, Traits, Allocator> s, size_t n)
{
    std::basic_string<Char, Traits, Allocator> tmp = s;
    for (size_t i = 0; i < n; ++i)
    {
        tmp += s;
    }
    return tmp;
}

template<typename Char, typename Traits, typename Allocator>
std::basic_string<Char, Traits, Allocator> operator *
        (size_t n, const std::basic_string<Char, Traits, Allocator>& s)
{
    return s * n;
}

TEST_CASE("Bad I/O"){
    ariel::Board b;
    unsigned int max_unsigned_int_size = std::numeric_limits<unsigned int>::max();

    // Empty str
    b.reset();
    b.post(0,0, ariel::Direction::Horizontal, "");
    CHECK("_" == b.read(0, 0, ariel::Direction::Horizontal, 1));

    b.post(0,0, ariel::Direction::Vertical, "");
    CHECK("_" == b.read(0, 0, ariel::Direction::Vertical, 1));

    // Read 0 len
    CHECK_THROWS(b.read(0, 0, ariel::Direction::Vertical, 0));
    CHECK_THROWS(b.read(0, 0, ariel::Direction::Horizontal, 0));

    // Out of bound of unsigned int
    const unsigned int targetIdx = max_unsigned_int_size - 5;
    const std::string targetText  = "Much longer than 5 chars :)";
    CHECK_THROWS(b.post(targetIdx, 0, ariel::Direction::Vertical, targetText));
    CHECK_THROWS(b.post(0, targetIdx, ariel::Direction::Horizontal, targetText));
    CHECK_THROWS(b.post(targetIdx, targetIdx, ariel::Direction::Horizontal, targetText));
}
TEST_CASE("Good I/O")
{
    ariel::Board b;

    // Empty read
    b.reset();
    CHECK("____" == b.read(0, 0, ariel::Direction::Horizontal, 4));
    CHECK("____" == b.read(0, 0, ariel::Direction::Vertical, 4));

    // Horizontal input
    b.reset();
    b.post(0, 0, ariel::Direction::Horizontal, "yuri");
    CHECK("yuri" == b.read(0, 0, ariel::Direction::Horizontal, 4));
    CHECK("yur" == b.read(0, 0, ariel::Direction::Horizontal, 3));
    CHECK("y" == b.read(0, 0, ariel::Direction::Horizontal, 1));
    CHECK("y___" == b.read(0, 0, ariel::Direction::Vertical, 4));

    // Vertical input
    b.reset();
    b.post(0, 0, ariel::Direction::Vertical, "yuri");
    CHECK("yuri" == b.read(0, 0, ariel::Direction::Vertical, 4));
    CHECK("yur" == b.read(0, 0, ariel::Direction::Vertical, 3));
    CHECK("y" == b.read(0, 0, ariel::Direction::Vertical, 1));
    CHECK("y___" == b.read(0, 0, ariel::Direction::Horizontal, 4));

    // Check msg override
    b.reset();
    b.post(0, 0, ariel::Direction::Vertical, "ball");
    b.post(0, 0, ariel::Direction::Horizontal, "yuri");
    CHECK("yall" == b.read(0, 0, ariel::Direction::Vertical, 4));

    // Really long good msg horizontal
    std::string testStr = "t";
    unsigned int max_unsigned_int_size = std::numeric_limits<unsigned int>::max();
    testStr = testStr * (max_unsigned_int_size/1000);

    b.post(0, 0, ariel::Direction::Vertical, testStr);
    b.post(0, 0, ariel::Direction::Horizontal, testStr);
    CHECK(testStr == b.read(0, 0, ariel::Direction::Vertical, max_unsigned_int_size));
    CHECK(testStr == b.read(0, 0, ariel::Direction::Horizontal, max_unsigned_int_size));

    // Check bondaries are kept horizontal
    b.reset();
    b.post(0, 0, ariel::Direction::Horizontal, "ab");
    b.post(1, 0, ariel::Direction::Vertical, "cd");
    b.post(0, 2, ariel::Direction::Horizontal, "ef");
    b.post(3, 0, ariel::Direction::Vertical, "gh");
    CHECK("ab" == b.read(0, 0, ariel::Direction::Horizontal, 2));
    CHECK("cd" == b.read(1, 0, ariel::Direction::Vertical, 2));
    CHECK("ef" == b.read(0, 2, ariel::Direction::Horizontal, 2));
    CHECK("gh" == b.read(3, 0, ariel::Direction::Vertical, 2));
}