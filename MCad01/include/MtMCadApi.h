////////////////////////////////////////////////////////////////////////////
//    �R�}���h�����p�o�b�N�O���E���h�̃^�X�N�̋N��
////////////////////////////////////////////////////////////////////////////
#pragma once

namespace MC
{

void	MtCmdOpen();
void	MtCmdClose();

UINT	MtThreadProcedure( LPVOID);
bool	MtLaunch( void);
void	MtCloseThread( void);
MINT	MtStopThread( void);
bool	MtChkStopThread( void);
	
} // namespace MC