#ifndef _GL_MODEL
#define _GL_MODEL

#include<string>
#include<gl/glut.h>
#include<qstring.h>
#include<QList>

using namespace std;

#define MAX_TEXTURE 256
//static int TextureArray[MAX_TEXTURE] = { 0 };

//������Ⱦģʽ
#define _GL_NONE (0) //0
#define _GL_FLAT (1<<0)//1
#define _GL_SMOOTH (1<<1)//2
#define _GL_TEXTURE (1<<2)//4
#define _GL_COLOR (1<<3)//8
#define _GL_METERIAL (1<<4)//16
#define _GL_SELECT (1<<5)//32 ѡ��ģʽ
#define _GL_RENDER (1<<6)//64 ��Ⱦģʽ
//����
struct  Material
{
	size_t index_Material;//��ǰ�Ĳ��ʵ�����,������model�еļ����еĵڼ���
	QString materialName;

	GLfloat _Ka[3];//ambient
	GLfloat _Kd[3];//diffuse
	GLfloat _Ks[3];//specular

	QString imageName;//ͼƬ��·�����ƣ��˴�ӦΪ����·��
};

//�ڵ�
struct Point3
{
	GLfloat _X;
	GLfloat _Y;
	GLfloat _Z;
};
//�ڵ㷨����
struct VertNormals
{
	GLfloat _NX;
	GLfloat _NY;
	GLfloat _NZ;
};
//�ڵ���������
struct TextCoords
{
	GLfloat U;
	GLfloat V;
};

//// ������ //********��ʱ���еļ��ζ�����ͨ�����������б�ʾ*********//
//struct Triangle
//{
//	int V[3];//�洢���������ڵ������
//	int N[3];
//	int T[3];
//
//	size_t index_Triangle;//ƽ�淨����������
//};

struct FacetNormal
{
	GLfloat NX;
	GLfloat NY;
	GLfloat NZ;
};

struct Face
{
	QString materialName;//��Ӧ��������

	int index_Face;//ƽ�淨����������
	int index_Text;//
	int index_Name;//pickname

	QList<int> list_index_Points;//��ĵ㼯����model�е�����
	QList<int> list_index_TextCoords;//
	QList<int> list_index_VertNormals;

	bool isS;//�����Ƿ�ѡ��״̬����ѡ������ȾΪ��ɫ
};

//ģ����
class _GLModel
{
public:


	QString path;//obj�ļ�·��
	QString mtllibName;//�����ļ�����
	size_t num_Vertices;//�ڵ����
	size_t num_Normals;//�ڵ������ĸ���
	size_t num_Textcoords;//�ڵ������������
	size_t num_Materials;//���ʸ���
	size_t num_Faces;//��ĸ���

	QList<Point3> list_Origin_Vertics;//ԭʼ����ĵ㼯
	QList<Point3> list_Vertices;//�ڵ���󼯺�
	QList<VertNormals> list_Normals;//�ڵ���������
	QList<TextCoords> list_Textcoords;//�������꼯��
	QList<Face> list_Faces;//�漯��
	QList<Material> list_Materials;//���ʼ���
	QList<FacetNormal> list_FaceNormal;//����������

	QList<QString> list_ImagePath;//��ͼ·������,ȫ·��

	int textureArray[MAX_TEXTURE];//ע����������
	int textureArray_Fake[MAX_TEXTURE];//ȡ��ע����������
	//std::vector<unsigned int> textVector;

	float center[3];
	size_t currentSelectedFace;//��ǰѡ���������
};

//��ͼ����ʾ����Ļ�м�
GLfloat _glUnitize(_GLModel* model,float *center);
//����ģ��ά�ȣ�����x��y��z�����ϵ����ֵ��
void _glDimensions(_GLModel* model, GLfloat* dimensions);
//�Ŵ���Сָ��������
void _glScale(_GLModel* model, GLfloat scale);
//��ת���е�ģ���еĶ�������ߣ�Ĭ������ʱ�뷽��Ҳ�ı䷨�����ķ���
void _glReverseWinding(_GLModel* model);
//�����淨�������ٶ���ʱ��
void _glFacetNormals(_GLModel* model);
//�����ڵ㷨����
void _glVertexNormals(_GLModel* model, GLfloat angle);
//�����������갴������ӳ�������ͶӰ
void _glLinearTexture(_GLModel* model);
//�����������갴������ӳ�������ͶӰ
void _glSpheremapTexture(_GLModel* model);
//�����ǰģ��
 void _glDelete(_GLModel* model);
//��ȡOBJ�ļ�
 _GLModel* _glReadOBJ(QString filename);
//��ģ��д�뵽OBJ�ļ���������
void _glWriteOBJ(_GLModel *model, QString filename, size_t mode);
//����ָ����ģʽ��Ⱦģ��
void _glDraw(_GLModel *model, size_t mode);
//Ϊָ����ģ�Ͳ���һ��չʾ�б�
size_t _glList(_GLModel *model, size_t mode);
//���������ӣ����������
size_t _glWeld(_GLModel* model, size_t mode);
//
void _glConstructIndexFromName(_GLModel* model);







#endif