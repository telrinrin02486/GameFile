#pragma once



//1208
//�����̎����ɂ��āB
//�e�`��Ƀf�t�H���g�ő��݂���킯�ł͂Ȃ��̂ŁA
//�ʂɍ��̂͂킩�邪�A
//��ɂ܂Ƃ߂��肩�A�A�A
//�h���̉������������ق��������񂶂�B�B�B�H
//�_�u���f�B�X�p�b�`�g����悤�ɂ���Ȃ炻���Ȃ��ˁB
//�ύX�\�肪�ł��܂����B

class Rect2;
class Range2;
//����
bool IsHit(const Rect2& r1_, const Rect2& r2_);
bool IsHit(const Range2& r1_, const Range2& r2_);

//�d�Ȃ��`�̎��o��
Rect2 Overlap(const Rect2& r1_, const Rect2& r2_);
Range2 Overlap(const Range2& r1_, const Range2& r2_);


//�������Ă鑊��̏���ێ�����̂͂����˂��B

//�ό`���遨�I�u�W�F�N�g�̃x�N�g�����K�v�B

//�ȈՕό`�菇
//





