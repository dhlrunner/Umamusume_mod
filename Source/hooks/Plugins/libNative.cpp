#include "libNative.h"

using namespace std;
using namespace Cute::Http::WWWRequest;

namespace libnative {


	void* LZ4_decompress_safe_ext_orig = nullptr;
	HWND currenthWnd = NULL;

	int LZ4_decompress_safe_ext_hook(
		char* src,
		char* dst,
		int compressedSize,
		int dstCapacity)
	{
		LastUrl = CurrentUrl;
		//printf("compressedSize=%d,dstCapacity=%d", compressedSize, dstCapacity);
		char* decrypted = NULL;
		//server_ip;
		int ret = 0;

		wchar_t buf[256];
		Logger::Info(L"LIBNATIVE", L"CurrentURL=%S", CurrentUrl.path().c_str());
		swprintf_s(buf, L"umamusume_L [%s %d]", wstring(CurrentUrl.path().begin(), CurrentUrl.path().end()).c_str(), compressedSize);
		SetWindowText(currenthWnd, buf);


		if (Settings::Global->lz4Encrypt) {
			decrypted = new char[dstCapacity];
			ret = reinterpret_cast<decltype(LZ4_decompress_safe_ext_hook)*>(LZ4_decompress_safe_ext_orig)(
				src, decrypted, compressedSize, dstCapacity);
		}
		else {
			char* realLZ4buff = new char[compressedSize - (int)4];
			decrypted = new char[dstCapacity];
			memcpy(realLZ4buff, src + 4, compressedSize - (int)4);

			ret = LZ4_decompress_safe(realLZ4buff, decrypted, compressedSize - (int)4, dstCapacity);
			Logger::Debug(L"LIBNATIVE", L"compressedSize: %d, dstCapacity:%d", compressedSize, dstCapacity);
			delete[] realLZ4buff;
		}

		Logger::Debug(L"LIBNATIVE", L"Server Response: %d Bytes", ret);
		if (Settings::Global->passPacket) {
			//printf("------Real Cygames server -> modding server(local) -> Client------\n");
			httplib::Headers headers = {
				{ "Url", LastUrl.str() }
			};

			httplib::Client cli(Settings::Global->serverIP, Settings::Global->serverPort);
			std::string data(decrypted, ret);
			cli.set_connection_timeout(2);
			auto res = cli.Post("/umamusume_uploadmsgpack/live", headers, data, "application/x-msgpack");
			if (res) {
				res->status;
				const char* returned = res->body.c_str();
				size_t clength = res->body.length();
				Logger::Debug(L"LIBNATIVE", L"Original Server length: %d, modified length: %d", ret, clength);
				ret = res->body.length();

				Logger::Debug(L"LIBNATIVE", L"Status: %d Content-Length:%d", res->status, clength);

				memcpy(dst, returned, clength);//sss
			}
			else {
				Logger::Error(L"LIBNATIVE", L"Msgpack send error: Server timeout");
				memcpy(dst, decrypted, ret);
			}


			//delete[] returned;
			//free(src);
			//printf("-----------------------------------------------------------------\n");
		}
		else {
			memcpy(dst, decrypted, ret);
		}
		//rpc->set(decrypted, ret, currentUrl.str().c_str());
		//printf("%s\n", msgPackToJson(decrypted, ret));
		delete[] decrypted;
		//dst = {0};
		return ret;
	}
	void* LZ4_compress_default_ext_orig = nullptr;

