//=====================================
//
// DepthRenderer.fx
// �@�\:�[�x�o�b�t�@�V���h�E�V�F�[�_
// Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
�O���[�o���ϐ�
***************************************/
float4x4 mtxWVP;
float4x4 mtxLWVP;
float4x4 mtxLWVPT;
float4 lightDir;

sampler tex1 : register(s1);

/**************************************
���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUTPUT
{
	float4 pos : POSITION;
	float4 color : COLOR0;
	float2 tex : TEXCOORD0;
	float2 depth : TEXCOORD1;
	float4 lightUV : TEXCOORD2;
};

/**************************************
���_�V�F�[�_
***************************************/
VS_OUTPUT VS(
	float4 pos : POSITION,
	float4 normal : NORMAL,
	float2 tex : TEXCOORD0)
{
	VS_OUTPUT Out;

	Out.pos = mul(pos, mtxWVP);

	Out.tex = tex;

	//�����v�Z
	float3 L = -lightDir.xyz;
	float3 N = normalize(normal.xyz);
	Out.color = max(0.0f, dot(N, L)) * float4(0.0f, 0.6f, 1.0f, 1.0f);
	Out.color.a = 1.0f;

	//���ˉe���W�n�ɕϊ�����Z�l���v�Z
	Out.depth.xy = mul(pos, mtxLWVP).zw;

	//�e�N�X�`�����W�n�ɕϊ��������_���W���v�Z
	Out.lightUV = mul(pos, mtxLWVPT);

	return Out;
}

/**************************************
�s�N�Z���V�F�[�_
***************************************/
float4 PS(VS_OUTPUT In) : COLOR0
{
	float4 Out = In.color;

	//Z�o�b�t�@����[�x�l���擾
	float d = tex2Dproj(tex1, In.lightUV).r;

	if (In.depth.x > d + 0.005f)
	{
		Out.rgb *= 0.1f;
		//Out.rgb = float3(1.0f, 1.0f, 1.0f) - Out.rgb;
	}

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