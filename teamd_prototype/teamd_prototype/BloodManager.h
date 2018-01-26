#pragma once
#include <vector>

#include "Singleton.h"

#include "Vector2.h"

class Camera;
struct Blood;
class BloodManager:
	public Singleton<BloodManager>
{
	friend Singleton<BloodManager>;
public:
	BloodManager();

	int Init();
	int Update();
	void Draw(const Camera& camera_);
	inline const std::vector<Blood>& Bloods() const {
		return _bloods;
	}
	//�ꗱ����
	void Create(const Vector2& pos_, const Vector2& vec_);

	inline const float& Radius() const {
		return _radius;
	}

private:
	int BloodUpdate(Blood& blood_);
	void BloodDraw(const Blood& blood_,const Camera& camera_);
	//�v�f�̒ǉ����ɑ啝�ȃ������ړ����N���蓾��
	//�ŏ��ɂ�����x�܂Ƃ߂Ċm�ۂ��Ă����āA�ォ��ǉ�����H
	//�ł��ŏ����炱�񂾂��̂��̂���������ɂ���Ǝז�����ˁB

	std::vector<Blood> _bloods;

	int		_handle;
	float	_radius;


};

