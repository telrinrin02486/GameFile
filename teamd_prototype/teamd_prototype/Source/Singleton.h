#pragma once

#include <memory>

//�X���b�h�Z�[�t�ł��邱�Ƃ�ۏ؂��������A
//�ǂ����b�N������΂����̂���������
//�~���[�e�b�N�X���b�N���I�ƌ��������Ƃ��낾����
//����A���������Ă������B
//���Ă��Ƃ́A�Q�Ƃ�n������Ȃ��B
//�����ێ������ƂƂĂ�����ˁB
//�܂��܂��l����̈�ł͂Ȃ��ˁB


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
