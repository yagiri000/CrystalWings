#pragma once
#include "Resource.h"
#include "Func.h"


void GraphBullet::load(){
	LoadToMap("circle32");
	LoadToMap("tilt_rect32");
}

void GraphHue::load(){
	LoadToMap("dot32");
	LoadToMap("rect32");
	LoadToMap("circle32");
	LoadToMap("capsule64_32");
	LoadToMap("lack_rect32");
	LoadToMap("rhombus128_32");
	LoadToMap("rhombus64_32");
	LoadToMap("ring32");
	LoadToMap("ring64");
	LoadToMap("r_tri16_32");
	LoadToMap("shape01_32"); 
	LoadToMap("tri32");
	LoadToMap("tri64");
	LoadToMap("tilt_rect32");
	LoadToMap("gra32");
}

void Graph::load(){
	LoadToMap("dot32");
	LoadToMap("rect32");
	LoadToMap("circle32");
	LoadToMap("capsule64_32");
	LoadToMap("lack_rect32");
	LoadToMap("rhombus128_32");
	LoadToMap("rhombus64_32");
	LoadToMap("ring32");
	LoadToMap("ring64");
	LoadToMap("r_tri16_32");
	LoadToMap("shape01_32");
	LoadToMap("tri32");
	LoadToMap("tri64");
	LoadToMap("back00");
	LoadToMap("back01");
	LoadToMap("gra00");
	LoadToMap("player");
	LoadToMap("playerBullet");
	LoadToMap("mini_title");
	LoadToMap("title");
	LoadToMap("result_back");
	LoadToMap("invincible");
}

void GraphDiv::load(){
	LoadToMap("box_blank", 16, 4, 4, 64, 64);
	LoadToMap("cir_blank", 16, 4, 4, 64, 64);
	LoadToMap("title_str", 8, 1, 8, 512, 64);
	LoadToMap("title_str_selected", 8, 1, 8, 512, 64);
	LoadToMap("pause_str", 8, 1, 8, 512, 64);
	LoadToMap("pause_str_selected", 8, 1, 8, 512, 64);
}

void Font::load(){
	LoadFont("SegoeUI18", "Segoe UI", 18, 3);

	std::string ttfName = "ostrich-regular.ttf";
	std::string fontName = "Ostrich Sans";
	LoadFont("OS12", ttfName.c_str(), fontName.c_str(), 12, 9);
	LoadFont("OS14", ttfName.c_str(), fontName.c_str(), 14, 9);
	LoadFont("OS18", ttfName.c_str(), fontName.c_str(), 18, 7);
	LoadFont("OS50", ttfName.c_str(), fontName.c_str(), 50, 9);
}

void Sound::load(){
	LoadToMap("chari05", 0.3, 30);
	LoadToMap("cut00");
	LoadToMap("mybomb01");
	LoadToMap("mybomb02");
	LoadToMap("mecha03");
	LoadToMap("main_bgm");
	LoadToMap("title_bgm");
	LoadToMap("pause_in");
	LoadToMap("pause_out");
	LoadToMap("title_out"); 
	LoadToMap("enemy_shot"); 
	LoadToMap("bomb_shoot");
	LoadToMap("title_cursor_move");
}




GraphBullet::GraphBullet(){
}

GraphBullet& GraphBullet::get(){
	static GraphBullet inst;
	return inst;
}

