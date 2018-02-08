#pragma once
#include "Enemy.h"
#include "Rect2.h"

#include <vector>

class CharaCollider;

class Player;
class House;
class Camera;
class GabyoMan :
	public Enemy
{
public:
	//��Ԋ�b�N���X
	class State {
	public:
		State();
		virtual ~State();

		virtual int Update() = 0;

	};
	//�����蔻��p�̃t���O�𗝉����₷�����p���邽�߂̃N���X
	//�i�����ł���Ƃ͌����ĂȂ��j
	class CollFlag {
	public:
		enum Type : unsigned char {
			//���������͉����瓖�����Ă܂����t���O�p
			sideAndBottomHit = 1 << 0,
			//OnCollided�Ă΂�܂������֘A
			called = 1 << 1,
			prevCalledFlag = 1 << 2,
		};
	public:
		CollFlag() :_flag() {}
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
		inline bool CalledConf() const {
			//0121
			//unsigned char�Ȃ̂�true��false���Ŕ�ׂ��킯�Ȃ����낧��E�E�E
			//���l����
			return (_flag & CollFlag::called) != ((_flag & CollFlag::prevCalledFlag) >> 1);
		}
		//�����瓖�����Ă�
		inline void SetSideAndBottomHitFlag() {
			_flag |= CollFlag::sideAndBottomHit;

		}
		//sideHit�t���O��܂�
		inline void ClearSideAndBottomHitFlag() {
			_flag &= ~CollFlag::sideAndBottomHit;
		}
		//�m�F
		inline bool SideAndBottomHit() const {
			return _flag & CollFlag::sideAndBottomHit;
		}

	private:
		unsigned char _flag;
	};
	//�莝���̃p�����^
	struct Parameter {
		Parameter(bool& groundFlag_, const House*& onHouse_, Enemy::State& enemyState_,
			unsigned char& name_)
			:isGround(groundFlag_), onHouse(onHouse_), enemyState(enemyState_),
			enemyName(name_),
			handle(), pos(), size(), vec(), life(),
			prevState(), nowState() 
		{}
		~Parameter() {
			if (prevState) { delete prevState; }
			if (nowState) { delete nowState; }
		}
		int		handle;//�摜�n���h��
		Vector2	pos;//���W
		Vector2 size;//��������
		Vector2	vec;//�̓x�N�g���l�H
		int		life;//�̗�
		int		ghostTime;//���G�^�C��
		CollFlag collFlag;//�t���O�Q
						  //����p
		//std::vector<CharaCollider*> _collider;

		//��b�N���X�������Ă�p�����^
		bool&	isGround;//�ڒn�t���O
		const House*& onHouse;//�����Ă��
		Enemy::State& enemyState;//���
		unsigned char& enemyName;//�����O
								 //state
		GabyoMan::State*	prevState;
		GabyoMan::State*	nowState;

		void ChangeState(State* nextState_) {
			if (prevState) { delete prevState; }
			prevState = nowState;
			nowState = nextState_;
		}
	};
private:
	class Idle;
	class Escaping;
	class Dying;
public:
	GabyoMan(const Vector2& pos_, const Player& player_);
	~GabyoMan();

	int Update() override;
	void Draw(const Camera& camera_) override;
	Vector2 Pos() const override {
		return _param.pos;
	}
	Rect2 Rect() const override {
		return Rect2(_param.pos, _param.size);
	}
	bool IsGround() const override {
		return _param.isGround;
	}
	void SetRect(const Rect2& rect_) override {
		_param.pos = rect_.LT();
		_param.size = rect_.Size();
	}

	void OnCollided(const Player& player_) override;
	void OnCollided(const House& house_) override;

private:
	Parameter _param;
	const Player& _player;

};

