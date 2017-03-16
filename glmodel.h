# ifndef GL_MODEL
#define GL_MODEL

#include<gl/glut.h>
#include <vector>
using namespace std;

#define MAX_TEXTURES 256
static GLuint textureArray[MAX_TEXTURES] = { 0 };

/* defines */
#define GLM_NONE     (0)    //0 /* render with only vertices */ֻ��Ⱦ�ڵ�
#define GLM_FLAT     (1 << 0) //1   /* render with facet normals */ ʹ���淨������Ⱦ
#define GLM_SMOOTH   (1 << 1) //2   /* render with vertex normals */ �ڵ㷨����
#define GLM_TEXTURE  (1 << 2) //4  /* render with texture coords */ ��������
#define GLM_COLOR    (1 << 3) //8   /* render with colors */ ��ɫ
#define GLM_MATERIAL (1 << 4) //16   /* render with materials */ ����

//���ʣ�����ͼ��Դ
typedef struct _GLMmaterial
{
	char* name;        /* name of material */ //���ƣ��� 1.mtl
	GLfloat diffuse[4];      /* diffuse component */ //����ɫ
	GLfloat ambient[4];      /* ambient component */ //���ʵ���Ӱɫ
	GLfloat specular[4];      /* specular component */ // �߹�ɫ
	//GLfloat emissive[4];      /* emmissive component */ // ����
	GLfloat shininess;      /* specular exponent */ // ����
	char* map_file;      /* filename of the texture map */ //�����ļ�ȫ��
} GLMmaterial;

//�飨��Ϊ~~��
typedef struct _GLMgroup {
	char*				name;    /* name of this group */
	GLuint            numtriangles;  /* number of triangles in this group */
	GLuint*           triangles;    /* array of triangle indices */
	GLuint            material;           /* index to material for group */
	struct _GLMgroup* next;    /* pointer to next group in model *///ָ����һ�����ָ��
} GLMgroup;

//�����νṹ��
typedef struct {
	GLuint vindices[3];      /* array of triangle vertex indices */
	GLuint nindices[3];      /* array of triangle normal indices */
	GLuint tindices[3];      /* array of triangle texcoord indices*/
	GLuint findex;      /* index of triangle facet normal */ //��ƽ�����������
} GLMtriangle;
//������
typedef struct{
	

} GLMHexahedron;
/* GLMmodel: Structure that defines a model.
*/
typedef struct {
	char*    pathname;      /* path to this model */ //·��
	char*    mtllibname;      /* name of the material library */ //mtl·��

	GLuint   numvertices;      /* number of vertices in model */ //�ڵ����
	GLfloat* vertices;      /* array of vertices  */ //�ڵ�����

	GLuint   numnormals;      /* number of normals in model */ //����������
	GLfloat* normals;      /* array of normals */	//����������

	GLuint   numtexcoords;    /* number of texcoords in model */ //�����������
	GLfloat* texcoords;      /* array of texture coordinates */	//������������

	GLuint   numfacetnorms;    /* number of facetnorms in model */ //�淨��������
	GLfloat* facetnorms;      /* array of facetnorms */	//�淨��������

	GLuint       numtriangles;    /* number of triangles in model */ //�����θ���
	GLMtriangle* triangles;    /* array of triangles */	//����������

	GLuint       nummaterials;    /* number of materials in model 
								  */ //���ʸ���

	std::vector <char*> textures;//ͼƬ��·��

	GLMmaterial* materials;    /* array of materials */ //��������

	GLuint			numgroups;    /* number of groups in model */ //�����
	GLMgroup*    groups;      /* linked list of groups *///������

	GLfloat position[3];      /* position of the model */ //ģ��λ�ã�

} GLMmodel;

//��ͼ����ʾ����Ļ�м�
GLfloat glmUnitize(GLMmodel* model, GLfloat center[3]);
//����ģ��ά�ȣ�����x��y��z�����ϵ����ֵ��
GLvoid glmDimensions(GLMmodel* model, GLfloat* dimensions);
//�Ŵ���Сָ��������
GLvoid glmScale(GLMmodel* model, GLfloat scale);
//��ת���е�ģ���еĶ�������ߣ�Ĭ������ʱ�뷽��Ҳ�ı䷨�����ķ���
GLvoid glmReverseWinding(GLMmodel* model);
//�����淨�������ٶ���ʱ��
GLvoid glmFacetNormals(GLMmodel* model);
//�����ڵ㷨����
GLvoid glmVertexNormals(GLMmodel* model, GLfloat angle);
//�����������갴������ӳ�������ͶӰ
GLvoid glmLinearTexture(GLMmodel* model);
//�����������갴������ӳ�������ͶӰ
GLvoid glmSpheremapTexture(GLMmodel* model);
//�����ǰģ��
GLvoid glmDelete(GLMmodel* model);
//��ȡOBJ�ļ�
GLMmodel* glmReadOBJ(char* filename);
//��ģ��д�뵽OBJ�ļ���������
GLvoid glmWriteOBJ(GLMmodel *model, char* filename, GLuint mode);
//����ָ����ģʽ��Ⱦģ��
GLvoid glmDraw(GLMmodel *model, GLuint mode);
//Ϊָ����ģ�Ͳ���һ��չʾ�б�
GLuint glmList(GLMmodel *model, GLuint mode);
//���������ӣ����������
GLuint glmWeld(GLMmodel* model, GLuint mode);
#endif