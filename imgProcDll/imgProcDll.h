// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 IMGPROCDLL_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// IMGPROCDLL_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef IMGPROCDLL_EXPORTS
#define IMGPROCDLL_API __declspec(dllexport)
#else
#define IMGPROCDLL_API __declspec(dllimport)
#endif

#include <fstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// 此类是从 imgProcDll.dll 导出的
//class IMGPROCDLL_API CimgProcDll {
//public:
//	CimgProcDll(void);
//	// TODO:  在此添加您的方法。
//};
//
//extern IMGPROCDLL_API int nimgProcDll;
//
//IMGPROCDLL_API int fnimgProcDll(void);

IMGPROCDLL_API void myResize(Mat & src, Mat &dst,int width, int height);


IMGPROCDLL_API void dataRead(unsigned short * tmp, char* m_path,int length);

IMGPROCDLL_API void data2Img(unsigned short * tmp, Mat& dst, int img_rows, int img_cols, float mintemp , int win_width , int color_type , int filter_type, float bot);

/*
unsigned short * tmp：原始数据，16bit的short int 指针
Mat& dst：目标图像，处理的结果
int img_rows, int img_cols,：图像的行，列数，img_rows*img_cols 应该= 原始数据的长度
float mintemp = 25：参考温度值，默认25
int win_width = 16：温度窗宽，默认16
int color_type = 2：图像配色方案，0-灰度；1-传统伪彩色；2-TTM
int filter_type = 0 ：滤波方法，0-中值；1-直方图均衡；2-不滤波
float bot：断层参考值，初始25
*/