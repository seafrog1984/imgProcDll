#ifndef _IRSDK_H
#define _IRSDK_H

#ifndef _WIN32
#define _WIN32
#endif

#ifdef _WIN32
#include <stdio.h>
#define IR_SDK_API  extern "C" __declspec(dllexport) 
#else
#define IR_SDK_API
#endif

#define DEVICE_COUNT			(32)							//���֧������32���豸��ʵ�����
#define OBJ_MAX					(32)							//���֧������32�������ϲ�ֻ������32�����ܳ���

typedef int (*CBF_IR)(void * lData, void * lParam);				//SDK�лص������ĸ�ʽ����

//�¶�ת��
#define CALTEMP(x,y)		((x-10000)/(float)y)				//Y16�������¶����ݵ�ת����ϵ

//�ļ�����
#define OPEN_FILE				(1)
#define CLOSE_FILE				(2)
#define WR_FRAME 				(3)

//�۽�����
#define  STOPFOCUS				(0)
#define  FARFOCUS				(1)
#define  NEARFOCUS				(2)
#define  AUTOFOCUS				(3)
#define  FOCUSSTATUS			(4)

//֡��ʽ,����ǰ��32Byte֡ͷ
typedef struct tagFrame
{
	unsigned short width;				//ͼ����	
	unsigned short height;				//ͼ��߶�
	unsigned short u16FpaTemp;			//�����¶�
	unsigned short u16EnvTemp;			//�����¶�
	unsigned char  u8TempDiv;			//����ת�����¶�ʱ��Ҫ���Ը����ݣ��ĵ�����˵��
	unsigned char  u8DeviceType;		//unused
	unsigned char  u8SensorType;		//unused
	unsigned char  u8MeasureSel;		//unused
	unsigned char  u8Lens;				//unused
	unsigned char  u8Fps;				//unused
	unsigned char  Reversed[18];		//unused
	unsigned short buffer[327680];		//ͼ�����ݣ����д洢�����֧�� 640x512��ÿ��������һ�� ushort ����
} Frame;
 

//�㣬 ��x,y)Ϊ����
typedef struct t_point
{
	unsigned short x;
	unsigned short y;
}T_POINT;

//�ߣ�P1,P2Ϊ���˵�
typedef struct t_line
{
	T_POINT P1;
	T_POINT P2;
}T_LINE;

//Բ��֧����Բ����Pc��ʾԲ�����꣬a��ʾ����ᣬb��ʾ�����ᣬ����Բ��a=b����ʾ�뾶
typedef struct t_circle
{
	T_POINT Pc;
	unsigned short a;
	unsigned short b;
}T_CIRCLE;

//���Σ� P1Ϊ�������϶������꣬P2Ϊ���¶�������
typedef struct t_rect
{
	T_POINT P1;
	T_POINT P2;
}T_RECT;

//�������Σ����֧��16�����㣬Pt_numΪ���������PtΪÿ���������
typedef struct t_polygon
{
	unsigned int Pt_num;
	T_POINT Pt[16];
}T_POLYGON;

//�״�ͼ�����֧��64�����㣬Pt_numΪ���������PtΪÿ���������
typedef struct t_radar
{
	unsigned int Pt_num;
	T_POINT Pt[64];
}T_RADAR;

//�����Сƽ���¶ȼ���ֵ��Ӧ����
typedef struct stat_temper
{
	float maxTemper;
	float minTemper;
	float avgTemper;

	T_POINT maxTemperPT;
	T_POINT minTemperPT;
}STAT_TEMPER;

//��ɫ
typedef struct t_color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
}T_COLOR;

//������������
enum T_ALARMTYPE
{
	OverHigh	= 0,			//���ڸ�����
	UnderLow	= 1,			//���ڵ�����
	BetweenHL	= 2,			//����
	DeBetweenHL = 3,			//��ѡ����
};

//�澯
typedef struct t_alarm
{
	unsigned char alarmType;	//�澯����
	unsigned char isDraw;		//�Ƿ�����
	unsigned char isVioce;		//�Ƿ������澯
	unsigned char isVideo;		//�Ƿ�¼��
	float		  HighThresh;	//������
	float		  LowThresh;	//������
	T_COLOR		  colorAlarm; 	//�澯��ɫ	
}T_ALARM;

