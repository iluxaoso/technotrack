#pragma once

//!includes
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

typedef int type;

class Stack
{
private:
	size_t size_;
	int count_;
	type* data_;

	const static int    ERROR        = -1;
	const static int    SIZE         =  255;
	const static int    POISON_DATA  = -666;
	const static int    POISON_SIZE  = -666;
	const static int    POISON_COUNT = -666;

	bool ok();
	int dump(const std::string fName);

public:
	explicit Stack(size_t size = SIZE);
	~Stack();

	int size();
	bool full();
	bool empty();

	double push(type value);
	int pop();
};