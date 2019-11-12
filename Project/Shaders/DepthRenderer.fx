//=====================================
//
// DepthRenderer.fx
// �@�\:Z�l�����_�����O�V�F�[�_
// Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxWorld;				//���[���h�s��
float4x4 mtxView;				//�r���[�s��
float4x4 mtxProjection;			//�v���W�F�N�V�����s��

/**************************************
���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float2 depth : TEXCOORD0;
};

/**************************************
�[�x�}�b�v�쐬���_�V�F�[�_
***************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float4 normal : NORMAL,
	float2 tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	//���[���h�r���[�v���W�F�N�V�����ϊ�
	Out.pos = mul(pos, mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);
	
	//�e�N�X�`�����W�𒸓_�ɍ��킹��
	Out.depth.xy = Out.pos.zw;

	return Out;
}

/**************************************
�[�x�}�b�v�쐬�s�N�Z���V�F�[�_
***************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out;

	//Z�l�Z�o
	Out = In.depth.x / In.depth.y;
	Out.w = 1.0f;

	return Out;
}

/**************************************
�e�N�j�b�N
***************************************/
technique tech
{
	pass P0
	{
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};