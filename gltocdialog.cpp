#include<gltocdialog.h>
#include "glmainwindow.h"

GLTOCDialog::GLTOCDialog(QWidget *parent) : QDockWidget(parent)
{
	mainWindow  = qobject_cast<GLMainWindow *>(parent);


	this->setWindowTitle(QString::fromLocal8Bit("Ŀ¼��ͼ"));
	this->layout();
}
GLTOCDialog::~GLTOCDialog()
{

}