//���Լ����¶�
typedef struct stat_point
{
	stat_point()
	{
		inputEmiss = 1.00;
		inputReflect = 0;
		inputDis = 3.0;
	}
	T_POINT sPoint;
	STAT_TEMPER sTemp;
	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR	 color;						//������ɫ
	T_ALARM  sAlarm;
}STAT_POINT;

//���Լ������¶�ͳ��
typedef struct stat_line
{
	stat_line()
	{
		inputEmiss = 1.00;
		inputReflect = 20.0;
		inputDis = 2.0;
	}
	T_LINE sLine;
	STAT_TEMPER sTemp;
	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR	 color;					//������ɫ	
	T_ALARM  sAlarm;
}STAT_LINE;

//Բ����Բ)�Լ�Բ���¶�ͳ��
typedef struct stat_circle
{
	stat_circle()
	{
		inputEmiss = 1.00;
		inputReflect = 20.0;
		inputDis = 2.0;
	}
	T_CIRCLE sCircle;
	STAT_TEMPER sTemp;
	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR		 color;					//������ɫ	
	T_ALARM  sAlarm;
}STAT_CIRCLE;

//�����Լ��������¶�ͳ��
typedef struct stat_rect
{
	stat_rect()
	{
		inputEmiss = 1.00;
		inputReflect = 20.0;
		inputDis = 2.0;
	}
	T_RECT sRect;
	STAT_TEMPER sTemp;
	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR	 color;					//������ɫ	
	T_ALARM  sAlarm;
}STAT_RECT;

//���������Լ���������¶�ͳ��
typedef struct stat_polygon
{
	stat_polygon()
	{
		inputEmiss = 1.00;
		inputReflect = 20.0;
		inputDis = 2.0;
	}
	T_POLYGON sPolygon;
	STAT_TEMPER sTemp;

	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;		
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR	 color;
	T_ALARM  sAlarm;
}STAT_POLYGON;

//����
typedef struct stat_radar
{
	stat_radar()
	{
		inputEmiss = 1.00;
		inputReflect = 20.0;
		inputDis = 2.0;
	}
	T_RADAR sRadar;
	STAT_TEMPER sTemp[64];

	unsigned int  LableEx[32];		//������
	unsigned char Lable[32];		//������
	float		  inputEmiss;		//���������
	float		  inputReflect;		//���뷴���¶�
	float		  inputDis;			//�������
	float		  Area;				//�������
	unsigned char reserved1;
	unsigned char reserved2;
	unsigned char reserved3;
	unsigned char reserved4;
	T_COLOR	 color;
	T_ALARM  sAlarm;
}STAT_RADAR;

//���ж��󣬸ýṹ������������в��¶���num��ʾ�����Ͷ���ĸ�������Ӧ��ָ�룬��Ҫָ����¶��󣬸ÿռ���Ҫ��ʹ��ǰ����
typedef struct stat_obj
{
	unsigned char numPt;
	unsigned char numLine;
	unsigned char numCircle;
	unsigned char numRect;
	unsigned char numPolygon;
	unsigned char Reserved1;
	unsigned char Reserved2;
	unsigned char Reserved3;

	T_ALARM sGlobalAlarm;		//ȫ�ָ澯��Ϣ

	STAT_POINT	sPt[OBJ_MAX];
	STAT_LINE	sLine[OBJ_MAX];
	STAT_CIRCLE sCircle[OBJ_MAX];
	STAT_RECT	sRect[OBJ_MAX];
	STAT_POLYGON sPolygon[OBJ_MAX];
	STAT_RADAR Reserved[1];
}STAT_OBJ;


//128byte���洢ԭʼ��Ƶʱ����ͷ��Ϣ�ᱣ�浽��Ƶ�ļ��У���ȡʱ���������ͷ��Ϣ�Թ�ʹ��
typedef struct tagSAVEHead
{
	unsigned char  Head[32];
	unsigned short width;
	unsigned short height;
	unsigned int   totalFrames;
	unsigned short Freq;
	unsigned char  isSaveObj;
	unsigned char  Reserved[85];
} T_SAVE_HEAD;

typedef struct tagTIME {
	unsigned short year;
	unsigned short month;
	unsigned short day;
	unsigned short hour;
	unsigned short minute;
	unsigned short sencond;
	unsigned short millisecond;
} T_TIME;


