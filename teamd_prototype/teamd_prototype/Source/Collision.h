#pragma once



//1208
//ここの実装について。
//各形状にデフォルトで存在するわけではないので、
//別に作るのはわかるが、
//一つにまとめるよりか、、、
//派生の何かがあったほうがいいんじゃ。。。？
//ダブルディスパッチ使えるようにするならそうなるよね。
//変更予定ができました。

class Rect2;
class Range2;
//判定
bool IsHit(const Rect2& r1_, const Rect2& r2_);
bool IsHit(const Range2& r1_, const Range2& r2_);

//重なり矩形の取り出し
Rect2 Overlap(const Rect2& r1_, const Rect2& r2_);
Range2 Overlap(const Range2& r1_, const Range2& r2_);


//当たってる相手の情報を保持するのはいいねぇ。

//変形する→オブジェクトのベクトルが必要。

//簡易変形手順
//





