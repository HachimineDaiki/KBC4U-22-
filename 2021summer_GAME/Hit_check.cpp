#include <Dxlib.h>
#include <math.h>
#include "Hit_check.h"
#include "3Dmodel.h"
#include "Player.h"
#include "Camera.h"
#include "Init.h"

float p_vz = 0;
struct STAGE
{
	int		ModelHandle;				// �X�e�[�W�̃��f���n���h��
	int		CollObjBaseModelHandle;		// �R���W�������f���̔h�����n���h��
	int		CollObjModelHandle[STAGECOLLOBJ_MAXNUM];	// �X�e�[�W�ɔz�u����R���W�������f���̃n���h��
	int		CollObjNum;				// �X�e�[�W�ɔz�u���Ă���R���W�������f���̐�
};

STAGE stg;

//�����m�����蔻��
bool Sph_hit_check(Sph sp[], Sph ob) {
	sph[0].v.x = ob.pos.x - sp[0].pos.x;//x����
	sph[0].v.y = ob.pos.y - sp[0].pos.y;//y����
	sph[0].v.z = ob.pos.z - sp[0].pos.z;//z����

	s_dis = sph[0].v.x * sph[0].v.x + sph[0].v.y * sph[0].v.y + sph[0].v.z * sph[0].v.z;//2�_�Ԃ̋���

	float radius_sum = (sp[0].radius + ob.radius) * (sp[0].radius + ob.radius); //���a�̘a
	return s_dis < radius_sum ? true : false;//2�_�Ԃ̋��������a�̘a��菬������Γ������Ă���Ɣ���
}

bool Decel_aria_check(Sph sp[], Sph decele[], int i) {
	decelearia[i].v.x = decele[i].pos.x - sp[0].pos.x;
	decelearia[i].v.y = decele[i].pos.y - sp[0].pos.y;
	decelearia[i].v.z = decele[i].pos.z - sp[0].pos.z;

	decelearia[i].dis = decelearia[i].v.x * decelearia[i].v.x + decelearia[i].v.y * decelearia[i].v.y + decelearia[i].v.z * decelearia[i].v.z;
	decelearia[i].radius_sum = (decele[i].radius + sp[0].radius) * (decele[i].radius + sp[0].radius);
	return decelearia[i].dis < decelearia[i].radius_sum ? true : false;
}

void Decel_aria_effect() {
	sph[0].zmove *= 0.93f;
}

//���Ƌ��̓����蔻������m������̏���
void Sph_hit(float dis) {
	float len = sqrtf(dis);
	float radius_sum = sph[0].radius + obj.radius;
	float merikomi = radius_sum - len;

	if (len > 0) len = 1 / len;

	sph[0].v.x *= len;
	sph[0].v.y *= len;
	sph[0].v.z *= len;

	merikomi /= 2.0f;

	//�߂荞�ݏC��
	//sph[0].pos.x -= sph[0].v.x * merikomi; 
	//sph[0].pos.y -= sph[0].v.y * merikomi;
	//sph[0].pos.z -= sph[0].v.z * merikomi;

	//obj.pos.x += sph[0].v.x * merikomi;
	//obj.pos.y += sph[0].v.y * merikomi;
	//obj.pos.z += sph[0].v.z * merikomi;
}

