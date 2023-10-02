#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {
}

// конструктор копирования
TSet::TSet(const TSet& s): MaxPower(s.MaxPower), BitField(s.BitField) {
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf) {
}

TSet::operator TBitField() {
    return this->BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return this->BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    this->BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    this->BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return this->BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return this->BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    TSet TMP = this->BitField | s.BitField;
    return TMP;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet TMP = *this;
    TMP.InsElem(Elem);
    return TMP;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet TMP = *this;
    TMP.DelElem(Elem);
    return TMP;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet TMP = this->BitField & s.BitField;
    return TMP;
}

TSet TSet::operator~(void) // дополнение
{
    TSet TMP = ~(this->BitField);
    return TMP;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    ostr << s.BitField;
    return ostr;
}