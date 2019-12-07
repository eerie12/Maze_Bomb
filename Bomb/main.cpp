/*
	���H�Q�[��
	�A�C�e�����g�p�\�Ȗ��H�Q�[�����쐬���܂����B
	���߂�ꂽ���ȊO�A�A�C�e�����g���āA�F��ȕ����ŃS�[���ɒH�蒅�����Ƃ��\�ɂ��܂����B
	Player,�ǂ��󂷔��e(Player�̍U��),�������A�C�e��,�ǉ����A�C�e��,���e�̒����𑝂₷�A�C�e�����쐬���܂����B

*/

#include<iostream>
#include <conio.h>
#include<time.h>
using namespace std;
#define Maze Maze
#define pPlayer pPlayer
#define pPlayerPos tPlayerPos
#define pStartPos tStartPos
#define pEndPos tEndPos
#define pBombArr tBombPos
#define pBombCount pBombCount
#define cItemType cItemType





/*
0: ��
1: ��
2: start
3: end
4: ���e
5: �p���[�A�C�e��
6: �ǉ����A�C�e��
7: �����A�C�e��
*/

struct _tagPoint
{
	int x;
	int y;
};

//typedef:type���Ē�`����@�\
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint tPos;
	bool      bWallPush;
	bool      bPushOnOff;
	bool      bTransparency;
	int       iBombPower;

}PLAYER, *PPLAYER;


void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos);//���H�ݒu
void Output(char Maze[21][21], PPLAYER pPlayer);//Draw
void MoveUp(char Maze[21][21], PPLAYER pPlayer);//Player_UP
void MoveDown(char Maze[21][21], PPLAYER pPlayer);//Player_DOWN
void MoveRight(char Maze[21][21], PPLAYER pPlayer);//Player_Right
void MoveLeft(char Maze[21][21], PPLAYER pPlayer);//Player_Left
void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char clnput);//Player_MOVE
void CreateBomb(char Maze[21][21], const PPLAYER nPlayer, PPOINT pBombArr, int*pBombCount);//��������鏈��
void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int*pBombCount);//����������
bool AddItem(char cItemType, PPLAYER pPlayer);






int main()
{
	srand((unsigned)time(0));

	//	20��20���H�����
	char strMaze[21][21] = {};

	PLAYER tPlayer = {};
	POINT tStartPos;
	POINT tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;
	POINT tBombPos[5];



	//���H��ݒ�@
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);


	while (true)
	{

		system("cls");
		//���H���o��
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "����" << endl;
			break;
		}

		cout << "t : ���e�ݒu  u : ���e�X�E�B�b�`  i : �ǉ��� ON/OFF" << endl;
		cout << "w : ��  s : ��  a : ��  d : �E  �I�� : " << endl;
		cout << endl;
		cout << "���ɒH�蒅������A�S�[���ɂȂ�܂��B" << endl;
		char cInput = _getch();



		if (cInput == 'q' || cInput == 'Q')
			break;
		else if (cInput == 't' || cInput == 'T')
		{
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else if (cInput == 'u' || cInput == 'U')
		{
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}
		else if (cInput == 'i' || cInput == 'I')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}

		MovePlayer(strMaze, &tPlayer, cInput);




	}


	return 0;
	//int key = 0;
	//cin>>key;

}
//--------------------------
//���[�U�[�֐�
//--------------------------

//--------------------------
//���H��ݒ�
//--------------------------
void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111100000000");
	strcpy_s(Maze[2], "00100010000111111100");
	strcpy_s(Maze[3], "01100010000000000100");
	strcpy_s(Maze[4], "01000011110001111100");
	strcpy_s(Maze[5], "01000000001111000000");
	strcpy_s(Maze[6], "01100000001000000000");
	strcpy_s(Maze[7], "00100000001111111000");
	strcpy_s(Maze[8], "00001110000000001000");
	strcpy_s(Maze[9], "01111011111111111000");
	strcpy_s(Maze[10], "01000000000000000000");
	strcpy_s(Maze[11], "01111100111111100000");
	strcpy_s(Maze[12], "00000111100000111110");
	strcpy_s(Maze[13], "01111100000000000010");
	strcpy_s(Maze[14], "01000000001111111110");
	strcpy_s(Maze[15], "01111110011000000000");
	strcpy_s(Maze[16], "0000001001000000000");
	strcpy_s(Maze[17], "01111110011111000000");
	strcpy_s(Maze[18], "01000000000001100000");
	strcpy_s(Maze[19], "11000000000000111113");

}

