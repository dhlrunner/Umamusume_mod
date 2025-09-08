#include "MasterLiveFixMemberData.h"

namespace Gallop::MasterLiveFixMemberData
{
	void* GetWithMusicId_orig = nullptr;
	LiveFixMemberData* GetWithMusicId_hook(Il2CppObject* _this, int musicId) {
		LiveFixMemberData* ret = reinterpret_cast<decltype(GetWithMusicId_hook)*>(GetWithMusicId_orig)(_this, musicId);
		Logger::Info(SECTION_NAME, L"GetWithMusicId_hook: musicId=%d ret=%p", musicId, ret);
		wprintf(L"=============================\n");
		//dump all members
		if (ret) {
			wprintf(L"Id=%d\n", ret->Id);
			wprintf(L"MusicId=%d\n", ret->MusicId);
			wprintf(L"Order=%d\n", ret->Order);
			wprintf(L"CharaId=%d\n", ret->CharaId);
			wprintf(L"DressId1=%d\n", ret->DressId1);
			wprintf(L"DressId2=%d\n", ret->DressId2);
			wprintf(L"DressColor1=%d\n", ret->DressColor1);
			wprintf(L"DressColor2=%d\n", ret->DressColor2);
		}


		if (ret == nullptr) {
			Logger::Warn(SECTION_NAME, L"GetWithMusicId_hook: not found musicId=%d", musicId);
			//return a dummy object to prevent crash
			//static LiveFixMemberData dummy(0, musicId, 0, 0, 0, 0, 0, 0);
			//return &dummy;
		}
		return ret;
		
	}

	void* GetListWithMusicId_orig = nullptr;
	void* GetListWithMusicId_hook(Il2CppObject* _this,  int musicId) {
		auto ret = reinterpret_cast<decltype(GetListWithMusicId_hook)*>(GetListWithMusicId_orig)(_this, musicId);
		
		auto list = reinterpret_cast<List_1_LiveFixMemberData*>(ret);
		auto size = list->fields._size;
		auto items = reinterpret_cast<Il2CppArraySize_t<LiveFixMemberData*>*>(list->fields._items);
		//if (!items) { wprintf(L"(items=null)\n"); return; }

		wprintf(L"=============================\n");
		wprintf(L"GetListWithMusicId_hook: count=%d\n", size);

		for (int i = 0; i < size; i++) {
			LiveFixMemberData* item = items->vector[i];
			if (!item) continue;

			// 필드가 진짜 존재하는지 모를 때는 il2cpp_field_get_value 사용 권장
			wprintf(L"--- Item %d ---\n", i);
			wprintf(L"Id=%d\n", item->Id);
			wprintf(L"MusicId=%d\n", item->MusicId);
			wprintf(L"Order=%d\n", item->Order);
			wprintf(L"CharaId=%d\n", item->CharaId);
			wprintf(L"DressId1=%d\n", item->DressId1);
			wprintf(L"DressId2=%d\n", item->DressId2);
			wprintf(L"DressColor1=%d\n", item->DressColor1);
			wprintf(L"DressColor2=%d\n", item->DressColor2);
		}

		if (size > 0) {
			//Create new vector for replace the list
			std::vector<Il2CppObject*> newItems;
			for (int i = 0; i < Global::customLiveFixMemberData.size(); i++)
			{
				if (Global::customLiveFixMemberData[i]->MusicId == musicId) {
					Il2CppObject* c = il2cpp_object_new(il2cpp_symbols::get_global_class("umamusume.dll", "LiveFixMemberData"));

					il2cpp_class_get_method_from_name_type<void(*)(Il2CppObject*,int,int,int,int,int,int,int,int)>(c->klass, ".ctor", 8)->methodPointer(
						c,
						Global::customLiveFixMemberData[i]->Id,
						Global::customLiveFixMemberData[i]->MusicId,
						Global::customLiveFixMemberData[i]->Order,
						Global::customLiveFixMemberData[i]->CharaId,
						Global::customLiveFixMemberData[i]->DressId1,
						Global::customLiveFixMemberData[i]->DressId2,
						Global::customLiveFixMemberData[i]->DressColor1,
						Global::customLiveFixMemberData[i]->DressColor2
					);

					
					newItems.push_back(c);
				}
			}
			
			
			if (newItems.size() == 0) {
				Logger::Info(SECTION_NAME, L"GetListWithMusicId_hook: no custom data for musicId=%d", musicId);
				return ret;
			}
			// listObj 는 Il2CppObject* (C#의 List<LiveFixMemberData>)
			//auto* newlist = reinterpret_cast<List_1_LiveFixMemberData*>(ret);

			// newItems.size() 만큼의 새 배열을 만든다.
			Il2CppArraySize_t<Il2CppObject*>* arr =
				il2cpp_array_new_type<Il2CppObject*>(
					il2cpp_symbols::get_global_class("umamusume.dll", "LiveFixMemberData"),
					newItems.size()
				);
				

			// vector 내용을 복사
			for (size_t i = 0; i < newItems.size(); i++) {
				il2cpp_array_setref(arr, i, newItems[i]);
				// write barrier 호출 필요할 수 있음
				il2cpp_gc_wbarrier_set_field(reinterpret_cast<Il2CppObject*>(arr),
					(void**)&arr->vector[i], newItems[i]);
			}

			// List 의 내부 교체
			list->fields._items = reinterpret_cast<Il2CppArray*>(arr);
			list->fields._size = static_cast<int32_t>(newItems.size());
			list->fields._version++;

			wprintf(L"GetListWithMusicId_hook: replaced count=%d\n", list->fields._size);
		}
	

		
		return ret;
	}

	void Init() {
		Logger::Info(SECTION_NAME, L"Init");

		auto GetWithMusicId_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterLiveFixMemberData", "GetWithMusicId", 1
		);
		EnableHook(GetWithMusicId_addr, &GetWithMusicId_hook, &GetWithMusicId_orig, L"MasterLiveFixMemberData_GetWithMusicId");

		auto GetListWithMusicId_addr = il2cpp_symbols::get_method_pointer(
			"umamusume.dll", "Gallop",
			"MasterLiveFixMemberData", "GetListWithMusicId", 1
		);
		EnableHook(GetListWithMusicId_addr, &GetListWithMusicId_hook, &GetListWithMusicId_orig, L"MasterLiveFixMemberData_GetListWithMusicId");


	}
}