#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len) {
    this->BitLen = len;
    this->MemLen = (this->BitLen - 1) / (sizeof(TELEM) * 8) + 1;
    this->pMem = new TELEM[len];
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->BitLen];
    for (int i = 0; i < this->BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField() {
    delete[this->BitLen] this->pMem;
    this->pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n > this->BitLen - 1) {
        throw(out_of_range("Index out of range"));
    }
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n > this->BitLen - 1) {
        throw(out_of_range("Index out of range"));
    }
    return pow(2, n % 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return this->BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > this->BitLen - 1) {
        throw(out_of_range("Index out of range"));
    }
    this->pMem[n] = 1;
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > this->BitLen - 1) {
        throw(out_of_range("Index out of range"));
    }
    this->pMem[n] = 0;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n > this->BitLen - 1) {
        throw(out_of_range("Index out of range"));
    }
    return this->pMem[n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    delete[this->BitLen] this->pMem;
    this->BitLen = bf.BitLen;
    this->MemLen = bf.MemLen;
    this->pMem = new TELEM[this->BitLen];
    for (int i = 0; i < this->BitLen; i++) {
        this->pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
    if (this->BitLen != bf.BitLen) {
        return false;
    }

    for (int i = 0; i < this->BitLen; i++) {
        if (this->pMem[i] != bf.pMem[i]) {
            return false;
        };
    }

    return true;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
    if (this->BitLen != bf.BitLen) {
        throw(length_error("Length of fields not equal"));
    }

    TBitField res(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        res.pMem[i] = (this->pMem[i] | bf.pMem[i]);
    }

    return res;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
    if (this->BitLen != bf.BitLen) {
        throw(length_error("Length of fields not equal"));
    }

    TBitField res(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        res.pMem[i] = (this->pMem[i] & bf.pMem[i]);
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(this->BitLen);
    for (int i = 0; i < this->BitLen; i++) {
        res.pMem[i] = !this->pMem[i];
    }

    return res;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    for (size_t i = 0; i < bf.GetLength(); i++) {
        int tmp;
        istr >> tmp;
        if (tmp == 0) {
            bf.ClrBit(i);
        }

        else if (tmp == 1){
            bf.SetBit(i);
        }

        else {
            throw std::invalid_argument("Bit value should be 0 or 1");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i) << ", ";
    }
    return ostr;
}
