// NoRules Compiler Library 
// ���������� ���������� - NRC.H

#include <NRC.h>
using namespace NRC;

// ������������ ����� ������ - ���������� ��� ������ ������
NRC::CharString NRC::SObject::Name()
{
	return CharString("NRC::Object");
}


//------------------------------------------------------------------------------------------------
// ���������� ��� ������ ������
NRC::CharString NRC::CharString::Name()
{
	return CharString("NRC::CharString");
}


// ������� �������� � ������ �������
void NRC::CharString::Trim()
{
	TrimLeft();
	TrimRight();
}


// ������� �������� �������
void NRC::CharString::TrimLeft()
{
	const char *p = c_str(), *q = p;
	
	while( isspace(*p) )
		p++;

	erase(0, p - q);
}


// ������� ������ �������
void NRC::CharString::TrimRight()
{
	const char *p = c_str() + length() - 1, *q = p;
	
	while( isspace(*p) && p != c_str() )
		p--;

	erase(length() - (q - p), q - p); 
}


// ����������� ������ � ���������� �� � �����
void NRC::CharString::Format( const char *s, ... )
{
	static char buf[1024];
	va_list ls;
	va_start(ls, s);
	_vsnprintf(buf, 1024, s, ls);
	va_end(ls);

	this->operator =(buf);
}


// ��������� ������ � ������ ������� 
void NRC::CharString::LowerCase()
{
	for( int i = 0; i<length(); i++ )
		this->operator[](i) = tolower(at(i));

}

	
// ��������� ������ � ������� �������
void NRC::CharString::UpperCase()
{	
	for( int i = 0; i<length(); i++ )
		this->operator[](i) = toupper(at(i));
}


// ����������� ������
void NRC::CharString::Reverse()
{
	CharString s = c_str();
	strrev((char*)s.c_str());
	*this = s;
}


// �������� ��� ������ ��� ����� ��������, �� � ������ ��������� ���������
bool NRC::CharString::CompareNoCase( const char *s )
{
	return !_stricoll(c_str(), s);
}


// ������� �� ������ ��� ������� ����������� � ������ 'set'
void NRC::CharString::DeleteInSet( const char *set )
{
	CharString out;

	out.reserve(length()+1);
	for( int i = 0; i<length(); i++ )
	{
		const char *p;
		if( (p = strchr(set, at(i))) == NULL )
			out += at(i);			
	}

	*this = out;
}


// �������� ������� �� ������ inset, ��������� �� ������ outset
// ������ ������� ������� �� inset ������ ��������������� ������
// �� outset, ���� ������ inset ������, �� ������� ����������
// defchar
void NRC::CharString::ChangeInSet( const char *inset, const char *outset, char defchar )
{
	int r = strlen(inset) - strlen(outset);
	CharString s;

	if( r > 0 )
	{
		s = outset;
		while(r)
			s += defchar, r--;
		outset = s.c_str();
	}

	for( int i = 0; i<length(); i++ )
	{
		const char *p;
		if( (p = strchr(inset, at(i))) != NULL )
			this->operator[](i) = outset[p-inset];
	}
}


// �������� � ������ ������ ������� �� ������
void NRC::CharString::KeepInSet( const char *set )
{
	CharString out;

	out.reserve(length()+1);
	for( int i = 0; i<length(); i++ )
	{
		const char *p;
		if( (p = strchr(set, at(i))) != NULL )
			out += at(i);
	}

	*this = out;
}


// ������������� �����, ��������� � ������ �������, ��� �������
// chkfunc ���������� ��������� ��������
void NRC::CharString::KeepInSet( int (*chkfunc)(int c) )
{
	CharString out;

	out.reserve(length()+1);
	for( int i = 0; i<length(); i++ )
	{
		if( chkfunc( at(i) ) != 0 )
			out += at(i);
	}

	*this = out;
}


// ������� ������� � ������ �� ���� ��� �������� ������ �� ������
// ������� ��������� ������
NRC::CharString NRC::CharString::DeleteLeftWhileNot( const char *set )
{
	int cnt = 0;
	while( strchr(set, at(cnt)) == NULL && cnt < length() )
		cnt++;
			
	CharString s = substr(0, cnt).c_str();
	erase(0, cnt);
	return s;
}


