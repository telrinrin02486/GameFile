#pragma once

#include "Vector2.h"
#include "Rect2.h"
//Enemy‚Í‚Â‚Ô‚ê‚È‚­‚Ä‚à‚¢‚¢‚ñ‚¶‚á‚È‚©‚ë‚¤‚©
//ˆêu‚ÅÁ–Å‚µ‚Ü‚¹‚¢I


//“GŠî‘b
class Camera;
class Player;
class House;
class Enemy
{
public:
	//‚¨‚¨‚Ü‚©‚Èó‘Ô
	enum class State {
		unknown,//“Á‚É‚È‚µB‚í‚©‚ç‚È‚¢B

		isDed,//€‹
		onHouse,//Œš•¨‚É‰B‚ê‚Ä‚é
		isGhost,//G‚ê‚È‚¢
	};
public:
	Enemy();
	virtual ~Enemy();

	virtual int Update() = 0;
	virtual void Draw(const Camera& camera_) = 0;

	Enemy::State GetState() const {
		return __state;
	}
	virtual Vector2 Pos() const = 0;

	inline void SetGroundFlag(bool groundFlag_) {
		__isGround = groundFlag_;
	}
	void SetOnHouse(const House* const house_) {
		__onHouse = house_;
	}
	virtual void SetRect(const Rect2& rect_) = 0;

	//“–‚½‚è”»’è‚Ég‚¤
	virtual Rect2 Rect() const = 0;
	//“–‚½‚Á‚½‚Ìˆ—
	virtual void OnCollided(const Player& player_) {};
	virtual void OnCollided(const House& house_) {};

protected:
	Enemy::State __state = State::unknown;
	bool __isGround = false;
	const House *__onHouse = nullptr;

};

