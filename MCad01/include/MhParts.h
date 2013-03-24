////////////////////////////////////////////////////////////////////////////
//	  �z�u��
////////////////////////////////////////////////////////////////////////////
#pragma once

namespace MC
{

class	MhSenBuzai
{
public:
	MgLine3		Ln;									// ���ނ̔z�u�_�A�z�u�����_
	MgVect3		vtUt;								// ���ނ̔z�u����
	MREAL		rW[2];								// ���ނ̉E���A����
	MREAL		rLH[2];								// ���ނ̒����␳�l
	MgLine3		LnWH;								// ���ނ̕␳�l���������̐���
	MgULine3	ULnW[2];							// ���ނ̉E�ӁA���Ӂ@����

public:
	MhSenBuzai()		{}
	MhSenBuzai( mhPlcInfo &PlcEn)		{ 
		Ln     = PlcEn.GetPIPlcIti();						// �����������̕���
		vtUt   = Ln.Vu();
		rLH[0] = PlcEn.GetPILenHosei( 0);
		rLH[1] = PlcEn.GetPILenHosei( 1);
		rW[0]  = PlcEn.GetMbWidthR() + PlcEn.GetPISinZure();
		rW[1]  = PlcEn.GetMbWidthL() - PlcEn.GetPISinZure();
		LnWH = MgLine3( Ln.p[0] - rLH[0] * vtUt + PlcEn.GetPISinZure() * vtUt.RotR90(),
						Ln.p[1] + rLH[1] * vtUt + PlcEn.GetPISinZure() * vtUt.RotR90());
		ULnW[0] = MgULine3( Ln.p[0] + vtUt.RotR90() * rW[0], vtUt);
		ULnW[1] = MgULine3( Ln.p[0] + vtUt.RotL90() * rW[1], vtUt);
	}
/*
	void operator = (mhPlcInfo &PlcEn) {
		Ln     = PlcEn.GetPIPlcIti();						// �����������̕���
		vtUt   = Ln.V();
		rLH[0] = PlcEn.GetPILenHosei( 0);
		rLH[1] = PlcEn.GetPILenHosei( 1);
		rW[0]  = PlcEn.GetMbWidthR() + PlcEn.GetPISinZure();
		rW[1]  = PlcEn.GetMbWidthL() - PlcEn.GetPISinZure();
	}	
*/
	//�@���u���ނƉ��u���ނ̈ʒu�֌W�𒲂ׂ�B
	//�@�Q�����ނ��d�Ȃ��Ă���ꍇ�́A�����Ȃ��i���s�j�Ƃ݂Ȃ��B
	//  �Q�����ނ��d�Ȃ�Ȃ������I�Ɍ������Ă���ꍇ�͂��̌����_����_�Ƃ݂Ȃ��B
	static MINT	MhOn(										// �X�e�C�^�X
														// MC_PARALLEL	(-1) �����Ȃ��i���s�j
														// MC_NINT	    (0)	�����Ȃ�
														// MC_INT		(1)	��������
					const	MhSenBuzai&	i_Bz1,			// ������1
					const	MhSenBuzai&	i_Bz2,			// ������2
							MgPoint3*	o_pPo,			// ��_
							MINT*		o_pist1,		// �⏕�X�e�C�^�X1
														//		MC_LEFT:	������1�͐�����2�̍����ɂ���	�i�����Ȃ��j
														//		MC_RIGHT:	������1�͐�����2�̉E���ɂ���	�i�����Ȃ��j
														//		MC_CLOSS:	������1�͐�����2�ƌ���			�i��������j
														//		MC_ON_LINE:	������1�͐�����2�̒�����ɂ���	�i���s�j
							MINT*		o_pist2			// �⏕�X�e�C�^�X2
														//		MC_PS_FAR:	������1�͐�����2���n�_���������i�����Ȃ��܂��͌�������j
														//		MC_PE_FAR:	������1�͐�����2���I�_���������i�����Ȃ��܂��͌�������j
														//		MC_PARALEL:	������1�͐�����2���n�_�ƏI�_�͓�����	�i���s�j
					);

	};


} // namespace MC