#pragma once

#include <memory>

//�X���b�h�Z�[�t�ȃV���O���g��


template <class T>
class Singleton
{
public:
	static T& Instance()
	{
		//����T::CreateInstance()�͔h�������Ăяo���Ă�
		//����́ACreateInstance��h�����ŏ������������������邩���B
		//typename�͂��������^��h���N���X�������Ă����Ęb�B
		//�����܂Ŕh�������Ăяo���d�g�݁B
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
