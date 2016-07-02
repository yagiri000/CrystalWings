#include "Func.h"

Draw::Draw() :
dx(0),
dy(0)
{}

Draw& Draw::get()
{
	static Draw inst;
	return inst;
}

void Draw::setdxdy(int x, int y){
	get().dx = x;
	get().dy = y;
	get().shift_vec.Set(x, y);
}

//通常の描画・座標は左上を指定
void Draw::normal(int x, int y, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(x + get().dx, y + get().dy, GrHandle, 1);
}

//画像の中央の座標を指定して描画
void Draw::center(int x, int y, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x + get().dx, y + get().dy, 1.0, 0.0, GrHandle, 1, TurnFlag);
}

//拡大・回転描画
void Draw::exrot(int x, int y, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(x + get().dx, y + get().dy, ExtRate, Angle, GrHandle, 1, TurnFlag);
}

//拡大・回転・中央指定描画
void Draw::exrot3(int x, int y, int cx, int cy, double ExtRateX, double ExtRateY, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(x + get().dx, y + get().dy, cx, cy, ExtRateX, ExtRateY, Angle, GrHandle, 1, TurnFlag);
}

//自由変形描画
void Draw::modi(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy,
		x3 + get().dx, y3 + get().dy, x4 + get().dx, y4 + get().dy,
		GrHandle, 1);
}

//左上・右下を指定して描画
void Draw::modi2(int x1, int y1, int x2, int y2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, GrHandle, 1);
}

//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
void Draw::modiOval(double x, double y, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = x + r * cos(angle + i * dangle - dr);
		gy[i] = y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0] + get().dx, gy[0] + get().dy,
		gx[1] + get().dx, gy[1] + get().dy,
		gx[2] + get().dx, gy[2] + get().dy,
		gx[3] + get().dx, gy[3] + get().dy, GrHandle, 1);
}

//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
void Draw::trim(int DestX, int DestY, int SrcX, int SrcY, int Width, int Height, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(DestX + get().dx, DestY + get().dy, SrcX, SrcY, Width, Height, GrHandle, 1, TurnFlag);
}

//サークルゲージ描画　(dx, dy)分シフト
void Draw::circlegauge(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x + get().dx, y + get().dy, 100, GrHandle, 100 - percent);
}

//サークルゲージ描画（逆方向）　(dx, dy)分シフト
void Draw::circlegauge_rev(int x, int y, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(x + get().dx, y + get().dy, percent, GrHandle);
}

//図形描画関数

//線を描画
void Draw::line(int sx, int sy, int ex, int ey, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx + get().dx, sy + get().dy, ex + get().dx, ey + get().dy, color, Thickness);
}

//独自
//始点と終点への距離、角度を指定して線を描画
void Draw::lineangle(int sx, int sy, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(sx + get().dx, sy + get().dy, sx + r * cos(angle) + get().dx, sy + r * sin(angle) + get().dy, color, Thickness);
}

//箱を描画
void Draw::box(int x1, int y1, int x2, int y2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, color, 1);
}

//独自
//中心を指定して箱を描画
void Draw::centerbox(double centerx, double centery, double width, double height, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		centerx - width / 2 + get().dx, centery - height / 2 + get().dy,
		centerx + width / 2 + get().dx, centery + height / 2 + get().dy,
		color, 1);
}

//円を描画
void Draw::circle(int x, int y, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(x + get().dx, y + get().dy, r, color, 1);
}

//三角形を描画
void Draw::triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(x1 + get().dx, y1 + get().dy, x2 + get().dx, y2 + get().dy, x3 + get().dx, y3 + get().dy, color, 1);
}


//文字描画関数

//文字を描画
void Draw::text(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(x + get().dx, y + get().dy, color, fonthandle, "%s", str.c_str());
}

//指定した座標を中心に文字を描画
void Draw::centertext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
	DrawFormatStringToHandle(x + get().dx - wd / 2, y + get().dy, color, fonthandle, "%s", str.c_str());
}

//文字の右上の座標を指定して文字を描画
void Draw::righttext(int x, int y, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
	DrawFormatStringToHandle(x + get().dx - wd, y + get().dy, color, fonthandle, "%s", str.c_str());
}

