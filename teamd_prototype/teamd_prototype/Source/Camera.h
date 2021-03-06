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
	//更新
	void Update();

	//現在地から移動
	void Move(float dirX_, float dirY_);
	void Move(const Vector2& dir_);
	//テレポート
	void Teleport(float posX_, float posY_);
	void Teleport(const Vector2& pos_);
	//座標取得
	inline const Vector2& Pos() const {
		return _pos;
	}
	//ズレ取得
	inline const Vector2& Offset() const {
		return _offset;
	}
	//画面サイズ
	inline const Vector2& WindowSize() const {
		return _size;
	}
	//地震をセット
	//連続には対応していない
	//揺れの足し合わせに対応
	void SetEarthquake(const Vector2& shakeValue_,//揺れの大きさ
		float reductionRate_ = 0.25f,//揺れの減少率
		float speed_ = 0.5f);//揺れる速度
	//地震をセット（手動で止めて）
	void SetPermanentEarthquake(const Vector2& shakeValue_,
		float speed_ = 0.5f);
	//地震を強制的に止める。
	void StopEarthquake();

	//状態を返すゾ。
	inline Camera::State IsState() {
		return _state;
	}

#pragma region シングルトン化
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
	Vector2		_pos;//座標
	Vector2		_offset;//ズレ

	Vector2		_size;//画面サイズ

	Camera::State _state = Camera::Idel;

	//シェイク用のパラメタ保存領域
	Vector2		_shakeValue;
	float		_reductionRate;
	float		_shakeSpeed;
	Vector2		_nowShakeValue;//1フレで揺れる値。
	Vector2		_length;//進むべき量
	Vector2		_nowLength;//進んだ量（現在値

	//シェイク関数
	bool Shake();
	//シェイク関数（揺れ値がへらない。）
	bool ShakeForever();
	//シェイク用関数ポインタ。
	bool(Camera::*_shakeFuncPtr)(void) = nullptr;
	
};

