
#include <Windows.h>

// 全局服务状态
SERVICE_STATUS g_serviceStatus = {};
SERVICE_STATUS_HANDLE g_statusHandle = nullptr;
HANDLE g_stopEvent = nullptr;
bool g_isRunning = true;

// 向 Windows 报告服务状态
void ReportStatus(DWORD currentState, DWORD win32ExitCode = NO_ERROR)
{
    g_serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_serviceStatus.dwCurrentState = currentState;
    g_serviceStatus.dwWin32ExitCode = win32ExitCode;
    g_serviceStatus.dwWaitHint = 0;

    g_serviceStatus.dwControlsAccepted =
        (currentState == SERVICE_RUNNING)
        ? SERVICE_ACCEPT_STOP
        : 0;

    if (g_statusHandle != nullptr)
    {
        SetServiceStatus(g_statusHandle, &g_serviceStatus);
    }
}

// 处理 Windows 发来的控制命令
void WINAPI ServiceHandler(DWORD control)
{
    if (control == SERVICE_CONTROL_STOP)
    {
        ReportStatus(SERVICE_STOP_PENDING);

        if (g_stopEvent != nullptr)
        {
            SetEvent(g_stopEvent);
			g_isRunning = false;
        }
    }
}

// 服务的主体逻辑
void WINAPI ServiceMain(DWORD argc, LPWSTR* argv)
{
    // 注册控制处理函数
    g_statusHandle = RegisterServiceCtrlHandlerW(
        L"MyService",
        ServiceHandler
    );

    if (g_statusHandle == nullptr)
    {
        return;
    }

    // 创建停止事件
    g_stopEvent = CreateEventW(
        nullptr,
        TRUE,   // 手动重置事件
        FALSE,  // 初始状态：未触发
        nullptr
    );

    if (g_stopEvent == nullptr)
    {
        ReportStatus(SERVICE_STOPPED, GetLastError());
        return;
    }

    // 通知 Windows：服务已经启动
    ReportStatus(SERVICE_RUNNING);

    // ==========================================
    // TODO: 在这里编写服务的主逻辑
    //
    // 例如：
    // 1. 初始化 TCP / UDP Socket
    // 2. 监听客户端请求
    // 3. 读取和处理数据
    // 4. 等待停止事件并退出
    //
    // 当前示例不执行任何业务逻辑，
    // 只等待 Windows 发出停止命令。
    // ==========================================
    while (g_isRunning)
    {
        Sleep(1000);
		OutputDebugStringA("Service is running...\n");
    }

    WaitForSingleObject(g_stopEvent, INFINITE);

    // 清理资源
    CloseHandle(g_stopEvent);
    g_stopEvent = nullptr;

    // 通知 Windows：服务已经停止
    ReportStatus(SERVICE_STOPPED);
}

// 程序入口
int wmain()
{
    SERVICE_TABLE_ENTRYW serviceTable[] =
    {
        {
            const_cast<LPWSTR>(L"MyService"),
            ServiceMain
        },
        { nullptr, nullptr }
    };

    // 将程序连接到 Windows 服务控制管理器
    if (!StartServiceCtrlDispatcherW(serviceTable))
    {
        return static_cast<int>(GetLastError());
    }

    return 0;
}