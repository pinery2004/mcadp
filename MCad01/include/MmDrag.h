/* MmDrag.H
* 
 * Abstract
 * MmDrag.h classes : declaration
 *
 */ 
#pragma once

																								//E #include "MCAD.h"

namespace MC
{

class MmWndInfo;
enum MmDragType
{
	NO,
	ZOOM,									// ズーム処理のマウス左ボタンダウン移動中
	ZOOM_WAIT,								// ズーム処理のマウス左ボタンダウンの移動待ち
	PAN,									// 移動処理中
	ROT_CYL,
	ROT_CYL_X,
	ROT_CYL_Y,
	ROT_CYL_Z,
	ROT_SPH
};

class MmDrag
{
	public:
		MmDrag() {};
		MmDrag(MmWndInfo* pWndInfo, MgPoint2D ptStart);
		~MmDrag(void);

		void SetMotion( MmDragType Motion)
						{ m_Motion = Motion;}
		MmDragType GetMotion()
						{ return m_Motion;}
		void SetLastPt( MgPoint2D ptLatest)
						{ m_ptLast = ptLatest;}
//		MgPoint2D GetLastPt()
//						{ return m_ptLast;}
		void SetStartPt( MgPoint2D ptLatest)
						{ m_ptStart = ptLatest;};
		MgPoint2D GetStartPt()
						{ return m_ptStart;};
		virtual bool Continue( MmWndInfo* pWndInfo, MgPoint2D ptLatest);

	protected:
		MmWndInfo*		m_pWndInfo;
		MgPoint2D		m_ptStart;
		MgPoint2D		m_ptLast;
		MINT			m_iPrevCursorMode;

		void			RedrawAfter( MmWndInfo* pWndInfo);

	public:
		MmDragType		m_Motion;
};
	

class MmDragZoom : public MmDrag
{
	public:
		MmDragZoom( MmWndInfo* pWndInfo, MgPoint2D ptStart);

		bool Continue( MmWndInfo* pWndInfo, MgPoint2D ptLatest);

};
	

class MmDragPan : public MmDrag
{
	public:
		MmDragPan( MmWndInfo* pWndInfo, MgPoint2D ptStart);

		bool Continue( MmWndInfo* pWndInfo, MgPoint2D ptLatest);
};

// _MmDrag_H

} // namespace MC
