#pragma once

#include <memory>

//スレッドセーフであることを保証したいが、
//どうロックかければいいのか見当つかん
//ミューテックスロックぅ！と言いたいところだけど
//いや、そう言っておこう。
//ってことは、参照を渡すじゃない。
//それを保持されるととても困るね。
//まぁまだ考える領域ではないね。


template <class T>
class Singleton
{
public:
	static T& Instance()
	{
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
