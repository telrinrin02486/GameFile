#pragma once

#include "Vector2.h"
#include "BloodManager.h"

//��
//Enemy���琁���o��
//�����܂�͂�����z���A����

//�ʂ������̂ŁA�������ꂩ���ɂ܂Ƃ߂���@���Ƃ��Ă݂�

//�Ǘ����X�V�ƕ`������那
//����ȊO�ɕʓr���@������Ȃ炻���              

class Blood
{
	friend BloodManager;
public:
	Blood()
		:_pos(), _vec(),_isAlive(),_isGround()
	{}
	Blood(const Vector2& pos_, const Vector2& vec_)
		:_pos(pos_), _vec(vec_), _isAlive(true),_isGround()
	{}

	inline void SetGroundFlag(bool flag_) {
		_isGround = flag_;
	}
	inline bool IsGround() const {
		return _isGround;
	}
	//�L���X�g�ɂ�����R�X�g�ƃ���������������R�X�g
	//�ǂ�����D�悵�悤����

private:
	Vector2		_pos;//���W
	Vector2		_vec;//����
	bool		_isAlive;//��������
	bool		_isGround;//�ڒn�t���O
};

