
// ���_V0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎��̖ʕ������߂�
inline MUSHORT MgEdgeNode::fcwv( MUSHORT v0)
{
	return ( ( v0 == PVT) ? NFACE: PFACE);
}

// ���_V0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎��̖ʕ������߂�
inline MUSHORT MgEdgeNode::fccwv( MUSHORT v0)
{
	return ( ( v0 == PVT) ? PFACE: NFACE);
}

// ���_V0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::ecwv( MUSHORT v0)
{
	return ( ( v0 = PVT) ? NCCW: PCCW);
}

// ���_V0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::eccwv( MUSHORT v0)
{
	return ( ( v0 == PVT) ? NCW: PCW);
}

// �ʕ�f0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::ecwf( MUSHORT f0)
{
	return ( ( f0 == PFACE) ? PCW: NCW);
}

// �ʕ�f0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::eccwf( MUSHORT f0)
{
	return ( ( f0 == PFACE) ? PCCW: NCCW);
}

// �ʕ�f0�̎���ɁA���v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::vcwf( MUSHORT f0)
{
	return ( ( f0 == PFACE) ? PCW: NCW);
}

// �ʕ�f0�̎���ɁA�����v��]�����ɉ�]�����ꍇ�̎���Edge�����߂�
inline MUSHORT MgEdgeNode::vccwf( MUSHORT f0)
{
	return ( ( f0 == PFACE) ? PCCW: NCCW);
}

// ���[���h�m�[�h�ւ̃|�C���^�𓾂�
inline MgWorldNode* MgNode::WRLD()			// (  O) ���[���h�m�[�h�ւ̃|�C���^
{
	return ( (MgWorldNode *)m_Node);
}

// ��m�[�h�h�c�����m�[�h�ւ̃|�C���^�𓾂�
inline MgEmptyNode* MgNode::EMPT(			// (  O) ��m�[�h�ւ̃|�C���^
						MINT	iM1			// (I  ) ��m�[�h�h�c(�z��ԍ�)
				)	
{
	return ( (MgEmptyNode *)&m_Node[iM1 * MSZNODE]);
}

// �\���b�h�m�[�h�h�c����\���b�h�m�[�h�ւ̃|�C���^�𓾂�
inline MgSolidNode* MgNode::SOLD(			// (  O) �\���b�h�m�[�h�ւ̃|�C���^
						MINT	iB1			// (I  ) �\���b�h�m�[�h�h�c(�z��ԍ�)
				)
{
	return ( (MgSolidNode *)&m_Node[iB1 * MSZNODE]);
}

// �Ő��m�[�h�h�c����Ő��m�[�h�ւ̃|�C���^�𓾂�
inline MgEdgeNode* MgNode::EDGE(			// (  O) �Ő��m�[�h�ւ̃|�C���^
						MINT	iE1			// (I  ) �Ő��m�[�h�h�c(�z��ԍ�)
				)
{
	return ( (MgEdgeNode *)&m_Node[iE1 * MSZNODE]);
}

// �ʃm�[�h�h�c����ʃm�[�h�ւ̃|�C���^�𓾂�
inline MgFaceNode* MgNode::FACE(			// (  O) �ʃm�[�h�ւ̃|�C���^
						MINT	iF1			// (I  ) �ʃm�[�h�h�c(�z��ԍ�)
				)
{
	return ( (MgFaceNode *)&m_Node[iF1 * MSZNODE]);
}

// ���_�m�[�h�h�c���璸�_�m�[�h�ւ̃|�C���^�𓾂�
inline MgVertexNode* MgNode::VRTX(			// (  O) ���_�m�[�h�ւ̃|�C���^
						MINT	iV1			// (I  ) ���_�m�[�h�h�c(�z��ԍ�)
				)
{
	return ( (MgVertexNode *)&m_Node[iV1 * MSZNODE]);
}

// �m�[�h���[���N���A����
inline void MgNode::CLR(
						MINT	iN1			// (I  ) �m�[�h�h�c(�z��ԍ�)
				)
{
	memset( &m_Node[iN1], 0, MSZNODE * sizeof(MINT));
}

// �m�[�h���[���N���A����
inline void MgNode::CLR(
						void*	pN1			// (I  ) �m�[�h�ւ̃|�C���^
				)
{
	memset( pN1, 0, MSZNODE * sizeof(MINT));
}

//	��m�[�h�𐶐�����
inline MINT MgNode::mkm()					// (  O) �󂫃m�[�h�h�c(�z��ԍ�)
{
	// ���R�̈�̐擪�m�[�h���g�p�\�ȃm�[�h�Ƃ���
	MINT iM1 = WRLD()->nlnk;
	
	// ���R�̈悩��̃����N����菜��
	WRLD()->nlnk = EMPT( iM1)->nlnk;							// �擾�m�[�h�̎��̃m�[�h
	EMPT( WRLD()->nlnk)->plnk = 0;								// WORLD�m�[�h

	return iM1;
}

