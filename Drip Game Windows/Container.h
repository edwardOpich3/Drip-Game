#pragma once
template <class T>
class Container
{
private:

	T* data = nullptr;

public:

	int count;
	int capacity;

	void push(T object)
	{
		if (count >= capacity)
		{
			resize();
		}
		data[count] = object;
		count++;
	};

	void remove(int index)
	{
		for (int i = index; i < count - 1; i++)
		{
			data[i] = data[i + 1];
		}
		count--;
	};

	void clear()
	{
		count = 0;
	};

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

	T& operator[](int index)
	{
		if (index < count && index > -1)
		{
			return data[index];
		}
		else
		{
			return T();
		}
	};

	const T& operator[](int index) const
	{
		if (index < count && index > -1)
		{
			return data[index];
		}
		else
		{
			return T();
		}
	};

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
		*this = other;
	};

	~Container()
	{
		delete[] data;
		data = nullptr;
	};
};

