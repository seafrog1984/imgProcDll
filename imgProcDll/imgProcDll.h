// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� IMGPROCDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// IMGPROCDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef IMGPROCDLL_EXPORTS
#define IMGPROCDLL_API __declspec(dllexport)
#else
#define IMGPROCDLL_API __declspec(dllimport)
#endif

#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// �����Ǵ� imgProcDll.dll ������
//class IMGPROCDLL_API CimgProcDll {
//public:
//	CimgProcDll(void);
//	// TODO:  �ڴ�������ķ�����
//};
//
//extern IMGPROCDLL_API int nimgProcDll;
//
//IMGPROCDLL_API int fnimgProcDll(void);

IMGPROCDLL_API void myResize(Mat & src, Mat &dst,int width, int height);


IMGPROCDLL_API void dataRead(unsigned short * tmp, char* m_path,int length);

IMGPROCDLL_API void data2Img(unsigned short * tmp, Mat& dst, int img_rows, int img_cols, float mintemp , int win_width , int color_type , int filter_type, float bot);

/*
unsigned short * tmp��ԭʼ���ݣ�16bit��short int ָ��
Mat& dst��Ŀ��ͼ�񣬴���Ľ��
int img_rows, int img_cols,��ͼ����У�������img_rows*img_cols Ӧ��= ԭʼ���ݵĳ���
float mintemp = 25���ο��¶�ֵ��Ĭ��25
int win_width = 16���¶ȴ���Ĭ��16
int color_type = 2��ͼ����ɫ������0-�Ҷȣ�1-��ͳα��ɫ��2-TTM
int filter_type = 0 ���˲�������0-��ֵ��1-ֱ��ͼ���⣻2-���˲�
float bot���ϲ�ο�ֵ����ʼ25
*/