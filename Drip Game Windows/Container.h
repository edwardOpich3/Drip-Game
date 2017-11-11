#pragma once
#include <stdexcept>
template <class T>
class Container
{
private:

	T* data = nullptr;	// The structure that will hold our data

public:

	int count;			// How many items are in our container
	int capacity;		// How many items our container can hold without resizing

	// Pushes a new object to the top of the container, resizing if necessary
	void push(T object)
	{
		if (count >= capacity)
		{
			resize();
		}
		data[count] = object;
		count++;
	};

	// Removes the object located at index.
	void remove(int index)
	{
		for (int i = index; i < count - 1; i++)
		{
			data[i] = data[i + 1];
		}
		count--;
	};

	// Clears the container. WARNING: Doesn't delete contents due to ambiguity over what they are! Do it manually first!
	void clear()
	{
		count = 0;
	};

	// Doubles the container's capacity.
	void resize()
	{
		T* temp = new T[capacity * 2];
		for (int i = 0; i < count; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = nullptr;
		data = temp;
		capacity *= 2;
	};

	// Access the data in the container. Used for writing.
	T& operator[](int index)
	{
		if (index < count && index > -1)
		{
			return data[index];
		}
		else
		{
			throw(std::out_of_range("Index is out of bounds!"));
		}
	};

	// Access the data in the container. Used for reading.
	const T& operator[](int index) const
	{
		if (index < count && index > -1)
		{
			return data[index];
		}
		else
		{
			throw(std::out_of_range("Index is out of bounds!"));
		}
	};

	// Copy assignment operator
	Container<T> operator=(const Container<T> &other)
	{
		if (data)
		{
			delete[] data;
			data = nullptr;
		}

		data = new T[other.capacity];
		count = 0;
		capacity = 1;
		for (int i = 0; i < other.count; i++)
		{
			push(other[i]);
		}

		return *this;
	};

	Container()
	{
		count = 0;
		capacity = 1;
		data = new T[capacity];
	};

	Container(const Container<T> &other)
	{
		data = new T[other.capacity];
		count = 0;
		capacity = 1;
		for (int i = 0; i < other.count; i++)
		{
			push(other[i]);
		}
	};

	~Container()
	{
		delete[] data;
		data = nullptr;
	};
};

