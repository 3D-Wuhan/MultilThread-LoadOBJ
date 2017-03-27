#include<qfile.h>
#include<qdebug.h>

using namespace std;
#include<_glmodel.h>
#include<transform.h>
#include<gleasymath.h>
#include<assert.h>

#ifndef GL_PI
#define GL_PI 3.14159265358979323846
#endif

enum{ _X, _Y, _Z, _W };//

#pragma region ˽�з���
//�����ļ���·����ȡ���ļ��е�·��
QString _glGetDir(QString filePath)
{
	int index = filePath.lastIndexOf('\\');
	if (index == -1)
		index = filePath.lastIndexOf('/');
	filePath.remove(index + 1, filePath.length() - index - 1);
	return filePath;
}

//��ȡmtl�ļ�
void _glReadMTL(_GLModel *model, QString fileName)
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		qDebug("mtl�ļ���ʧ�ܡ�");
		return;
	}
	QString dirPath;

	Material *material = NULL; QStringList list;
	int index = -1;//��������
	QString split = ' ';
	while (!file.atEnd())
	{
		QByteArray line = file.readLine();
		if (line.length() == 2 && line.at(line.length() - 2) == '\r'&&line.at(line.length() - 1) == '\n')//��������˿����Ҳ���ָ�벻Ϊ�գ���ô֤����ǰ�Ĳ����Ѿ�����
		{
			if (material&&material->materialName != NULL)
				model->list_Materials.push_back(*material);
		}

		QString str(line);
		if (str[0] == 'n')//����
		{
			list = str.split(split);
			material = new Material();
			material->_Ka[_X] = 0.0; material->_Ka[_Y] = 0.0; material->_Ka[_Z] = 0.0;
			material->_Kd[_X] = 0.0; material->_Kd[_Y] = 0.0; material->_Kd[_Z] = 0.0;
			material->_Ks[_X] = 0.0; material->_Ks[_Y] = 0.0; material->_Ks[_Z] = 0.0;

			QString str1 = list[1];
			material->materialName = str1.trimmed();
			material->index_Material = ++index;
			model->num_Materials++;
		}
		else if (str[0] == 'm')//��ͼ·��
		{
			list = str.split(split);
			dirPath = _glGetDir(fileName);//��ȡ�ļ���·��
			dirPath.append(list[1].trimmed());
			material->imageName = dirPath;
			model->list_ImagePath.push_back(dirPath);
		}
		else if (str[0] == 'K')
		{
			list = str.split(split);
			if (str[1] == 'a')
			{
				material->_Ka[0] = list[1].toFloat();
				material->_Ka[1] = list[2].toFloat();
				material->_Ka[2] = list[3].toFloat();
			}
			else if (str[1] == 'd')
			{
				material->_Kd[0] = list[1].toFloat();
				material->_Kd[1] = list[2].toFloat();
				material->_Kd[2] = list[3].toFloat();
			}
			else if (str[1] == 's')
			{
				material->_Ks[0] = list[1].toFloat();
				material->_Ks[1] = list[2].toFloat();
				material->_Ks[2] = list[3].toFloat();
			}
		}
	}
}

#pragma endregion

