#ifndef GLCANVAS_H
#define GLCANVAS_H

#include<qopenglwidget.h>
#include<QtOpenGL\qgl.h>
#include<QKeyEvent>
#include<process.h>


#include<gltrackball.h>
#include<_glmodel.h>
#include<glpick.h>


class GLMainWindow;
class GLCanvas :public QGLWidget//public QOpenGLWidget
{
	Q_OBJECT
public:
	GLCanvas(QWidget *parent = 0);
	~GLCanvas();
	void InitParameter();
	bool BindTexture();
	void ReviewInit();//�ָ���ʼ״̬
	void InitHDC();
	void ClearSelection();
protected:
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void keyPressEvent(QKeyEvent *e);
	void keyReleaseEvent(QKeyEvent *e);
	void wheelEvent(QWheelEvent *e);

	void initializeGL();
	void resizeGL(int w, int h); //���Զ�ˢ����Ļ
	void paintGL();
	//����
public:
	_GLModel* pModel;
	bool isPickFace;//������ʾ��ǰ�Ƿ�ʼʰȡ��~
	size_t redrawMode;//�ػ��ģʽ

	double pModelViewMatrix[16];//ģ����ͼ
	double pProjectMatrix[16];//ͶӰ��ͼ
private:
	GLMainWindow *mainWindow;
	bool leftButtonPress;//��ǰ�������
	bool middleButtonPress;
	int oldX;
	int oldY;

	int oldMiddleX;
	int oldMiddleY;

public:
	float scale;

	_WINDEF_::HDC	hDC;  // Private GDI Device Context
	HGLRC  hRC;  // Permanent Rendering Context
	HGLRC  hRCShareing;// ���ڷ���hRC����Դ

signals:
	void SendInfo(QString&);//������ʾ��Ϣ���ź�

private :
	void sendInfo(Face *f);
};

#endif // GLCANVAS_H
