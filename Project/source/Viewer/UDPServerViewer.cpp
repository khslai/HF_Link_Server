//=============================================================================
//
// UDP�T�[�o�[�`��N���X [UDPServerViewer.cpp]
// Author : HAL���� GP12B332 41 ���M��
//
//=============================================================================
#include "../../main.h"
#include "UDPServerViewer.h"
#include "RankViewer.h"
#include "TextureDrawer.h"
#include "../Effect/GameParticleManager.h"

#include "../../Framework/String/String.h"
#include "../../Framework/Tool/DebugWindow.h"
#include "../../Framework/Math/Easing.h"
#include "../../Framework/Network/PacketConfig.h"

const int RankingMaxNum = 7;
const float RankInterval = 120.0f;
const D3DXVECTOR3 DefaultPos = D3DXVECTOR3(SCREEN_CENTER_X - 300.0f, 240.0f, 0.0f);

enum ViewerState
{
	Idle,
	Move,
	Expand,
};

//*****************************************************************************
// �X�^�e�B�b�N�ϐ��錾
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^
//=============================================================================
UDPServerViewer::UDPServerViewer() :
	InsertTemp(nullptr)
{
	RankingTitle = new TextureDrawer(D3DXVECTOR2(966.0f, 208.0f));
	RankingTitle->LoadTexture("data/TEXTURE/Viewer/RankingViewer/RankingTitle.png");
	RankingTitle->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 108.0f, 0.0f));

	ExpandTexture = new TextureDrawer(D3DXVECTOR2(SCREEN_WIDTH, 120.0f));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
UDPServerViewer::~UDPServerViewer()
{
	SAFE_DELETE(RankingTitle);
	SAFE_DELETE(ExpandTexture);
	SAFE_DELETE(InsertTemp);
	Utility::DeleteContainer(Ranking);
	Utility::DeleteContainer(InsertStack);
}

//=============================================================================
// �X�V
//=============================================================================
void UDPServerViewer::Update(void)
{
	const int MoveFrame = 30;
	const int ExpandFrame = 60;
	const float MoveSpeed = RankInterval / MoveFrame;

	if (State == ViewerState::Idle)
	{
		if (InsertStack.empty())
		{
			// ���Ԃɂ���āA�\�����W��ݒ�
			int Num = 0;
			for (auto &RankVec : Ranking)
			{
				RankVec->SetRankNum(Num);
				RankVec->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, Num * RankInterval, 0.0f));
				Num++;
			}
		}
		else
		{
			InsertTemp = InsertStack.at(0);
			InsertStack.erase(InsertStack.begin());
			SortRanking(InsertTemp);
		}
	}
	else if (State == ViewerState::Move)
	{
		if (CountFrame < MoveFrame)
		{
			CountFrame++;

			// ���X�ɉ��Ɉړ�����
			for (unsigned int i = InsertNum; i < Ranking.size(); i++)
			{
				D3DXVECTOR3 CenterPos = Ranking.at(i)->GetPosition();
				Ranking.at(i)->SetPosition(CenterPos + D3DXVECTOR3(0.0f, MoveSpeed, 0.0f));
			}

			// �ړ��I��
			if (CountFrame == MoveFrame)
			{
				// ���ʂ̒���
				for (unsigned int i = InsertNum; i < Ranking.size(); i++)
				{
					Ranking.at(i)->SetRankNum(i + 1);
				}

				// �����L���O�W�J
				RankingExpand();
			}
		}
	}
	else if (State == ViewerState::Expand)
	{
		if (CountFrame < ExpandFrame)
		{
			CountFrame++;
			float Time = (float)CountFrame / ExpandFrame;

			ExpandTexture->SetTextureExpand(Time);

			// �W�J�I��
			if (CountFrame == ExpandFrame)
			{
				// �����L���O�ɒǉ�
				RankingInsert();
				State = ViewerState::Idle;
			}
		}
	}

#if _DEBUG
	Debug::Begin("Ranking Test");
	if (Debug::Button("Clear"))
		ClearRanking();
	else if (Debug::Button("123"))
		CreateRankViewer("Player", "123");
	else if (Debug::Button("123455"))
		CreateRankViewer("Player", "123455");
	else if (Debug::Button("123456"))
		CreateRankViewer("Player", "123456");
	else if (Debug::Button("123457"))
		CreateRankViewer("Player", "123457");
	else if (Debug::Button("123456789"))
		CreateRankViewer("Player", "123456789");
	else if (Debug::Button("123456789123"))
		CreateRankViewer("Player", "123456789123");
	else if (Debug::Button("123456789123456"))
		CreateRankViewer("Player", "123456789123456");
	Debug::End();
#endif
}

