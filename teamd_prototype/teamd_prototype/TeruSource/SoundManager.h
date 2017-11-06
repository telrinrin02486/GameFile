#pragma once


//sound�̎��
//�܂��ǉ����Ă܂���
enum SOUND_TYPE
{
	HIT_1,
	TENKA,
	EXPLOSION,

	SOUND_MAX

};

class SoundManager
{
private:

	int sound[SOUND_MAX];

	
	SoundManager();		
	~SoundManager();	
	SoundManager(const SoundManager &Inst);				
	SoundManager & operator=(const SoundManager &Inst); 

public:

	
	static SoundManager &GetInstance()
	{
		static SoundManager Instance;
		return Instance;
	}

	void Initialize();
	void Play(SOUND_TYPE _type, int _volume = 128);			//�w��sound�̍Đ�(1��)
	void PlayLoop(SOUND_TYPE _type, int _volume = 128);		//�w��sound�̍Đ�(Loop)
	void Stop(SOUND_TYPE _type);							//�Đ���sound�̒�~
};

