#pragma once
#include <vector>

#include "Singleton.h"

#include "Point2.h"

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
	void Create(const Point2& point_, const Point2& vec_);

	inline const float& Radius() const {
		return _radius;
	}
private:
	//要素の追加時に大幅なメモリ移動が起こり得る

	std::vector<Blood> _bloods;

	int		_handle;
	float	_radius;


};