//512byte���豸��Ϣ�������ַ�����ʽ�洢���ÿռ��Ѿ����٣�����Ҫ������ռ�
typedef struct tagDeviceID
{
	unsigned char  Name[32];			//�豸����
	unsigned char  Model[32];		//�豸�ͺ�
	unsigned char  SerialNum[32];	//�豸���к�
	unsigned char  Lens[32];			//��ͷ���
	unsigned char  FactoryTime[32];	//����ʱ��
	unsigned char  WorkTime[32];		//����ʱ��
	unsigned char  Mac[32];			//MAC��ַ
	unsigned char  IP[32];			//IP��ַ
	unsigned char  Reserved1[32];
	unsigned char  Reserved2[32];
	unsigned char  Reserved3[32];
	unsigned char  Reserved4[32];
	unsigned char  Reserved5[32];
	unsigned char  Reserved6[32];
	unsigned char  Reserved7[32];
	unsigned char  Reserved8[32];
}T_DEVICE_INFO;

typedef struct tagIPADDR
{
	char IPAddr[32];			//IP
	unsigned char Reserved[32]; //����
	unsigned int DataPort;		//Port
	unsigned char isValid;		//�Ƿ�����
	unsigned char totalOnline;  //���߸���
	unsigned char Index;        //���б��е�����
}T_IPADDR;

//������������
enum T_PARAMTYPE
{
	paramDevice			= 0,			//�豸����
	paramDownSample		= 1,			//������
	paramDecCoef		= 2,			//У��ϵ��
	paramReserved1	    = 3,			//����
	paramReserved2		= 4,			//����
	paramSpaceFilter	= 5,			//�����˲�
	paramReserved4 		= 6,			//����
	paramTempSegSel		= 7,			//�¶ȶ�ѡ��
	paramReserved6		= 8,			//����
	paramReserved7		= 9,			//����
	paramReserved8		= 10,			//����
	paramCaliSwitch		= 11,			//����У������
};


#ifndef _T_CTRLPROTOCOL			//��ֹ�ظ�����
#define _T_CTRLPROTOCOL
//�˶���������
enum T_PARAMCTRL
{
	//Э��ѡ��
	paramPelcod 		= 0,		   //pelco-d
	paramUserDef1		= 1,		   //�Զ���Э��1�������ˣ�
	paramUserDef2		= 2,		   //�Զ���Э��2�������
	paramUserDef3		= 3,		   //�Զ���Э��3��ת̨��

	//����
	paramCtrlUp			= 4,			//��
	paramCtrlDown		= 5,			//��
	paramCtrlLeft		= 6,			//��
	paramCtrlRight		= 7,			//��
	paramCtrlStop		= 8,			//ֹͣ
	paramCtrlBaudRate	= 9,			//������
};
#endif

IR_SDK_API int IRSDK_Init(void);
IR_SDK_API int IRSDK_Quit(void);
IR_SDK_API int IRSDK_Create(int handle, T_IPADDR sIPAddr, CBF_IR cbf_stm, CBF_IR cbf_cmd, CBF_IR cbf_comm, void * param = 0);
IR_SDK_API int IRSDK_Destroy(int handle);
IR_SDK_API int IRSDK_Connect(int handle);
IR_SDK_API int IRSDK_Play(int handle);
IR_SDK_API int IRSDK_Stop(int handle);
IR_SDK_API int IRSDK_SetIP(int handle, char * pIp);
IR_SDK_API int IRSDK_Command(int handle, int command, int param);
IR_SDK_API int IRSDK_Calibration(int handle);
IR_SDK_API int IRSDK_CommSend(int handle, char *pBuf, int len);
IR_SDK_API int IRSDK_IsConnected(int handle);
IR_SDK_API int IRSDK_NearFarFocus(int handle, unsigned int param);
IR_SDK_API int IRSDK_InqureIP(void * pIpInfo, unsigned int TimerInterval);
IR_SDK_API int IRSDK_InqureDeviceInfo(int handle, T_DEVICE_INFO* pDevInfo);

IR_SDK_API int IRSDK_ParamCfg(int handle, T_PARAMTYPE mParamType, float f32Param);