//--------------------------
//���H�̏o��
//--------------------------
void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (Maze[i][j] == '4')
				cout << "��";
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "��";
			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";
			else if (Maze[i][j] == '5')
				cout << "��";
			else if (Maze[i][j] == '6')
				cout << "��";
			else if (Maze[i][j] == '7')
				cout << "��";

		}
		cout << endl;
	}

	cout << "���e�̃p���[ : " << pPlayer->iBombPower << endl;
	cout << "�ǂ��� : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "�ǉ��� : ";
	if (pPlayer->bWallPush)
	{
		cout << "�\ /";
		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}


	else
		cout << "�s�\ / OFF" << endl;


}

//--------------------------
//Player�̈ړ�����
//--------------------------
void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char clnput)
{
	switch (clnput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}

}

bool AddItem(char cItemType, PPLAYER pPlayer)
{
	if (cItemType == '5')
	{
		if (pPlayer->iBombPower < 5)//���e�̃p���[����
			++pPlayer->iBombPower;
		return true;
	}
	else if (cItemType == '6')
	{
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;
		return true;
	}
	else if (cItemType == '7')
	{
		pPlayer->bTransparency = true;
		return true;
	}
	return false;

}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{


		//�ǃ`�F�b�N
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			--pPlayer->tPos.y;
		}

		//�ǉ����`�F�b�N && �オ�ǂ̏ꍇ
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			//�ǉ����`�F�b�N ON�B
			if (pPlayer->bPushOnOff)
			{
				//�オ0���傫���ꍇ�AIndex����B
				if (pPlayer->tPos.y - 2 >= 0)
				{
					//�オ���̏ꍇ�ǉ����\->���Ȃ̂����`�F�b�N�B(�ǂ������ꍇ)
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.y;
					}
					//���������ꍇ
					else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1')
					{
						//��̏�͕ǂɂ�
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						//��͓��ɂ���B
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						//Player�𓮂����B
						--pPlayer->tPos.y;

					}

				}
				else if (pPlayer->bTransparency)
				{
					--pPlayer->tPos.y;

				}

			}
			//�ǉ���OFF�̏ꍇ
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.y;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}


	}

}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		//�ǃ`�F�b�N
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			++pPlayer->tPos.y;
		}

		//�ǉ����`�F�b�N && �����ǂ̏ꍇ
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			//�ǉ����`�F�b�N ON�B
			if (pPlayer->bPushOnOff)
			{
				//����0���傫���ꍇ�AIndex����B
				if (pPlayer->tPos.y + 2 < 20)
				{
					//�������̏ꍇ�ǉ����\->���Ȃ̂����`�F�b�N�B(�ǂ������ꍇ)
					if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.y;
					}
					//���������ꍇ
					else if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '1')
					{
						//���̉��͕ǂɂ�
						Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						//���͓��ɂ���B
						Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						//Player�𓮂����B
						++pPlayer->tPos.y;

					}

				}
				else if (pPlayer->bTransparency)
				{
					++pPlayer->tPos.y;

				}

			}
			//�ǉ���OFF�̏ꍇ
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.y;
		}

		else if (pPlayer->bTransparency)
			++pPlayer->tPos.y;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

	}

}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		//�ǃ`�F�b�N
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			++pPlayer->tPos.x;
		}

		//�ǉ����`�F�b�N && �E���ǂ̏ꍇ
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			//�ǉ����`�F�b�N ON�B
			if (pPlayer->bPushOnOff)
			{
				//�E��0���傫���ꍇ�AIndex����B
				if (pPlayer->tPos.x + 2 >= 0)
				{
					//�E�����̏ꍇ�ǉ����\->���Ȃ̂����`�F�b�N�B(�ǂ������ꍇ)
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '0')
					{
						if (pPlayer->bTransparency)
							++pPlayer->tPos.x;
					}
					//���������ꍇ
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '1')
					{
						//�E�̉E�͕ǂɂ�
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						//�E�͓��ɂ���B
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						//Player�𓮂����B
						++pPlayer->tPos.x;

					}

				}
				else if (pPlayer->bTransparency)
				{
					++pPlayer->tPos.x;

				}

			}
			//�ǉ���OFF�̏ꍇ
			else if (pPlayer->bTransparency)
				++pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			++pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

	}

}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		//�ǃ`�F�b�N
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			--pPlayer->tPos.x;
		}

		//�ǉ����`�F�b�N && �オ�ǂ̏ꍇ
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			//�ǉ����`�F�b�N ON�B
			if (pPlayer->bPushOnOff)
			{
				//����0���傫���ꍇ�AIndex����B
				if (pPlayer->tPos.x - 2 >= 0)
				{
					//�������̏ꍇ�ǉ����\->���Ȃ̂����`�F�b�N�B(�ǂ������ꍇ)
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '0')
					{
						if (pPlayer->bTransparency)
							--pPlayer->tPos.x;
					}
					//���������ꍇ
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '1')
					{
						//���̍��͕ǂɂ�
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						//���͓��ɂ���B
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						//Player�𓮂����B
						--pPlayer->tPos.x;

					}

				}
				else if (pPlayer->bTransparency)
				{
					--pPlayer->tPos.x;

				}

			}
			//�ǉ���OFF�̏ꍇ
			else if (pPlayer->bTransparency)
				--pPlayer->tPos.x;
		}

		else if (pPlayer->bTransparency)
			--pPlayer->tPos.x;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
		{
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
		}

	}

}
//--------------------------
//���e�̏���
//--------------------------
//�|�C���^�[�ϐ���const�ō��ƒl�̕ύX���ł��Ȃ��Ȃ�B
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int*pBombCount)
{
	if (*pBombCount == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;



	for (int i = 0; i < *pBombCount; i++)
	{
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	++(*pBombCount);
	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{



	for (int i = 0; i < *pBombCount; i++)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;

		}
		for (int j = 0; j <= pPlayer->iBombPower; j++)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
				{
					//Item�h���b�v�̊m��
					if (rand() % 100 < 20)
					{
						int iPersent = rand() % 100;
						if (iPersent < 40)
						{
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
						}
						else if (iPersent < 70)
						{
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						}
						else
						{
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
						}

					}
					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}
				//Player�����e�ɓ����Start�ɖ߂��B
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;

				}

			}
			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
				{
					//Item�h���b�v�̊m��
					if (rand() % 100 < 20)
					{
						int iPersent = rand() % 100;
						if (iPersent < 40)
						{
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
						}
						else if (iPersent < 70)
						{
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						}
						else
						{
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
						}

					}
					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';

				}

				//Player�����e�ɓ����Start�ɖ߂��B
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;

				}
			}
			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
				{
					//Item�h���b�v�̊m��
					if (rand() % 100 < 20)
					{
						int iPersent = rand() % 100;
						if (iPersent < 40)
						{
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
						}
						else if (iPersent < 70)
						{
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						}
						else
						{
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
						}

					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';

				}


				//Player�����e�ɓ����Start�ɖ߂��B
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;

				}
			}
			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
				{
					//Item�h���b�v�̊m��
					if (rand() % 100 < 20)
					{
						int iPersent = rand() % 100;
						if (iPersent < 40)
						{
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
						}
						else if (iPersent < 70)
						{
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						}
						else
						{
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
						}

					}
					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';

				}


				//Player�����e�ɓ����Start�ɖ߂��B
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;

				}
			}
		}


	}
	*pBombCount = 0;

}


