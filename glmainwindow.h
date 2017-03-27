#ifndef GL_MAINWINDOW_H
#define GL_MAINWINDOW_H

#include <qmainwindow.h>
#include <gltocdialog.h>
#include <glcanvas.h>
#include <_glmodel.h>
#include <gleasymath.h>

class GLMainWindow :public QMainWindow
{
	Q_OBJECT
public:
	GLMainWindow();
	~GLMainWindow();

public:
	void OpenOBJFile();//��obj·���ļ�
	void RestoreView();
	void StartPickFace();
	_GLModel* getObjModel();//��ȡ��ǰ��ģ��

private:

	GLTOCDialog *gltocDialog;
	GLCanvas *glCancas;

	QAction *importObjAction;
	QAction *restoreMatrixAction;
	QAction *pickFaceAction;

	QMenu *fileMenu;
	QToolBar *fileToolBar;

	
public:

};
#endif // !GL_MAINWINDOW_H
