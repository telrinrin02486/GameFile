#pragma once
#include <vector>

#include "Singleton.h"

#include "Vector2.h"

class Camera;
class Blood;
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
	//一粒生成
	void Create(const Vector2& pos_, const Vector2& vec_);

	inline const float& Radius() const {
		return _radius;
	}

private:
	int BloodUpdate(Blood& blood_);
	void BloodDraw(const Blood& blood_,const Camera& camera_);
	//要素の追加時に大幅なメモリ移動が起こり得る
	//最初にある程度まとめて確保しておいて、後から追加する？
	//でも最初からこんだけのものがメモリ上にあると邪魔だよね。

	std::vector<Blood> _bloods;

	int		_handle;
	float	_radius;


};

