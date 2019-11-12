//=====================================
//
//�p�[�e�B�N���V�F�[�_[Particle.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/***************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxView;		//�r���[�s��
float4x4 mtxProj;		//�v���W�F�N�V�����s��
float4x4 mtxInvView;	//�r���[�t�s��
float4x4 mtxScreenProj;	//2D�p�̃v���W�F�N�V�����s��

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
	float4 color : COLOR0;
};

/**************************************************************
���_�V�F�[�_(3D�p)
***************************************************************/
VS_OUTPUT VS_3D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0,
	float4 mtxWorld1 : TEXCOORD1,
	float4 mtxWorld2 : TEXCOORD2,
	float4 mtxWorld3 : TEXCOORD3,
	float4 mtxWorld4 : TEXCOORD4,
	float2 texUV : TEXCOORD5
) {
	VS_OUTPUT Out;

	Out.pos = float4(pos, 1.0f);

	//world
	float4x4 mtxWorld = {
		mtxWorld1,
		mtxWorld2,
		mtxWorld3,
		mtxWorld4
	};
	Out.pos = mul(Out.pos, mtxWorld);

	//view & projection
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProj);

	//texUV
	Out.uv = localUV + texUV;

	//Color
	Out.color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return Out;
}

/**************************************************************
���_�V�F�[�_(2D�p)
***************************************************************/
VS_OUTPUT VS_2D(
	float3 pos : POSITION,
	float2 localUV : TEXCOORD0,
	float4 mtxWorld1 : TEXCOORD1,
	float4 mtxWorld2 : TEXCOORD2,
	float4 mtxWorld3 : TEXCOORD3,
	float4 mtxWorld4 : TEXCOORD4,
	float2 texUV : TEXCOORD5
) {
	VS_OUTPUT Out;

	Out.pos = float4(pos, 1.0f);

	//world
	float4x4 mtxWorld = {
		mtxWorld1,
		mtxWorld2,
		mtxWorld3,
		mtxWorld4
	};
	Out.pos = mul(Out.pos, mtxWorld);

	//projection
	Out.pos = mul(Out.pos, mtxScreenProj);

	//texUV
	Out.uv = localUV + texUV;

	//Color
	Out.color = float4(1.0f, 1.0f, 1.0f, 1.0f);

	return Out;
}

/**************************************************************
�s�N�Z���V�F�[�_
***************************************************************/
float4 psMain(VS_OUTPUT In) : COLOR0
{
	//�e�N�X�`������J���[���擾
	return tex2D(s0, In.uv) * In.color;
}

/**************************************************************
�e�N�j�b�N
***************************************************************/
technique tech {
	pass p0 {
		VertexShader = compile vs_2_0 VS_3D();
		PixelShader = compile ps_2_0 psMain();
	}

	pass p1 {
		VertexShader = compile vs_2_0 VS_2D();
		PixelShader = compile ps_2_0 psMain();
	}
};