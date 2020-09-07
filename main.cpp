//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "DxLib.h"

#define GAME_WIDTH			 960	//��ʂ̉��̑傫��
#define GAME_HEIGHT			 640	//��ʂ̏c�̑傫��
#define GAME_COLOR			  32	//��ʂ̃J���[�r�b�g

#define GAME_WINDOW_BAR		0				//�^�C�g���o�[�̓f�t�H���g�ɂ���
#define GAME_WINDOW_NAME	"Dxlib_Movie"	//�E�B���h�E�̃^�C�g��

//���������� �v���O�����ǉ��������� ����������������������������������������

//MOVIE�t�H���_�ƁAmp4�t�@�C�����A�ǉ����ĉ�����
#define MOVIE_PATH			".\\MOVIE\\neko.mp4"	//����̃p�X

int handle = -1;	//����̃n���h��

//���������� �v���O�����ǉ������܂� ����������������������������������������

//########## �v���O�����ōŏ��Ɏ��s�����֐� ##########
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);				//log.txt���o�͂��Ȃ�
	ChangeWindowMode(TRUE);								//�E�B���h�E���[�h�ɐݒ�
	SetGraphMode(GAME_WIDTH, GAME_HEIGHT, GAME_COLOR);	//�w��̐��l�ŃE�B���h�E��\������
	SetWindowStyleMode(GAME_WINDOW_BAR);				//�^�C�g���o�[�̓f�t�H���g�ɂ���
	SetMainWindowText(TEXT(GAME_WINDOW_NAME));			//�E�B���h�E�̃^�C�g���̕���
	SetAlwaysRunFlag(TRUE);								//��A�N�e�B�u�ł����s����

	if (DxLib_Init() == -1) { return -1; }	//�c�w���C�u��������������

	//���������� �v���O�����ǉ��������� ����������������������������������������

	//����̓ǂݍ���
	handle = LoadGraph(MOVIE_PATH);

	//���������� �v���O�����ǉ������܂� ����������������������������������������

	//�������[�v
	while (TRUE)
	{
		if (ProcessMessage() != 0) { break; }	//���b�Z�[�W�����̌��ʂ��G���[�̂Ƃ��A�����I��
		if (ClearDrawScreen() != 0) { break; }	//��ʂ������ł��Ȃ������Ƃ��A�����I��

		//���������� �v���O�����ǉ��������� ����������������������������������������

		if (GetMovieStateToGraph(handle) == 0)
		{
			SeekMovieToGraph(handle, 0);	//����̍Đ��o�[���ŏ�����ɂ���
			PlayMovieToGraph(handle);		//������Đ���Ԃɂ���

			//����̉��𒲐�����(0�������`255������̉���)
			ChangeMovieVolumeToGraph(127, handle);
		}

		//�^�C�g������`��
		//DrawGraph(0, 0, handle, FALSE);

		//������E�B���h�E�T�C�Y�ƍ��킹�����I
		DrawExtendGraph(0, 0, GAME_WIDTH, GAME_HEIGHT, handle, FALSE);

		//���������� �v���O�����ǉ������܂� ����������������������������������������


		DrawString(0, 0, "������Đ����Ă��܂��E�E�E", GetColor(255, 255, 255));

		ScreenFlip();		//���j�^�̃��t���b�V�����[�g�̑����ŗ���ʂ��ĕ`��
	}

	DxLib_End();	//�c�w���C�u�����g�p�̏I������

	//���������� �v���O�����ǉ��������� ����������������������������������������

	DeleteGraph(handle);	//����̍폜

	//���������� �v���O�����ǉ������܂� ����������������������������������������

	return 0;
}