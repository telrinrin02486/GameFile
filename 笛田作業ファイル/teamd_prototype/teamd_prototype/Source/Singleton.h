#pragma once

#include <memory>

//スレッドセーフなシングルトン


template <class T>
class Singleton
{
public:
	static T& Instance()
	{
		//↓のT::CreateInstance()は派生側を呼び出してる
		//これは、CreateInstanceを派生側で書き換えたい時があるからよ。
		//typenameはそういう型を派生クラスが持ってるよって話。
		//あくまで派生側を呼び出す仕組み。
		static typename T::singleton_pointer_type instance(T::CreateInstance());
		return Reference(instance);
	}
private:
	typedef std::unique_ptr<T> singleton_pointer_type;

	inline static T* CreateInstance() { return new T(); }
	inline static T& Reference(const singleton_pointer_type& ptr) { return* ptr; }

protected:
	Singleton() {}
	virtual ~Singleton() {}
private:
	Singleton(const Singleton &) = delete;
	Singleton& operator=(const Singleton &) = delete;
	Singleton(Singleton &&) = delete;
	Singleton& operator=(Singleton &&) = delete;
};
