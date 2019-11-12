//=====================================
//
//�p�[�e�B�N���V�F�[�_[Particle.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/***************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxWorld;		//���[���h�ϊ��s��
float4x4 mtxView;		//�r���[�s��
float4x4 mtxProj;		//�v���W�F�N�V�����s��
float4x4 mtxScreenProj;	//2D�p�̃v���W�F�N�V�����s��

float2 texUV;			//�e�N�X�`����UV���W

float4 diffuse;			//�}�e���A���̃f�B�t���[�Y

/**************************************************************
�e�N�X�`���T���v���[�i0�Ԃ�SetTexture�����e�N�X�`�����g�p����
***************************************************************/
sampler s0 : register(s0);

/**************************************************************
���_�V�F�[�_�o�͍\����
***************************************************************/
struct VS_OUTPUT {
	float4 pos : POSITION;
	float2 uv : TEXCOORD0;
};

/**************************************************************
���_�V�F�[�_(3D�p)
***************************************************************/
VS_OUTPUT VS_3D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	Out.uv = localUV + texUV;

	return Out;
}

/**************************************************************
���_�V�F�[�_(2D�p)
***************************************************************/
VS_OUTPUT VS_2D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0)
{
	VS_OUTPUT Out = (VS_OUTPUT)0;

	Out.pos = mul(float4(pos, 0.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxScreenProj);

	Out.uv = localUV + texUV;

	return Out;
}

/**************************************************************
�s�N�Z���V�F�[�_
***************************************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	return tex2D(s0, In.uv) * diffuse;
}

/**************************************************************
�e�N�j�b�N
***************************************************************/
technique tech
{
	pass P0 {
		ALPHABLENDENABLE = true;
		VertexShader = compile vs_2_0 VS_3D();
		PixelShader = compile ps_2_0 PS();
	}

	pass P1 {
		ALPHABLENDENABLE = true;
		VertexShader = compile vs_2_0 VS_2D();
		PixelShader = compile ps_2_0 PS();
	}
};