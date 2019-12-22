// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len < 0) {
		throw(" ");
	}
	BitLen = len;
	MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen) {
		throw(" ");
	}
	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen) {
		throw(" ");
	}
	return 1 << 32 * GetMemIndex(n) + n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0) {
		throw(" ");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen) {
		throw(" ");
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen) {
		throw(" ");
	}
	return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this == &bf) {
		return *this;
	}
	delete[]pMem;
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 0;
	}
	int flag = 1;
	for (int i = 0; i < MemLen; i++) {
		if (GetMemIndex(i) != bf.GetMemIndex(i)) {
			flag = 0;
		}
	}
	return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) {
		return 1;//true
	}
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i]) {
			return 1;//true
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen) {
		TELEM *tmp = new TELEM[bf.MemLen];
		for (int i = 0; i < MemLen; i++) {
			tmp[i] = pMem[i];
		}
		for (int i = MemLen; i < bf.MemLen; i++) {
			tmp[i] = 0;
		}
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = tmp;
	}
	for (int i = 0; i < MemLen; i++) {
		pMem[GetMemIndex(i)] |= bf.GetMemIndex(i);
	}
	return *this;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen < bf.BitLen) {
		TELEM *tmp = new TELEM[bf.MemLen];
		for (int i = 0; i < MemLen; i++) {
			tmp[i] = pMem[i];
		}
		for (int i = MemLen; i < bf.MemLen; i++) {
			tmp[i] = 0;
		}
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = tmp;
	}
	for (int i = 0; i < MemLen; i++) {
		pMem[GetMemIndex(i)] &= bf.GetMemIndex(i);
	}
	return *this;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] == 0) {
			pMem[i] = 1;
		}
		else
		{
			pMem[i] = 0;
		}
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int temp;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> temp;
		if (temp == 1) bf.SetBit(i);
		else bf.ClrBit(i);
	}
	return istr;
}


ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		if (bf.GetBit(i)) {
			ostr << i << " ";
		}
	}
	return ostr;
}