//指定した座標を中心に文字を描画 文字の間隔を指定可能
void Draw::centertext_space(int x, int y, int color, int fonthandle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(x + i * space + basex, y, color, fonthandle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(x + i * space + basex, y, color, fonthandle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
}



//Vector2使用

//通常の描画・座標は左上を指定
void Draw::normal(const Vector2& pos, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawGraph(pos.x + get().dx, pos.y + get().dy, GrHandle, 1);
}

//画像の中央の座標を指定して描画
void Draw::center(const Vector2& pos, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x + get().dx, pos.y + get().dy, 1.0, 0.0, GrHandle, 1, TurnFlag);
}

//拡大・回転描画
void Draw::exrot(const Vector2& pos, double ExtRate, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph(pos.x + get().dx, pos.y + get().dy, ExtRate, Angle, GrHandle, 1, TurnFlag);
}

//拡大・回転・中央指定描画
void Draw::exrot3(const Vector2& pos, const Vector2& center_pos, const Vector2& Exrate_vec, double Angle, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRotaGraph3(pos.x + get().dx, pos.y + get().dy, center_pos.x, center_pos.y, Exrate_vec.x, Exrate_vec.y, Angle, GrHandle, 1, TurnFlag);
}

//自由変形描画
void Draw::modi(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, const Vector2& pos4, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraph(
		pos1.x + get().dx, pos1.y + get().dy, pos2.x + get().dx, pos2.y + get().dy,
		pos3.x + get().dx, pos3.y + get().dy, pos4.x + get().dx, pos4.y + get().dy,
		GrHandle, 1);
}

//左上・右下を指定して描画
void Draw::modi2(const Vector2& pos1, const Vector2& pos2, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawExtendGraph(pos1.x + get().dx, pos1.y + get().dy, pos2.x + get().dx, pos2.y + get().dy, GrHandle, 1);
}

//楕円上にグラフを描画　rで円の半径・rate:縦にrをrateの比の分ひしゃげさせる・angle:回転角
void Draw::modiOval(const Vector2& pos, double r, double rate, double angle, int GrHandle, int Alpha, int BlendMode){
	float gx[4];
	float gy[4];
	float dr = PI * -0.75;
	for (int i = 0; i < 4; i++){
		float dangle = PI * 0.5;
		gx[i] = pos.x + r * cos(angle + i * dangle - dr);
		gy[i] = pos.y + rate * r * sin(angle + i * dangle - dr);
	}

	SetDrawBlendMode(BlendMode, Alpha);
	DrawModiGraphF(
		gx[0] + get().dx, gy[0] + get().dy,
		gx[1] + get().dx, gy[1] + get().dy,
		gx[2] + get().dx, gy[2] + get().dy,
		gx[3] + get().dx, gy[3] + get().dy, GrHandle, 1);
}

//画像の指定した部分のみ描画　描画座標・左上座標・描画画像サイズ
void Draw::trim(const Vector2& pos, const Vector2& graph_ul_pos, const Vector2& size, int GrHandle, int Alpha, int TurnFlag, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawRectGraph(pos.x + get().dx, pos.y + get().dy, graph_ul_pos.x, graph_ul_pos.y, size.x, size.y, GrHandle, 1, TurnFlag);
}

//サークルゲージ描画　(dx, dy)分シフト
void Draw::circlegauge(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x + get().dx, pos.y + get().dy, 100, GrHandle, 100 - percent);
}

//サークルゲージ描画（逆方向）　(dx, dy)分シフト
void Draw::circlegauge_rev(const Vector2& pos, double percent, int GrHandle, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircleGauge(pos.x + get().dx, pos.y + get().dy, percent, GrHandle);
}

//図形描画関数

//線を描画
void Draw::line(const Vector2& start_pos, const Vector2& end_pos, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x + get().dx, start_pos.y + get().dy, end_pos.x + get().dx, end_pos.y + get().dy, color, Thickness);
}

//独自
//始点と終点への距離、角度を指定して線を描画
void Draw::lineangle(const Vector2& start_pos, int r, double angle, int color, int Alpha, int Thickness, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawLine(start_pos.x + get().dx, start_pos.y + get().dy, start_pos.x + r * cos(angle) + get().dx, start_pos.y + r * sin(angle) + get().dy, color, Thickness);
}

//箱を描画
void Draw::box(const Vector2& pos1, const Vector2& pos2, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(pos1.x + get().dx, pos1.y + get().dy, pos2.x + get().dx, pos2.y + get().dy, color, 1);
}

//独自
//中心を指定して箱を描画
void Draw::centerbox(const Vector2& center_pos, const Vector2& size, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawBox(
		center_pos.x - size.x / 2 + get().dx, center_pos.y - size.y / 2 + get().dy,
		center_pos.x + size.x / 2 + get().dx, center_pos.y + size.y / 2 + get().dy,
		color, 1);
}

//円を描画
void Draw::circle(const Vector2& pos, int r, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawCircle(pos.x + get().dx, pos.y + get().dy, r, color, 1);
}

//三角形を描画
void Draw::triangle(const Vector2& pos1, const Vector2& pos2, const Vector2& pos3, int color, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawTriangle(pos1.x + get().dx, pos1.y + get().dy, pos2.x + get().dx, pos2.y + get().dy, pos3.x + get().dx, pos3.y + get().dy, color, 1);
}


