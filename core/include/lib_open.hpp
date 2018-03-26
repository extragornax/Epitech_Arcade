//
// EPITECH PROJECT, 2018
// Arcade
// File description:
// Lib loader header
//

#ifndef LIB_LOADER_HPP_
	#define LIB_LOADER_HPP_

#include <iostream>
#include <memory>

class Dlloader {
public:
	Dlloader(std::string path);
	~Dlloader();
	void seLib(std::string path);
	std::unique_ptr<T> getInstance(std::string entryPoint);
private:
	std::string _path;
	void *_handler;
	void *_open;
};

#endif /* LIB_LOADER_HPP_ */