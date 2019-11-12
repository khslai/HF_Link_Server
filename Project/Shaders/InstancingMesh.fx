//=====================================
//
//�C���X�^���V���O���b�V���V�F�[�_[ModelInstancing.fx]
//Author:GP12B332 21 ���ԗY��
//
//=====================================

/**************************************
*�O���[�o���ϐ�
***************************************/
float4x4 mtxView;				//�r���[�s��
float4x4 mtxProjection;			//�v���W�F�N�V�����s��
float4 materialDiffuse;			//�}�e���A���f�B�t���[�Y
float4 materialAmbient;			//�}�e���A���A���r�G���g
float4 materialSpecular;		//�}�e���A���X�y�L�����[

float4 lightDiffuse[3];			//���C�g�f�B�t���[�Y
float4 lightAmbient[3];			//���C�g�A���r�G���g
float4 lightSpecular[3];		//���C�g�X�y�L����
float4 lightDirection[3];		//���C�g����

/**************************************
*�e�N�X�`���T���v���[
***************************************/
sampler s0 : register(s0);

/**************************************
*���_�V�F�[�_�o�͍\����
***************************************/
struct VS_OUT {
	float4 pos	: POSITION;
	float2 uv	: TEXCOORD0;
	float4 color : COLOR0;
};

/**************************************
*���_�V�F�[�_
***************************************/
VS_OUT VS(
	float3 pos : POSITION,
	float3 normal : NORMAL,
	float2 uv : TEXCOORD0,
	float4 mtxWorld1 : TEXCOORD1,
	float4 mtxWorld2 : TEXCOORD2,
	float4 mtxWorld3 : TEXCOORD3,
	float4 mtxWorld4 : TEXCOORD4)
{
	VS_OUT Out = (VS_OUT)0;

	float4x4 mtxWorld = { mtxWorld1, mtxWorld2, mtxWorld3, mtxWorld4 };

	//���_��ϊ�
	Out.pos = mul(float4(pos, 1.0f), mtxWorld);
	Out.pos = mul(Out.pos, mtxView);
	Out.pos = mul(Out.pos, mtxProjection);

	//�@�������[���h�ϊ�
	float3 N = mul(normal, (float3x3)mtxWorld);
	N = normalize(N);
	
	//UV���W���i�[
	Out.uv = uv;

	//���C�g�ɂ��F���v�Z
	float4 diffuse = (float4)0;
	float4 ambient = (float4)0;

	for (int i = 0; i < 3; i++)
	{
		float3 L = normalize(-lightDirection[i].xyz);
		diffuse += max(0.0f, dot(L, N)) * lightDiffuse[i];
		ambient += lightAmbient[i];
	}

	Out.color = saturate(diffuse * materialDiffuse + ambient * materialAmbient);

	Out.color.a = 1.0f;

	return Out;
}

/**************************************
*�s�N�Z���V�F�[�_
***************************************/
float4 PS(VS_OUT In) : COLOR0
{
	return tex2D(s0, In.uv) * In.color;
}

/**************************************
*�e�N�j�b�N
**************************************/
technique tech
{
	pass p0 {
		VertexShader = compile vs_2_0 VS();
		PixelShader = compile ps_2_0 PS();
	}
};