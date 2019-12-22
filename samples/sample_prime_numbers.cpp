TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// ����������� �����������
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	this->MaxPower = s.MaxPower;
}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	this->MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return TBitField(BitField);
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
	return this->MaxPower;
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
	if (Elem < MaxPower) {
		BitField.SetBit(Elem);
	}
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
	if (Elem < MaxPower) {
		BitField.ClrBit(Elem);
	}
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{
	if (this == &s) {
		return *this;
	}
	this->BitField = s.BitField;
	this->MaxPower = s.MaxPower;
}

int TSet::operator==(const TSet &s) const // ���������
{
	if (this->MaxPower != s.MaxPower) {
		return 0;//false
	}
	if (this->BitField == s.BitField) {
		return 1;//true
	}
	return 0;//false
}

int TSet::operator!=(const TSet &s) const // ���������
{
	if (this->MaxPower != s.MaxPower) {
		return 1;//true
	}
	if (this->BitField != s.BitField) {
		return 1;//true
	}
	return 0;//false
}

TSet TSet::operator+(const TSet &s) // �����������
{
	TSet tmp(this->BitField | s.BitField);
	return tmp;
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
	TSet tmp(BitField);
	tmp.BitField.SetBit(Elem);
	return tmp;
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
	TSet tmp(BitField);
	tmp.BitField.ClrBit(Elem);
	return tmp;
}

TSet TSet::operator*(const TSet &s) // �����������
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

TSet TSet::operator~(void) // ����������
{
	TSet tmp(BitField);
	return tmp;
}

// ���������� �����/������

istream &operator�(istream &istr, TSet &s) // ����
{
	istr � s.BitField;
	return istr;
}

ostream& operator�(ostream &ostr, const TSet &s) // �����
{
	ostr � s.BitField;
	return ostr;
}