void Ground_model_hit() {
	st_model_hit.movepos = VGet(0.0f, 0.0f,0.0f);//�ړ��x�N�g��
	st_model_hit.MoveFlag = 0;// �ړ��������ǂ����̃t���O��������Ԃł́u�ړ����Ă��Ȃ��v��\���O�ɂ���

	P_input_move();//�v���C���[����
	P_move();
	//�n�ʂɂ��Ă��Ȃ�������d�͔���
	if (!st_model_hit.groundflg) {
		Sph_Gravity();//�d��
	}
	Sph_Gravity();//�d��
	/*DrawFormatString(100, 220, GetColor(255, 0, 0), " %d", st_model_hit.groundflg);*/
	// �ړ��{�^���������ꂽ���ǂ����ŏ����𕪊�
	if (st_model_hit.MoveFlag == 1)
	{
		// �ړ��x�N�g���𐳋K���������̂��v���C���[�������ׂ������Ƃ��ĕۑ�
		st_model_hit.TargetMoveDirection = VNorm(st_model_hit.movepos);
		/*DrawFormatString(100, 200, GetColor(255, 255, 255), " %.1f , %.1f , %.1f ", st_model_hit.TargetMoveDirection.x, st_model_hit.TargetMoveDirection.y, st_model_hit.TargetMoveDirection.z);*/
		// �v���C���[�������ׂ������x�N�g�����v���C���[�̃X�s�[�h�{�������̂��ړ��x�N�g���Ƃ���
		st_model_hit.movepos = VScale(st_model_hit.TargetMoveDirection, sph[0].speed);


		/*DrawFormatString(100, 230, GetColor(255, 0, 0), "Vscale %.1f , %.1f , %.1f ", st_model_hit.movepos.x, st_model_hit.movepos.y, st_model_hit.movepos.z);*/
	}
	if (p_zmoveflg == true) {

		st_model_hit.movepos.z = st_model_hit.movepos.z + sph[0].zmove;
		
		if (st_model_hit.gmoveflg == false) {
			// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z
			sinParam = (float)sin(cameraHAngle / 180.0f * DX_PI_F);
			cosParam = (float)cos(cameraHAngle / 180.0f * DX_PI_F);
			// �e�x�N�g�����ƂɌv�Zy�͕��u

			TempMoveVector.x = st_model_hit.movepos.x * cosParam - st_model_hit.movepos.z * sinParam;
			TempMoveVector.y = 0.0f;
			TempMoveVector.z = st_model_hit.movepos.x * sinParam + st_model_hit.movepos.z * cosParam;

			st_model_hit.movepos = TempMoveVector;
		}
	}

	Ground_model_hit_check(st_model_hit.movepos);
}
void Ground_model_hit_check(VECTOR MoveVector) {
	// �ړ��O�̍��W��ۑ�
	st_model_hit.OldPos = sph[0].pos;
	// �ړ���̍��W���Z�o
	st_model_hit.NowPos = VAdd(sph[0].pos, MoveVector);
	 //�v���C���[�̎��͂ɂ���X�e�[�W�|���S�����擾����
	 //( ���o����͈͈͂ړ��������l������ )
	st_model_hit.HitDim[0] = MV1CollCheck_Sphere(ground.handle, -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	// �v���C���[�̎��͂ɂ���R���W�����I�u�W�F�N�g�̃|���S�����擾����
	for (int i = 0; i < stg.CollObjNum; i++)
	{

		st_model_hit.HitDim[i + 1] = MV1CollCheck_Sphere(stg.CollObjModelHandle[i], -1, sph[0].pos, PLAYER_ENUM_DEFAULT_SIZE + VSize(MoveVector));
	}

	// HitDim �̗L���Ȑ��̓R���W�����I�u�W�F�N�g�̐��ƃX�e�[�W���̂̃R���W����
	st_model_hit.HitDimNum = stg.CollObjNum + 1;
	// x����y�������� 0.01f �ȏ�ړ������ꍇ�́u�ړ������v�t���O���P�ɂ���
	if (fabs(MoveVector.x) > 0.01f || fabs(MoveVector.z) > 0.01f)
	{
		st_model_hit.MoveFlag = 1;
	}
	else
	{
		st_model_hit.MoveFlag = 0;
	}

	// ���o���ꂽ�|���S�����ǃ|���S��( �w�y���ʂɐ����ȃ|���S�� )�����|���S��( �w�y���ʂɐ����ł͂Ȃ��|���S�� )���𔻒f����
	{
		// �ǃ|���S���Ə��|���S���̐�������������
		st_model_hit.KabeNum = 0;
		st_model_hit.YukaNum = 0;


		// ���o���ꂽ�|���S���̐������J��Ԃ�
		for (int j = 0; j < st_model_hit.HitDimNum; j++)
		{
			for (int i = 0; i < st_model_hit.HitDim[j].HitNum; i++)
			{
				// �w�y���ʂɐ������ǂ����̓|���S���̖@���̂x�������O�Ɍ���Ȃ��߂����ǂ����Ŕ��f����
				if (st_model_hit.HitDim[j].Dim[i].Normal.y < 0.000001f && st_model_hit.HitDim[j].Dim[i].Normal.y > -0.000001f)
				{
					// �ǃ|���S���Ɣ��f���ꂽ�ꍇ�ł��A�v���C���[�̂x���W�{�P�D�O����荂���|���S���̂ݓ����蔻����s��
					if (st_model_hit.HitDim[j].Dim[i].Position[0].y > sph[0].pos.y + 1.0f ||
						st_model_hit.HitDim[j].Dim[i].Position[1].y > sph[0].pos.y + 1.0f ||
						st_model_hit.HitDim[j].Dim[i].Position[2].y > sph[0].pos.y + 1.0f)
					{
						// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
						if (st_model_hit.KabeNum < PLAYER_MAX_HITCOLL)
						{
							// �|���S���̍\���̂̃A�h���X��ǃ|���S���|�C���^�z��ɕۑ�����
							st_model_hit.Kabe[st_model_hit.KabeNum] = &st_model_hit.HitDim[j].Dim[i];

							// �ǃ|���S���̐������Z����
							st_model_hit.KabeNum++;
						}
					}
				}
				else
				{
					// �|���S���̐����񋓂ł�����E���ɒB���Ă��Ȃ�������|���S����z��ɒǉ�
					if (st_model_hit.YukaNum < PLAYER_MAX_HITCOLL)
					{
						// �|���S���̍\���̂̃A�h���X�����|���S���|�C���^�z��ɕۑ�����
						st_model_hit.Yuka[st_model_hit.YukaNum] = &st_model_hit.HitDim[j].Dim[i];

						// ���|���S���̐������Z����
						st_model_hit.YukaNum++;
					}
				}
			}
		}
	}

	//// �ǃ|���S���Ƃ̓����蔻�菈��
	//if (st_model_hit.KabeNum != 0)
	//{
	//	// �ǂɓ����������ǂ����̃t���O�͏�����Ԃł́u�������Ă��Ȃ��v�ɂ��Ă���
	//	st_model_hit.HitFlag = 0;

	//	// �ړ��������ǂ����ŏ����𕪊�
	//	if (st_model_hit.MoveFlag == 1)
	//	{
	//		// �ǃ|���S���̐������J��Ԃ�
	//		for (int i = 0; i < st_model_hit.KabeNum; i++)
	//		{
	//			// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
	//			st_model_hit.Poly = st_model_hit.Kabe[i];

	//			// �|���S���ƃv���C���[���������Ă��Ȃ������玟�̃J�E���g��
	//			if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == FALSE) continue;

	//			// �����ɂ�����|���S���ƃv���C���[���������Ă���Ƃ������ƂȂ̂ŁA�|���S���ɓ��������t���O�𗧂Ă�
	//			st_model_hit.HitFlag = 1;

	//			//�ǂɓ���������ǂɎՂ��Ȃ��ړ������������ړ�����
	//			{
	//				VECTOR SlideVec;	// �v���C���[���X���C�h������x�N�g��

	//				// �i�s�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o
	//				SlideVec = VCross(MoveVector, st_model_hit.Poly->Normal);

	//				// �Z�o�����x�N�g���ƕǃ|���S���̖@���x�N�g���ɐ����ȃx�N�g�����Z�o�A���ꂪ
	//				// ���̈ړ���������Ǖ����̈ړ������𔲂����x�N�g��
	//				SlideVec = VCross(st_model_hit.Poly->Normal, SlideVec);

	//				// ������ړ��O�̍��W�ɑ��������̂�V���ȍ��W�Ƃ���
	//				st_model_hit.NowPos = VAdd(st_model_hit.OldPos, SlideVec);
	//			}

	//			int j;
	//			// �V���Ȉړ����W�ŕǃ|���S���Ɠ������Ă��Ȃ����ǂ����𔻒肷��
	//			for (j = 0; j < st_model_hit.KabeNum; j++)
	//			{
	//				// j�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
	//				st_model_hit.Poly = st_model_hit.Kabe[j];

	//				// �������Ă����烋�[�v���甲����
	//				if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == TRUE) break;
	//			}

	//			// j �� KabeNum �������ꍇ�͂ǂ̃|���S���Ƃ�������Ȃ������Ƃ������ƂȂ̂�
	//			// �ǂɓ��������t���O��|������Ń��[�v���甲����
	//			if (j == st_model_hit.KabeNum)
	//			{
	//				st_model_hit.HitFlag = 0;
	//				break;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		// �ړ����Ă��Ȃ��ꍇ�̏���

	//		// �ǃ|���S���̐������J��Ԃ�
	//		for (int i = 0; i < st_model_hit.KabeNum; i++)
	//		{
	//			// i�Ԗڂ̕ǃ|���S���̃A�h���X��ǃ|���S���|�C���^�z�񂩂�擾
	//			st_model_hit.Poly = st_model_hit.Kabe[i];

	//			// �|���S���ɓ������Ă����瓖�������t���O�𗧂Ă���Ń��[�v���甲����
	//			if (HitCheck_Capsule_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), PLAYER_HIT_WIDTH, st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]) == TRUE)
	//			{
	//				st_model_hit.HitFlag = 1;
	//				break;
	//			}
	//		}
	//	}
	//}


	// ���|���S���Ƃ̓����蔻��
	if (st_model_hit.YukaNum != 0)
	{


		float MaxY;

		// ���~�����W�����v���ł͂Ȃ��ꍇ�̏���

		// ���|���S���ɓ����������ǂ����̃t���O��|���Ă���
		st_model_hit.HitFlag = 0;

		// ��ԍ������|���S���ɂԂ���ׂ̔���p�ϐ���������
		MaxY = 0.0f;

		// ���|���S���̐������J��Ԃ�
		for (int i = 0; i < st_model_hit.YukaNum; i++)
		{
			// i�Ԗڂ̏��|���S���̃A�h���X�����|���S���|�C���^�z�񂩂�擾
			st_model_hit.Poly = st_model_hit.Yuka[i];


			// �����Ă���ꍇ�͓��̐悩�炻�������Ⴂ�ʒu�̊Ԃœ������Ă��邩�𔻒�( �X�΂ŗ�����ԂɈڍs���Ă��܂�Ȃ��� )
			/*st_model_hit.LineRes = HitCheck_Line_Triangle(VAdd(st_model_hit.NowPos, VGet(0.0f, 0.0f, 0.0f)), VAdd(st_model_hit.NowPos, VGet(0.0f, PLAYER_HIT_HEIGHT, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);*/
			st_model_hit.LineRes = HitCheck_Line_Triangle(st_model_hit.NowPos, VAdd(st_model_hit.NowPos, VGet(0.0f, -200, 0.0f)), st_model_hit.Poly->Position[0], st_model_hit.Poly->Position[1], st_model_hit.Poly->Position[2]);

			if (st_model_hit.LineRes.HitFlag == FALSE) { 
				
				continue; 
			}
			//�����܂ł����
			
			// ���ɓ��������|���S��������A�����܂Ō��o�������|���S�����Ⴂ�ꍇ�͉������Ȃ�
			if (st_model_hit.HitFlag == 1 && MaxY > st_model_hit.LineRes.Position.y) continue;

			// �|���S���ɓ��������t���O�𗧂Ă�
			st_model_hit.HitFlag = 1;
			// �ڐG�����x���W��ۑ�����
			MaxY = st_model_hit.LineRes.Position.y + sph[0].radius;
			/*DrawFormatString(100, 240, GetColor(255, 0, 0), " Line.Y %d", st_model_hit.LineRes.Position.y);*/
			st_model_hit.groundflg = true; //�n�ʂɂ����t���O�𗧂Ă�
		}
		DrawLine3D(st_model_hit.NowPos, VAdd(st_model_hit.NowPos,VGet(0.0f,-200.f,0.0f)), GetColor(255, 0, 0));
		// ���|���S���ɓ����������ǂ����ŏ����𕪊�
		if (st_model_hit.HitFlag == 1)
		{
			// ���������ꍇ

			// �ڐG�����|���S���ň�ԍ����x���W���v���C���[�̂x���W�ɂ���
			st_model_hit.NowPos.y = MaxY;
		}
	}

	
	sph[0].pos = st_model_hit.NowPos;
	
	MV1SetPosition(rock.handle, sph[0].pos);
	/*DrawSphere3D(sph[0].pos, sph[0].radius, 32, sph[0].color, GetColor(255, 255, 255), TRUE);*/
	// ���o�����v���C���[�̎��͂̃|���S�������J������
	for (int i = 0; i < st_model_hit.HitDimNum; i++)
	{
		MV1CollResultPolyDimTerminate(st_model_hit.HitDim[i]);
	}
}

////���f���Ƌ��̓����蔻��`�F�b�N
//void Model_hit_check() {
//	//���̃x�N�g���^ Pos�ɑ��
//	sph[0].pos = VGet(sph[0].x, sph[0].y, sph[0].z);
//
//	//���f���Ƌ��̓����蔻����擾
//	for (int i = 0; i < TREE_NUM; i++) {
//		HitPolyDim[i] = MV1CollCheck_Sphere(tree_handle[i], -1, sph[0].pos, sph[0].radius);
//	}
//}

//void Model_hit() {
//	//�����蔻������m������̏���
//	for (int j = 0; j < TREE_NUM; j++) {
//		if (HitPolyDim[j].HitNum >= 1)
//		{
//			SetFontSize(50);
//			DrawFormatString(600, 250, GetColor(255, 0, 0), "[�؂̃��f�� HIT]");
//			SetFontSize(20);
//		}
//		//DrawFormatString(100, 300 + ((j + 1) * 20), GetColor(255, 255, 255), "%d", HitPolyDim[j].HitNum);//�����������f����polygon���\��
//	}
//
//	//���f������̃��������
//	for (int i = 0; i < TREE_NUM; i++) {
//		MV1CollResultPolyDimTerminate(HitPolyDim[i]);
//	}
//}

//�v���C���[�̍��E�ړ��͈͂𐧌�����
void Move_Limits()
{
	//�����̂�X���W�����Ƃɍ��
	int lhit_magnification = 2;    //X�̈ړ��͈͊O�ɂł��ꍇ�̖߂��͂̔{��
	//��
	static VECTOR player_before_pos = VGet(0.0f, 0.0f, 0.0f);

	if (sph[0].pos.z < st_model_hit.branch_point[0] && sph[0].pos.y < 5470.0f) {
		//���E�̂ǂ��炩�͈̔͊O�Ɉړ����悤�Ƃ�����t���O��true�ɂ���
		if ((sph[0].pos.x <= st_model_hit.glimits_verification[0] ||
			sph[0].pos.x >= st_model_hit.glimits_verification[1]) && st_model_hit.gmoveflg != true) {
			st_model_hit.gmoveflg = true;
			player_before_pos = sph[0].pos;
		}

		if (st_model_hit.gmoveflg == true) {
			//�͈͓��ɖ߂�����(��)
			if (sph[0].pos.x <= player_before_pos.x + sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 1) {
				sph[0].pos.x += 10;
			}
			//�͈͓��ɖ߂�����(�E)
			else if (sph[0].pos.x >= player_before_pos.x - sph[0].zmove * lhit_magnification && st_model_hit.landr_move == 2) {
				sph[0].pos.x -= 10;
			}
			//�t���O�����Ƃɖ߂�
			else {
				//sph[0].zmove = 0.0f;
				//sph[0].zaccl = 2.0f;
				st_model_hit.gmoveflg = false;
			}

		}
	}
}