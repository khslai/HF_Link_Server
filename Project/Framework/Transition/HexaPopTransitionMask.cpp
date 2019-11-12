//=====================================
//
//�w�L�T�|�b�v�g�����W�V��������[HexaPopTransitionMask.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "HexaPopTransitionMask.h"
#include "../Renderer2D/Polygon2D.h"

using namespace std;
/**************************************
static�����o
***************************************/
const int HexaPopTransitionMask::DivineX = 10;
const int HexaPopTransitionMask::DivineY = 10;
const float HexaPopTransitionMask::Duration = 0.5f;
const float HexaPopTransitionMask::Interval = 0.08f;

typedef BaseTransitionMask Base;
/**************************************
�R���X�g���N�^
***************************************/
HexaPopTransitionMask::HexaPopTransitionMask()
{
	polygon = new Polygon2D();

	//�|���S���̑傫�����v�Z
	float sizeX = (float)SCREEN_WIDTH / DivineX;
	float sizeY = (float)SCREEN_HEIGHT / DivineY;
	polygon->SetSize(sizeX, sizeY);
	polygon->LoadTexture("data/TRANSITION/HexaMask.png");

	//X����1��ň�̃x�N�^�[�Ƃ���
	//2�����z��̂悤�Ƀx�N�^�[�̃x�N�^�[�����
	for (int y = 0; y < DivineY + 2; y++)
	{
		vector<Hexagon*> list;
		for (int x = 0; x < DivineX + 3; x++)
		{
			D3DXVECTOR3 pos = D3DXVECTOR3(x * sizeX, (y - 1) * sizeY, 0.0f);

			if (x % 2 != 0)
				pos.y += sizeY * 0.5f;

			list.push_back(new Hexagon(pos));
		}
		hexList.push_back(list);
	}

	//�e��̃x�N�^�[�ɑ΂��ẴC�e���[�^��������
	itrList.resize(hexList.size());
	for (UINT i = 0; i < itrList.size(); i++)
	{
		itrList[i] = hexList[i].begin();
	}
}

/**************************************
�f�X�g���N�^
***************************************/
HexaPopTransitionMask::~HexaPopTransitionMask()
{
	for (auto& list : hexList)
	{
		Utility::DeleteContainer(list);
	}
	hexList.clear();

	SAFE_DELETE(polygon);
}

/**************************************
�X�V����
***************************************/
MaskResult HexaPopTransitionMask::Update()
{
	if (!active)
		return MaskResult::Continuous;

	//�X�V�����̌���
	MaskResult result = MaskResult::Continuous;

	//���������J�n����s���w���C���f�b�N�X�̍X�V
	int interval = (int)(FramePerSecond * Interval);
	if (cntFrame++ % interval == 0)	
		rowIndex = Math::Clamp((UINT)0, (UINT)hexList.size(), ++rowIndex);

	//�Z�p�`��������
	for (UINT y = 0; y < rowIndex; y++)
	{
		if (itrList[y] != hexList[y].end())
		{
			(*itrList[y])->Init();
			itrList[y]++;
		}
	}

	//�Z�p�`���X�V
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			hex->Update(*this);
		}
	}

	//�S�Ă̘Z�p�`�̃C�[�W���O���I�����Ă�����I���ʒm��Ԃ�
	if (isFinished)
	{
		active = false;
		result = isTransitionOut ? MaskResult::FinishTransitionOut : FinishTransitionIn;
	}

	return result;
}

/**************************************
�`�揈���X�V����
***************************************/
void HexaPopTransitionMask::Draw()
{
	if (!active)
		return;

	//�}�X�N�J�n
	Base::BeginMask();

	//�}�X�N�̈�`��
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			polygon->SetTransform(hex->transform);
			polygon->Draw();
		}
	}

	//�}�X�N�I��
	Base::EndMask();
}

/**************************************
�Z�b�g����
***************************************/
void HexaPopTransitionMask::Set(bool isTransitionOut)
{
	if (active)
		return;

	//�C�[�W���O�p�̃p�����[�^������
	startScale = isTransitionOut ? D3DXVECTOR3(0.0f, 0.0f, 0.0f) : D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	endScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f) - startScale;
	type = isTransitionOut ? EaseType::OutSine : EaseType::InSine;
	cntFrame = 0;

	//�w�L�T���X�g������
	for (auto& list : hexList)
	{
		for (auto& hex : list)
		{
			hex->active = false;
			hex->transform.SetScale(startScale);
		}
	}

	//�t���O������
	active = true;
	this->isTransitionOut = isTransitionOut;
	isFinished = false;

	//�J�E���g������
	cntFrame = 0;
	rowIndex = 0;
	
	//�C�e���[�^������
	for (UINT i = 0; i < itrList.size(); i++)
	{
		itrList[i] = hexList[i].begin();
	}
}

/**************************************
Hexagon�R���X�g���N�^
***************************************/
HexaPopTransitionMask::Hexagon::Hexagon(D3DXVECTOR3 pos)
{
	transform.SetPosition(pos);
	cntFrame = 0;
	active = false;
}

/**************************************
Hexagon����������
***************************************/
void HexaPopTransitionMask::Hexagon::Init()
{
	cntFrame = 0;
	active = true;
}

/**************************************
Hexagon�X�V����
***************************************/
void HexaPopTransitionMask::Hexagon::Update(HexaPopTransitionMask& parent)
{
	if (!active)
		return;

	//�C�[�W���O
	cntFrame++;
	float t = ((float)cntFrame / FramePerSecond) / Duration;
	transform.SetScale(Easing::EaseValue(t, parent.startScale, parent.endScale, parent.type));

	//�I������
	if (t >= Duration && IsLastHexa(parent))
		parent.isFinished = true;
}

/**************************************
Hexagon�I�[�m�F
***************************************/
bool HexaPopTransitionMask::Hexagon::IsLastHexa(HexaPopTransitionMask& parent)
{
	return  *((parent.hexList.end() - 1)->end() - 1) == this;
}