#include <qaction.h>
#include<qmenubar.h>
#include<qtoolbar.h>
#include<qfiledialog.h>
#include<qdebug.h>
#include<qmessagebox.h>

#include <glmainwindow.h>
#include <transform.h>

GLMainWindow::GLMainWindow()
{
	gltocDialog = new GLTOCDialog(this);
	gltocDialog->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	addDockWidget(Qt::LeftDockWidgetArea, gltocDialog);

	glCancas = new GLCanvas(this);
	setCentralWidget(glCancas);

	//importObjAction = new QAction(QIcon(":/images/import_mesh.png"), tr("&Open OBJ"), this);//��Ҫ����Qt5Gui.lib����Qt5Guid.lib
	importObjAction = new QAction(QString::fromLocal8Bit("��OBJ"), this);
	importObjAction->setShortcutContext(Qt::ApplicationShortcut);
	importObjAction->setShortcut(Qt::CTRL + Qt::Key_I);
	connect(importObjAction, &QAction::triggered, this, &GLMainWindow::OpenOBJFile);

	fileMenu = menuBar()->addMenu(tr("&File"));//��Ҫmenubarͷ�ļ�

	fileMenu->addAction(importObjAction);

	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(importObjAction);


}

GLMainWindow::~GLMainWindow()
{
}



void GLMainWindow::OpenOBJFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��OBJ"), "/home", "OBJ Files (*.obj)");
	//����Ѿ������ˣ���ô��ɾ����ģ��
	if (glCancas->pModel)
	{
		_glDelete(glCancas->pModel);
		glCancas->pModel = NULL;
	}
	
	glCancas->pModel = _glReadOBJ(fileName);
	if (!glCancas->pModel)
	{
		qDebug(T_Char2Char("�޷���OBJ�ļ�"));
		return;
	}
	_glConstructIndexFromName(glCancas->pModel);
	//��textture
	glCancas->BindTexture(glCancas->pModel);

	_glFacetNormals(glCancas->pModel);
	glCancas ->scale = _glUnitize(glCancas->pModel);

	// Init the modelview matrix as an identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, glCancas->pModelViewMatrix);
	
	glCancas->setFocus();
	glCancas->update();
}








