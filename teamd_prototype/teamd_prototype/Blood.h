#pragma once

#include "Vector2.h"

//��
//Enemy���琁���o��
//�����܂�͂�����z���A����

//�ʂ������̂ŁA�������ꂩ���ɂ܂Ƃ߂���@���Ƃ��Ă݂�

//�Ǘ����X�V�ƕ`������那
//����ȊO�ɕʓr���@������Ȃ炻���              

struct Blood
{
	Blood()
		:pos(), vec(),isAlive()
	{}

	//�L���X�g�ɂ�����R�X�g�ƃ���������������R�X�g
	//�ǂ�����D�悵�悤����

	Point2		pos;//���W
	Point2		vec;//����
	bool		isAlive;//��������



};