void GraphBullet::LoadToMap(std::string name){
	std::string loadname = "Images/" + name;
	HandleArray hArray;
	int tmp_handle = LoadGraph((loadname + ".png").c_str());
	int sizeX, sizeY;
	GetGraphSize(tmp_handle, &sizeX, &sizeY);
	for (int i = 0; i < colorNum; i++){
		hArray.arr[i] = MakeScreen(sizeX, sizeY, TRUE);
		SetDrawScreen(hArray.arr[i]);
		int hue = i * 360 / colorNum;
		int easeV = 0;
		if (abs(hue - 60) < 15){
			easeV = 1.5 * (15 - abs(hue - 60));
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		Func::SetDrawBrightHSV(hue, 220, 255 - easeV);
		//5回描画することで半透明の黒っぽい部分を消す
		for (int i = 0; i < 5; i++){
			DrawGraph(0, 0, tmp_handle, TRUE);
		}
	}
	SetDrawBright(255, 255, 255);

	handlemap.emplace(name, hArray);
}

int GraphBullet::handle(std::string name, int num){
	if (num < 0){
		num %= colorNum;
		num += colorNum;
	}
	else{
		num %= colorNum;
	}
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphBullet::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}

int GraphBullet::handled(std::string name, double hue){
	hue = fmod(hue, 1.0);
	if (hue < 0.0){
		hue += 1.0;
	}
	int num = (int)(hue * colorNum) % colorNum;
	if (num < 0){
		std::string log = "GraphBullet::handled内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
		num = 0;
	}
	if (num >= 36){
		num = 36;
	}

	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphBullet::handled内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}



GraphHue::GraphHue(){

}

GraphHue& GraphHue::get(){
	static GraphHue inst;
	return inst;
}

void GraphHue::LoadToMap(std::string name){
	std::string loadname = "Images/" + name;
	HandleArray hArray;
	int tmp_handle = LoadGraph((loadname + ".png").c_str());
	int sizeX, sizeY;
	GetGraphSize(tmp_handle, &sizeX, &sizeY);
	for (int i = 0; i < colorNum; i++){
		hArray.arr[i] = MakeScreen(sizeX, sizeY, TRUE);
		SetDrawScreen(hArray.arr[i]);
		int hue = i * 360 / colorNum;
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		Func::SetDrawBrightHSV(hue, 140, 255);
		//5回描画することで半透明の黒っぽい部分を消す
		for (int i = 0; i < 5; i++){
			DrawGraph(0, 0, tmp_handle, TRUE);
		}
	}
	SetDrawBright(255, 255, 255);

	handlemap.emplace(name, hArray);
}

int GraphHue::handle(std::string name, int num){
	if (num < 0){
		num %= colorNum;
		num += colorNum;
	}
	else{
		num %= colorNum;
	}
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphHue::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}

int GraphHue::handled(std::string name, double hue){
	hue = fmod(hue, 1.0);
	if (hue < 0.0){
		hue += 1.0;
	}
	int num = (int)(hue * colorNum) % colorNum;
	if (num < 0){
		std::string log = "GraphHue::handled内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
		num = 0;
	}
	if (num >= 36){
		num = 36;
	}

	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphHue::handled内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}



Graph::Graph(){
}

Graph& Graph::get(){
	static Graph inst;
	return inst;
}

//ハンドル取得
int Graph::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Graph::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

void Graph::LoadToMap(std::string name){
	int gh;
	std::string loadname = "Images/" + name;
	gh = LoadGraph((loadname + ".png").c_str());
	if (gh != -1){
		handlemap.emplace(name, gh);
		return;
	}
	gh = LoadGraph((loadname + ".jpg").c_str());
	if (gh != -1){
		handlemap.emplace(name, gh);
		return;
	}
}



GraphDiv::GraphDiv(){
}
GraphDiv& GraphDiv::get(){
	static GraphDiv inst;
	return inst;
}

//ハンドル取得
int GraphDiv::handle(std::string name, int num){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "GraphDiv::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name).arr[num];
}


void GraphDiv::LoadToMap(std::string name, int AllNum, int XNum, int YNum, int XSize, int YSize){
	std::string loadname = "Images/" + name;
	gh_array gh_array_;
	LoadDivGraph((loadname + ".png").c_str(), AllNum, XNum, YNum, XSize, YSize, &gh_array_.arr[0]);
	handlemap.emplace(name, gh_array_);
}



Font::Font(){
}

Font& Font::get(){
	static Font inst;
	return inst;
}

int Font::operator()(std::string name){
	return get().handlemap.at(name);
}

//ハンドル取得
int Font::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Font::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap.at(name);
}

Font& font = Font::get();

//登録名・ファイルのパス・フォントの名前を指定（PCに元から入っているもの）
//ex ("HG96", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string font_name, int fontsize, int thick){
	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}