IR_SDK_API int IRSDK_FrameConvert(Frame *pFrame, unsigned short *pGray, float f32Constrast, float f32Bright, unsigned int *pGethist, STAT_TEMPER *pFull_temper, unsigned short u16TFilterCoef);

IR_SDK_API int IRSDK_Gray2Rgb(unsigned short* pGray, unsigned char* pRgb, unsigned short Width, unsigned short Height, int PalType, int Pal);

IR_SDK_API int IRSDK_GetPaletteJpeg(unsigned char* pPaletteJpeg, unsigned int *pJpegLen, unsigned char Method, int PalType, int Pal);
IR_SDK_API int IRSDK_GetPaletteBmp(unsigned char* pPaletteBmp, unsigned int *pBmpLen, unsigned char Method, int PalType, int Pal);

IR_SDK_API int IRSDK_GetPointTemp(Frame *pFrame, STAT_POINT *pPointStat);
IR_SDK_API int IRSDK_GetLineTemp(Frame *pFrame, STAT_LINE *pLineStat);
IR_SDK_API int IRSDK_GetCircleTemp(Frame *pFrame, STAT_CIRCLE *pCircleStat);
IR_SDK_API int IRSDK_GetRectTemp(Frame *pFrame, STAT_RECT *pRectStat);
IR_SDK_API int IRSDK_GetPolygonTemp(Frame *pFrame, STAT_POLYGON *pPolygonStat);
IR_SDK_API int IRSDK_GetObjTemp(Frame *pFrame, STAT_OBJ *pObjStat);

IR_SDK_API int IRSDK_Rgb2Bmp(unsigned char * pBmpData, unsigned int *pLen, unsigned char* pRgb, unsigned short Width, unsigned short Height);
IR_SDK_API int IRSDK_Rgb2Jpeg(unsigned char * pJpegout, unsigned int *pLen, int quality, unsigned char * pRgb, unsigned short Width, unsigned short Height);

IR_SDK_API int IRSDK_SaveFrame2Jpeg(char* pFile, Frame *pFrame, unsigned char* pRgb, unsigned char isSaveObj, STAT_OBJ *pObj);
IR_SDK_API int IRSDK_ReadJpeg2Frame(char *pFile, Frame *pFrame, unsigned char isLoadObj, STAT_OBJ *pObj);

IR_SDK_API int IRSDK_SaveFrame2Video(char *pFile, Frame *pFrame, unsigned char Op, unsigned char isSaveObj, STAT_OBJ *pObj, unsigned char * pThreadBuf);
IR_SDK_API int IRSDK_ReadVideo2Frame(char *pFile, Frame *pFrame, unsigned int Index, unsigned char Op, T_SAVE_HEAD *pVideoHead, STAT_OBJ *pObj, unsigned char * pThreadBuf);

IR_SDK_API int IRSDK_SaveRgb2AVI(char* pFile, unsigned char *pRgb, unsigned short Width, unsigned short Height, unsigned char Op, int quality, unsigned char * pThreadBuf);

IR_SDK_API int IRSDK_SaveObj2CSV(char *pFile, unsigned char Op, STAT_OBJ *pObj, STAT_TEMPER *pGlobalTemper, unsigned int u32Tinterval, unsigned char * pThreadBuf);
IR_SDK_API int IRSDK_SaveFrame2CSV(char* pFile, Frame *pFrame);
IR_SDK_API int IRSDK_SaveLine2CSV(char* pFile, Frame *pFrame, T_LINE sLine, unsigned char u8Format);
IR_SDK_API int IRSDK_SaveRect2CSV(char* pFile, Frame *pFrame, T_RECT sRect);
IR_SDK_API int IRSDK_SaveCircle2CSV(char* pFile, Frame *pFrame, T_CIRCLE sCircle);
IR_SDK_API int IRSDK_SavePolygon2CSV(char* pFile, Frame *pFrame, T_POLYGON sPolygon);

IR_SDK_API int IRSDK_MoveCtrl(int handle, T_PARAMCTRL mProtocol, T_PARAMCTRL mType, unsigned int u32Param);
IR_SDK_API int IRSDK_TempCorrect(float f32Emiss, float f32Reflect, float f32Dis, STAT_TEMPER *pFull_temper);
#endif
