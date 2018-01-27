#pragma once

#include <vector>
#include "Rect2.h"

class Enemy;
class Camera;
class Player;
//�G���������ނ�����
//���͉摜�̍��ق����Ȃ��ł���B
//���߂ē�����ʂƂ����炢�B
//�ׂ��̂����d��
//Enemy���������Ď������������₷����
//CB_�P�Ƃقڕς��Ȃ������ŁB
class House
{
public:
	House(const Vector2& pos_);
	~House();

	int Update();
	void Draw(const Camera& camera_);


	bool IsDead() const {
		return !_alive;
	}

	void Crushed(const Player& player);

	inline const Rect2& Rect() const {
		return _rect;
	}
	inline const Vector2& Vec() const {
		return _vec;
	}

	//setter
	void SetGroundFlag(bool groundFlag_) {
		_isGround = groundFlag_;
	}
	void SetRect(const Rect2& rect_) {
		_rect = rect_;
	}
	//���������ۂ̌��I�Ή�
	virtual void OnCollided(const Player& player_);
	virtual void OnCollided(const Enemy& enemy_);
	//�����瓖�����Ă܂���t���O
	inline bool SideHitFlag() const {
		return _collFlag.SideHit();
	}
private:
	class CollFlag {
	public:
		enum Type : unsigned char{
			//�����瓖�����Ă܂����t���O�p
			sideHit			= 1 << 0,
			verticalHit		= 1 << 1,
			//OnCollided�Ă΂�܂������֘A
			called			= 1 << 2,
			prevCalledFlag	= 1 << 3,
		};
	public:
		CollFlag() :_flag(){}
		//OnCollided�Ă΂ꂽ
		inline void SetCalledFlag() {
			_flag ^= CollFlag::called;
		}
		//�Ă΂ꂽ����O���Ƃ��ĕۑ�
		inline void SetPrevCalledFlag() {
			//�����Ƃ��������肻�������ǂ悭�킩��Ȃ��i���m�j
			//�܂�����
			_flag &= ~CollFlag::prevCalledFlag;
			//called�̕����Ɠ����l�ɂ���
			_flag |= (_flag & CollFlag::called) ? CollFlag::prevCalledFlag : 0x00;
		}
		//�m�F
		//�ȑO�Ă΂ꂽ���ۂ���
		//called��prevCalledFlag�̒l���قȂ�ꍇ��true
		inline bool CalledConf() const{
			//0121
			//unsigned char�Ȃ̂�true��false���Ŕ�ׂ��킯�Ȃ����낧��E�E�E
			//���l����
			return (_flag & CollFlag::called) != ((_flag & CollFlag::prevCalledFlag) >> 1);
		}
		//�����瓖�����Ă�
		inline void SetSideHitFlag() {
			ClearVerticalHitFlag();
			_flag |= CollFlag::sideHit;
			
		}
		//sideHit�t���O��܂�
		inline void ClearSideHitFlag() {
			_flag &= ~CollFlag::sideHit;
		}
		//�m�F
		inline bool SideHit() const{
			return _flag & CollFlag::sideHit;
		}
		//�c���瓖�����Ă�
		inline void SetVerticalHitFlag() {
			ClearSideHitFlag();
			_flag |= CollFlag::verticalHit;
		
		}
		//VerticalHit�t���O��܂�
		inline void ClearVerticalHitFlag() {
			_flag &= ~CollFlag::verticalHit;
		}
		//�m�F
		inline bool VerticalHit() const {
			return _flag & CollFlag::verticalHit;
		}
	private:
		unsigned char _flag;
	};
private:
	bool	_isGround;
	int		_handle;
	Rect2		_rect;
	bool		_alive;
	unsigned int	_count;
	Vector2		_vec;
	float		_durability;//�ł�
	int		_hitPoint;
	int		_maxHitPoint;
	unsigned int _imageSuffix;
	float _angle;
	bool _isTurn;

	CollFlag	_collFlag;
};
