//==========================================================================================
//  Copyright (C) 2006-2008. K.Matsu. All rights reserved.
//
//  MODULE: MgSort.cpp
//
//  K.Matsu           08/01/04    Created.
//==========================================================================================
#include "stdafx.h"
#include "MsBasic.h"
//#include "MlLog.h"

#define	DLL_EXPORT_GEO_DO

#include "MgLib.h"

namespace MC
{

//
//===========================================================================
//	�_����x�N�g�������̍��W���ɕ��ד�����W�̓_�͎�菜��
//
void	MGeo::SortVGPt2(						//
				const	MgVect2D&	V1, 		// (I  ) �x�N�g��
						MgGPoint2D*	GPt2 		// (I O) �_�Q
		)	
{
	MINT	ic;
	bool	bswap;
	MINT	inum = GPt2->m_n;
//
	MBMALCBUFF( dd, MREAL, inum, MX_PNT1); 
//
	if ( inum < 2) MQUIT;
//
	for ( ic=0; ic<inum; ic++) {
		dd[ic] = GPt2->m_p[ic] * V1;
	}
//
	MINT	icf = 1;
	do {
		bswap = false;
		for ( ic=icf; ic<inum; ic++) {
			if (dd[ic-1] > dd[ic]) {
				msSwap( GPt2->m_p[ic-1], GPt2->m_p[ic]);
				msSwap( dd[ic-1], dd[ic]);
				bswap = true;
			}
		}
		if (!bswap) break;
		bswap = false;
		for ( ic=inum-1; ic>0; ic--) {
			if (dd[ic-1] > dd[ic]) {
				msSwap( GPt2->m_p[ic-1], GPt2->m_p[ic]);
				msSwap( dd[ic-1], dd[ic]);
				bswap = true;
			}
		}
		icf = 2;
	} while (bswap);
//
	MINT	ic1 = 0;
	for ( ic=1; ic<inum; ic++) {
		if (GPt2->m_p[ic] != GPt2->m_p[ic1]) GPt2->m_p[++ic1] = GPt2->m_p[ic];
	}
	GPt2->m_n = ic1 + 1;
exit:;
}

////
////===========================================================================
////	�����Q�𐳋K������B�i�����̋t�����̏d�Ȃ����������j
////
//void	MgNorm(									//
//				const	MgGLine2D&	GLn1,		// (I  ) ����
//				const	MgGLine2D*	GLn2		// (  O) �d�Ȃ��������̐���
//		)
//{
//	MgLine2D		work[MX_LIN1+1];			// �����̐��p�̃G���A��ǉ�������ƃG���A���m�ۂ���
//	MgGLine2D	*GLn = (MgGLine2D*)work;
//	MgDivideGLn2( GLn1, GLn);					// ��������_�ŕ�������
////	MgThinOut( *GLn, GLn2);					// ���������ƊJ���[�����������Ԉ���
//}

/*
//===========================================================================
//
//	QuickSort �T���v��
//
typedef struct {
	int index;
	float fSomeFloat;
	TCHAR SomeString[128];
} UserType;

BOOL operator > (UserType & first, UserType & second)
{
	return (first.index > second.index);
}

BOOL operator < (UserType & first, UserType & second)
{
	return (first.index < second.index);
}

void MgSample_sort1() 
{
	if (m_iType == 0) {
		CQArray <int, int &> qArr;
		qArr.SetSize(m_uiArrSize);
		qArr.QuickSort(m_bAscending);
	} else {
		CQArray <UserType, UserType &> qArr;
		qArr.SetSize(m_uiArrSize);
		qArr.QuickSort(m_bAscending);
	}
}

void MgSample_sort2() 
{
	if (m_iType == 0) {
		int *dataArray = new int[m_uiArrSize];
		QuickSort(dataArray,m_uiArrSize,m_bAscending);
		delete [] dataArray;
	} else {
		UserType *dataArray = new UserType[m_uiArrSize];
		QuickSort(dataArray,m_uiArrSize,m_bAscending);
		delete [] dataArray;
	}
}
*/

///*
//// Sorts on a given column using the cell text
//BOOL CGridCtrl::SortTextItems(int nCol, BOOL bAscending, LPARAM data /* = 0 */)
//{
//    return CGridCtrl::SortItems(pfnCellTextCompare, nCol, bAscending, data);
//}
//
//void CGridCtrl::SetCompareFunction(PFNLVCOMPARE pfnCompare)
//{
//	m_pfnCompare = pfnCompare;
//}
//
//// Sorts on a given column using the cell text and using the specified comparison
//// function
//BOOL CGridCtrl::SortItems(int nCol, BOOL bAscending, LPARAM data /* = 0 */)
//{
//    SetSortColumn(nCol);
//    SetSortAscending(bAscending);
//    ResetSelectedRange();
//    SetFocusCell(-1, - 1);
//
//	if (m_pfnCompare == NULL)
//		return CGridCtrl::SortItems(pfnCellTextCompare, nCol, bAscending, data);
//	else
//	    return CGridCtrl::SortItems(m_pfnCompare, nCol, bAscending, data);
//}
//
//// Sorts on a given column using the supplied compare function (see CListCtrl::SortItems)
//BOOL CGridCtrl::SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending,
//                          LPARAM data /* = 0 */)
//{
//    SetSortColumn(nCol);
//    SetSortAscending(bAscending);
//    ResetSelectedRange();
//    SetFocusCell(-1, -1);
//    return SortItems(pfnCompare, nCol, bAscending, data, GetFixedRowCount(), -1);
//}
//
//int CALLBACK CGridCtrl::pfnCellTextCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//{
//	UNUSED_ALWAYS(lParamSort);
//
//	CGridCellBase* pCell1 = (CGridCellBase*) lParam1;
//	CGridCellBase* pCell2 = (CGridCellBase*) lParam2;
//	if (!pCell1 || !pCell2) return 0;
//
//	return _tcscmp(pCell1->GetText(), pCell2->GetText());
//}
//
//int CALLBACK CGridCtrl::pfnCellNumericCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//{
//	UNUSED_ALWAYS(lParamSort);
//
//	CGridCellBase* pCell1 = (CGridCellBase*) lParam1;
//	CGridCellBase* pCell2 = (CGridCellBase*) lParam2;
//	if (!pCell1 || !pCell2) return 0;
//
//	int nValue1 = _ttol(pCell1->GetText());
//	int nValue2 = _ttol(pCell2->GetText());
//
//	if (nValue1 < nValue2)
//		return -1;
//	else if (nValue1 == nValue2)
//		return 0;
//	else
//		return 1;
//}
//
//// private recursive sort implementation
//BOOL CGridCtrl::SortItems(PFNLVCOMPARE pfnCompare, int nCol, BOOL bAscending, LPARAM data,
//                          int low, int high)
//{
//    if (nCol >= GetColumnCount())
//        return FALSE;
//
//    if (high == -1)
//        high = GetRowCount() - 1;
//
//    int lo = low;
//    int hi = high;
//    
//    if (hi <= lo)
//        return FALSE;
//    
//    //LPARAM midItem = GetItemData((lo + hi)/2, nCol);
//	LPARAM pMidCell = (LPARAM) GetCell((lo + hi)/2, nCol);
//    
//    // loop through the list until indices cross
//    while (lo <= hi)
//    {
//        // Find the first element that is greater than or equal to the partition 
//        // element starting from the left Index.
//        if (bAscending)
//            while (lo < high  && pfnCompare( (LPARAM)GetCell(lo, nCol), (LPARAM) pMidCell, data) < 0)
//                ++lo;
//        else
//            while (lo < high && pfnCompare((LPARAM)GetCell(lo, nCol), pMidCell, data) > 0)
//				++lo;
//                
//		// Find an element that is smaller than or equal to  the partition 
//		// element starting from the right Index.
//		if (bAscending)
//			while (hi > low && pfnCompare((LPARAM)GetCell(hi, nCol), pMidCell, data) > 0)
//				--hi;
//		else
//			while (hi > low && pfnCompare((LPARAM)GetCell(hi, nCol), pMidCell, data) < 0)
//				--hi;
//                        
//        // If the indexes have not crossed, swap if the items are not equal
//        if (lo <= hi)
//        {
//			// swap only if the items are not equal
//            if ( pfnCompare((LPARAM)GetCell(lo, nCol), (LPARAM)GetCell(hi, nCol), data) != 0)
//            {
//				for (int col = 0; col < GetColumnCount(); col++)
//                {
//					CGridCellBase *pCell = GetCell(lo, col);
//                    SetCell(lo, col, GetCell(hi, col));
//                    SetCell(hi, col, pCell);
//                }
//                UINT nRowHeight = m_arRowHeights[lo];
//                m_arRowHeights[lo] = m_arRowHeights[hi];
//                m_arRowHeights[hi] = nRowHeight;
//            }
//                            
//            ++lo;
//            --hi;
//         }
//    }
//    
//    // If the right index has not reached the left side of array
//    // must now sort the left partition.
//    if (low < hi)
//        SortItems(pfnCompare, nCol, bAscending, data, low, hi);
//    
//    // If the left index has not reached the right side of array
//    // must now sort the right partition.
//    if (lo < high)
//        SortItems(pfnCompare, nCol, bAscending, data, lo, high);
//    
//    return TRUE;
//}
//
//*/

} // namespace MC
