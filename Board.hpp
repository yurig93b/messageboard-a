//
// Created by Yuri Grigorian on 24/03/2021.
//

#ifndef MESSAGEBOARD_A_BOARD_HPP
#define MESSAGEBOARD_A_BOARD_HPP

#include <iostream>
#include "Direction.hpp"

namespace ariel{

    class Board{
        const std::string test = "test";
        const std::string DEFAULT_EMPTY_CHAR = "_";

        public:
            void post(const unsigned int &row, const unsigned int &column,const Direction &dir, const std::string &msg);
            const std::string& read(const unsigned int &row,  const unsigned int &column, const Direction &dir, const unsigned int &len);
            void show();
            void reset();
    };
}

#endif //MESSAGEBOARD_A_BOARD_HPP
