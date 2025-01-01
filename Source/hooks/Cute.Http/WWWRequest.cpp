#include "WWWRequest.h"
using namespace std;

namespace Cute::Http::WWWRequest {
	Url LastUrl;
	Url CurrentUrl;

	void* Post_orig = nullptr;
	void Post_hook(void* _this, Il2CppString* url, char* postdata, void* headers) {
		Logger::Debug(SECTION_NAME, L"Original URL: %s", url->chars);
		wstring url_raw = wstring(url->chars);
		string url_conv;
		url_conv.assign(url_raw.begin(), url_raw.end());
		Url posturl(url_conv);
		CurrentUrl = posturl;
		if (strlen(Settings::Global->customHost) > 0) {
			Url replaceUrl(Settings::Global->customHost);
			posturl.scheme(replaceUrl.scheme());
			posturl.host(replaceUrl.host());
			posturl.port(replaceUrl.port());
			Logger::Debug(SECTION_NAME, L"Replaced URL: %s", posturl.str().c_str()); //change this log to Logger::Debug

		}

		return reinterpret_cast<decltype(Post_hook)*>
			(Post_orig)(_this, il2cpp_string_new(posturl.str().c_str()), postdata, headers);

	}


	void Init() {
		Logger::Info(SECTION_NAME, L"Init");
		auto Post_addr = il2cpp_symbols::get_method_pointer(
			"Cute.Http.Assembly.dll", "Cute.Http",
			"WWWRequest", "Post", 3
		);
		if (Post_addr == nullptr) {
			Logger::Error(SECTION_NAME, L"Post_addr is nullptr");
			return;
		}
		else {
			Logger::Info(SECTION_NAME, L"Post_addr=%p", Post_addr);
			MH_CreateHook(Post_addr, &Post_hook, &Post_orig);
			MH_EnableHook(Post_addr);
		}
	}
}