//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MsTime.cpp
//
//		��������
//
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
#include "MsLib.h"

namespace MC
{

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z���ݎ������擾����
//�y�Ԓl�zMTIME�^�@���ݎ���

MTIME mslib::GetCurrentTime()
{
	return CTime::GetCurrentTime();
}

	//struct	tm newTime;
	//time_t	longTime;
	//static char	cTimeBf[26];
	//errno_t err;

	//time(&longTime);
	//err = localtime_s( &newTime, &longTime );
	//ASSERT( err);

	//long yy = newTime.tm_year+1900;				// �N 
	//long mm = newTime.tm_mon+1;					// ��
	//long dd = newTime.tm_mday;					// ��
	//long wk = newTime.tm_wday;					// �j��
	//long hh = newTime.tm_hour;					// ���� 
	//long mn = newTime.tm_min;					// ��
	//long ss = newTime.tm_sec;					// �b


////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�������r����
//�y�Ԓl�z��r���� -1 : cTime1������
//					0 : ����
//					1 : cTime2������

MINT MsCmpTime(
						MTIME		i_cTime1,	// ��r�Ώێ���1
						MTIME		i_cTime2	// ��r�Ώێ���2
				)
{

	MINT		ist;

	if ( i_cTime1 < i_cTime2)
		ist = -1;
	else if ( i_cTime1 == i_cTime2)
		ist = 0;
	else
		ist = 1;

	return ist;
}

////////////////////////////////////////////////////////////////////////////
//�y�@�\�z�����^�����ɕϊ�����
//�y�Ԓl�z> 0 : MTIME�^�@���ݎ���
//		  < 0 : �G���[

MTIME MsMTime(
						MINT		i_iYear,	// �N
						MINT		i_iMonth,	// ��
						MINT		i_iDay,		// ��
						MINT		i_iHour,	// ��
						MINT		i_iMin,		// ��
						MINT		i_iSec		// �b
				)
{
	return CTime( i_iYear, i_iMonth, i_iDay, i_iHour, i_iMin, i_iSec, 0);
}

///////////////////////////////////////////////////////////////////////////////
//	CTime�̓�����CString�ɕϊ�����
CString MsCnvSCTime(							// 
						MINT		i_iMode,	// �ϊ��`��
												//	 1: YYMMDD
												//	 2: YYMMDDhh
												//	 3: YYMMDDhhmm
												//	 4: YYMMDDhhmmss
												//	11: YYYYMMDD
												//	12: YYYYMMDDhh
												//	13: YYYYMMDDhhmm
												//	14: YYYYMMDDhhmmss
												//	21: YY/MM/DD
												//	23: YY/MM/DD hh:mm
												//	24: YY/MM/DD hh:mm:ss
												//	31: YYYY/MM/DD
												//	33: YYYY/MM/DD hh:mm
												//	34: YYYY/MM/DD hh:mm:ss
						CTime&		i_theTime	// CTime ����
				)
{
	static MCHAR cTimeBf[20];

	MINT iYear	= i_theTime.GetYear();
	MINT iMonth	= i_theTime.GetMonth();
	MINT iDay	= i_theTime.GetDay();
	MINT iHour	= i_theTime.GetHour();
	MINT iMin	= i_theTime.GetMinute();
	MINT iSec	= i_theTime.GetSecond();

	switch ( i_iMode)
	{
	case 1:
		Msprintf_s( cTimeBf, Mstr( "%02d%02d%02d"), iYear-2000, iMonth, iDay);
		break;
	case 2:
		Msprintf_s( cTimeBf, Mstr( "%02d%02d%02d%02d"), iYear-2000, iMonth, iDay, iHour);
		break;
	case 3:
		Msprintf_s( cTimeBf, Mstr( "%02d%02d%02d%02d%02d"), iYear-2000, iMonth, iDay, iHour, iMin);
		break;
	case 4:
		Msprintf_s( cTimeBf, Mstr( "%02d%02d%02d%02d%02d%02d"), iYear-2000, iMonth, iDay, iHour, iMin, iSec);
		break;
	case 11:
		Msprintf_s( cTimeBf, Mstr( "%4d%02d%02d"), iYear, iMonth, iDay);
		break;
	case 12:
		Msprintf_s( cTimeBf, Mstr( "%4d%02d%02d %02d"), iYear, iMonth, iDay, iHour);
		break;
	case 13:
		Msprintf_s( cTimeBf, Mstr( "%4d%02d%02d %02d:%02d"), iYear, iMonth, iDay, iHour, iMin);
		break;
	case 14:
		Msprintf_s( cTimeBf, Mstr( "%4d%02d%02d %02d:%02d:%02d"), iYear, iMonth, iDay, iHour, iMin, iSec);
		break;
	case 21:
		Msprintf_s( cTimeBf, Mstr( "%02d/%02d/%02d"), iYear-2000, iMonth, iDay);
		break;
	case 22:
		Msprintf_s( cTimeBf, Mstr( "%02d/%02d/%02d %02d"), iYear-2000, iMonth, iDay, iHour);
		break;
	case 23:
		Msprintf_s( cTimeBf, Mstr( "%02d/%02d/%02d %02d:%02d"), iYear-2000, iMonth, iDay, iHour, iMin);
		break;
	case 24:
		Msprintf_s( cTimeBf, Mstr( "%02d/%02d/%02d %02d:%02d:%02d"), iYear-2000, iMonth, iDay, iHour, iMin, iSec);
		break;
	case 31:
		Msprintf_s( cTimeBf, Mstr( "%4d/%02d/%02d"), iYear, iMonth, iDay);
		break;
	case 32:
		Msprintf_s( cTimeBf, Mstr( "%4d/%02d/%02d %02d"), iYear, iMonth, iDay, iHour);
		break;
	case 33:
		Msprintf_s( cTimeBf, Mstr( "%4d/%02d/%02d %02d:%02d"), iYear, iMonth, iDay, iHour, iMin);
		break;
	case 34:
		Msprintf_s( cTimeBf, Mstr( "%4d/%02d/%02d %02d:%02d:%02d"), iYear, iMonth, iDay, iHour, iMin, iSec);
		break;
	}
	return cTimeBf;
}

///////////////////////////////////////////////////////////////////////////////
//	�c�F���[�̌���
//	(�N�A���A���@����@�j�������߂�: 0�����j�A1�����j�A�c6���y�j)
int zeller(int y, int m, int d)
{
	int value;
	
	if( m == 1 || m == 2) {
		--y; /* 1,2���͑O�̔N��13,14���Ƃ��Ĉ������߂P�N�߂����߂�-1������ */
		m += 12; /* 1,2���͑O�̔N��13,14���Ƃ��Ĉ�������12�𑫂� */
	} 

	value = (y + y / 4 - y / 100 + y / 400 + (13 * m + 8) / 5 + d) % 7;
		/* �i�N + �N / 4 - �N / 100 + �N / 400 + (13 * �� + 8) / 5 + ��)
			���V�Ŋ������]��Ƃ����c�F���[�̌������̂��� */
	
	return value; /* �����̌��ʂ�߂�l�Ƃ��� */
}

} // namespace MC