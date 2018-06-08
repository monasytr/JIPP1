#pragma once

#include <cstddef>

template <typename T>
class Vector {
private:
	size_t dimensions;
	T* data;

public:
	Vector<T>(size_t dimensions) :
		dimensions(dimensions), data(new T[dimensions]()) {}
	virtual ~Vector<T>() {
		if (data) delete[] data;
	}

	size_t size() const {
		return dimensions;
	}

	T& at(size_t index) {
		return data[index];
	}

	const T& at(size_t index) const {
		return data[index];
	}
};

template<typename T>
Vector<T> add(const Vector<T>& a, const Vector<T>& b) {
	Vector<T> c(a.size());
	for (size_t i = 0; i < a.size(); i++) {
		c[i] = a[i] + b[i];
	}
	return c;
}

template<typename T>
bool equals(const Vector<T>& a, const Vector<T>& b) {
	if (&a == &b) return true;
	if (a.size() != b.size())
		return false;
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) return false;
	}
	return true;
}