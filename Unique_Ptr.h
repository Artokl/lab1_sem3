#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H
#include <iostream>
#include <cstddef>

#include "Swap.h"
#include "Additional_Structures.h"
#include "Deleters.h"
#include "Move.h"

template<typename T, typename Deleter = DefaultDelete<T>>
class unique_ptr
{
	using U = remove_extent_t<T>;
private:
	U* ptr;
	Deleter my_delete = Deleter();
	U* get() const
	{
		return ptr;
	}
	friend bool operator ==(const unique_ptr& other1, const unique_ptr& other2)
	{
		return other1.get() == other2.get();
	}
	friend bool operator !=(const unique_ptr& other1, const unique_ptr& other2)
	{
		return !(other1 == other2);
	}
	friend bool operator == (const unique_ptr& other, std::nullptr_t)
	{
		return other.get() == nullptr;
	}

	friend bool operator ==(std::nullptr_t, const unique_ptr& other)
	{
		return other.get() == nullptr;
	}
	friend bool operator !=(const unique_ptr& other, std::nullptr_t)
	{
		return !(other == nullptr);
	}
	friend bool operator !=(std::nullptr_t, const unique_ptr& other)
	{
		return !(other == nullptr);
	}
public:
	inline void swap(unique_ptr& other) noexcept {
		my_swap(ptr, other.ptr);
	}
	//конструкторы+деструктор
	unique_ptr() :ptr(nullptr) {}
	explicit unique_ptr(std::nullptr_t) :unique_ptr() {}
	explicit unique_ptr(U* other) :ptr(move(other)) {}
	unique_ptr(const unique_ptr& other) = delete;
	unique_ptr(unique_ptr&& other) noexcept :ptr(other.ptr)
	{
		other.ptr = nullptr;
	}
	virtual ~unique_ptr()
	{
		my_delete(ptr);
	}

	//методы
	bool isNull() const
	{
		return ptr == nullptr;
	}
	void reset()
	{
		unique_ptr buffer = unique_ptr();
		swap(buffer);
	}
	U* release()
	{
		U* buffer = ptr;
		ptr = nullptr;
		return buffer;
	}
	
	//операторы
	U& operator*() const
	{
		return *ptr;
	}
	U* operator->() const
	{
		return ptr;
	}
	template<typename K = T, typename = enable_if_t<typename is_array<K>::value>>
	U& operator[](int index) const
	{
		return ptr[index];
	}
	unique_ptr& operator =(const unique_ptr& other) = delete;
	unique_ptr& operator = (std::nullptr_t)
	{
		unique_ptr buffer;
		swap(buffer);
		return *this;
	}
	unique_ptr& operator =(unique_ptr&& other) noexcept {
		unique_ptr buffer(move(other));
		swap(buffer);
		return *this;
	}
};

template<typename T, class Deleter = DefaultDelete<T>, typename... Args,
		 typename = std::enable_if_t<!std::is_array_v<T>>>
unique_ptr<T, Deleter> make_unique(Args&& ... args) {
	return unique_ptr<T, Deleter>(new T(std::forward<Args>(args)...));
}

template<typename T, class Deleter = DefaultDelete<std::remove_extent_t<T>>, typename... Args>
unique_ptr<T, Deleter> make_unique(const size_t size, Args&& ... args) {
	using BaseType = std::remove_extent_t<T>;
	static_assert(!std::is_same_v<BaseType, void>, "Cannot create array of void.");
	BaseType* ptr = new BaseType[size];
	for (size_t i = 0; i < size; ++i) {
		ptr[i] = BaseType(std::forward<Args>(args)...);
	}
	return unique_ptr<T, Deleter>(ptr);
}

template<typename T, class Deleter = DefaultDelete<std::remove_extent_t<T>>>
unique_ptr<T, Deleter> make_unique(const size_t size) {
	using BaseType = std::remove_extent_t<T>;
	static_assert(!std::is_same_v<BaseType, void>, "Cannot create array of void.");
	BaseType* ptr = new BaseType[size]();
	return unique_ptr<T, Deleter>(ptr);
}



#endif //UNIQUE_PTR_H
