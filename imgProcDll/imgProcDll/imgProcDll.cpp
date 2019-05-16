// imgProcDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "imgProcDll.h"
#include <fstream>



using namespace cv;

// ���ǵ���������һ��ʾ��
//IMGPROCDLL_API int nimgProcDll=0;
//
//// ���ǵ���������һ��ʾ����
//IMGPROCDLL_API int fnimgProcDll(void)
//{
//	return 42;
//}
//
//// �����ѵ�����Ĺ��캯����
//// �й��ඨ�����Ϣ������� imgProcDll.h
//CimgProcDll::CimgProcDll()
//{
//	return;
//}


IMGPROCDLL_API void myResize(Mat & src, Mat &dst, int width, int height)
{
	resize(src, dst, Size(width, height));
}

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


IMGPROCDLL_API void data2Img(unsigned short * tmp, Mat& dst, int img_rows, int img_cols, float mintemp = 25, int win_width=16,int color_type = 2, int filter_type = 2)
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
		//unsigned char  *dest = (unsigned char  *)m_ImageData8;
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
		float bot = mintemp;
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
				//float tmper;
				//if (displayValue < 40)
				//{
				//	tmper = 0;
				//}
				//else
				//{
				//	tmper = mintemp + ((value - bottomvalue) * 15) / range;
				//}
				float tmper = mintemp + ((value - bottomvalue) * 15) / range;
				//			float tmper = value/100;
				row = i / img_cols;
				col = i%img_cols;

				//g_tmpdst.at<uchar>(row, col) = displayValue;
				uchar* pG_dstData = g_tmpdst.ptr<uchar>(row);

				*(pG_dstData + col) = displayValue;

				uchar* p_tmpdstData = tmpdst.ptr<uchar>(row);
				switch (color_type)
				{
				case 1:////��ͳα��ɫ
					step = (top - bot) / 4;
					if (tmper < bot)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = 0;
						*(p_tmpdstData + col * 3) = 0;
					}
					if (tmper < bot + step)
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
					//����TTM8�Ʋ�
					step = (top - bot) / 16;
					if (tmper < bot)
					{
						*(p_tmpdstData + col * 3 + 2) = 0;
						*(p_tmpdstData + col * 3 + 1) = 0;
						*(p_tmpdstData + col * 3) = 0;
					}
					if (tmper < bot + step*1.5)
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

	//	Mat g_dstImage2, g_dstImage3, g_dstImage4, tempImage,g_tempImage;
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

		for (int i = 0; i < g_tmpdst2.rows; i++)
		{

			uchar *p_gtmpdstData = g_tmpdst2.ptr<uchar>(i);

			for (int j = 0; j < g_tmpdst2.cols; j++)
			{
				uchar *p_dstData = dst.ptr<uchar>(j);
				//dst.at<uchar>(j, HEIGHT - 1 - i) = g_tmpdst.at<uchar>(i, j);
				*(p_dstData + (img_rows - 1 - i)) = *(p_gtmpdstData + j);

			}
		}
	}
	else
	{
		//	tmpdst.copyTo(tmpdst2);
		dst.create(Size(tmpdst2.rows, tmpdst2.cols), CV_8UC3);
		for (int i = 0; i < tmpdst2.rows; i++)
		{
			uchar* p_tmpdstData = tmpdst2.ptr<uchar>(i);
			for (int j = 0; j < tmpdst2.cols; j++)
			{
				//	dst.at<Vec3b>(j, HEIGHT - 1 - i)[0] = tmpdst2.at<Vec3b>(i, j)[0];
				//	dst.at<Vec3b>(j, HEIGHT - 1 - i)[1] = tmpdst2.at<Vec3b>(i, j)[1];
				//	dst.at<Vec3b>(j, HEIGHT - 1 - i)[2] = tmpdst2.at<Vec3b>(i, j)[2];
				uchar *p_dstData = dst.ptr<uchar>(j);
				*(p_dstData + (img_rows - 1 - i) * 3) = *(p_tmpdstData + j * 3);
				*(p_dstData + (img_rows - 1 - i) * 3 + 1) = *(p_tmpdstData + j * 3 + 1);
				*(p_dstData + (img_rows - 1 - i) * 3 + 2) = *(p_tmpdstData + j * 3 + 2);
			}
		}

		cvtColor(dst, dst, CV_BGR2RGB);
	}


	tmpdst.release();
	g_tmpdst.release();

}