//文字描画関数

//文字を描画
void Draw::text(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	DrawFormatStringToHandle(pos.x + get().dx, pos.y + get().dy, color, fonthandle, "%s", str.c_str());
}

//指定した座標を中心に文字を描画
void Draw::centertext(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x + get().dx - wd / 2, pos.y + get().dy, color, fonthandle, "%s", str.c_str());
}

//文字の右上の座標を指定して文字を描画
void Draw::righttext(const Vector2& pos, int color, int fonthandle, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int wd = GetDrawFormatStringWidthToHandle(fonthandle, "%s", str.c_str());
	DrawFormatStringToHandle(pos.x + get().dx - wd, pos.y + get().dy, color, fonthandle, "%s", str.c_str());
}

//指定した座標を中心に文字を描画 文字の間隔を指定可能
void Draw::centertext_space(const Vector2& pos, int color, int fonthandle, int space, const std::string &str, int Alpha, int BlendMode){
	SetDrawBlendMode(BlendMode, Alpha);
	int str_num = (int)(str.size());
	if ((str_num % 2) == 0){
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space + space / 2;
			centertext(pos.x + i * space + basex, pos.y, color, fonthandle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
	else{
		for (int i = 0; i < (int)(str_num); i++){
			double basex = -(double)(str_num / 2) * space;
			centertext(pos.x + i * space + basex, pos.y, color, fonthandle, str.substr(i, 1), Alpha, BlendMode);
		}
	}
}



Input::Input() :
m_mousex(0),
m_mousey(0),
m_eframe(0),
Allzeroframe(0),
IsAllzero(false)
{

}

Input& Input::get(){
	static Input inp;
	return inp;
}

void Input::update(){
	get().do_update();
}

//キーが押されているかをboolで返す
bool Input::keynow(int i){
	return get().keystate[i] > 0;
}

//キーが押されたフレームだけtrueを返す
bool Input::keydown(int i){
	return (get().keystate[i] == 1 && get().keystate_pre[i] != -1);
}

//キーが離されたフレームだけtrueを返す
bool Input::keyup(int i){
	return (get().keystate[i] == 0) && (get().keystate_pre[i] > 0);
}

//キーが押されているフレームを返す
int Input::keyframe(int i){
	return get().keystate[i];
}

int Input::mousex(){
	return get().m_mousex;
}

int Input::mousey(){
	return get().m_mousey;
}

Vector2 Input::mousePos(){
	return get().m_mousePos;
}

int Input::eframe(){
	return get().m_eframe;
}

//Allzeroframeの間keystateがすべて0に
void Input::setAllzeroframe(int t){
	if (t > 0){
		get().Allzeroframe = t;
	}
}

//Allzerooffが呼ばれるまでkeystateをすべて0に
void Input::Allzeroon(){
	get().IsAllzero = true;
}

//keystateすべて0 を解除 Allzeroframeを0に
void Input::Allzerooff(){
	get().IsAllzero = false;
	get().Allzeroframe = 0;
}


void Input::do_update(){
	GetHitKeyStateAll(buf);
	buf[250] = GetMouseInput() & MOUSE_INPUT_LEFT;
	buf[251] = ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) ? 0 : 1;
	for (int i = 0; i < 256; i++){
		//1フレーム前の情報を保存
		keystate_pre[i] = keystate[i];
		//keystateを更新
		if (buf[i] == 1){
			if (keystate[i] == -1) keystate[i] = 0;
			keystate[i]++;
		}
		else{
			keystate[i] = 0;
		}
	}
	if (IsAllzero == true || Allzeroframe > 0){
		Allzero();
	}
	if (Allzeroframe > 0){
		Allzeroframe--;
	}
	//マウス座標更新
	GetMousePoint(&m_mousex, &m_mousey);
	m_mousePos.Set(m_mousex, m_mousey);
	//経過フレーム計測
	m_eframe++;
}

void Input::Allzero(){
	for (int i = 0; i < 256; i++){
		keystate[i] = -1;
		keystate_pre[i] = -1;
	}
}

//class Random
Random::Random(){
	//SeedSetUseRDでMTの初期値を設定
	SeedSetUseRD();
}

Random& Random::get()
{
	static Random r;
	return r;
}

//MTの初期値をRandom_deviceを使用して設定
void Random::SeedSetUseRD(){
	std::random_device r;
	get().mt.seed(r());
}
//MTの初期値設定
void Random::Initialize(int seed)
{
	get().mt.seed(seed);
}
//mtエンジン本体を取得
std::mt19937& Random::getMT(){
	return get().mt;
}

//完全乱数
unsigned int Random::RamdomDeviceValue()
{
	std::random_device r;
	return r();
}

//通常のrand取得
int Random::Rand(){
	return get().mt();
}
//0~max指定取得(int)
int Random::Rand(int max)
{
	std::uniform_int_distribution<int> uid(0, max);
	return uid(get().mt);
}
//min~maxを返す(int)
int Random::Rand(int min, int max)
{
	if (min > max){
		int tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_int_distribution<int> uid(min, max);
	return uid(get().mt);
}
//1か-1を返す関数
int Random::RandPM1(){
	std::uniform_int_distribution<int> uid(0, 1);
	return uid(get().mt) * 2 - 1;
}
//0~1を返す(double)
double Random::Value()
{
	std::uniform_real_distribution<double> urd(0, 1);
	return urd(get().mt);
}
//0~maxを返す(double)
double Random::FRand(double max)
{
	std::uniform_real_distribution<double> urd(0, max);
	return urd(get().mt);
}
//min~maxを返す(double)
double Random::FRand(double min, double max)
{
	if (min > max){
		double tmp = min;
		min = max;
		max = tmp;
	}
	std::uniform_real_distribution<double> urd(min, max);
	return urd(get().mt);
}
//正規分布
double Random::FRandND(double mean, double sigma)
{
	std::normal_distribution<double> nd(mean, sigma);
	return nd(get().mt);
}
double Random::FRandND(double mean, double sigma, double limit)
{
	std::normal_distribution<double> nd(mean, sigma);
	double r = nd(get().mt);
	if (r < mean - limit)
		r = mean - limit;
	if (r > mean + limit)
		r = mean + limit;
	return r;
}
//正規分布 平均とレンジ指定
double Random::NormalDist(double ave, double range){
	std::normal_distribution<double> nd(ave, range / 3.0);
	double ret = nd(get().mt);
	if (ret < ave - range || ret > ave + range){
		ret = FRand(ave - range, ave + range);
	}
	return ret;
}

//ラジアンで取得
double Random::FRadRand()
{
	return FRand(-PI, PI);
}
double Random::FRadRand(double deg_min, double deg_max)
{
	return FRand(deg_min * DegToRad, deg_max * DegToRad);
}
double Random::FRadRandND(double deg_mean, double deg_sigma)
{
	return FRandND(deg_mean * DegToRad, deg_sigma * DegToRad);
}
//半径rの円上の点を返す
void Random::RandOnCircle(double r, double &x, double &y){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
}
//半径rの円上の点を返す　原点からの角度も返す
void Random::RandOnCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	x = r * cos(randang);
	y = r * sin(randang);
	ang = randang;
}
//半径rの円内部の点を返す
void Random::RandInCircle(double r, double &x, double &y){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
}
//半径rの円内部の点を返す　原点からの角度も返す
void Random::RandInCircle(double r, double &x, double &y, double &ang){
	double randang = FRadRand();
	double rr = r * Value();
	x = rr * cos(randang);
	y = rr * sin(randang);
	ang = randang;
}
//半径rの円上の点を返す
Vector2 Random::RandOnCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	temp.x = r * cos(randang);
	temp.y = r * sin(randang);
	return temp;
}
//半径rの円内部の点を返す
Vector2 Random::RandInCircle(double r){
	Vector2 temp;
	double randang = FRadRand();
	double rr = r * Value();
	temp.x = rr * cos(randang);
	temp.y = rr * sin(randang);
	return temp;
}

