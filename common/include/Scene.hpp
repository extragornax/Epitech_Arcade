//
// EPITECH PROJECT, 2018
// cpp_arcade
// File description:
// Scene class header
//

#pragma once

# include <ctime>
# include "Board.hpp"

class Scene {
    public:
	Scene();
	~Scene();

    public:
        Board &getBoardGame();
        Board &getBoardFooter();
        std::string &getTitle();
        std::clock_t &getClock();
        size_t &getScore;
    
    private:
        Board _boardGame;
        Board _boardFooter;
        std::string _title;
        std::clock_t _clock;
        size_t _score;
};
