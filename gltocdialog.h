#ifndef GL_TOCDIALOG_H
#define GL_TOCDIALOG_H

#include <qdockwidget.h>
#include <qtreewidget.h>
#include<qplaintextedit.h>
#include <qboxlayout.h>
class GLMainWindow;

class GLTOCDialog :public QDockWidget
{
	Q_OBJECT
public:
	GLTOCDialog(QWidget *parent = 0);
	~GLTOCDialog();
private:
	GLMainWindow* mainWindow;
	QWidget *dockWidgetContents;//�ӿռ�����
	QVBoxLayout *vLayout;
	QTreeView *treeView;//Ŀ¼��
	QPlainTextEdit *infoText;//��ʾ�ı���Ϣ

public:
	QString infomation;//��Ҫ��ʾ����Ϣ
	QString infoHTML;//html��ʽ����Ϣ

public:
	void ShowCurrentRebackInfo(QString& info);//��ʾ��ǰ��Ϣ
};


#endif // !TOCDIALOG_H