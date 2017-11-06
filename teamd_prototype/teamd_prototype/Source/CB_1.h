#pragma once

#include "CrushedBox.h"
#include "Rect2.h"

//‰ó‚ê•û‚P
//¡‚ğ‚Â‚Ô‚·‚¾‚¯B

class Player;
class EffectManager;

class CB_1 :
	public CrushedBox
{
public:
	CB_1(EffectManager& efm_,float durability_ = 0.5f);

	~CB_1()
	{}

	int Update() override;
	void Draw(const Vector2& offset_) override;

	bool IsDead() const {
		return !_alive;
	}

	void Crushed(const Player& player);

	inline const Rect2& Rect() const {
		return _rect;
	}

private:
	int			_handle;
	Rect2		_rect;
	bool		_alive;

	EffectManager& _efm;

	float		_durability;//ŒÅ‚³
	int			_hitPoint;

};

