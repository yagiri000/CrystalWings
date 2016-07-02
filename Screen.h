#pragma once

#include <string>

class Screen{
public:
	//�V���O���g��
	Screen& operator=(const Screen& a) = delete;
	Screen(const Screen& a) = delete;
	static Screen& get();

	//�X�N���[���T�C�Y
	const int width;
	const int height;

	int afterImageAlpha;
	int screenShakeFrame;	//0�̊Ԃ̓X�N���[���͗h��Ȃ�
	int screenShakeDistance;
	int transitionFrame;
	int transitionFrameMax;

	//�X�N���[��
	int mainScreen;		//��ɂ���ɕ`�悷��
	int afterImageScreen;//�c���p���C���[
	int tmpScreen;
	int subScreen; //�V�F�[�_�[�K�p�p

	static void setTransition(int frame);

	// �K�E�X�t�B���^�[���{��
	static void Gauss(int pal_1 = 8, int pal_2 = 1000);

	// HSB�t�B���^�[���{��
	static void HSB(int type, int hue, int saturation, int bright);

	// �K�����]�t�B���^�[���{��
	static void Invert();

	// Level�t�B���^�[���{��
	static void Level(int min, int max, int gamma, int afterMin, int afterMax);

	// �O���f�[�V�����}�b�v�t�B���^�[���{��
	static void GradiendMap(int handle);

	//�`��J�n
	static void DrawStart();

	//�V�F�[�_�[�Ƃ��K�p���鎞�p
	static void SetDrawScreenSub();

	//�V�F�[�_�[�Ƃ��K�p�������Ɨp
	static void SetDrawScreenMain();

	//�`��I���E�t���b�v
	static void DrawEnd();

	//�X�N���[���h���ݒ�
	static void SetShake(int frame, int distance);

	//�c�����C���[�Ɍ��݂̃��C���[���R�s�[
	static void SetAfterImageScreen();

	//�c�����C���[��`��
	static void DrawAfterImageScreen();

private:
	Screen();
	void init();
};


