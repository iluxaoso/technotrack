#pragma once
#include "includes.h"

class Array
{
	int counter_;
	int capacity_;
	double *data_;
	bool alloc_;

	Array();
	explicit Array(int size);
	explicit Array(Array& data);
	~Array();
	bool ArrayOK();

	void Dump(const std::string fName);
	void resize(int size);

};