//=============================================================================
// �`��
//=============================================================================
void UDPServerViewer::Draw(void)
{
	// �^�C�g��
	RankingTitle->Draw();

	// �W�J���o�p�̃e�N�X�`��
	if (State == ViewerState::Expand)
	{
		ExpandTexture->Draw();
	}

	// �����L���O
	for (auto & Rank : Ranking)
	{
		Rank->Draw();
	}
}

//=============================================================================
// �p�P�b�g�̓��e������
//=============================================================================
void UDPServerViewer::CreateRankViewer(string PlayerName, string AILevel)
{
	if (InsertTemp == nullptr)
	{
		InsertTemp = new RankViewer(PlayerName, AILevel);
		SortRanking(InsertTemp);
	}
	else
	{
		InsertStack.push_back(new RankViewer(PlayerName, AILevel));
	}
}

//=============================================================================
// �p�P�b�g�̓��e������
//=============================================================================
void UDPServerViewer::ReceivePacket(int PacketType, const std::vector<string>& SpliteStr)
{
	if (PacketType != Packet::Viewer::ShowRanking)
		return;

	string Name = SpliteStr.at(Packet::Rank::PlayerName);
	string AILevel = SpliteStr.at(Packet::Rank::AILevel);

	if (InsertTemp == nullptr)
	{
		InsertTemp = new RankViewer(Name, AILevel);
		SortRanking(InsertTemp);
	}
	else
	{
		InsertStack.push_back(new RankViewer(Name, AILevel));
	}
}

//=============================================================================
// �����L���O�̏��Ԃ����߂�
//=============================================================================
void UDPServerViewer::SortRanking(RankViewer* Rank)
{
	int Num = 0;

	// �󂢂���ǉ�
	if (Ranking.empty())
	{
		InsertNum = 0;
		RankingExpand();
	}
	else
	{
		unsigned long long AILevel = Rank->GetAILevel();

		// �ŉ��ʂ̃X�R�A��菭�Ȃ��A�������L���O�܂��󗓂���
		if (AILevel <= Ranking.back()->GetAILevel() && Ranking.size() < RankingMaxNum)
		{
			// �����L���O�ɒǉ�
			InsertNum = Ranking.size();
			RankingExpand();
		}
		else
		{
			for (auto &RankVec : Ranking)
			{
				unsigned long long AILevelVec = RankVec->GetAILevel();

				// �X�R�A�̔�r
				if (AILevel > AILevelVec)
				{
					RankingMoveStart(Num);
					break;
				}
				else if (AILevel == AILevelVec && Ranking.size() < RankingMaxNum)
				{
					RankingMoveStart(Num + 1);
					break;
				}
				Num++;
			}
		}
	}
}

//=============================================================================
// �����L���O�̈ړ��J�n
//=============================================================================
void UDPServerViewer::RankingMoveStart(int Num)
{
	State = ViewerState::Move;
	InsertNum = Num;
	CountFrame = 0;
}

//=============================================================================
// �����L���O�̓W�J�J�n
//=============================================================================
void UDPServerViewer::RankingExpand()
{
	LPDIRECT3DTEXTURE9 NewTexture = nullptr;

	// ���ʂ̐ݒ�
	InsertTemp->SetRankNum(InsertNum);
	// �����_�^�[�Q�b�g��ς��A�e�N�X�`���𐶐�
	InsertTemp->CreateRankTexture(&NewTexture);

	// ���o�p�e�N�X�`���̐ݒ�
	ExpandTexture->LoadTexture(&NewTexture);
	ExpandTexture->SetPosition(DefaultPos + D3DXVECTOR3(300.0f, InsertNum * RankInterval, 0.0f));
	ExpandTexture->SetTextureExpand(0.0f);

	// �G�t�F�N�g
	GameParticleManager::Instance()->SetExpandEffect(
		DefaultPos + D3DXVECTOR3(300.0f - SCREEN_CENTER_X, InsertNum * RankInterval, 0.0f));

	CountFrame = 0;
	State = ViewerState::Expand;
}

//=============================================================================
// �����L���O�ǉ�����
//=============================================================================
void UDPServerViewer::RankingInsert(void)
{
	InsertTemp->SetPosition(DefaultPos + D3DXVECTOR3(0.0f, InsertNum * RankInterval, 0.0f));
	Ranking.insert(Ranking.begin() + InsertNum, InsertTemp);
	InsertTemp = nullptr;

	// �ő�\������葽����΁A�ŉ��ʂ̐l���폜
	if (Ranking.size() > RankingMaxNum)
	{
		Ranking.pop_back();
	}
}

#if _DEBUG
void UDPServerViewer::ClearRanking(void)
{
	Utility::DeleteContainer(Ranking);
}
#endif