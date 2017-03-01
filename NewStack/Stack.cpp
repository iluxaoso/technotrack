#include "Stack.h"

Stack::Stack(size_t size)
{
	assert(this);

	data_ = (type*)calloc(size, sizeof(type));
	for (int i = 0; i < size; i++)
	{
		data_[i] = POISON_DATA;
	}
	size_ = size;
	count_ = 0;
}

Stack::~Stack()
{
	assert(this);

	size_ = POISON_SIZE;
	count_ = POISON_COUNT;

	free(data_);
	data_ = NULL;
}

int Stack::size()
{
	return size_;
}

bool Stack::full()
{
	return count_ >= size_ ? true : false;
}

bool Stack::empty()
{
	return count_ <= 0 ? true : false;
}

double Stack::push(type value)
{
	assert(this);

	if (full())
	{
		return ERROR;
	}

	data_[count_++] = value;

	return 0;
}

int Stack::pop()
{
	assert(this);

	if (empty())
	{
		return POISON_DATA;
	}

	type ret = data_[count_--];
	data_[count_] = POISON_DATA;

	return ret;
}

bool Stack::ok()
{
	return (this != NULL) &&
		   data_ &&
		   (count_ >= 0) &&
		   size_            &&
		   count_ <= size_;
}

int Stack::dump(const std::string fName)
{
	std::string okText;
	if (ok())
	{
		okText = "ok";
	}
	else
	{
		okText = "no";
		assert(this);
		assert(data_);
	}

	std::ofstream dump("stack.dump", std::ofstream::app);

	dump << "Stack |" << fName << " | (" << okText << ") [" << &(*this) << "]\n";
	dump << "{\n\tdata_[" << size_ << "] = [" << data_ << "]\n";

	dump << "\t{\n";
	for (int i = 0; i < size_; i++)
	{
		if (i < count_)
		{
			dump << "\t\t[" << i << "] = " << data_[i] << "\n";
		}
		else
		{
			dump << "\t\t[" << i << "] = " << data_[i] << "POISON_DATA!\n";
		}
	}

	dump << "\t}\n\tcount_ = " << count_ << "\n";
	dump << "\tsize_ = " << size_ << "}\n";

	dump.close();

	return 0;
}