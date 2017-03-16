#ifndef TRANSFORM
#define TRANSFORM

#include<QString>
//QStringת��Ϊchar*
static char* T_QString2Char(QString str)
{
	QByteArray b = str.toLatin1();
	char* strChar = b.data();
	return strChar;
}

/*�ַ����ȵ�ת������*/
//��ô����ԭ������Ϊ��Ҫ��ʾ����
static char* T_Char2Char(char* str)
{
	QString err = QString::fromLocal8Bit(str);
	return T_QString2Char(err);
}


static QString TrimEnd(QString str)
{
	str = str.left(str.length() - 1);
	
	return str;
}

static QString T_char2QString(char* str)
{
	QString str1 = QString::fromLocal8Bit(str);
	return str1;
}

static int RoundUpToTheNextHighestPowerOf2(int v)
{
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

#endif // !TRANSFORM
