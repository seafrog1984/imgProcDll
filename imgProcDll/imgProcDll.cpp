// imgProcDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "imgProcDll.h"
#include <fstream>



using namespace cv;

// 这是导出变量的一个示例
//IMGPROCDLL_API int nimgProcDll=0;
//
//// 这是导出函数的一个示例。
//IMGPROCDLL_API int fnimgProcDll(void)
//{
//	return 42;
//}
//
//// 这是已导出类的构造函数。
//// 有关类定义的信息，请参阅 imgProcDll.h
//CimgProcDll::CimgProcDll()
//{
//	return;
//}



IMGPROCDLL_API void dataRead(unsigned short * tmp, char* m_path, int length)
{
	ifstream fin((LPSTR)(LPCSTR)m_path);

	for (int i = 0; i < length; i++)
	{
		fin >> *(tmp + i);
		if (*(tmp + i) == ' ')
			i--;
	}

	fin.close();

}


IMGPROCDLL_API void data2Temper(unsigned short * tmp, Mat&T, int img_rows, int img_cols, float x=100.00)
{
	int i, col, row;
	float value;
	unsigned short *src = (unsigned short *)tmp;

	for (int i = 0; i < img_rows*img_cols; i++)
	{
		value = *src++;

		float temper = (value - 10000) / x;

		row = i / img_cols;
		col = i%img_cols;


		float* pG_dstData = T.ptr<float>(row);

		*(pG_dstData + col) = temper;
	}
}

