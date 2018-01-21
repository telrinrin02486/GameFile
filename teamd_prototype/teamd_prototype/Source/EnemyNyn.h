#pragma once
#include "Enemy.h"
#include "Rect2.h"

class Player;
class House;
class Camera;
class EnemyNyn :
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
	//�莝���̃p�����^
	struct Parameter {
		Parameter(bool& groundFlag_,const House*& onHouse_,Enemy::State& enemyState_)
			:isGround(groundFlag_),onHouse(onHouse_),enemyState(enemyState_),
			handle(), pos(),size(), vec(), life(),
			prevState(), nowState() {

		}
		int		handle;//�摜�n���h��
		Vector2	pos;//���W
		Vector2 size;//��������
		Vector2	vec;//�̓x�N�g���l�H
		int		life;//�̗�
		int		ghostTime;//���G�^�C��
		//��b�N���X�������Ă�p�����^
		bool&	isGround;//�ڒn�t���O
		const House*& onHouse;//�����Ă��
		Enemy::State& enemyState;//���

		EnemyNyn::State*	prevState;
		EnemyNyn::State*	nowState;

		void ChangeState(State* nextState_) {
			if (prevState) { delete prevState; }
			prevState = nowState;
			nowState = nextState_;
		}
	};
public:
	EnemyNyn(const Vector2& pos_,const Player& player_);
	~EnemyNyn();

	int Update() override;
	void Draw(const Camera& camera_) override;
	Vector2 Pos() const override {
		return _param.pos;
	}
	Rect2 Rect() const override {
		return Rect2(_param.pos, _param.size);
	}
	void SetRect(const Rect2& rect_) override{
		_param.pos = rect_.LT();
		_param.size = rect_.Size();
	}

	void OnCollided(const Player& player_) override;
private:
	Parameter _param;

	const Player& _player;
};

