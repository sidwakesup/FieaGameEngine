// Game.Desktop.DirectX.cpp : Defines the entry point for the console application.

#include "pch.h"

#define WindowXPosition 300
#define WindowYPosition 300
#define WindowWidth 640
#define WindowHeight 480

#define ViewportWidth 800
#define ViewportHeight 600

#pragma comment (lib, "d3d11.lib")

//global declarations
IDXGISwapChain *swapChain;			//the pointer to the swap chain interface
ID3D11Device *device;				//the pointer to our Direct3D device interface
ID3D11DeviceContext *deviceContext;	//the pointer to our Direct3D device context
ID3D11RenderTargetView *backBuffer;	

//function prototypes
void InitD3D(HWND hWnd);		//sets up and initializes Direct3D
void RenderFrame(void);			//renders a single frame
void CleanD3D(void);			//closes Direct3D and releases memory

//the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//the entry point of any Windows program
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(hPrevInstance);

	//the handle for the window, filled by a function
	HWND hWnd;

	//this struct holds the information for the window class
	WNDCLASSEX wc;

	//clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	//fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";

	//register the window class
	RegisterClassEx(&wc);

	//create the window and use the result as the handle
	hWnd = CreateWindowEx(
		NULL,
		L"WindowClass",					//name of the window class
		L"Window Created in DirectX",	//title of the window
		WS_OVERLAPPEDWINDOW,			//window style
		WindowXPosition,
		WindowYPosition,
		WindowWidth,
		WindowHeight,
		NULL,							//we have no parent window
		NULL,							//we are not using menus
		hInstance,						//application handle
		NULL							//used with multiple windows
	);

	//display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	//set up and initialize Direct3D
	InitD3D(hWnd);

	//Main Loop:

	//this struct holds Window event messages
	MSG msg;

	//enter the infinite message loop
	while (TRUE)
	{
		//check to see if any messages are waiting in the queue
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//Translate the message and dispatch it to WindowProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//if the message is VM_QUIT, exit the while loop
			if (msg.message == WM_QUIT)
				break;
		}

		RenderFrame();
	}

	//clean up DirectX and COM
	CleanD3D();

	//return this part of the WM_QUIT message to Windows
	return (int)msg.wParam;

}

//this function initializes and prepares Direct3D for use
void InitD3D(HWND hWnd)
{
	//create a struct to hold information about the swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDescription;

	//clear out the struct for use
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));

	//fill the swap chain description struct
	swapChainDescription.BufferCount = 1;										//one back buffer
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		//use 32-bit color
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;			//how swap chain is to be used
	swapChainDescription.OutputWindow = hWnd;									//the window to be used
	swapChainDescription.SampleDesc.Count = 4;									//how many multisamples
	swapChainDescription.Windowed = TRUE;										//windowed/full-screen mode

	//create a device, device context and swap chain using the information in the swapChainDescription structure
	D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		NULL,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&swapChainDescription,
		&swapChain,
		&device,
		NULL,
		&deviceContext
	);

	//get the address of the back buffer
	ID3D11Texture2D *pBackBuffer;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

	//use the back buffer address to create the render target
	device->CreateRenderTargetView(pBackBuffer, NULL, &backBuffer);
	pBackBuffer->Release();

	//set the render target as the back buffer
	deviceContext->OMSetRenderTargets(1, &backBuffer, NULL);

	//set the viewport
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = ViewportWidth;
	viewport.Height = ViewportHeight;

	deviceContext->RSSetViewports(1, &viewport);
}

//this is the function that cleans up Direct3D and COM
void CleanD3D()
{
	//close and release all existing COM objects
	swapChain->Release();
	backBuffer->Release();
	device->Release();
	deviceContext->Release();
}

//this is the function used to render a single frame
void RenderFrame(void)
{
	//clear the back buffer to a deep blue
	float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	deviceContext->ClearRenderTargetView(backBuffer, color);

	//do 3D rendering on the back buffer here

	//switch the back buffer and the front buffer
	swapChain->Present(0, 0);
}

//this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//sort through and find what code to run for the message given
	switch (message)
	{
		//this message is read when the window is closed
	case WM_DESTROY:
		//close the application entirely
		PostQuitMessage(0);
		return 0;
		break;
	}

	//handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}