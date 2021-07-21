#pragma once
#include <DxLib.h>
#include <math.h>
#include "Init.h"

// �v���C���[�֌W�̒�`
#define PLAYER_MOVE_SPEED			30.0f		// �ړ����x
#define PLAYER_ANGLE_SPEED			0.2f		// �p�x�ω����x
#define PLAYER_MAX_HITCOLL			2048		// ��������R���W�����|���S���̍ő吔
#define PLAYER_ENUM_DEFAULT_SIZE	800.0f		// ���͂̃|���S�����o�Ɏg�p���鋅�̏����T�C�Y
#define PLAYER_HIT_WIDTH			100.0f		// �����蔻��J�v�Z���̔��a
#define PLAYER_HIT_HEIGHT			700.0f		// �����蔻��J�v�Z���̍���
#define PLAYER_HIT_TRYNUM			16		// �ǉ����o�������̍ő厎�s��
#define PLAYER_HIT_SLIDE_LENGTH		5.0f		// ��x�̕ǉ����o�������ŃX���C�h�����鋗��

// �X�e�[�W�֌W�̒�`
#define STAGECOLLOBJ_MAXNUM			256		// �ǉ��̃R���W�����I�u�W�F�N�g�̍ő吔

//�v���g�^�C�v�錾
//bool Sph_hit_check(Sph sp[]);
//void Sph_hit();
//void Model_hit_check();
//void Model_hit();
void Ground_model_hit();
void Ground_model_hit_check(VECTOR MoveVector);
struct StageModelHit
{
	int i, j, k;						// �ėp�J�E���^�ϐ�
	int MoveFlag;						// ���������Ɉړ��������ǂ����̃t���O( �O:�ړ����Ă��Ȃ�  �P:�ړ����� )
	int HitFlag;						// �|���S���ɓ����������ǂ������L�����Ă����̂Ɏg���ϐ�( �O:�������Ă��Ȃ�  �P:�������� )
	MV1_COLL_RESULT_POLY_DIM HitDim[STAGECOLLOBJ_MAXNUM + 1];			// �v���C���[�̎��͂ɂ���|���S�������o�������ʂ��������铖���蔻�茋�ʍ\����
	int HitDimNum;						// HitDim �̗L���Ȕz��v�f��
	int KabeNum;						// �ǃ|���S���Ɣ��f���ꂽ�|���S���̐�
	int YukaNum;						// ���|���S���Ɣ��f���ꂽ�|���S���̐�
	MV1_COLL_RESULT_POLY* Kabe[PLAYER_MAX_HITCOLL];	// �ǃ|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* Yuka[PLAYER_MAX_HITCOLL];	// ���|���S���Ɣ��f���ꂽ�|���S���̍\���̂̃A�h���X��ۑ����Ă������߂̃|�C���^�z��
	MV1_COLL_RESULT_POLY* Poly;				// �|���S���̍\���̂ɃA�N�Z�X���邽�߂Ɏg�p����|�C���^( �g��Ȃ��Ă��ς܂����܂����v���O�����������Ȃ�̂ŁE�E�E )
	HITRESULT_LINE LineRes;				// �����ƃ|���S���Ƃ̓����蔻��̌��ʂ�������\����
	VECTOR OldPos;						// �ړ��O�̍��W	
	VECTOR NowPos;						// �ړ���̍��W
	//�ړ��x�N�g��
	VECTOR TargetMoveDirection;			// ���f���������ׂ������̃x�N�g��
	VECTOR movepos;

	VECTOR upvec = VGet(0.0f, 0.0f, 1.0f);
	VECTOR downvec = VGet(0.0f, 0.0f, -1.0f);
	VECTOR rightvec = VGet(1.0f, 0.0f, 0.0f);
	VECTOR leftvec = VGet(-1.0f, 0.0f, 0.0f);

};

extern StageModelHit st_model_hit;
