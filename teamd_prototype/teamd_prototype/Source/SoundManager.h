#pragma once


//sound‚Ìí—Ş
//‚Ü‚¾’Ç‰Á‚µ‚Ä‚Ü‚¹‚ñ
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
	void Play(SOUND_TYPE _type, int _volume = 128);			//w’èsound‚ÌÄ¶(1‰ñ)
	void PlayLoop(SOUND_TYPE _type, int _volume = 128);		//w’èsound‚ÌÄ¶(Loop)
	void Stop(SOUND_TYPE _type);							//Ä¶’†sound‚Ì’â~
};

