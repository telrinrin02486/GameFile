#pragma once

#include "Vector2.h"

#include "Rect2.h"


class Camera
{
public:
	enum State {
		Idel,
		Earthquake,
	};
public:
	static Camera& Instance() {
		static Camera i;
		return i;
	}
	//�X�V
	void Update();

	//���ݒn����ړ�
	void Move(float dirX_, float dirY_);
	void Move(const Vector2& dir_);
	//�e���|�[�g
	void Teleport(float posX_, float posY_);
	void Teleport(const Vector2& pos_);
	//���W�擾
	inline const Vector2& Pos() const {
		return _pos;
	}
	//�Y���擾
	inline const Vector2& Offset() const {
		return _offset;
	}
	//�n�k���Z�b�g
	//�A���ɂ͑Ή����Ă��Ȃ�
	//�h��̑������킹�ɑΉ�
	void SetEarthquake(const Vector2& shakeValue_,//�h��̑傫��
		float reductionRate_ = 0.25f,//�h��̌�����
		float speed_ = 0.5f);//�h��鑬�x
	//�n�k���Z�b�g�i�蓮�Ŏ~�߂āj
	void SetPermanentEarthquake(const Vector2& shakeValue_,
		float speed_ = 0.5f);
	//�n�k�������I�Ɏ~�߂�B
	void StopEarthquake();

	//��Ԃ�Ԃ��]�B
	inline Camera::State IsState() {
		return _state;
	}

#pragma region �V���O���g����
protected:
	~Camera();
private:
	Camera(const Vector2& pos_ = Vector2());
	Camera(const Camera&) = delete;
	Camera(const Camera&&) = delete;
	Camera& operator=(const Camera&) = delete;
	Camera& operator=(const Camera&&) = delete;
#pragma endregion

private:
	Vector2		_pos;//���W
	Vector2		_offset;//�Y��

	Camera::State _state = Camera::Idel;

	//�V�F�C�N�p�̃p�����^�ۑ��̈�
	Vector2		_shakeValue;
	float		_reductionRate;
	float		_shakeSpeed;
	Vector2		_nowShakeValue;//1�t���ŗh���l�B
	Vector2		_length;//�i�ނׂ���
	Vector2		_nowLength;//�i�񂾗ʁi���ݒl

	//�V�F�C�N�֐�
	bool Shake();
	//�V�F�C�N�֐��i�h��l���ւ�Ȃ��B�j
	bool ShakeForever();
	//�V�F�C�N�p�֐��|�C���^�B
	bool(Camera::*_shakeFuncPtr)(void) = nullptr;
	
};

