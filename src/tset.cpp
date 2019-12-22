// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	this->MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return TBitField(BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < MaxPower) {
		BitField.SetBit(Elem);
	}
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < MaxPower) {
		BitField.ClrBit(Elem);
	}
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	if (this == &s) {
		return *this;
	}
	this->BitField = s.BitField;
	this->MaxPower = s.MaxPower;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (this->MaxPower != s.MaxPower) {
		return 0;//false
	}
	if (this->BitField == s.BitField) {
		return 1;//true
	}
	return 0;//false
}


int TSet::operator!=(const TSet &s) const // сравнение
{
	if (this->MaxPower != s.MaxPower) {
		return 1;//true
	}
	if (this->BitField != s.BitField) {
		return 1;//true
	}
	return 0;//false
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet tmp(this->BitField | s.BitField);
	return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet tmp(BitField);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet tmp(BitField);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (this->MaxPower >= s.MaxPower) {
		TSet tmp(BitField);
		tmp.BitField = tmp.BitField & s.BitField;
		return tmp;
	}
	else {
		TSet tmp(s.BitField);
		tmp.BitField = tmp.BitField & this->BitField;
		return tmp;
	}
}

TSet TSet::operator~(void) // дополнение
{
	TSet tmp(BitField);
	return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return ostr;
}