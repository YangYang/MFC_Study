
// myapp_1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "myapp_1.h"
#include "myapp_1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmyapp_1Dlg 对话框




Cmyapp_1Dlg::Cmyapp_1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmyapp_1Dlg::IDD, pParent)
	, time_sum(0)
	, tv_time_left(_T(""))
	, et_zkz(_T(""))
	, et_sfz(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmyapp_1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BEGIN_TEXT, btn_begin_test);
	DDX_Text(pDX, IDC_TIME_LEFT, tv_time_left);
	DDX_Text(pDX, IDC_EDIT1, et_zkz);
	DDV_MaxChars(pDX, et_zkz, 11);
	DDX_Text(pDX, IDC_EDIT2, et_sfz);
	DDV_MaxChars(pDX, et_sfz, 18);
}

BEGIN_MESSAGE_MAP(Cmyapp_1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Cmyapp_1Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BEGIN_TEXT, &Cmyapp_1Dlg::OnBnClickedBeginText)
//	ON_WM_TCARD()
ON_WM_TIMER()
END_MESSAGE_MAP()


// Cmyapp_1Dlg 消息处理程序

BOOL Cmyapp_1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cmyapp_1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cmyapp_1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmyapp_1Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void Cmyapp_1Dlg::OnBnClickedBeginText()
{
	// TODO: 在此添加控件通知处理程序代码
	//这里需要判断用户输入的准考证信息，身份证信息是否合法，暂时先省略
	//判断准考证号
	UpdateData(TRUE);
	int zkz_result = check_zkz(et_zkz);
    if (zkz_result == 1)
    {
        MessageBox(_T("准考证为11位数字"));
        return;
    }

	int sfz_result = check_sfz(et_sfz);
	if(sfz_result==1)
	{
		 MessageBox(_T("身份证号为18位数字（最后一位可以是x，支持大小写）"));
        return;
    }
    if (sfz_result == 2)
    {
        MessageBox(_T("对不起，您的年龄不在合法的职工年龄范围"));
        return;
    }
    if (sfz_result == 3)
    {
        MessageBox(_T("身份证号码错误"));
        return;
    }
    btn_begin_test.EnableWindow(FALSE);//让按钮无法点击
    SetTimer(1,1000,NULL);//设置一个定时器，这里有三个参数,第一个参数：定时器id，第二个参数：时间间隔，第三个参数：需要触发的函数，当值为NULL交给系统处理
}


//void Cmyapp_1Dlg::OnTCard(UINT /*idAction*/, DWORD /*dwActionData*/)
//{
//	// TODO: 在此处添加消息处理程序代码
//}


void Cmyapp_1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	tv_time_left = getFormatTime(++time_sum);
    UpdateData(FALSE);
    CDialogEx::OnTimer(nIDEvent);
}



CString Cmyapp_1Dlg::getFormatTime(int time_left)
{
	int sum = 15*60 - time_left;
    int second = sum % 60;
    int minute = sum / 60;
    CString t;
    t.Format(L"%d分%d秒",minute,second);
    return t;
}



int Cmyapp_1Dlg::check_zkz(CString zkz)
{
	int length = zkz.GetLength();
	if(length==11)
		return 0;
	return 1;
}


int Cmyapp_1Dlg::check_sfz(CString sfz)
{
	int length=sfz.GetLength();
	if(length==18)
	{
		return 0;
	}
	return 1;
}