Vector2 Random::RandScreenEdge(){
	double marge = 50;
	double p = (double)ScreenHeight / (ScreenWidth + ScreenHeight);

	if (Random::RandBool(p)){
		if (Random::RandBool(0.5)){
			return Vector2(-marge, Random::FRand(ScreenHeight * 0.5));
		}
		else{
			return Vector2(ScreenWidth + marge, Random::FRand(ScreenHeight * 0.5));
		}
	}
	else{
		return Vector2(Random::FRand(ScreenWidth), -marge);
	}
}

//pの確率でtrueを返す
bool Random::RandBool(double p){
	return Random::FRand(1.0) < p;
}


namespace Func{

	//2乗
	double Sqr(double x)
	{
		return x*x;
	}
	//内積計算
	double Dot2D(double Ax, double Ay, double Bx, double By)
	{
		return Ax*Bx + Ay*By;
	}
	//外積計算
	double Cross2D(double Ax, double Ay, double Bx, double By)
	{
		return Ax*By - Bx*Ay;
	}

	//円形同士
	bool Circles(double x1, double y1, double r1, double x2, double y2, double r2)
	{
		return Sqr(x2 - x1) + Sqr(y2 - y1) < Sqr(r2 + r1);
	}
	bool Circles(const Vector2& c1, double r1, const Vector2& c2, double r2)
	{
		return Sqr(c2.x - c1.x) + Sqr(c2.y - c1.y) < Sqr(r2 + r1);
	}
	//矩形同士
	bool Boxes(double a1x, double a1y, double a2x, double a2y, double b1x, double b1y, double b2x, double b2y)
	{
		return a1x < b2x && a1y < b2y && b1x < a2x && b1y < a2y;
	}
	bool Boxes(const Vector2& a1, const Vector2& a2, const Vector2& b1, const Vector2& b2)
	{
		return a1.x < b2.x && a1.y < b2.y && b1.x < a2.x && b1.y < a2.y;
	}
	//点と幅のある線 (点の座標、幅のある線の始点・終点)
	bool BroadLinePoint(double px, double py, double line_sx, double line_sy, double line_ex, double line_ey, double broad){
		double x, y, ang, width;
		x = px - line_sx;
		y = py - line_sy;
		ang = atan2(line_ey - line_sy, line_ex - line_sx);
		width = dist(line_sx, line_sy, line_ex, line_ey);

		rotateonzero(x, y, -ang);

		if (x > 0 && x < width && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と幅のある線 (点の座標、幅のある線の始点・終点までの距離、角度)
	bool BroadLinePointAng(double px, double py, double line_sx, double line_sy, double e_r, double e_ang, double broad){
		double x, y;
		x = px - line_sx;
		y = py - line_sy;

		rotateonzero(x, y, -e_ang);

		if (x > 0 && x < e_r && y > -broad && y < broad){
			return true;
		}
		else{
			return false;
		}
	}

	//点と矩形
	bool BoxPoint(int px, int py, int box_cx, int box_cy, int box_width, int box_height){
		return abs(px - box_cx) < box_width / 2
			&& abs(py - box_cy) < box_height / 2;
	}

	//点と矩形
	bool BoxPoint(const Vector2& p_pos, const Vector2& box_pos, const Vector2& box_size){
		return abs(p_pos.x - box_pos.x) < box_size.x / 2
			&& abs(p_pos.y - box_pos.y) < box_size.y / 2;
	}
	//普通の点と矩形
	bool DotAndRect(double px, double py, double b1x, double b1y, double b2x, double b2y)
	{
		return  b1x < px  && px < b2x
			&&  b1y < py  && py < b2y;
	}

	//円(半径cr,(cx,cy))の近似正方形と　長方形(左上(rx1,ry1), 右下(rx2, ry2))の当たり判定
	bool CircleAndRect(double cx, double cy, double cr, double rx1, double ry1, double rx2, double ry2){
		double rectx = (rx1 + rx2) / 2.0;
		double recty = (ry1 + ry2) / 2.0;
		return	cx > rx1 - cr && cy > ry1 - cr &&
			cx < rx2 + cr && cy < ry2 + cr;
	}
	//線分同士(0ならあたってない、0以上はあたってる
	double Lines(double a_x, double a_y, double b_x, double b_y, double c_x, double c_y, double d_x, double d_y)
	{
		double c0;
		c0 = Cross2D(b_x - a_x, b_y - a_y, d_x - c_x, d_y - c_y);
		if (c0 == 0.0f)
			return 0.0f;
		double r0, r1;
		r0 = Cross2D(c_x - a_x, c_y - a_y, b_x - a_x, b_y - a_y) / c0;
		r1 = Cross2D(c_x - a_x, c_y - a_y, d_x - c_x, d_y - c_y) / c0;
		if (r0 >= 0.0f && r0 <= 1.0f && r1 >= 0.0f && r1 <= 1.0f)
			return r1;
		else
			return 0.0f;
	}
	//Linesで当たってた場合は位置を計算できる
	Vector2 LinesCalcCrossPoint(double lines_result, double a_x, double a_y, double b_x, double b_y)
	{
		Vector2 AB(b_x - a_x, b_y - a_y);
		AB *= lines_result;
		AB.Translate(a_x, a_y);
		return AB;
	}
	//円と線分
	bool CircleAndLine(double cx, double cy, double r, double sx, double sy, double ex, double ey)
	{
		if (distSqr(sx, sy, cx, cy) < r*r || distSqr(ex, ey, cx, cy) < r*r){
			return true;
		}
		else {
			double k = ey - sy;
			double l = ex - sx;
			if (!((k*cx - l*cy - k*sx + l*sy)*(k*cx - l*cy - k*sx + l*sy) < r * r * (k*k + l*l))){
				return false;
			}
			if (((sx - cx)*(ex - cx) + (sy - cy)*(ey - cy)) < 0){
				return true;
			}
		}
		return false;
	}


	//ベクトル

	//原点を中心にang分回転
	void rotateonzero(double &x, double &y, double ang){
		double sx = x - 0;
		double sy = y - 0;
		x = sx * cos(ang) - sy * sin(ang) + 0;
		y = sx * sin(ang) + sy * cos(ang) + 0;
	}

	//ある点(centerx,centery)を中心にang分回転
	void rotateonpoint(double &x, double &y, double centerx, double centery, double ang){
		double sx = x - centerx;
		double sy = y - centery;
		x = sx * cos(ang) - sy * sin(ang) + centerx;
		y = sx * sin(ang) + sy * cos(ang) + centery;
	}

	//(原点から(sx,sy)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy){
		double rd = atan2(sy, sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(sx,sy)から(ex,ey)への単位ベクトルを求める
	void normalizedVector(double &vx, double &vy, double sx, double sy, double ex, double ey){
		double rd = atan2(ey - sy, ex - sx);
		vx = cos(rd);
		vy = sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに代入
	void calVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx = dist * cos(rd);
		resulty = dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double sx, double sy, double ex, double ey, double dist, double &resultx, double &resulty){
		double rd = atan2(ey - sy, ex - sx);
		resultx += dist * cos(rd);
		resulty += dist * sin(rd);
	}

	//(dx,dy)方向、大きさdistのベクトルを求め、結果をresultに加算
	void addVector(double r, double angle, double &resultx, double &resulty){
		resultx += r * cos(angle);
		resulty += r * sin(angle);
	}

	//極座標表現からxy表現に直す
	void polartoxy(double &x, double &y, double r, double ang){
		x = r * cos(ang);
		y = r * sin(ang);
	}

	//角度を計算
	double calAngle(double x, double y){
		return atan2(y, x);
	}

	//角度を計算
	double calAngle(double sx, double sy, double ex, double ey){
		return atan2(ey - sy, ex - sx);
	}

	/*
	startx : 開始の値(開始時の座標やスケールなど)
	enddif : 開始と終了の値の差分
	time_now : 現在の時間
	time_end : Tweenの合計時間
	*/

	//／＼　←こういうグラフ
	double linef(double startx, double dif, double time_now, double time_end){
		return startx + (dif - startx) * (abs(time_end / 2 - time_now) / (time_end / 2));
	}

	//／＼　←こういう2次曲線
	double quadraticf(double startx, double dif, double time_now, double time_end){
		double x = time_now / time_end;
		return startx + (dif - startx) * -4 * (x * x - x);
	}


	//3点を通る直線グラフ
	double graph3(double x0, double x1, double x2, double t1, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1 + x0;
		}
		else{
			return (x2 - x1) * (t_now - t1) / (t_end - t1) + x1;
		}
	}

	//4点を通る直線グラフ
	double graph4(double x0, double x1, double x2, double x3, double t1, double t2, double t_now, double t_end){
		if (t_now < t1){
			return (x1 - x0) * t_now / t1 + x0;
		}
		else if (t_now < t2){
			return (x2 - x1) * (t_now - t1) / (t2 - t1) + x1;
		}
		else{
			return (x3 - x2) * (t_now - t2) / (t_end - t2) + x2;
		}
	}


	//イージング曲線

	/*
	t : 現在の時間
	b : 開始の値(開始時の座標やスケールなど)
	c : 開始と終了の値の差分
	d : Tweenの合計時間
	*/

	//イージング曲線 Cubic
	double ease_cubic_in(double t, double b, double c, double d){
		t /= d;
		return c*t*t*t + b;
	}

	double ease_cubic_out(double t, double b, double c, double d){
		t /= d;
		t = t - 1;
		return c*(t*t*t + 1) + b;
	}

	double ease_cubic_inout(double t, double b, double c, double d){
		t /= d / 2.0;
		if (t < 1){
			return c / 2.0*t*t*t + b;
		}
		else{
			t = t - 2;
			return c / 2.0 * (t*t*t + 2) + b;
		}
	}


	//イージング曲線 Sinusoidal
	double ease_sin_in(double t, double b, double c, double d){
		return -c * cos(t / d * (PI / 2.0)) + c + b;
	}

	double ease_sin_out(double t, double b, double c, double d){
		return c * sin(t / d * (PI / 2.0)) + b;
	}

	double ease_sin_inout(double t, double b, double c, double d){
		return -c / 2.0 * (cos(PI*t / d) - 1) + b;
	}

	//イージング曲線 Exponential
	double ease_exp_in(double t, double b, double c, double d){
		return c * pow(2.0, (10 * (t / d - 1))) + b;
	}

	double ease_exp_out(double t, double b, double c, double d){
		return c * (-(pow(2.0, (-10.0 * t / d))) + 1) + b;
	}

	double ease_exp_inout(double t, double b, double c, double d){
		t /= d / 2.0;
		if (t < 1)
			return c / 2.0 * pow(2.0, (10.0 * (t - 1))) + b;
		t = t - 1;
		return c / 2.0 * (-(pow(2.0, (-10 * t))) + 2) + b;
	}

	//イージング曲線 Circular
	double ease_sqrt_in(double t, double b, double c, double d){
		t /= d;
		return -c * (sqrt(1 - t*t) - 1) + b;
	}

	double ease_sqrt_out(double t, double b, double c, double d){
		t /= d;
		t = t - 1;
		return c * sqrt(1 - t*t) + b;
	}

	double ease_sqrt_inout(double t, double b, double c, double d){
		t /= d / 2.0;
		if (t < 1)
			return -c / 2.0 * (sqrt(1 - t*t) + 1);
		t = t - 2;
		return c / 2.0 * (sqrt(1 - t*t) + 1) + b;
	}



	//ベジェ曲線  p1->p2->p3  0<t<1
	double bz_curve(double p1, double p2, double p3, double t){
		double tp = 1 - t;
		return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
	}

	//ベジェ曲線  p1->p2->p3  nowtime, endtime
	double bz_curve(double p1, double p2, double p3, double nowt, double endt){
		double t = nowt / endt;
		double tp = 1 - t;
		return t*t*p3 + 2 * t*tp*p2 + tp*tp*p1;
	}

	//アニメーション用・＼／＼／＼／となるグラフ
	int Repeat(int frame, int loop_num)
	{
		--loop_num;
		frame = frame % (loop_num * 2);
		if (frame > loop_num)
			return loop_num * 2 - frame;
		else
			return frame;
	}

	//2次ベジエ曲線を計算する関数
	Vector2 GetBezier2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t)
	{
		Vector2 Result;
		// P = t^2*P0 + 2t(1-t)P1 + (1-t)^2P2
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*Control.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*Control.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//2次ベジエ曲線で制御点も通るように引きたい場合の制御点を返す関数
	Vector2 GetBezierPassC2(const Vector2 &Start, const Vector2 &End, const Vector2 &PassPoint)
	{
		Vector2 C;
		C.x = (4 * PassPoint.x - Start.x - End.x) / 2.0f;
		C.y = (4 * PassPoint.y - Start.y - End.y) / 2.0f;
		return C;
	}

	//Controlを通る2次ベジエ曲線を計算する関数
	Vector2 GetBezierCtrl2(const Vector2& Start, const Vector2& Control, const Vector2& End, float t)
	{
		Vector2 C;//Controlを通る2次ベジエ曲線の制御点
		Vector2 Result;
		C.x = (4 * Control.x - Start.x - End.x) / 2.0f;
		C.y = (4 * Control.y - Start.y - End.y) / 2.0f;
		Result.x = (t*t)*End.x + 2 * t*(1 - t)*C.x + (1 - t)*(1 - t)*Start.x;
		Result.y = (t*t)*End.y + 2 * t*(1 - t)*C.y + (1 - t)*(1 - t)*Start.y;
		return Result;
	}

	//3次ベジエ曲線を計算する関数
	Vector2 GetBezier3(const Vector2& Start, const Vector2& ControlPoint1, const Vector2& ControlPoint2, const Vector2& End, float t)
	{
		Vector2 Result;
		Result.x = (t*t*t)*End.x + 3 * t*t*(1 - t)*ControlPoint2.x
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.x + (1 - t)*(1 - t)*(1 - t)*Start.x;
		Result.y = (t*t*t)*End.y + 3 * t*t*(1 - t)*ControlPoint2.y
			+ 3 * t*(1 - t)*(1 - t)*ControlPoint1.y + (1 - t)*(1 - t)*(1 - t)*Start.y;
		return Result;
	}
	//便利関数

	//HSVをRGBに換算 直接関数の引数に渡す用
	DWORD GetColorHSV(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch (i){
		case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		return GetColor(rgb[0], rgb[1], rgb[2]);
	}

	//HSVをRGBに換算 intに保存する用
	int HSVtoRGB(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch (i){
		case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		return ((rgb[0]) << 16) + ((rgb[1]) << 8) + rgb[2];
	}

	//HSVでsetdrawbright
	void SetDrawBrightHSV(int h, int s, int v){
		float f;
		int i, p, q, t;
		int rgb[3];

		i = ((int)floor(h / 60.0f)) % 6;
		f = (float)(h / 60.0f) - (float)floor(h / 60.0f);
		p = (int)(v * (1.0f - (s / 255.0f)));
		q = (int)(v * (1.0f - (s / 255.0f) * f));
		t = (int)(v * (1.0f - (s / 255.0f) * (1.0f - f)));

		switch (i){
		case 0: rgb[0] = v; rgb[1] = t; rgb[2] = p; break;
		case 1: rgb[0] = q; rgb[1] = v; rgb[2] = p; break;
		case 2: rgb[0] = p; rgb[1] = v; rgb[2] = t; break;
		case 3: rgb[0] = p; rgb[1] = q; rgb[2] = v; break;
		case 4: rgb[0] = t; rgb[1] = p; rgb[2] = v; break;
		case 5: rgb[0] = v; rgb[1] = p; rgb[2] = q; break;
		}

		SetDrawBright(rgb[0], rgb[1], rgb[2]);
	}

	//0xXXXXXXでSetDrawBrightする関数
	void SetDrawBrightInt(int col){
		SetDrawBright(col >> 16, (col >> 8) & (0x00FF), col & 0x0000FF);
	}

	//自分の角度,相手の角度 2角の関係を返す　時計回り側に動いたほうが近ければ1 そうでなければ-1
	int abs_angle(double angle1, double angle2){
		if (sin(angle2 - angle1) > 0){
			return 1;
		}
		else{
			return -1;
		}
	}

	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  tarxとの差がerange以下でtarx = xにする
	void moverate(double &x, double tarx, double rate, double erange)
	{
		x = x * (1 - rate) + tarx * rate;
		if (abs(x - tarx) < erange){
			x = tarx;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moverate(double &x, double &y, double tarx, double tary, double rate, double erangedist)
	{
		x = x * (1 - rate) + tarx * rate;
		y = y * (1 - rate) + tary * rate;
		if (dist(x, y, tarx, tary) < erangedist){
			x = tarx;
			y = tary;
		}
	}
	//内分した点に移動、rateは自分から相手方向への移動率 0.0 - 1.0  distが0.5以下でtarP = Pにする
	void moverate(Vector2 &v2, const Vector2 &tarv2, double rate, double erangedist)
	{
		v2.x = v2.x * (1 - rate) + tarv2.x * rate;
		v2.y = v2.y * (1 - rate) + tarv2.y * rate;
		if (dist(v2.x, v2.y, tarv2.x, tarv2.y) < erangedist){
			v2 = tarv2;
		}
	}


	//原点との距離を返す
	double dist(double x, double y){
		return sqrt(x*x + y*y);
	}

	//2点の距離を返す
	double dist(double x1, double y1, double x2, double y2){
		return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
	}

	//2点の距離の2乗を返す
	double distSqr(double x1, double y1, double x2, double y2){
		return (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	}


	//rateとcoolのセットのcoolを更新・boolを返す
	bool coolcount(int &cool){
		if (cool > 0){
			cool--;
			return false;
		}
		else{
			cool = 0;
			return true;
		}
	}

	//基準・振幅・周期(秒)・経過フレームを指定してsinを返す
	double sinsec(double base, double a, double t, double frame){
		return base + a * sin(2 * PI * frame / 60.0 / t);
	}

	//スクリーンの中心を返す
	Vector2 GetScreenCenter(){
		return Vector2(ScreenWidth / 2, ScreenHeight / 2);
	}

	//スクリーンからどれだけ外にいるかを計算し、一定以上だったらfalseを返す
	bool IsAlivePos(const Vector2 &pos){
		double length = 0.0;
		if (pos.x < 0){
			length += -pos.x;
		}
		if (pos.x > ScreenWidth){
			length += pos.x - ScreenWidth;
		}
		if (pos.y < 0){
			length += -pos.y;
		}
		if (pos.y > ScreenHeight){
			length += pos.y - ScreenHeight;
		}
		return length < AliveLength;
	}

	//ランダムな2文字の大文字アルファベットを返す
	std::string randStr(){
		std::string str;
		for (int i = 0; i < 2; i++){
			str += (char)((int)'A' + GetRand(25));
		}
		return str;
	}
	//ランダムな2文字の大文字アルファベットを返す
	std::string randStr(int loop){
		std::string str;
		for (int i = 0; i < loop; i++){
			str += (char)((int)'A' + GetRand(25));
		}
		return str;
	}


	Vector2 ease_v2_sin(int eFrame, int reqFrame, Vector2 start, Vector2 end){
		if (eFrame < 0){
			return start;
		}
		else if (eFrame > reqFrame){
			return end;
		}
		else{
			double t = 1.0 * sin((double)eFrame / reqFrame * (PI / 2.0));
			Func::moverate(start, end, t);
			return start;
		}
	}


	//こんな感じで使う
	//Func::randStrVec({ "circle32", "lack_rect32" })
	std::string randStrVec(std::vector<std::string> strVec){
		int r = Random::Rand(strVec.size() - 1);
		return strVec[r];
	}

}//end of namespace Func

