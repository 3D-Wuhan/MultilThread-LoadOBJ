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

	glCanvas = new GLCanvas(this);
	setCentralWidget(glCanvas);

	//importObjAction = new QAction(QIcon(":/images/import_mesh.png"), tr("&Open OBJ"), this);//��Ҫ����Qt5Gui.lib����Qt5Guid.lib
	importObjAction = new QAction(QString::fromLocal8Bit("��OBJ"), this);
	importObjAction->setShortcutContext(Qt::ApplicationShortcut);
	importObjAction->setShortcut(Qt::CTRL + Qt::Key_O);
	connect(importObjAction, &QAction::triggered, this, &GLMainWindow::OpenOBJFile);
	//��ԭ��ͼ
	restoreMatrixAction = new QAction(QString::fromLocal8Bit("��ԭ��ͼ"), this);
	connect(restoreMatrixAction, &QAction::triggered, this, &GLMainWindow::RestoreView);

	//ʰȡ��
	pickFaceAction = new QAction(QString::fromLocal8Bit("ʰȡ��"),this);
	connect(pickFaceAction, &QAction::triggered, this, &GLMainWindow::StartPickFace);
	pickFaceAction->setCheckable(true);
	pickFaceAction->setChecked(false);

	//����������ͼ
	textureRenderAction = new QAction(QString::fromLocal8Bit("��������"), this);
	connect(textureRenderAction, &QAction::triggered, this, &GLMainWindow::StartTexture);
	textureRenderAction->setCheckable(true);
	textureRenderAction->setChecked(false);
	textureRenderAction->setEnabled(false);

	//�˵�
	fileMenu = menuBar()->addMenu(tr("&File"));//��Ҫmenubarͷ�ļ�
	fileMenu->addAction(importObjAction);
	//������
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(importObjAction);
	fileToolBar->addAction(restoreMatrixAction);
	fileToolBar->addAction(pickFaceAction);
	fileToolBar->addAction(textureRenderAction);

}

void GLMainWindow::setTextureActionEnable(bool isEnable)
{
	this->textureRenderAction->setEnabled(isEnable);
	this->textureRenderAction->setChecked(true);
	glCanvas->update();
}

//��ʼ��������߳�
void GLMainWindow::initialTextureThread()
{

	_TextureThread* textureThread = new _TextureThread(glCanvas);
	connect(textureThread, &_TextureThread::loadReady, this, &GLMainWindow::setTextureActionEnable);
	connect(textureThread, &_TextureThread::finished, textureThread, &QObject::deleteLater);
	textureThread->start();

}

GLMainWindow::~GLMainWindow()
{

}

void GLMainWindow::RestoreView()
{
	glCanvas->ReviewInit();
}

void GLMainWindow::StartPickFace()
{
	if (glCanvas->pModel&&this->pickFaceAction->isChecked())
	{
		glCanvas->isPickFace = true;
	}
	else
	{
		glCanvas->isPickFace = false;
	}
}

void GLMainWindow::OpenOBJFile()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("��OBJ"), "/home", "OBJ Files (*.obj)");
	//����Ѿ������ˣ���ô��ɾ����ģ��

	if (fileName.isNull())
		return;

	if (glCanvas->pModel)
	{
		_glDelete(glCanvas->pModel);
		glCanvas->pModel = NULL;
	}

	glCanvas->pModel = _glReadOBJ(fileName);
	if (!glCanvas->pModel)
	{
		qDebug(T_Char2Char("�޷���OBJ�ļ�"));
		return;
	}
	//glCanvas->InitHDC();
	//glCanvas->hDC = wglGetCurrentDC();
	//glCanvas->hRC = wglCreateContext(glCanvas->hDC);
	//glCanvas->hRCShareing = wglCreateContext(glCanvas->hDC);
	//wglShareLists(glCanvas->hRCShareing, glCanvas->hRC);//��һ��rc�Ƿ��������Դ���ڶ�����
	//wglMakeCurrent(glCanvas->hDC, glCanvas->hRC);
	//initialTextureThread();
	glCanvas->BindTexture();
	_glConstructIndexFromName(glCanvas->pModel);
	//��textture
	_glFacetNormals(glCanvas->pModel);
	glCanvas->scale = _glUnitize(glCanvas->pModel, glCanvas->pModel->center);


	// Init the modelview matrix as an identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetDoublev(GL_MODELVIEW_MATRIX, glCanvas->pModelViewMatrix);

	glCanvas->setFocus();
	glCanvas->update();
}

void GLMainWindow::StartTexture()
{
	if (!glCanvas->pModel)
		return;
	if (this->textureRenderAction->isChecked())
	{
		glCanvas->redrawMode = _GL_FLAT | _GL_TEXTURE;
	}
	else
	{
		glCanvas->redrawMode = _GL_FLAT;
	}
	glCanvas->update();
}






