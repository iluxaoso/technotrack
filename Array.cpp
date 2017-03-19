#include "Array.h"

Array::Array()
{
	counter_ = 0;
	capacity_ = 0;
	data_ = nullptr;
	alloc_ = false;
}

Array::Array(int size)
{
	counter_ = 0;
	capacity_ = size;
	data_ = new double[counter_];
	alloc_ = true;
}

Array::Array(Array& data)
{
	assert(&data);

	counter_ = 0;
	capacity_ = data.capacity_;
	data_ = new double[capacity_];
	alloc_ = true;
}

Array::~Array()
{
	if (alloc_ = true)
	{
		delete[] data_;
		counter_ = COUNTER_POISON;
		capacity_ = CAPACITY_POISON;
		data_ = nullptr;
		alloc_ = false;
	}

	std::cout << "Array destructed!\n";
}

void Array::resize(int size)
{
	if (size > capacity_)
	{
		data_ = (double *)realloc(data_, sizeof(data_) * size);
		capacity_ = size;
		counter_ = 0;
		alloc_ = true;
	}
}

bool Array::ArrayOK()
{
	if (capacity_ > 0)
	{
		return data_ != nullptr     &&
			   counter_ < capacity_ &&
			   alloc_ == true;
	}
	else
	{
		return data_ == nullptr &&
			   !capacity_       &&
			   !counter_        &&
			   alloc_ == false;
	}
}

void Array::Dump(const std::string fName)
{
	std::string okText;
	if (ArrayOK())
	{
		okText = "good";
	}
	else
	{
		okText = "bad";
		assert(this);
		assert(data_);
	}

	std::ofstream dump("array.dump", std::ofstream::app);

	dump << "Array |" << fName << " | (" << okText << ") [" << &(*this) << "]\n";
	dump << "{\n\tdata_[" << capacity_ << "] = [" << data_ << "]\n";

	dump << "\t{\n";
	for (int i = 0; i < capacity_; i++)
	{
		if (i < counter_)
		{
			dump << "\t\t[" << i << "] = " << data_[i] << "\n";
		}
		else
		{
			dump << "\t\t[" << i << "] = " << data_[i] << "POISON_DATA!\n";
		}
	}

	dump << "\t}\n\tcount_ = " << counter_ << "\n";
	dump << "\tsize_ = " << capacity_ << "}\n";

	dump.close();
}