//登録名・ファイルのパス・フォントの名前を指定
//ex ("HG96", "hoge.ttf", "Hogeman's_Font", 96, 5)
void Font::LoadFont(std::string reg_name, std::string file_path, std::string font_name, int fontsize, int thick){

	file_path = "Fonts/" + file_path;
	const char* filename = file_path.c_str();

	// ファイルのサイズを得る
	int FontFileSize = FileRead_size(filename);
	// フォントファイルを開く
	int FontFileHandle = FileRead_open(filename);
	// フォントデータ格納用のメモリ領域を確保
	void *Buffer = malloc(FontFileSize);
	// フォントファイルを丸ごとメモリに読み込む
	FileRead_read(Buffer, FontFileSize, FontFileHandle);
	// AddFontMemResourceEx引数用
	DWORD font_num = 0;
	// メモリに読み込んだフォントデータをシステムに追加
	if (AddFontMemResourceEx(Buffer, FontFileSize, NULL, &font_num) != 0){}
	else
	{
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}

	int tmp_handle = CreateFontToHandle(font_name.c_str(), fontsize, thick, DX_FONTTYPE_ANTIALIASING_4X4);
	handlemap.emplace(reg_name.c_str(), tmp_handle);
}



SoundHandle::SoundHandle() :
handle(0),
volume(0),
play_cool(0),
play_rate(0)
{
}

SoundHandle::SoundHandle(int handle_, double volume_, int play_rate_) :
handle(handle_),
volume(volume_),
play_cool(0),
play_rate(play_rate_)
{
}

void SoundHandle::SetVolume(double master)
{
	ChangeVolumeSoundMem(master * volume * 255.0, handle);
}

Sound::Sound(){
}

Sound& Sound::get(){
	static Sound inst;
	return inst;
}

//ハンドルを取得
int Sound::handle(std::string name){
	if (get().handlemap.find(name) == get().handlemap.end()){
		std::string log = "Sound::handle内部で読み込みエラー発生\n読み込もうとしたstring : " + name;
		MessageBox(NULL, log.c_str(), "", MB_OK);
	}
	return get().handlemap[name].handle;
}

//一回だけ再生
void Sound::playone(std::string name){
	auto &a = get().handlemap[name];
	if (a.play_cool <= 0){
		PlaySoundMem(get().handle(name), DX_PLAYTYPE_BACK);
		a.play_cool = a.play_rate;
	}
}

//ループ再生
void Sound::playloop(std::string name){
	PlaySoundMem(get().handle(name), DX_PLAYTYPE_LOOP);
}

//BGM再生 BGMは常時一つだけ
void Sound::playbgm(std::string name){
	StopSoundMem(get().bgmhandle);
	get().bgmhandle = get().handle(name);
	PlaySoundMem(get().bgmhandle, DX_PLAYTYPE_LOOP);
}

//BGM停止
void Sound::stopbgm(){
	StopSoundMem(get().bgmhandle);
}

//再生中の音をすべて停止
void Sound::stopall(){
	for (auto &i : get().handlemap){
		StopSoundMem(i.second.handle);
	}
}

//指定した音の再生を停止
void Sound::stopone(std::string name){
	StopSoundMem(get().handle(name));
}

//ボリュームをセット
void Sound::setvolume(double master)
{
	get().masterVolume = master;
	for (auto &i : get().handlemap){
		i.second.SetVolume(get().masterVolume);
	}
}

//再生間隔フレームを更新
void Sound::update()
{
	for (auto &i : get().handlemap){
		if (i.second.play_cool > 0){
			i.second.play_cool--;
		}
	}
}

void Sound::LoadToMap(std::string name){
	int tmphandle;
	std::string loadname = "Sounds/" + name;
	std::string arr[3] = { ".wav", ".ogg", ".mp3" };
	for (int i = 0; i < 3; i++){
		tmphandle = LoadSoundMem((loadname + arr[i]).c_str());
		if (tmphandle != -1){
			handlemap.emplace(name, SoundHandle(tmphandle));
			return;
		}
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
	//assert(1 == 0 && "sound file is not exist" && name.c_str());
}

void Sound::LoadToMap(std::string name, double volume, int play_rate){
	int tmphandle;
	std::string loadname = "Sounds/" + name;
	std::string arr[3] = { ".wav", ".ogg", ".mp3" };
	for (int i = 0; i < 3; i++){
		tmphandle = LoadSoundMem((loadname + arr[i]).c_str());
		if (tmphandle != -1){
			handlemap.emplace(name, SoundHandle(tmphandle, volume, play_rate));
			return;
		}
	}
	OutputDebugString(("\n" + name + " is not exist\n").c_str());
}