//	�ʕ��A�Ő��A���_�̊e�����O�͋�̏�ԂŃ\���b�h�̃m�[�h�𐸐����A
//	���[���h�u���b�N�̃\���b�h�̃����O�Ɋ܂߂�
inline MINT MgNode::mks()					// (  O) �\���b�h�m�[�h�h�c(�z��ԍ�)
{
	// �g�p�\�ȃm�[�h���\���b�h�̃m�[�h	�Ƃ���
	MINT iS1 = mkm();
	
	//	�ʕ��A�Ő��A���_�̊e�����O�͋�̏�Ԃɂ���
	SOLD( iS1)->NFACE = SOLD( iS1)->PFACE = iS1;				// �ʃ����O�͋�
	SOLD( iS1)->NED = SOLD( iS1)->PED = iS1;					// �Ő������O�͋�
	SOLD( iS1)->NVT = SOLD( iS1)->PVT = iS1;					// ���_�����O�͋�

	return iS1;
}

//	�V�����ʕ��̃m�[�h�𐶐����A�ʕ��̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
inline MINT MgNode::mkf(					// (  O) �ʕ��m�[�h�h�c(�z��ԍ�)
						MINT	iS1			// (I  ) �\���b�h�m�[�h�h�c(�z��ԍ�)
				)
{
	// �g�p�\�ȃm�[�h��ʕ��̃m�[�h�Ƃ���
	MINT iF1 = mkm();
	
	// �ʕ��̃m�[�h���\���b�h�̖ʕ��̃����N�̍ŏI�ɕt����
	FACE( iF1)->NFACE = iS1;
	FACE( iF1)->PFACE = SOLD( iS1)->PFACE;
	FACE( FACE( iF1)->PFACE)->NFACE = iF1;
	SOLD( iS1)->PFACE = iF1;

	return iF1;
}

//	�V�����Ő��̃m�[�h�𐶐����A�Ő��̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
inline MINT MgNode::mke(					// (  O) �Ő��m�[�h�h�c(�z��ԍ�)
						MINT	iS1			// (I  ) �\���b�h�m�[�h�h�c(�z��ԍ�)
				)
{
	// �g�p�\�ȃm�[�h��Ő��̃m�[�h�Ƃ���
	MINT iE1 = mkm();

	// �Ő��̃m�[�h���\���b�h�̗Ő��̃����N�̍ŏI�ɕt����
	EDGE( iE1)->NED = iS1;
	EDGE( iE1)->PED = SOLD( iS1)->PED;
	EDGE( EDGE( iE1)->PED)->NED = iE1;
	SOLD( iS1)->PED = iE1;

	return iE1;
}

//	�V�������_�̃m�[�h�𐶐����A���_�̃����O���Ɋ܂߂�(�����N�̍ŏI�ɕt����)
inline MINT MgNode::mkv(						// (  O) ���_�m�[�h�h�c(�z��ԍ�)
						MINT	iS1				// (I  ) �\���b�h�m�[�h�h�c(�z��ԍ�)
				)
{
	// �g�p�\�ȃm�[�h�𒸓_�̃m�[�h�Ƃ���
	MINT iV1 = mkm();

	// ���_�̃m�[�h���\���b�h�̒��_�̃����N�̍ŏI�ɕt����
	VRTX( iV1)->NVT = iS1;
	VRTX( iV1)->PVT = SOLD( iS1)->PVT;
	VRTX( VRTX( iV1)->PVT)->NVT = iV1;
	SOLD( iS1)->PVT = iV1;

	return iV1;
}

// �m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
inline void MgNode::klm(
						MINT	iM1				// (I  ) �m�[�h�h�c (�z��ԍ�)
				)
{
	// �m�[�h�������O��菜������
	MINT iMn = EMPT( iM1)->nlnk;
	MINT iMp = EMPT( iM1)->plnk;
	EMPT( iMn)->plnk = iMp;
	EMPT( iMp)->nlnk = iMn;

	// �t���[�ɂȂ����m�[�h���A���R�̈�̐擪�m�[�h�Ƃ��ă����N�t����
	EMPT( iM1)->nlnk = 0;
	EMPT( iM1)->plnk = WRLD()->plnk;
	WRLD()->plnk = iM1;
}

// �\���b�h�̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
inline void MgNode::kls(
						MINT	iS1				// (I  ) �\���b�h�̃m�[�h�h�c (�z��ԍ�)
				)
{
	klm( iS1);
}

// �ʕ��̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
inline void  MgNode::klf(
						 MINT	iF1				// (I  ) �ʕ��m�[�h�h�c (�z��ԍ�)
				)
{
	klm( iF1);
}

// �Ő��̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
inline void  MgNode::kle(
						 MINT	iE1				// (I  ) �Ő��m�[�h�h�c (�z��ԍ�)
				)
{
	klm( iE1);
}

// ���_�̃m�[�h�������O��菜�����A���R�̈�ւ̕ԋp���s��
inline void  MgNode::klv(
						 MINT	iV1				// (I  ) ���_�m�[�h�h�c (�z��ԍ�)
				)
{
	klm( iV1);
}

