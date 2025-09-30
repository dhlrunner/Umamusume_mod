#include "ImguiWindows.h"

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace UnityEngine::Application;
namespace ImGuiWindows {
	typedef HRESULT(__stdcall* Present) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
	typedef HRESULT(__stdcall* ResizeBuffers)(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags);

	struct ScrollingBuffer {
		int MaxSize;
		int Offset;
		ImVector<ImVec2> Data;
		ScrollingBuffer(int max_size = 2000) {
			MaxSize = max_size;
			Offset = 0;
			Data.reserve(MaxSize);
		}
		void AddPoint(float x, float y) {
			if (Data.size() < MaxSize)
				Data.push_back(ImVec2(x, y));
			else {
				Data[Offset] = ImVec2(x, y);
				Offset = (Offset + 1) % MaxSize;
			}
		}
		void Erase() {
			if (Data.size() > 0) {
				Data.shrink(0);
				Offset = 0;
			}
		}
	};

	bool imguiShow = false;
	bool imguiSettingWndOpened = false;

	static ImVector<ImRect> s_GroupPanelLabelStack;

	Present oPresent;
	ResizeBuffers oResizeBuffers;
	HWND umaWindow = NULL;
	WNDPROC oWndProc;
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pContext = NULL;
	ID3D11RenderTargetView* mainRenderTargetView;
	IDXGISwapChain* g_pSwapChain = NULL;

	static std::vector<void*> rootObjList;
	ID3D11ShaderResourceView* texture_kimura = NULL;
	int kimura_image_width = 0;
	int kimura_image_height = 0;

	const int MAX_FPS_VALUES = 100;               // 최근 100개의 FPS 값을 저장
	static ScrollingBuffer fpsValues;                  // FPS 값들을 저장할 큐

	int UILoop();
	void InitImGui();



	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
			return true;

		return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
	}


	bool init = false;
	HRESULT __stdcall hkPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
	{
		if (!init)
		{
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&pDevice)))
			{
				g_pSwapChain = pSwapChain;
				pDevice->GetImmediateContext(&pContext);
				DXGI_SWAP_CHAIN_DESC sd;
				pSwapChain->GetDesc(&sd);
				umaWindow = sd.OutputWindow;
				ID3D11Texture2D* pBackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
				if (pBackBuffer)
				{
					pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
				}
				else
				{
					Logger::Error(L"IMGUI", L"Failed to create render target view");
				}

				pBackBuffer->Release();
				oWndProc = (WNDPROC)SetWindowLongPtr(umaWindow, GWLP_WNDPROC, (LONG_PTR)WndProc);
				InitImGui();
				Logger::Info(L"IMGUI", L"pSwapChain=%p 3D11DeviceAddr=%p", g_pSwapChain, pDevice);
				init = true;
				
			}

			else
				return oPresent(pSwapChain, SyncInterval, Flags);
		}
		if (Global::Game_HookFinished)
			UILoop();

		return oPresent(pSwapChain, SyncInterval, Flags);
	}

	HMODULE GetCurrentModule()
	{ // NB: XP+ solution!
		HMODULE hModule = NULL;
		GetModuleHandleEx(
			GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
			(LPCTSTR)GetCurrentModule,
			&hModule);

		return hModule;
	}
	// Simple helper function to load an image into a DX11 texture with common settings
	bool LoadTextureFromMemory(const unsigned char* buf, int size, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height)
	{
		// Load from disk into a raw RGBA buffer
		int image_width = 0;
		int image_height = 0;
		unsigned char* image_data = (unsigned char*)stbi_load_from_memory((unsigned char*)buf, size, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = image_width;
		desc.Height = image_height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem = image_data;
		subResource.SysMemPitch = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		pDevice->CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		if (pTexture != nullptr) {
			pDevice->CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		}
		else {
			// Handle the error appropriately, e.g., log it or set a default value for out_srv
			// For example:
			*out_srv = nullptr;
			Logger::Error(L"IMGUI", L"Failed to create texture");
		}
		pTexture->Release();

		*out_width = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}

	void createRenderTarget()
	{
		ID3D11Texture2D* pBackBuffer;
		g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
		if (pBackBuffer == nullptr)
		{
			Logger::Error(L"IMGUI", L"Failed to get back buffer");
			return;
		}
		else
		{
			pDevice->CreateRenderTargetView(pBackBuffer, NULL, &mainRenderTargetView);
			pBackBuffer->Release();
		}
	}

	void cleanupRenderTarget()
	{
		if (nullptr != mainRenderTargetView)
		{
			mainRenderTargetView->Release();
			mainRenderTargetView = nullptr;
		}
	}


	//dx11 ResizeBuffers Hook
	HRESULT __stdcall hkResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
	{
		HRESULT hr = 0;
		if (pDevice != NULL) {
			//printf("resize\n");
			cleanupRenderTarget();
			hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
			createRenderTarget();
		}
		else {
			hr = oResizeBuffers(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);
		}

		return hr;
	}
	DWORD WINAPI MainThread(LPVOID lpReserved)
	{
		bool init_hook = false;
		Logger::Info(L"KIERO", L"Waiting for D3D11...");
		do
		{
			if (kiero::init(kiero::RenderType::D3D11) == kiero::Status::Success)
			{
				Logger::Info(L"KIERO", L"Kiero initialized");
				kiero::bind(8, (void**)&oPresent, hkPresent);
				kiero::bind(13, (void**)&oResizeBuffers, hkResizeBuffers);
				init_hook = true;
			}
		} while (!init_hook);
		return TRUE;
	}

	void InitKiero() {
		Logger::Info(L"KIERO", L"Initializing Kiero");
		HMODULE hMod = GetCurrentModule();
		DisableThreadLibraryCalls(hMod);
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hMod, 0, nullptr);
		
	}

	void InitImGui() {

		il2cpp_thread_attach(il2cpp_domain_get());
		Logger::Info(L"IMGUI", L"Initializing ImGui");

		ImVec2 size = ImVec2(750.0f, 900.0f);

		Logger::Info(L"IMGUI", L"Entering CreateContext()");
		ImGui::CreateContext();
		Logger::Info(L"IMGUI", L"CreateContext() End");

		ImPlot::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
		//io.MouseDrawCursor = true;
		//io.WantCaptureMouse = true;
		ImGui_ImplWin32_Init(umaWindow);
		ImGui_ImplDX11_Init(pDevice, pContext);
		static const ImWchar ranges[] = { 0x0001, 0xffff, 0 };
		ImFontConfig config;
		config.MergeMode = true;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\malgun.ttf", 25.0f, NULL, io.Fonts->GetGlyphRangesKorean());
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 25.0f, &config, io.Fonts->GetGlyphRangesJapanese());
		ImGui::StyleColorsDark();

		//수고하셨습니다. 기무라 유이토씨
		//bool ret = LoadTextureFromMemory(야떼미로, sizeof(야떼미로) / sizeof(야떼미로[0]), &texture_kimura, &kimura_image_width, &kimura_image_height);
		//IM_ASSERT(ret);

		ImGui::MergeIconsWithLatestFont(16.f, false);
		//UILoop();
		//imguiwindow();
	}

	void BeginGroupPanel(const char* name, const ImVec2& size = ImVec2(0.0f, 0.0f));
	void BeginGroupPanel(const char* name, const ImVec2& size)
	{
		ImGui::BeginGroup();

		auto cursorPos = ImGui::GetCursorScreenPos();
		auto itemSpacing = ImGui::GetStyle().ItemSpacing;
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();
		ImGui::BeginGroup();

		ImVec2 effectiveSize = size;
		//if (size.x < 0.0f)
		//	effectiveSize.x = ImGui::GetContentRegionAvailWidth();
		//else
		effectiveSize.x = size.x;
		ImGui::Dummy(ImVec2(effectiveSize.x, 0.0f));

		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::BeginGroup();
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::TextUnformatted(name);
		auto labelMin = ImGui::GetItemRectMin();
		auto labelMax = ImGui::GetItemRectMax();
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(0.0, frameHeight + itemSpacing.y));
		ImGui::BeginGroup();

		//ImGui::GetWindowDrawList()->AddRect(labelMin, labelMax, IM_COL32(255, 0, 255, 255));

		ImGui::PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x -= frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x -= frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x -= frameHeight * 0.5f;