	int LZ4_compress_default_ext_hook(
		char* src,
		char* dst,
		int srcSize,
		int dstCapacity)
	{

		//char* decrypted = new char[dstCapacity] {};
		char* raw_data = new char[srcSize] {};
		memcpy(raw_data, src, srcSize);

		/*auto dialogData = il2cpp_object_new(
			il2cpp_symbols::get_class("umamusume.dll", "Gallop", "DialogCommon/Data"));
		il2cpp_runtime_object_init(dialogData);

		dialogData =
			il2cpp_class_get_method_from_name_type<Il2CppObject * (*)(Il2CppObject * _this, uint64_t headerTextId, Il2CppString * message, Il2CppDelegate * onClickCenterButton, uint64_t closeTextId)>(dialogData->klass, "SetSimpleOneButtonMessage", 4)->methodPointer
			(dialogData, 2, il2cpp_string_new(to_string(srcSize).c_str()), il2cpp::CreateDelegateStatic(+[] { MessageBox(0, L"Clicked", L"TEST", MB_OK); }), 9);
		il2cpp_symbols::get_method_pointer<Il2CppObject* (*)(Il2CppObject* data, bool isEnableOutsideClick)>("umamusume.dll", "Gallop", "DialogManager", "PushSystemDialog", 2)(dialogData, true);
*/

		if (Settings::Global->passPacket) {
			httplib::Client cli(Settings::Global->serverIP, Settings::Global->serverPort);
			std::string data(raw_data, srcSize);
			//printf("------Client -> modding server(local) -> Real Cygames server------\n");
			httplib::Headers headers = {
				{ "Url", LastUrl.str() }
			};

			

			cli.set_connection_timeout(2);
			auto res = cli.Post("/umamusume_uploadmsgpack/uma_client_request_toserver", headers, data, "application/x-msgpack");
			size_t clength = 0;
			if (res) {
				res->status;
				const char* returned = res->body.c_str();
				clength = res->body.length();
				memcpy(src, returned, clength);
			}
			else {
				clength = srcSize;
				memcpy(src, raw_data, clength);
			}
			
			int ret = 0;
			if (Settings::Global->lz4Encrypt) {
				ret = reinterpret_cast<decltype(LZ4_compress_default_ext_hook)*>(LZ4_compress_default_ext_orig)(
					src, dst, clength, dstCapacity);
			}
			else {
				ret = LZ4_compress_default(src, dst, clength, dstCapacity);
			}
			Logger::Debug(L"LIBNATIVE", L"Raw Client data: %d Bytes , Modified Clinet Req data: %d bytes, (Finally Compressed/Encrypted to %d bytes)", srcSize, clength, ret);


			//printf("-------------------------------------------------------------------------\n");
			delete[] raw_data;

			return ret;
		}
		else {
			int ret = 0;
			if (Settings::Global->lz4Encrypt) {
				ret = reinterpret_cast<decltype(LZ4_compress_default_ext_hook)*>(LZ4_compress_default_ext_orig)(
					src, dst, srcSize, dstCapacity);
			}
			else {
				ret = LZ4_compress_default(src, dst, srcSize, dstCapacity);

			}

			Logger::Debug(L"LIBNATIVE",L"Raw Client data: %d Bytes (Compressed/Encrypted to %d bytes) -> ", srcSize, ret);


			delete[] raw_data;
			return ret;
		}


	}

	void Init(HWND currentHWND) {
		//창 타이틀 변경위함
		currenthWnd = currentHWND;

		auto libnative_module = GetModuleHandle(L"libnative.dll");
		Logger::Debug(L"LIBNATIVE", L"libnative.dll at %p", libnative_module);
		if (libnative_module == nullptr)
		{
			Logger::Error(L"LIBNATIVE", L"libnative.dll is nullptr");
			return;
		}
		auto LZ4_decompress_safe_ext_ptr = GetProcAddress(libnative_module, "LZ4_decompress_safe_ext");
		Logger::Debug(L"LIBNATIVE", L"LZ4_decompress_safe_ext at %p", LZ4_decompress_safe_ext_ptr);
		EnableHook(LZ4_decompress_safe_ext_ptr, &LZ4_decompress_safe_ext_hook, &LZ4_decompress_safe_ext_orig, L"LZ4_decompress_safe_ext");

		auto LZ4_compress_default_ext_ptr = GetProcAddress(libnative_module, "LZ4_compress_default_ext");
		Logger::Debug(L"LIBNATIVE", L"LZ4_compress_default_ext at %p", LZ4_compress_default_ext_ptr);
		EnableHook(LZ4_compress_default_ext_ptr, &LZ4_compress_default_ext_hook, &LZ4_compress_default_ext_orig, L"LZ4_compress_default_ext");
	}
}
