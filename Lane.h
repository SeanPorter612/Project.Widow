#pragma once

class LaneV2
{
// Construction
public:
	LaneV2();

// Attributes
public:

// Operations
public:
	virtual void TransformString ( char* csKey, char* csTarget);

protected:
	virtual void SetKey ( char* csKey);
	virtual void GetKey ( char* csKey);
	virtual void TransformChar ( unsigned char& csTarget );

// Implementation
public:
	virtual ~LaneV2( );

// Attributes
protected:

	char* m_csKey;

    unsigned long           m_LFSR_A;
    unsigned long           m_LFSR_B;
    unsigned long           m_LFSR_C;
    const unsigned long     m_Mask_A;
    const unsigned long     m_Mask_B;
    const unsigned long     m_Mask_C;
    const unsigned long     m_Rot0_A;
    const unsigned long     m_Rot0_B;
    const unsigned long     m_Rot0_C;
    const unsigned long     m_Rot1_A;
    const unsigned long     m_Rot1_B;
    const unsigned long     m_Rot1_C;

};