#else
		ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x -= frameHeight * 0.5f;
#endif
		ImGui::GetCurrentWindow()->Size.x -= frameHeight;

		auto itemWidth = ImGui::CalcItemWidth();
		ImGui::PushItemWidth(ImMax(0.0f, itemWidth - frameHeight));

		s_GroupPanelLabelStack.push_back(ImRect(labelMin, labelMax));
	}

	void EndGroupPanel()
	{
		ImGui::PopItemWidth();

		auto itemSpacing = ImGui::GetStyle().ItemSpacing;

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

		auto frameHeight = ImGui::GetFrameHeight();

		ImGui::EndGroup();

		//ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(0, 255, 0, 64), 4.0f);

		ImGui::EndGroup();

		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Dummy(ImVec2(frameHeight * 0.5f, 0.0f));
		ImGui::Dummy(ImVec2(0.0, frameHeight - frameHeight * 0.5f - itemSpacing.y));

		ImGui::EndGroup();

		auto itemMin = ImGui::GetItemRectMin();
		auto itemMax = ImGui::GetItemRectMax();
		//ImGui::GetWindowDrawList()->AddRectFilled(itemMin, itemMax, IM_COL32(255, 0, 0, 64), 4.0f);

		auto labelRect = s_GroupPanelLabelStack.back();
		s_GroupPanelLabelStack.pop_back();

		ImVec2 halfFrame = ImVec2(frameHeight * 0.25f, frameHeight) * 0.5f;
		ImRect frameRect = ImRect(itemMin + halfFrame, itemMax - ImVec2(halfFrame.x, 0.0f));
		labelRect.Min.x -= itemSpacing.x;
		labelRect.Max.x += itemSpacing.x;
		for (int i = 0; i < 4; ++i)
		{
			switch (i)
			{
				// left half-plane
			case 0: ImGui::PushClipRect(ImVec2(-FLT_MAX, -FLT_MAX), ImVec2(labelRect.Min.x, FLT_MAX), true); break;
				// right half-plane
			case 1: ImGui::PushClipRect(ImVec2(labelRect.Max.x, -FLT_MAX), ImVec2(FLT_MAX, FLT_MAX), true); break;
				// top
			case 2: ImGui::PushClipRect(ImVec2(labelRect.Min.x, -FLT_MAX), ImVec2(labelRect.Max.x, labelRect.Min.y), true); break;
				// bottom
			case 3: ImGui::PushClipRect(ImVec2(labelRect.Min.x, labelRect.Max.y), ImVec2(labelRect.Max.x, FLT_MAX), true); break;
			}

			ImGui::GetWindowDrawList()->AddRect(
				frameRect.Min, frameRect.Max,
				ImColor(ImGui::GetStyleColorVec4(ImGuiCol_Border)),
				halfFrame.x);

			ImGui::PopClipRect();
		}

		ImGui::PopStyleVar(2);

#if IMGUI_VERSION_NUM >= 17301
		ImGui::GetCurrentWindow()->ContentRegionRect.Max.x += frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->WorkRect.Max.x += frameHeight * 0.5f;
		ImGui::GetCurrentWindow()->InnerRect.Max.x += frameHeight * 0.5f;
#else
		ImGui::GetCurrentWindow()->ContentsRegionRect.Max.x += frameHeight * 0.5f;
#endif
		ImGui::GetCurrentWindow()->Size.x += frameHeight;

		ImGui::Dummy(ImVec2(0.0f, 0.0f));

		ImGui::EndGroup();
	}

	static void HelpMarker(const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
		{
			ImGui::BeginTooltip();
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}

	static void HelpMarker(void* image, int width, int height, const char* desc)
	{
		ImGui::TextDisabled("(?)");
		if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayShort))
		{
			ImGui::BeginTooltip();
			ImGui::Image(ImTextureID(image), ImVec2(width, height));
			ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
			ImGui::TextUnformatted(desc);
			ImGui::PopTextWrapPos();
			ImGui::EndTooltip();
		}
	}


	// Main code loop
	int UILoop()
	{
		//printf("uiloop in\n");
		// Our state
		bool show_demo_window = false;
		bool show_tool_window = false;
		bool show_obj_window = false;

		bool enable_edit = false;
		bool camera_base = false;


		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);



		// Main loop
		bool done = false;
		//while (!done)
		{
			
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			ImGuiContext& g = *GImGui;


			ImGui::SetNextWindowPos({ 50, 50 }, ImGuiCond_Once);
			ImGui::SetNextWindowSize({ 550, 550 }, ImGuiCond_Once);



			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
			ImGui::RenderNotifications();
			ImGui::PopStyleVar(1); // Don't forget to Pop()
			ImGui::PopStyleColor(1);

			
			


			bool isCamStopped = Settings::Local->stopLiveCam;
			//wprintf();
			if (wcsncmp(Global::currSceneName->chars, L"Live", Global::currSceneName->length) == 0) {
				int width = 0, height = 0;
				float currentFps = ImGui::GetIO().Framerate;
				static float t = 0;
				t += ImGui::GetIO().DeltaTime;
				RECT rect;
				if (GetWindowRect(Global::currenthWnd, &rect))
				{
					width = rect.right - rect.left;
					height = rect.bottom - rect.top;
				}

				if (Settings::Global->isShowLivePerfInfo) {
					ImGui::Begin("Status Bar", NULL,
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_AlwaysAutoResize);




					fpsValues.AddPoint(t, currentFps);




					//glfwGetWindowSize(window, &width, &height);
					ImGui::SetWindowPos(ImVec2(0, 0));
					ImGui::SetWindowSize(ImVec2(static_cast<float>(width), 0));


					ImGui::Text("%02d:%02d / %02d:%02d | Current: %.3f sec |", static_cast<int>(Global::liveTimeSec) / 60, static_cast<int>(Global::liveTimeSec) % 60,
						static_cast<int>(Global::liveTotalTimeSec) / 60, static_cast<int>(Global::liveTotalTimeSec) % 60, Global::liveTimeSec);
					ImGui::SameLine();

					//ImGui::SameLine(width - 150); // Adjust this value accordingly
					ImGui::Text("출력: %s (%d hz) | 게임: %dx%d %.1f fps | 제한: %d fps | 카메라 %s | 타임라인 %s",
						"",//GPUName,
						0,//getCurrentDisplayHz(),
						width, height, currentFps, Settings::Global->maxFps, Settings::Local->stopLiveCam ? "수동" : "자동", Settings::Local->isLiveTimeManual ? "수동" : "자동");

					ImGui::End();
				}



				//Fps graph

				if (Settings::Global->isShowLiveFPSGraph) {
					ImGui::SetNextWindowPos(ImVec2(width - 600, 0), ImGuiCond_Always); // 오른쪽 상단에 위치
					ImGui::SetNextWindowSize(ImVec2(600, 300), ImGuiCond_Always);      // 윈도우 크기 설정



					if (ImGui::Begin("FPS Graph", NULL,
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoResize))
					{
						if (ImPlot::BeginPlot("Frame per second")) {
							//ImPlot::SetupAxes(NULL, NULL, flags, flags);
							ImPlot::SetupAxisLimits(ImAxis_X1, t - 10.0f, t, ImGuiCond_Always);
							ImPlot::SetupAxisLimits(ImAxis_Y1, 0.0, 240.0);
							ImPlot::SetNextFillStyle(IMPLOT_AUTO_COL, 0.5f);
							ImPlot::PlotLine("FPS", &fpsValues.Data[0].x, &fpsValues.Data[0].y, fpsValues.Data.size(), 0, fpsValues.Offset, 2 * sizeof(float));
							//ImPlot::PlotLine("My Line Plot", x_data, y_data, fpsValues.size());
							ImPlot::EndPlot();
						}

						ImGui::End();
					}
				}

				//Seek bar test
				{

					// 현재 디스플레이의 크기 얻기
					ImVec2 displaySize = ImGui::GetIO().DisplaySize;

					// Seek Bar 창의 크기 정의
					ImVec2 windowSize(displaySize.x - 350, 90);
					ImVec2 windowPos(displaySize.x * 0.5f - windowSize.x * 0.5f, displaySize.y - windowSize.y);

					ImGui::SetNextWindowPos(windowPos);
					ImGui::SetNextWindowSize(windowSize);

					static bool isHovered = false;

					if (isHovered) {
						ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1);
						Global::isShowingSeekbar = true;
					}
					else {
						ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.0001);
						Global::isShowingSeekbar = false;
					}


					//static int

					if (ImGui::Begin("Seek Bar", NULL, ImGuiWindowFlags_NoTitleBar
						| ImGuiWindowFlags_NoResize
						| ImGuiWindowFlags_NoMove
						| ImGuiWindowFlags_AlwaysAutoResize))
					{

						isHovered = ImGui::IsWindowHovered() || ImGui::IsWindowFocused();


						// Seek bar 그리기
						ImGui::Text("%02d:%02d", static_cast<int>(Global::liveTimeSec) / 60, static_cast<int>(Global::liveTimeSec) % 60);
						ImGui::SameLine();
						ImGui::PushItemWidth(-60);
						if (ImGui::SliderFloat("##seekbar", &Global::liveTimeSec, 0.0f, Global::liveTotalTimeSec, "%.5f"))
						{
							Settings::Local->isLiveTimeManual = true;
						}
						//ImGui::PopItemWidth();
						ImGui::SameLine();
						ImGui::Text("%02d:%02d", static_cast<int>(Global::liveTotalTimeSec) / 60, static_cast<int>(Global::liveTotalTimeSec) % 60);

						if (ImGui::Button(Settings::Local->isLiveTimeManual ? "▶" : "||", ImVec2(40, 40))) {
							Settings::Local->isLiveTimeManual = !Settings::Local->isLiveTimeManual;
						}
						ImGui::SameLine();
						if (ImGui::Button("|◀"))
						{
							Global::liveTimeSec = 0.0f;
						}
						ImGui::SameLine();
						ImGui::Button("■");
						ImGui::SameLine();
						if (ImGui::Button("▶|"))
						{
							Global::liveTimeSec = Global::liveTotalTimeSec;
						}




						ImGui::PopStyleVar(1);
						// 창 종료
						ImGui::End();
					}




				}



			}
			else
			{
				Global::isShowingSeekbar = false;
			}

			if (wcsncmp(Global::currSceneName->chars, L"Race", Global::currSceneName->length) == 0) 
			{
				int width = 0, height = 0;
				float currentFps = ImGui::GetIO().Framerate;
				static float t = 0;
				t += ImGui::GetIO().DeltaTime;
				RECT rect;
				if (GetWindowRect(Global::currenthWnd, &rect))
				{
					width = rect.right - rect.left;
					height = rect.bottom - rect.top;
				}

					ImGui::Begin("Horse Meter", NULL,
						ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoResize |
						ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoScrollbar |
						ImGuiWindowFlags_NoSavedSettings |
						ImGuiWindowFlags_AlwaysAutoResize);




					fpsValues.AddPoint(t, currentFps);




					//glfwGetWindowSize(window, &width, &height);
					ImGui::SetWindowPos(ImVec2(0, 0));
					ImGui::SetWindowSize(ImVec2(static_cast<float>(width), 0));


					std::string horseName = "";
					int horseIndex = 0;

					if (Global::playerHorseData) 
					{
						void* raceView = il2cpp_class_get_method_from_name_type<void* (*)(
							Il2CppObject * _this
							)>(Global::raceManager->klass, "get_RaceView", 0)->methodPointer(Global::raceManager);

						if (raceView)
						{
							horseIndex = Global::playerHorseData->horseIndex;
							horseName = Utils::ConvertWstringToUTF8(Global::playerHorseData->charaName->chars);
						}
					}
					

					static float maxSpeed = 0;

					ImGui::Text("[%d] %s | %.2f km/h | Max %.2f km/h\n", horseIndex + 1, horseName.c_str(), Global::raceHorseSpeed, maxSpeed);
					ImGui::SameLine();

					ImGui::End();
					if (maxSpeed < Global::raceHorseSpeed)
					{
						maxSpeed = Global::raceHorseSpeed;
					}
					else if (Global::raceHorseSpeed < 1)
					{
						maxSpeed = 0;
					}
			}

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
			if (Global::imgui_settingwnd_open)
			{
				static float f = 0.0f;
				static int counter = 0;


				ImGui::Begin("설정 메뉴 (토글 키: F12)", &Global::imgui_settingwnd_open);



				//ImGui::SetNextWindowPos();
				ImGui::Text("Host: %s", Settings::Global->customHost);

				if (ImGui::CollapsingHeader("게임 시스템", ImGuiTreeNodeFlags_DefaultOpen)) {

					BeginGroupPanel("그래픽");
					if (ImGui::Checkbox("수직 동기", &Settings::Global->enableVSync)) {
						if (Settings::Global->enableVSync) {
							Settings::Local->vsync_count = 1;
						}
						else {
							Settings::Local->vsync_count = 0;
						}
					} ImGui::SameLine(); HelpMarker("수직 동기화를 적용합니다.");
					ImGui::Checkbox("자동 fps 설정", &Settings::Global->autoFpsSet); ImGui::SameLine(); HelpMarker("모니터 Hz 수에 맞춰서 fps를 자동 설정합니다.");
					ImGui::SliderInt("FPS 제한", &Settings::Global->maxFps, 0, 240); ImGui::SameLine(); HelpMarker("제한할 fps를 설정합니다. \"자동 fps 설정\" 이 비활성화 된 경우에만 작동합니다.\n(0인 경우 제한없음)");
					if (ImGui::Button("적용")) {
						UnityEngine::Application::set_targetFrameRate_hook(Settings::Global->maxFps);
					} ImGui::SameLine(); HelpMarker("fps 제한을 적용합니다.");

					ImGui::Checkbox("강제 가로모드", &Settings::Global->forceLandscape); ImGui::SameLine(); HelpMarker("게임을 가로 모드로 고정합니다.\n변경 내용은 게임 리셋 시 적용됩니다.");
					ImGui::Checkbox("자동 전체화면", &Settings::Global->autoFullscreen); ImGui::SameLine(); HelpMarker("가로모드 시 자동으로 전체화면이 됩니다.");
					if (ImGui::Checkbox("고품질 그래픽", &Settings::Global->highQuality)) {
						if (Settings::Global->highQuality) {
							Settings::Local->graphics_quality = 3;
							Settings::Local->antialiasing = 8;
							//int screenWidth = GetSystemMetrics(SM_CXSCREEN);
							//int screenHeight = GetSystemMetrics(SM_CYSCREEN);
						}
						else {
							Settings::Local->graphics_quality = -1;
							Settings::Local->antialiasing = -1;
						}
					} ImGui::SameLine(); HelpMarker("안티 에일리어싱, MSAA 허용 등 전반적인 3D 그래픽 품질을 높입니다.\n변경 내용은 게임 리셋 시 적용됩니다.");
					ImGui::SliderFloat("UI 배율", &Settings::Global->uiScale, 0.1, 10.0, "%.1f"); ImGui::SameLine(); HelpMarker("GUI의 배율을 설정합니다.\n변경 내용은 게임 리셋 시 적용됩니다.");
					ImGui::SliderFloat("3D 해상도 배율", &Settings::Global->virtualResolutionMultiple, 0.1, 10.0, "%.1f"); ImGui::SameLine(); HelpMarker("3D 렌더링 해상도의 배율을 설정합니다.\n1080P 해상도에서 앨리어싱 문제를 크게 줄일 수 있습니다.\n일부 2D 이미지의 배경이 너무 작아질 수 있습니다.\n권장 값: 4k 미만: 2.0; 4K 이상: 1.5. 기본값:1.0.");
					//if (ImGui::Button("Test"))
					//	set_antialiasing_hook(8);

					EndGroupPanel();

					BeginGroupPanel("배속");
					float timescale = UnityEngine::CoreModule::get_TimeScale();
					if (ImGui::SliderFloat("게임 배속", &timescale, 0.0, 10.0, "%.4f")) {
						UnityEngine::CoreModule::set_TimeScale(timescale);
					}ImGui::SameLine(); HelpMarker("게임의 배속을 설정합니다.\n단축키: LCtrl+PGUP, LCtrl+PGDN");
					if (ImGui::Button("정지"))
						UnityEngine::CoreModule::set_TimeScale(0.0);
					ImGui::SameLine();
					HelpMarker("배속을 0.0으로 설정합니다.\n단축키: LCtrl+P");
					ImGui::SameLine();
					if (ImGui::Button("초기화"))
						UnityEngine::CoreModule::set_TimeScale(1.0);
					ImGui::SameLine(); HelpMarker("배속을 기본값인 1.0으로 설정합니다.\n단축키: LCtrl+END");
					EndGroupPanel();


					BeginGroupPanel("시스템");
					ImGui::Checkbox("강제 리셋 허용", &Settings::Global->gotoTitleOnError); ImGui::SameLine(); HelpMarker("게임 내에서 강제적으로 타이틀 화면으로 돌아가는 동작을 허용합니다.");
					if (ImGui::Checkbox("클릭 이펙트 켜기", &Settings::Global->isTapEffectEnabled))
					{
						if (Settings::Global->isTapEffectEnabled) {
							UnityEngine::CoreModule::GameObject_SetActive("Gallop.GameSystem/SystemManagerRoot/SystemSingleton/UIManager/SystemCanvas/TapEffectCanvas", true);

							printf("tapeffect on\n");
						}
						else {
							UnityEngine::CoreModule::GameObject_SetActive("Gallop.GameSystem/SystemManagerRoot/SystemSingleton/UIManager/SystemCanvas/TapEffectCanvas", false);
							printf("tapeffect off\n");
						}

					}
					EndGroupPanel();



				}
				if (ImGui::CollapsingHeader("캐릭터", ImGuiTreeNodeFlags_DefaultOpen)) {
					ImGui::Checkbox("스토리용 3D 모델 강제 변경 활성화", &Settings::Local->changeStoryChar);
					
				}

				if (ImGui::CollapsingHeader("레이스", ImGuiTreeNodeFlags_DefaultOpen)) {
					ImGui::SliderFloat("등수 표시기 출력 위치", &Settings::Global->rankUIShowMeter, 0.0, 3000.0, "%.2f M"); ImGui::SameLine(); HelpMarker("레이스 시작 후 등수 표시기를 출력할 위치를 정합니다.\n(LCtrl+슬라이더 클릭으로 직접 입력 가능)");
					ImGui::SliderFloat("등수 표시기 숨김 위치", &Settings::Global->rankUIHideoffset, 0.0, 9999.0, "%.2f"); ImGui::SameLine(); HelpMarker("등수 표시기를 숨길 타이밍을 지정합니다.\n(LCtrl+슬라이더 클릭으로 직접 입력 가능)");
					ImGui::Checkbox("착순 마크 표시", &Global::showFinishOrderFlash); ImGui::SameLine(); HelpMarker("레이스 결과 화면에서 착순 애니메이션을 표시합니다.");
					
					BeginGroupPanel("캐릭터 모션 고정");

					static char numberStr[7] = "";


					// InputText for 6-character integer value
					if (ImGui::InputText("CardID", numberStr, sizeof(numberStr), ImGuiInputTextFlags_CharsDecimal)) {
						// Optional: Validate and convert the input to an integer
						int number;
						bool inputError = false;
						try {
							// Validate and convert the input to an integer
							number = std::stoi(numberStr);
							Settings::Local->cardid = number;
							inputError = false;
						}
						catch (const std::invalid_argument&) {
							// Handle invalid input (non-numeric characters)
							inputError = true;
							std::cerr << "Invalid input: not a number" << std::endl;
						}
						catch (const std::out_of_range&) {
							// Handle out-of-range input
							inputError = true;
							std::cerr << "Invalid input: out of range" << std::endl;
						}

						
						
					}
					// InputText for 6-character integer value
					if (ImGui::InputText("GradeNum", numberStr, sizeof(numberStr), ImGuiInputTextFlags_CharsDecimal)) {
						// Optional: Validate and convert the input to an integer
						int number;
						bool inputError = false;
						try {
							// Validate and convert the input to an integer
							number = std::stoi(numberStr);
							Settings::Local->raceResultCutinMotionGrade = number;
							inputError = false;
						}
						catch (const std::invalid_argument&) {
							// Handle invalid input (non-numeric characters)
							inputError = true;
							std::cerr << "Invalid input: not a number" << std::endl;
						}
						catch (const std::out_of_range&) {
							// Handle out-of-range input
							inputError = true;
							std::cerr << "Invalid input: out of range" << std::endl;
						}



					}
					static ImGuiTextFilter filter;
					ImGui::Text("Search:");
					filter.Draw("##searchbar", 340.f);
					ImGui::BeginChild("listbox child", ImVec2(340, 400));
					for (int i = 0; i < Global::MasterCharaData.size(); i++) {
						//auto charObj = Global::MasterCharaData->get_Values()[i];
						//auto name = il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject * _this)>(charObj->klass, "get_Name", 0)->methodPointer(charObj);
						auto nameC = Utils::ConvertWstringToUTF8(Global::MasterCharaData[i]->Name->chars);
						//std::wcout << Global::MasterCharaData[i]->Name->chars;
						//std::cout << "\n";
						if (filter.PassFilter((std::to_string(i) + nameC).c_str())) {
							std::string label = nameC + "##" + std::to_string(i); //do this or you will have problems selecting elements with the same name
							ImGui::Selectable(label.c_str());
							//if (ImGui::Selectable(label.c_str()))
								//Menu::Config.skins[selector] = i; //used for skinchanger, ignore
						}

					}

					ImGui::EndChild();

					EndGroupPanel();
				}

				if (ImGui::CollapsingHeader("라이브", ImGuiTreeNodeFlags_DefaultOpen)) {
					ImGui::Checkbox("라이브 카메라 멈추기", &Settings::Local->stopLiveCam); ImGui::SameLine(); HelpMarker("라이브에서 카메라 워크를 정지합니다.\n단축키: S");
					ImGui::Checkbox("라이브 제목 창 출력", &Settings::Global->showLiveTitleWindow); ImGui::SameLine(); HelpMarker("라이브 시작 시 제목 창을 표시합니다.");
					ImGui::Checkbox("강제 세로모드 해제", &Settings::Global->ignoreLiveForcePortrait); ImGui::SameLine(); HelpMarker("세로 모드 고정 라이브를 강제로 가로모드로 전환합니다.");
					ImGui::Checkbox("모든 의상 강제 활성화", &Settings::Global->enableForceAllLiveDressUse); ImGui::SameLine(); HelpMarker("모든 의상을 선택할 수 있게 합니다. (서버 지원 필요)");
					BeginGroupPanel("타임라인");

					//int minutes = static_cast<int>(liveTimeSec / 60); // 분 계산
					//int remainingSeconds = static_cast<int>(seconds) % 60; // 초 계산

					//printf("%02d:%02d", minutes, remainingSeconds);

					ImGui::Text("%02d:%02d / %02d:%02d", static_cast<int>(Global::liveTimeSec) / 60, static_cast<int>(Global::liveTimeSec) % 60,
						static_cast<int>(Global::liveTotalTimeSec) / 60, static_cast<int>(Global::liveTotalTimeSec) % 60);

					if (ImGui::SliderFloat("시간 조정", &Global::liveTimeSec, 0.0, Global::liveTotalTimeSec, "%.3f Sec")) {
						Settings::Local->isLiveTimeManual = true;
					}ImGui::SameLine(); HelpMarker("라이브 타임라인을 설정합니다.\n단축키: Ctrl+LeftArrow, Ctrl+RightArrow");

					ImGui::PushMultiItemsWidths(1, ImGui::CalcItemWidth());
					ImGui::Indent(5.0f);
					ImGui::PushID(0);
					if (ImGui::Button("+")) {
						Settings::Local->isLiveTimeManual = true;
						Global::liveTimeSec = Global::liveTimeSec + Global::liveTimelineManualScale;
					}ImGui::SameLine(0, g.Style.ItemInnerSpacing.x);
					if (ImGui::InputScalar("##scale", ImGuiDataType_Float, &Global::liveTimelineManualScale, NULL, NULL, "%.3f")) {}; ImGui::SameLine();
					if (ImGui::Button("-")) {
						Settings::Local->isLiveTimeManual = true;
						Global::liveTimeSec = Global::liveTimeSec - Global::liveTimelineManualScale;
					}ImGui::SameLine();
					ImGui::PopID();
					ImGui::PopItemWidth();
					if (ImGui::Checkbox("수동 조정", &Settings::Local->isLiveTimeManual)) {
						//ImGui::InsertNotification({ ImGuiToastType_Success, 3000, "Hello World! This is a success! %s", "수동 조정이 활성화되었습니다." });
						//showAlertMessage(5.0, "수동 조정이 활성화되었습니다.");
					} ImGui::SameLine(); HelpMarker("타임라인 수동 조정을 활성화합니다.");
					ImGui::SliderInt("타겟 타임라인 갱신 fps 설정", &Global::liveTimeLineFPS, 0, Settings::Global->maxFps);
					
					EndGroupPanel();
					//ImGui::Checkbox("isCameraShake", &IsCamShake);

				}

				if (ImGui::CollapsingHeader("???", ImGuiTreeNodeFlags_DefaultOpen)) {
					//수고하셨습니다. 기무라 유이토씨.
					//ImGui::Checkbox("키무라 챌린지", &Global::isKimuraChallenge); ImGui::SameLine(); HelpMarker(texture_kimura, kimura_image_width, kimura_image_height, "\"야떼미로-\"");
					ImGui::Checkbox("Urara", &Settings::Global->walkMotionAllUrara); ImGui::SameLine(); HelpMarker("홈화면 캐릭터들의 도보 모션을 전부 우라라 전용 모션으로 설정합니다.");
					ImGui::Checkbox("◆", &Settings::Global->homeAllDiamond); ImGui::SameLine(); HelpMarker("Just Diamond.");
					ImGui::Checkbox("Win.564", &Settings::Global->winMotion564); ImGui::SameLine(); HelpMarker("1착 모션이 캐릭터에 관계없이 전부 골드쉽 모션으로 바뀝니다.\n어이어이, 헛소리 하지 마! 이번에야말로 고루시짱의 시대잖냐아아앗!");
					//int id = 1001;
					//if (ImGui::InputInt("GetCharaNameByCharaId", &id, 1, 9999)) {
					//	//_setmode(_fileno(stdout), _O_U16TEXT); // <=== Windows madness
					//
					//	 Il2CppString_unk* ret = (Il2CppString_unk*)GetCharaNameByCharaId(id);
					//	 std::cout << UmaGetString(ret)  << std::endl;
					//	//ImGui::SameLine();
					//	ImGui::Text("%s",  UmaGetString(ret));
					//}
				}
				if (ImGui::CollapsingHeader("디버그 정보")) {
					if (ImGui::TreeNode("Hooked List")) {
						ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;
						ImGui::BeginChild("ChildL", ImVec2(ImGui::GetContentRegionAvail().x, 360), false, window_flags);


						//for_each(hooked_addr.begin(), hooked_addr.end(), [&](hookStr& item) {
						//	ImGui::Text("[%s]", item.assemblyName);
						//	ImGui::SameLine();
						//	ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s.", item.namespaceName);
						//	ImGui::SameLine();
						//	ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.5f, 1.0f), "%s.", item.className);
						//	ImGui::SameLine();
						//	ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "%s(%d)", item.methodName, item.argsCount);
						//	ImGui::SameLine();
						//	ImGui::Text(" = 0x%p ", item.addr);
						//	});
						ImGui::EndChild();
						ImGui::TreePop();
					}




					//if (masterDBconnection != nullptr) {
					//	//std::wstring path = masterDBconnection->dbPath->start_char;
					//	ImGui::Text("MasterDBConnection ptr: 0x%p", masterDBconnection->Handle);
					//	//ImGui::Text("MasterDBPath: %s", path);
					//}
					else {
						ImGui::Text("MasterDBConnection ptr: nullptr");
						//ImGui::Text("MasterDBPath: nullptr");
					}
					//if (ImGui::Button("SQLTest")) {
					//	Il2CppObject* dbQuery = il2cpp_object_new((Il2CppClass*)il2cpp_symbols::get_class("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query"));
					//	auto query = reinterpret_cast<void (*)(Il2CppObject * _instance, Connection * conn, Il2CppString * querystr)>(il2cpp_symbols::get_method_pointer("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query", "_Setup", 2));
					//	auto query_exec = reinterpret_cast<bool (*)(Il2CppObject * _instance)>(il2cpp_symbols::get_method_pointer("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query", "Exec", 0));
					//	printf("query_exec ok\n");
					//	//auto query_GetText = reinterpret_cast<Il2CppString * (*)(Il2CppObject * _instance, int idx)>(il2cpp_symbols::get_method_pointer("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query", "GetText", 1));
					//	query(dbQuery, masterDBconnection, il2cpp_string_new("update text_data set `text`=\"EditTest\" where id=6 and category=6 and `index`=1001;"));
					//	bool r = query_exec(dbQuery);
					//	//printf("Excuting %s\n", );
					//	printf("Exec = %d\n", r);
					//	//Il2CppString* q_res = query_GetText(dbQuery, 2);
					//	//wprintf(L"GetText = %s\n", q_res->start_char);
					//}
					//ImGui::Text("Livecam1 x=% 04.3f, y=% 04.3f, z=% 04.3f", liveCam_pos1.x, liveCam_pos1.y, liveCam_pos1.z);

					//if (liveCam_Lookat != NULL) {
					//	ImGui::Text("liveCam_Lookat x=% 04.3f, y=% 04.3f, z=% 04.3f", liveCam_Lookat.x, liveCam_Lookat.y, liveCam_Lookat.z);
					//	//printf("liveCam_Lookat x=% 04.3f, y=% 04.3f, z=% 04.3f\n", liveCam_Lookat->x, liveCam_Lookat->y, liveCam_Lookat->z);
					//}
					//else {
					//	ImGui::Text("liveCam_Lookat is nullptr");
					//}
					//if (liveCam_pos1 != NULL) {
					//	ImGui::Text("Livecam1 x=% 04.3f, y=% 04.3f, z=% 04.3f", liveCam_pos1.x, liveCam_pos1.y, liveCam_pos1.z);
					//}
					//else {
					//	ImGui::Text("Livecam1 is nullptr");
					//}
					//if (liveCam_pos2 != NULL) {
					//	ImGui::Text("Livecam2 x=% 04.3f, y=% 04.3f, z=% 04.3f", liveCam_pos2.x, liveCam_pos2.y, liveCam_pos2.z);
					//}
					//else {
					//	ImGui::Text("Livecam2 is nullptr");
					//}



				}






				ImGui::Separator();

				ImGui::Checkbox("콘솔 커멘드 입력 활성화", &Settings::Local->isCanInputCommands);

				if (ImGui::Button("타이틀로 돌아가기 (게임 리셋)")) {
					UnityEngine::CoreModule::ResetGame();
				} ImGui::SameLine(); HelpMarker("단축키: LCtrl+R");

				if (ImGui::Button("게임 종료"))
					ImGui::OpenPopup("확인");


				bool open = true;
				if (ImGui::BeginPopupModal("확인", &open))
				{
					ImGui::Text("정말 게임을 종료할까요?");
					if (ImGui::Button("아니오"))
						ImGui::CloseCurrentPopup();
					ImGui::SameLine();
					if (ImGui::Button("예")) {
						exit(0);
					}

					ImGui::EndPopup();
				}
				//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color



				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();


				// Render toasts on top of everything, at the end of your code!
				// You should push style vars here


			}

			/*if (true) {
				ImGuiTreeNodeFlags a = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
			}*/
			
			ImGui::Render();
			//const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
			pContext->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
			//pContext->ClearRenderTargetView(mainRenderTargetView, clear_color_with_alpha);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


		}


		
		
		return 0;
	}
}

