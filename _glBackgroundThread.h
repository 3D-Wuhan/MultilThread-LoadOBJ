#ifndef _GL_BACKGROUND_THREAD_H
#define _GL_BACKGROUND_THREAD_H
/*�����̨�߳�*/
#include<qthread.h>
#include<_glmodel.h>
#include<glcanvas.h>

class _TextureThread :public QThread
{
	Q_OBJECT
		void run() Q_DECL_OVERRIDE
	{
		bool isReady;
		//��ʼִ�а�����
		isReady = canvas->BindTexture();

		emit loadReady(isReady);//�����ź�
	}
	signals:

	void loadReady(const bool isEnable);

public:
	_TextureThread(GLCanvas* canvas){ 
		this->canvas = canvas;
	};

	GLCanvas* canvas;//��ǰ��ģ�Ͷ���
};




#endif // !_GL_BACKGROUND_THREAD_H