//��ȡOBJ�ļ�
_GLModel* _glReadOBJ(QString filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return NULL;
	}
	QString dirPath = _glGetDir(filename); QStringList list; QString currentMaterialName;

	_GLModel* model;
	model = new _GLModel();
	QString split = ' ';

	model->path = filename;
	model->num_Faces = 0;
	model->num_Materials = 0;
	model->num_Normals = 0;
	model->num_Textcoords = 0;
	model->num_Vertices = 0;

	Point3 *v;
	TextCoords *vt;
	VertNormals *vn;
	Face *f;

	while (!file.atEnd()) {
		QByteArray line = file.readLine();
		QString str(line);
		if (str.length() < 2)//̫��~
			continue;
		if (str[0] == 'm')
		{
			QStringList str0 = str.split(' ');
			QString mtlname = str0[1];
			mtlname = mtlname.trimmed();
			dirPath.append(mtlname);
			model->mtllibName = dirPath;
			_glReadMTL(model, model->mtllibName);
		}
		else if (str[0] == 'v'){
			if (str[1] == 't'){//����
				list = str.split(split);//�����Ƿ����Z�����������ȡǰ����ֵ
				vt = new TextCoords();
				vt->U = list[_Y].toFloat(); vt->V = list[_Z].toFloat();
				model->num_Textcoords++;
				model->list_Textcoords.push_back(*vt);
			}
			else if (str[1] == 'n'){//������
				list = str.split(split);
				vn = new VertNormals();
				vn->_NX = list[_Y].toFloat(); vn->_NY = list[_Z].toFloat(); vn->_NZ = list[_W].toFloat();
				model->num_Normals++;
				model->list_Normals.push_back(*vn);
			}
			else//�ڵ�~
			{
				list = str.split(split);
				v = new Point3();
				v->_X = list[_Y].toFloat(); v->_Y = list[_Z].toFloat(); v->_Z = list[_W].toFloat();
				model->num_Vertices++;
				model->list_Vertices.push_back(*v);
			}
		}
		else if (str[0] == 'u')//���ʵ�����
		{
			list = str.split(split);
			currentMaterialName = list[1].trimmed();
		}
		else if (str[0] == 'f')//��
		{
			str = str.trimmed();
			list = str.split(split);

			f = new Face();
			f->materialName = currentMaterialName;
			f->isS = false;

			if (list[1].contains('/'))
			{

				for (int i = 1; i < list.length(); i++)
				{
					QStringList sublist = list[i].split('/');
					f->list_index_Points.push_back(sublist[_X].toInt() - 1);
					f->list_index_TextCoords.push_back(sublist[_Y].toInt() - 1);
					if (list[1].split('/').length() == 3)//ֻ��v��vt
					{
						f->list_index_VertNormals.push_back(sublist[_Z].toInt() - 1);
					}
				}
			}
			else//������/����ôֻ�нڵ�
			{
				for (int i = 1; i < list.length(); i++)
				{
					f->list_index_Points.push_back(list[i].toInt() - 1);
				}
			}
			model->num_Faces++;
			model->list_Faces.push_back(*f);
		}
	}
	return model;
}

//�ͷ�֮ǰ��model
void _glDelete(_GLModel* model)
{
	if (model)
		delete model;
	//�ͷ�model�еļ��϶���
}

//������ķ�����
void _glFacetNormals(_GLModel* model)
{
	FacetNormal *fn;
	float u[3];
	float v[3];

	float cross[3];
	for (int i = 0; i < model->list_Faces.length(); i++)
	{
		fn = new FacetNormal();
		Point3 p0 = model->list_Vertices[model->list_Faces[i].list_index_Points[0]];
		Point3 p1 = model->list_Vertices[model->list_Faces[i].list_index_Points[1]];
		//Point3 p2 = model->list_Vertices[model->list_Faces[i].list_index_Points[2]];//�ڶ���������ʱ����Ч

		Point3 pn = model->list_Vertices[model->list_Faces[i].list_index_Points[model->list_Faces[i].list_index_Points.length() - 1]];//����ʹ�����һ��ųɹ�

		u[_X] = p1._X - p0._X;
		u[_Y] = p1._Y - p0._Y;
		u[_Z] = p1._Z - p0._Z;

		v[_X] = pn._X - p0._X;
		v[_Y] = pn._Y - p0._Y;
		v[_Z] = pn._Z - p0._Z;

		vCross(u, v, cross);//���㽻��˻�
		vNormal(cross);//��λ��

		model->list_Faces[i].index_Face = i;
		fn->NX = cross[0];
		fn->NY = cross[1];
		fn->NZ = cross[2];
		model->list_FaceNormal.push_back(*fn);
	}
}

