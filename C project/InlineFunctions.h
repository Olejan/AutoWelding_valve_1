//=========================== inline section ===============================
// Write here inline functions
//==========================================================================
inline BOOL isPedal1Pressed()
{
	if(!(PINPEDAL1 & (1<<pinPedal1)))
		return TRUE; // ������ ���������������� ������ ������
	return FALSE; // ������ ���������������� ������ ������
}
inline BOOL isPedal2Pressed()
{
	if(!(PINPEDAL2 & (1<<pinPedal2)))
		return TRUE; // ������ ������
	return FALSE; // ������ ������
}
//==========================================================================
