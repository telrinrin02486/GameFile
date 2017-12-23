#pragma once

//“GŠî‘b
class Camera;
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update() = 0;
	virtual void Draw(const Camera& camera_) const = 0;

	inline bool IsAlive() const {
		return _alive;
	}
protected:
	inline void Ded() {
		_alive = false;
	}
private:
	bool _alive = true;

};