//��ͼ���Ƶ���Ļ�м���
float _glUnitize(_GLModel* model, float* center)
{
	float maxx, minx, maxy, miny, maxz, minz;
	float cx, cy, cz, w, h, d;
	float scale;

	if (model&&model->list_Vertices.size() > 0)
	{
		maxx = minx = model->list_Vertices[0]._X;
		maxy = miny = model->list_Vertices[0]._Y;
		maxz = minz = model->list_Vertices[0]._Z;

		for (size_t i = 1; i < model->num_Vertices; i++)
		{
			if (maxx < model->list_Vertices[i]._X)
				maxx = model->list_Vertices[i]._X;
			if (minx > model->list_Vertices[i]._X)
				minx = model->list_Vertices[i]._X;


			if (maxy < model->list_Vertices[i]._Y)
				maxy = model->list_Vertices[i]._Y;
			if (miny > model->list_Vertices[i]._Y)
				miny = model->list_Vertices[i]._Y;


			if (maxz < model->list_Vertices[i]._Z)
				maxz = model->list_Vertices[i]._Z;
			if (minz > model->list_Vertices[i]._Z)
				minz = model->list_Vertices[i]._Z;
		}

		w = _glmAbs(maxx) + _glmAbs(minx);
		h = _glmAbs(maxy) + _glmAbs(miny);
		d = _glmAbs(maxz) + _glmAbs(minz);

		//����ģ�͵�����
		cx = (maxx + minx) / 2.0;
		cy = (maxy + miny) / 2.0;
		cz = (maxz + minz) / 2.0;

		scale = 2.0 / _glmMax(w, _glmMax(h, d));

		//�����İ��ձ���ת��
		for (size_t i = 0; i < model->num_Vertices; i++)
		{
			model->list_Vertices[i]._X -= cx;
			model->list_Vertices[i]._Y -= cy;
			model->list_Vertices[i]._Z -= cz;

			model->list_Vertices[i]._X *= scale;
			model->list_Vertices[i]._Y *= scale;
			model->list_Vertices[i]._Z *= scale;
		}

		center[0] = 0.0;
		center[1] = 0.0;
		center[2] = 0.0;

		//center[0] = -cx;
		//center[1] = -cy;
		//center[2] = -cz;
	}

	return scale;
}

int GetIndexFromMaterialName(_GLModel* model, QString materialName)
{
	for (size_t i = 0; i < model->num_Materials; i++)
	{
		if (materialName == model->list_Materials[i].materialName)
			return --i;
	}
	return -1;
}

void _glConstructIndexFromName(_GLModel* model)
{
	int index;
	for (size_t i = 0; i < model->num_Faces; i++)
	{
		QString name = model->list_Faces[i].materialName;
		index = GetIndexFromMaterialName(model, name);
		if (index > 0)
			model->list_Faces[i].index_Text = index;
		model->list_Faces[i].index_Name = ++index;
	}
}

//��Ⱦģ��
void _glDraw(_GLModel* model, size_t mode)
{
	if (mode & _GL_FLAT && model->list_FaceNormal.size() == 0)
	{
		qDebug(T_QString2Char("Flatģʽ�����ã�"));
		mode &= ~_GL_FLAT;
	}
	if (mode & _GL_SMOOTH && model->num_Normals == 0) {
		qDebug(T_QString2Char("Smoothģʽ�����ã�"));
		mode &= ~_GL_SMOOTH;
	}
	if (mode & _GL_TEXTURE && model->num_Textcoords == 0) {
		qDebug(T_QString2Char("Textureģʽ�����ã�"));
		mode &= ~_GL_TEXTURE;
	}
	glPushMatrix();
	glTranslatef(model->center[0], model->center[1], model->center[2]);

	for (size_t i = 0; i < model->num_Faces; i++)
	{
		Face f = model->list_Faces[i];

		if (mode&_GL_TEXTURE)
		{
			glEnable(GL_TEXTURE_2D);
			if (f.index_Text != -1)//����ָ��������һ��Ҫ����Ӧ��������������
				glBindTexture(GL_TEXTURE_2D, model->textureArray[f.index_Text]);
		}
		if (f.isS)
			glColor3f(1.0f, 0.0f, 0.0f); // ��ɫ����Ϊ��ɫ  
		else glColor3f(1.0f, 1.0f, 0.0f);//��ɫ

		glBegin(GL_POLYGON);
		//glBegin(GL_QUADS);
		if (mode&_GL_FLAT)
		{
			FacetNormal fn = model->list_FaceNormal[f.index_Face];
			glNormal3f(fn.NX, fn.NY, fn.NZ);
		}

		for (int k = 0; k < f.list_index_Points.size(); k++)
		{

			if (mode&_GL_TEXTURE)
			{
				TextCoords tc = model->list_Textcoords[f.list_index_TextCoords[k]];
				glTexCoord2f(tc.U, tc.V);
			}
			if (mode&_GL_SMOOTH&&f.list_index_VertNormals.size()>0)
			{
				VertNormals vn = model->list_Normals[f.list_index_VertNormals[k]];
				glNormal3f(vn._NX, vn._NY, vn._NZ);
			}
			Point3 p = model->list_Vertices[f.list_index_Points[k]];
			glVertex3f(p._X, p._Y, p._Z);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		//glLineWidth(1.5f);
		for (int j = 0; j < f.list_index_Points.size(); j++)
		{
			Point3 p = model->list_Vertices[f.list_index_Points[j]];
			glVertex3f(p._X, p._Y, p._Z);
		}
		glEnd();
	}
	glPopMatrix();
}