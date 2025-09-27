#include "LibNative.Sqlite3.h"

namespace LibNative::Sqlite3
{
	void* Open_orig = nullptr;
	bool Open_hook(Il2CppObject* _this, Il2CppString* fileName, Il2CppString* vfsName, Il2CppArraySize_t<char>* key, int cipherType) {
		Logger::Info(SECTION_NAME, L"Open_hook: fileName=%s, vfsName=%s, keyLen=%d, cipherType=%d",
			fileName ? fileName->chars : L"(null)",
			vfsName ? vfsName->chars : L"(null)",
			key ? key->max_length : -1,
			cipherType);

		//dump key
		if (key) {
			printf("byte[] ENCODE_KEY_ARRAY = { ");
			for (int i = 0; i < key->max_length; i++) {
				printf("%d,", key->vector[i]);
			}
			printf(" };\n");
		}
		return reinterpret_cast<decltype(Open_hook)*>(Open_orig)(_this, fileName, vfsName, key, cipherType);
		
	}

	void* OpenWritable_orig = nullptr;

	//public bool OpenWritable(string fileName, string journalMode = "MEMORY", string synchronouos = "1", string lockingMode = "EXCLUSIVE", bool enableSharedCache = false, byte[] key = null, Cipher.TYPE cipherType = Cipher.TYPE.CODEC_TYPE_CHACHA20)
	bool OpenWritable_hook(Il2CppObject* _this, Il2CppString* fileName, Il2CppString* journalMode, Il2CppString* synchronouos, Il2CppString* lockingMode, bool enableSharedCache, Il2CppArraySize_t<char>* key, int cipherType) {
		Logger::Info(SECTION_NAME, L"OpenWritable_hook: fileName=%s, journalMode=%s, synchronouos=%s, lockingMode=%s, enableSharedCache=%d, keyLen=%d, cipherType=%d",
			fileName ? fileName->chars : L"(null)",
			journalMode ? journalMode->chars : L"(null)",
			synchronouos ? synchronouos->chars : L"(null)",
			lockingMode ? lockingMode->chars : L"(null)",
			enableSharedCache,
			key ? key->max_length : -1,
			cipherType);
		
		//check db file header is plane db (SQLite format 3) or not
		static constexpr std::array<unsigned char, 16> kSqliteHeader = {
			'S','Q','L','i','t','e',' ','f','o','r','m','a','t',' ','3','\0'
		};
		std::ifstream ifs(fileName->chars, std::ios::binary);
		if (!ifs) return reinterpret_cast<decltype(OpenWritable_hook)*>(OpenWritable_orig)(_this, fileName, journalMode, synchronouos, lockingMode, enableSharedCache, key, cipherType);
		std::array<unsigned char, 16> header{};
		ifs.read(reinterpret_cast<char*>(header.data()), header.size());
		bool plainDb = (header == kSqliteHeader);

		if (plainDb) {
			Logger::Info(SECTION_NAME, L"Detected plain sqlite db file, skipping key");
			return reinterpret_cast<decltype(OpenWritable_hook)*>(OpenWritable_orig)(_this, fileName, journalMode, synchronouos, lockingMode, enableSharedCache, nullptr, cipherType);
		}
		Logger::Info(SECTION_NAME, L"Detected encrypted sqlite db. Decrypting....");
		bool ret = reinterpret_cast<decltype(OpenWritable_hook)*>(OpenWritable_orig)(_this, fileName, journalMode, synchronouos, lockingMode, enableSharedCache, key, cipherType);
		auto exec = il2cpp_class_get_method_from_name_type<bool(*)(Il2CppObject*, Il2CppString*)>(_this->klass, "Exec", 1);
		bool ret1 = exec->methodPointer(_this, il2cpp_string_new16(L"PRAGMA rekey = '';"));
		if (!ret1) {
			Logger::Error(SECTION_NAME, L"PRAGMA rekey failed");
		}	
		//dump key
		

		if (key) {
			printf("byte[] ENCODE_KEY_ARRAY = { ");
			for (int i = 0; i < key->max_length; i++) {
				printf("0x%2X,", key->vector[i]);
			}
			printf(" };\n");

			//try export to plain db
			//auto Query = (Il2CppObject* (*)(Il2CppObject* ,Il2CppString*))il2cpp_class_get_method_from_name_type<Il2CppObject* (*)(Il2CppObject*, Il2CppString*)>(_this->klass, "Query", 1)->methodPointer;
			//auto Step = (bool (*)(Il2CppObject*))il2cpp_class_get_method_from_name_type<bool (*)(Il2CppObject*)>(il2cpp_symbols::get_class("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query"), "Step", 0)->methodPointer;
			//auto GetText = (Il2CppString * (*)(Il2CppObject*, int))il2cpp_class_get_method_from_name_type<Il2CppString * (*)(Il2CppObject*, int)>(il2cpp_symbols::get_class("LibNative.Runtime.dll", "LibNative.Sqlite3", "Query"), "GetText", 1)->methodPointer;
			//
			//Il2CppObject* o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher failed");
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher result: %s", result->chars);
			//}
			//

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_list;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_list failed");
			//}
			//else{
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_list result: %s", result->chars);
			//}
			//

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_page_size;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_page_size failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_page_size result: %s", result->chars);
			//}
			//

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA kdf_iter;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA kdf_iter failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA kdf_iter result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA hmac_use;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA hmac_use failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA hmac_use result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA page_size;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA page_size failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA page_size result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_hmac_algorithm;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_hmac_algorithm failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_hmac_algorithm result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_kdf_algorithm;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_kdf_algorithm failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_kdf_algorithm result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_use_hmac;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_use_hmac failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_use_hmac result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_version;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_version failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_version result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA cipher_provider;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA cipher_provider failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA cipher_provider result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA plaintext_header_size;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA plaintext_header_size failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA plaintext_header_size result: %s", result->chars);
			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA legacy;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA legacy failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA legacy result: %s", result->chars);

			//}

			//o = Query(_this, il2cpp_string_new16(L"PRAGMA legacy_page_size;"));
			//if (!Step(o)) {
			//	Logger::Error(SECTION_NAME, L"PRAGMA legacy_page_size failed");
			//	//return ret;
			//}
			//else {
			//	Il2CppString* result = GetText(o, 0);
			//	Logger::Info(SECTION_NAME, L"PRAGMA legacy_page_size result: %s", result->chars);
			//}


			//auto exec = il2cpp_class_get_method_from_name_type<bool(*)(Il2CppObject*, Il2CppString*)>(_this->klass, "Exec", 1);
			//bool ret1 = exec->methodPointer(_this, il2cpp_string_new16(L"PRAGMA rekey = '';"));
			//bool ret2 = exec->methodPointer(_this, il2cpp_string_new16(L"SELECT sqlcipher_export('main','plain');"));
			//bool ret3 = exec->methodPointer(_this, il2cpp_string_new16(L"DETACH DATABASE plain;"));
			//Logger::Info(SECTION_NAME, L"Export plain db result: %d", ret1);
		}
		return ret;
	}

	

	void Init()
	{
		Logger::Info(SECTION_NAME, L"Init");
		auto sqlite3_open_addr = reinterpret_cast<bool(*)(Il2CppObject*, Il2CppString*, Il2CppString*, Il2CppArraySize_t<char>*, int)>(il2cpp_symbols::get_method_pointer(
			"LibNative.Runtime.dll", "LibNative.Sqlite3",
			"Connection", "Open", 4
		));
		EnableHook(sqlite3_open_addr, &Open_hook, &Open_orig, L"sqlite3_open");

		auto sqlite3_openwritable_addr = reinterpret_cast<bool(*)(Il2CppObject*, Il2CppString*, Il2CppString*, Il2CppString*, Il2CppString*, bool, Il2CppArraySize_t<char>*, int)>(il2cpp_symbols::get_method_pointer(
			"LibNative.Runtime.dll", "LibNative.Sqlite3",
			"Connection", "OpenWritable", 7
		));
		EnableHook(sqlite3_openwritable_addr, &OpenWritable_hook, &OpenWritable_orig, L"sqlite3_openwritable");
	}
}