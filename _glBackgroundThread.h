#ifndef _GL_BACKGROUND_THREAD_H
#define _GL_BACKGROUND_THREAD_H
/*�����̨�߳�*/
#include<qthread.h>
#include<_glmodel.h>

class _TextureThread :public QThread
{
	Q_OBJECT
	void run() Q_DECL_OVERRIDE
	{
		bool isReady;
		//��ʼִ�а�����

		emit loadReady(isReady);//�����ź�
	}
signals:

	void loadReady(const bool isEnable);


};




#endif // !_GL_BACKGROUND_THREAD_H