IMGPROCDLL_API void data2Img(unsigned short * tmp, Mat& dst, int img_rows, int img_cols, int win_width = 16, int color_type = 2, int filter_type = 2, float bot=22)
{
	Mat g_tmpdst, tmpdst;
	tmpdst.create(img_rows, img_cols, CV_8UC3);
	g_tmpdst.create(img_rows, img_cols, CV_8UC1);


	if (tmp)
	{

		bool auto_range = true; // set to false to use manual range...

		// Manual range values

		int i, end, col, row;
		float value;
		unsigned short *src = (unsigned short *)tmp;
	
		unsigned char displayValue;
		end = img_rows*img_cols;  // image size...

		int	bottomvalue = 99999;
		int	topvalue = -99999;
		if (auto_range)
		{

			for (i = 0; i < end; i++)
			{
				value = src[i];
				bottomvalue = bottomvalue<value ? bottomvalue : value;
				topvalue = topvalue>value ? topvalue : value;
			}
		}

		float range = topvalue - bottomvalue;

		float top = bot + win_width;
		float step = (top - bot) / 12;
		if (range != 0)
		{

			for (i = 0; i < end; i++)
			{
				value = *src++;
				// Limit upper + lower values
				if (value < bottomvalue) value = bottomvalue;
				if (value > topvalue)    value = topvalue;
				// Scale to 0..255 for display
				displayValue = ((value - bottomvalue) * 255) / range;

				float tmper = (value -10000) / 100.00;
	
				row = i / img_cols;
				col = i%img_cols;


				uchar* pG_dstData = g_tmpdst.ptr<uchar>(row);

				int gray = bot - 22 + displayValue;
				if (gray < 0) gray = 0;
				if (gray >255) gray = 255;

				*(pG_dstData + col) = gray;

				uchar* p_tmpdstData = tmpdst.ptr<uchar>(row);

				switch (color_type)
				{
				case 1:////传统伪彩色
					step = (top - bot) / 4;
					if (tmper < bot)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = 0;
						*(p_tmpdstData + col * 3) = 0;
					}
					else if (tmper < bot + step)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = (tmper - bot) * 255 / step;
						*(p_tmpdstData + col * 3) = 255;

					}
					else if (tmper <= bot + step * 2)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = 255;
						*(p_tmpdstData + col * 3) = (bot + step * 2 - tmper) * 255 / step;
					}
					else if (tmper <= bot + step * 3)
					{
						*(p_tmpdstData + col * 3 + 2) = (tmper - bot - step * 2) * 255 / step;
						*(p_tmpdstData + col * 3 + 1) = 255;
						*(p_tmpdstData + col * 3) = 0;
					}
					else if (tmper <= top)
					{
						*(p_tmpdstData + col * 3 + 2) = 255;
						*(p_tmpdstData + col * 3 + 1) = (top - tmper) * 255 / step;
						*(p_tmpdstData + col * 3) = 0;
					}
					else
					{
						*(p_tmpdstData + col * 3 + 2) = 255;
						*(p_tmpdstData + col * 3 + 1) = 255;
						*(p_tmpdstData + col * 3) = 255;
					}
					break;
				case 2:
					//根据TTM8推测
					step = (top - bot) / 16;
					if (tmper < bot)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = 0;
						*(p_tmpdstData + col * 3) = 0;
					}
					else if (tmper < bot + step*1.5)
					{
						*(p_tmpdstData + col * 3 + 2) = (tmper - bot) * 84 / (step*1.5);;
						*(p_tmpdstData + col * 3 + 1) = (tmper - bot) * 84 / (step*1.5);
						*(p_tmpdstData + col * 3) = (tmper - bot) * 84 / (step*1.5);

					}
					else if (tmper <= bot + step * 3)
					{
						*(p_tmpdstData + col * 3 + 2) = (bot + step * 3 - tmper) * 84 / (step*1.5);
						*(p_tmpdstData + col * 3 + 1) = (bot + step * 3 - tmper) * 84 / (step*1.5);
						*(p_tmpdstData + col * 3) = 84 + (tmper - (bot + step * 1.5)) * 252 / (step*2.5);
					}
					else if (tmper <= bot + step * 4)
					{
						*(p_tmpdstData + col * 3 + 2) = (tmper - (bot + step * 3)) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = (tmper - (bot + step * 3)) * 84 / step;;
						*(p_tmpdstData + col * 3) = 84 + (tmper - (bot + step * 3)) * 168 / (step*2.5);;
					}
					else if (tmper <= bot + step * 6)
					{
						*(p_tmpdstData + col * 3 + 2) = ((bot + step * 6) - tmper) * 84 / (step * 2);
						*(p_tmpdstData + col * 3 + 1) = 84 + (tmper - (bot + step * 4)) * 84 / (step * 2);
						*(p_tmpdstData + col * 3) = 168 + ((bot + step * 6) - tmper) * 84 / (step * 2);
					}
					else if (tmper <= bot + step * 8)
					{
						*(p_tmpdstData + col * 3 + 2) = (tmper - (bot + step * 6)) * 84 / (step * 2);
						*(p_tmpdstData + col * 3 + 1) = 168 + (tmper - (bot + step * 6)) * 84 / (step * 2);
						*(p_tmpdstData + col * 3) = 168 + (tmper - (bot + step * 6)) * 84 / (step * 2);
					}
					else if (tmper <= bot + step * 9)
					{
						*(p_tmpdstData + col * 3 + 2) = ((bot + step * 9) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = 168 + ((bot + step * 9) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3) = ((bot + step * 9) - tmper) * 252 / step;
					}
					else if (tmper <= bot + step * 10)
					{
						*(p_tmpdstData + col * 3 + 2) = (tmper - (bot + step * 9)) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = 168 + (tmper - (bot + step * 9)) * 84 / step;
						*(p_tmpdstData + col * 3) = (tmper - (bot + step * 9)) * 84 / step;
					}
					else if (tmper <= bot + step * 11)
					{
						*(p_tmpdstData + col * 3 + 2) = 84 + (tmper - (bot + step * 10)) * 168 / step;
						*(p_tmpdstData + col * 3 + 1) = 252;
						*(p_tmpdstData + col * 3) = 84;
					}
					else if (tmper <= bot + step * 12)
					{
						*(p_tmpdstData + col * 3 + 2) = 168 + ((bot + step * 12) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = 84 + (bot + step * 12 - tmper) * 168 / step;
						*(p_tmpdstData + col * 3) = ((bot + step * 12) - tmper) * 84 / step;
					}
					else if (tmper <= bot + step * 13)
					{
						*(p_tmpdstData + col * 3 + 2) = 168 + (tmper - (bot + step * 12)) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = 84;
						*(p_tmpdstData + col * 3) = (tmper - (bot + step * 12)) * 252 / step;
					}
					else if (tmper <= bot + step * 14)
					{
						*(p_tmpdstData + col * 3 + 2) = 168 + ((bot + step * 14) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = ((bot + step * 14) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3) = 168 + ((bot + step * 14) - tmper) * 84 / step;
					}
					else if (tmper <= bot + step * 15)
					{
						*(p_tmpdstData + col * 3 + 2) = 168 + (tmper - (bot + step * 14)) * 84 / step;
						*(p_tmpdstData + col * 3 + 1) = (tmper - (bot + step * 14)) * 84 / step;
						*(p_tmpdstData + col * 3) = 84 + ((bot + step * 15) - tmper) * 84 / step;
					}
					else if (tmper <= bot + step * 16)
					{
						*(p_tmpdstData + col * 3 + 2) = 252;
						*(p_tmpdstData + col * 3 + 1) = ((bot + step * 16) - tmper) * 84 / step;
						*(p_tmpdstData + col * 3) = ((bot + step * 16) - tmper) * 84 / step;
					}
					else
					{
						*(p_tmpdstData + col * 3 + 2) = 252;
						*(p_tmpdstData + col * 3 + 1) = 252;
						*(p_tmpdstData + col * 3) = 252;
					}

				}
			}
		}
	}

	Mat tmpdst2;
	if (filter_type == 0)
	{
		medianBlur(tmpdst, tmpdst2, 3);
	}
	else if (filter_type == 1)
	{

		Mat channels[3];
		split(tmpdst, channels);

		for (int i = 0; i < 3; i++)
		{
			equalizeHist(channels[i], channels[i]);
		}

		merge(channels, 3, tmpdst2);

	}
	else
	{
		tmpdst.copyTo(tmpdst2);

	}


	if (color_type == 0)
	{
		Mat g_tmpdst2;
		if (filter_type == 0)
		{

			medianBlur(g_tmpdst, g_tmpdst2, 3);
		}
		else if (filter_type == 1)
		{

			equalizeHist(g_tmpdst, g_tmpdst2);
		}
		else
		{
			g_tmpdst.copyTo(g_tmpdst2);
		}


		dst.create(Size(g_tmpdst2.rows, g_tmpdst2.cols), CV_8UC1);

		transpose(g_tmpdst2, dst);     //转置

		flip(dst, dst, 0);     //镜像


	}
	else
	{
		//	tmpdst.copyTo(tmpdst2);
		dst.create(Size(tmpdst2.rows, tmpdst2.cols), CV_8UC3);

		transpose(tmpdst2,dst);     //转置

		flip(dst, dst, 0);     //镜像

		cvtColor(dst, dst, CV_BGR2RGB);
	}


	tmpdst.release();
	g_tmpdst.release();

}