// ������� ������� � ����� �� ���� ��� �������� ������ �� ������
// ������� ��������� ������
NRC::CharString NRC::CharString::DeleteRightWhileNot( const char *set )
{
	int cnt = 0, i = length()-1;
	while( i >= 0 && strchr(set, at(i)) == NULL )
		cnt++, i--;
	
	CharString s = substr(i+1, cnt+1).c_str();
	erase(i, cnt);
	return s;
}


// ������� ��������� �� �����
NRC::CharString::operator const char *()
{
	return c_str();
}


// ������������� ����� ����� � ������ � ��������
NRC::CharString &NRC::CharString::operator=( int d )
{
	char buf[25];
	_snprintf(buf, 25, "%d", d);
	this->operator=( buf );
	return *this;
}

	
// ������������� ������������ ����� � ������ � ��������
NRC::CharString &NRC::CharString::operator=( double f )
{
	char buf[100];
	_snprintf(buf, 100, "%lf", f);
	this->operator=( buf );
	return *this;
}

//------------------------------------------------------------------------------------------------
// ���������� ��� ������ ������
NRC::CharString NRC::StringList::Name() 
{
	return CharString("NRC::StringList");
}
	

// �������� ������ � ����� ������
void NRC::StringList::Append( CharString &s )
{
	CharString *n = new CharString(s);
	push_back(n);
}

	
// ������� ������ � ������� N. 
// ���������� ���������� � ����
void NRC::StringList::Delete( int n )
{
	if( n < 0 || n >= size() )
		return;

	iterator p = begin();
	for( int i = 0; i<n; i++, p++ ) 
		continue;

	delete at(n);
	erase(p);
}

	
// �������� ���� ������
void NRC::StringList::Clear()
{
	for( int i = 0; i<size(); i++ )
		delete at(i);
	clear();
}


// ��������� ������ �� �����
bool NRC::StringList::LoadFromFile( const char *fname )
{
	ifstream fin(fname);
	fin.flags( fin.flags() | ios::skipws );

	if( fin.fail() )
		return false;

	CharString s;
	
	while( getline(fin, s, '\n') )
		Append(s);

	fin.close();
	return true;
}


// ��������� ������ � �����
bool NRC::StringList::SaveToFile( const char *fname )
{
	ofstream fout(fname);
	if( fout.fail() )
		return false;

	for( int i = 0; i<Count(); i++ )
		if( !(fout << (*this)[i] << '\n') )
		{
			fout.close();
			return false;
		}

	fout.close();
	return true;
}


// ������� ������ ����� � ���� ������
NRC::CharString NRC::StringList::Text()
{
	CharString s;

	for( int i = 0; i<Count(); i++ )
		s += (*this)[i] + '\n';

	return s;
}


// ��������� ������ �� �����, ����� ������-�����������
// � ��������� �� � ������ �����. ��� ���� ���������� ���������
// ������ ���������. ������ ����������� � ������� ��� ��������� �������
// ��������� ����� ������, ���������� �� �����������
void NRC::StringList::DelimText( const CharString &s, char delim )
{
	Clear();
	
	CharString out;
	bool quote = false;

	for( int i = 0; i<s.length(); i++ )
	{
		// ������ ����������� � �������
		if( s[i] == '\"' )
		{
			if( i != 0 && s[i-1] == '\\' )
				quote = true;
			else
				quote = !quote;

			if( !quote )
			{
				out += '\"';
				goto addword;
			}
		}

		// ��������� �����
		if( s[i] == delim || isspace(s[i]) )
		{			
			if( out.empty() || quote )
				continue;

		addword:
			Append(out);
			out = "";
		}

		else
			out += s[i];
	}
}


// ����� ������ ��������������� �������
int NRC::StringList::Find( const CharString &s, 
			bool (*fcmp)(const CharString &, const CharString&), int startPos )	const
{
	if( startPos < 0 ||  startPos >= Count() )
		return -1;

	for( int i = 0; i<Count(); i++ )
		if( !fcmp( (*this)[i], s ) )
			return i;
	return -1;
}


// ���������� �����
void NRC::StringList::Sort( bool (*fcmp)(const CharString *, const CharString*) )
{
	sort(begin(), end(), fcmp);
}


// �������� ������� � �������
NRC::CharString &NRC::StringList::operator[]( int ix )
{
	static CharString def;
	if( ix < 0 || ix >= size() )
		return def;

	return *at(ix);
}


// const
const CharString &NRC::StringList::operator[]( int ix ) const
{
	static CharString def;
	if( ix < 0 || ix >= size() )
		return def;

	return *at(ix);
}