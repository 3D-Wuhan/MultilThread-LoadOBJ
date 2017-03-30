#ifndef GL_MAINWINDOW_H
#define GL_MAINWINDOW_H

#include <qmainwindow.h>
#include <gltocdialog.h>
#include <glcanvas.h>
#include <_glmodel.h>
#include <gleasymath.h>
#include<_glBackgroundThread.h>

class GLMainWindow :public QMainWindow
{
	Q_OBJECT
public:
	GLMainWindow();
	~GLMainWindow();

public://action��Ӧ����
	void OpenOBJFile();//��obj·���ļ�
	void RestoreView();
	void StartPickFace();
	void StartTexture();
public:
	_GLModel* getObjModel();//��ȡ��ǰ��ģ��
	void initialTextureThread();//��ʼ�������߳�
		
private:
	void setTextureActionEnable(bool isEnable);

private:

	GLTOCDialog *gltocDialog;
	GLCanvas *glCanvas;

	QAction *importObjAction;
	QAction *restoreMatrixAction;
	QAction *pickFaceAction;
	QAction *textureRenderAction;

	QMenu *fileMenu;
	QToolBar *fileToolBar;

};
#endif // !GL_MAINWINDOW_H
