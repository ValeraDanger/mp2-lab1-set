#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {
}

// ����������� �����������
TSet::TSet(const TSet& s): MaxPower(s.MaxPower), BitField(s.BitField) {
}

// ����������� �������������� ����
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {
}

TSet::operator TBitField() {
    return this->BitField;
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
    this->BitField.ClrBit(Elem);
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet& s) // ������������
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // ���������
{
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // ���������
{
    return this->BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // �����������
{
    TSet TMP = this->BitField | s.BitField;
    return TMP;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
    TSet TMP = *this;
    TMP.InsElem(Elem);
    return TMP;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
    TSet TMP = *this;
    TMP.DelElem(Elem);
    return TMP;
}

TSet TSet::operator*(const TSet& s) // �����������
{
    TSet TMP = this->BitField & s.BitField;
    return TMP;
}

TSet TSet::operator~(void) // ����������
{
    TSet TMP = ~(this->BitField);
    return TMP;
}

// ���������� �����/������

istream& operator>>(istream& istr, TSet& s) // ����
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // �����
{
    ostr << s.BitField;
    return ostr;
}