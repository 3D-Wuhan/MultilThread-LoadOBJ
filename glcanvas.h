#ifndef GLCANVAS_H
#define GLCANVAS_H

#include<qopenglwidget.h>
#include<QtOpenGL\qgl.h>
#include<qopenglfunctions.h>
#include<QKeyEvent>
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

};

#endif // GLCANVAS_H
