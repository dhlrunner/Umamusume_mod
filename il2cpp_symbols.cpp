#include "il2cpp_symbols.hpp"

il2cpp_string_new_utf16_t il2cpp_string_new_utf16;
il2cpp_string_new_t il2cpp_string_new;
il2cpp_domain_get_t il2cpp_domain_get;
il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open;
il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
il2cpp_class_from_name_t il2cpp_class_from_name;
il2cpp_class_get_methods_t il2cpp_class_get_methods;
il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;
il2cpp_method_get_param_t il2cpp_method_get_param;
il2cpp_property_get_get_method_t il2cpp_property_get_get_method;
il2cpp_property_get_set_method_t il2cpp_property_get_set_method;
il2cpp_object_new_t il2cpp_object_new;
il2cpp_resolve_icall_t il2cpp_resolve_icall;
il2cpp_array_new_t il2cpp_array_new;
il2cpp_thread_attach_t il2cpp_thread_attach;
il2cpp_thread_detach_t il2cpp_thread_detach;
il2cpp_class_get_type_t il2cpp_class_get_type;
il2cpp_class_get_type_token_t il2cpp_class_get_type_token;
il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name;
il2cpp_field_get_value_t il2cpp_field_get_value;
il2cpp_field_set_value_t il2cpp_field_set_value;
il2cpp_field_static_get_value_t il2cpp_field_static_get_value;
il2cpp_field_static_set_value_t il2cpp_field_static_set_value;
il2cpp_field_get_type_t il2cpp_field_get_type;
il2cpp_type_get_object_t il2cpp_type_get_object;
il2cpp_class_get_fields_t il2cpp_class_get_fields;
il2cpp_class_get_nested_types_t il2cpp_class_get_nested_types;
il2cpp_runtime_object_init_t il2cpp_runtime_object_init;

il2cpp_image_get_name_t il2cpp_image_get_name;
il2cpp_image_get_class_count_t il2cpp_image_get_class_count;
il2cpp_type_is_byref_t il2cpp_type_is_byref;
il2cpp_method_get_flags_t il2cpp_method_get_flags;
il2cpp_method_get_return_type_t il2cpp_method_get_return_type;
il2cpp_class_from_type_t il2cpp_class_from_type;
il2cpp_class_get_name_t il2cpp_class_get_name;
il2cpp_class_get_properties_t il2cpp_class_get_properties;
il2cpp_class_is_enum_t il2cpp_class_is_enum;
il2cpp_method_get_name_t il2cpp_method_get_name;
il2cpp_method_get_param_count_t il2cpp_method_get_param_count;
il2cpp_method_get_param_name_t il2cpp_method_get_param_name;
il2cpp_class_get_parent_t il2cpp_class_get_parent;
il2cpp_class_get_interfaces_t il2cpp_class_get_interfaces;
il2cpp_class_get_namespace_t il2cpp_class_get_namespace;
il2cpp_class_get_flags_t il2cpp_class_get_flags;
il2cpp_class_is_valuetype_t il2cpp_class_is_valuetype;
il2cpp_property_get_flags_t il2cpp_property_get_flags;
il2cpp_property_get_name_t il2cpp_property_get_name;
il2cpp_property_get_parent_t il2cpp_property_get_parent;
il2cpp_field_get_flags_t il2cpp_field_get_flags;
il2cpp_field_get_name_t il2cpp_field_get_name;
il2cpp_field_get_parent_t il2cpp_field_get_parent;
il2cpp_field_get_offset_t il2cpp_field_get_offset;
il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;
il2cpp_image_get_class_t il2cpp_image_get_class;

std::unordered_map<std::string, std::string> il2cpp_function_map;

char* il2cpp_array_addr_with_size(void* array, int32_t size, uintptr_t idx)
{
	return ((char*)array) + kIl2CppSizeOfArray + size * idx;
}

LPCSTR GetObsfucatedFnName(LPCSTR name)
{
	if (!il2cpp_function_map.empty())
	{
		//find the function name in the map
		auto obsfucatedName = il2cpp_function_map[name].c_str();
		Logger::Debug(L"IL2CPP", L"Found %S is %S", name, obsfucatedName);
		return obsfucatedName;
	}
	else {
		Logger::Error(L"IL2CPP", L"il2cpp_function_map is empty");
		return NULL;
	}
	
}

namespace il2cpp_symbols
{
#define RESOLVE_IMPORT(name) name = reinterpret_cast<name##_t>(GetProcAddress(game_module, GetObsfucatedFnName(#name)))

	void* il2cpp_domain = nullptr;
	
	void init(HMODULE game_module)
	{
		il2cpp_function_map = il2cpp::GenarateSymbolMap();

		RESOLVE_IMPORT(il2cpp_string_new_utf16);
		RESOLVE_IMPORT(il2cpp_string_new);
		RESOLVE_IMPORT(il2cpp_domain_get);
		RESOLVE_IMPORT(il2cpp_domain_assembly_open);
		RESOLVE_IMPORT(il2cpp_assembly_get_image);
		RESOLVE_IMPORT(il2cpp_class_from_name);
		RESOLVE_IMPORT(il2cpp_class_get_methods);
		RESOLVE_IMPORT(il2cpp_class_get_method_from_name);
		RESOLVE_IMPORT(il2cpp_method_get_param);
		RESOLVE_IMPORT(il2cpp_object_new);
		RESOLVE_IMPORT(il2cpp_resolve_icall);
		RESOLVE_IMPORT(il2cpp_array_new);
		RESOLVE_IMPORT(il2cpp_thread_attach);
		RESOLVE_IMPORT(il2cpp_thread_detach);
		RESOLVE_IMPORT(il2cpp_class_get_type);
		RESOLVE_IMPORT(il2cpp_class_get_type_token);
		RESOLVE_IMPORT(il2cpp_class_get_field_from_name);
		RESOLVE_IMPORT(il2cpp_field_get_value);
		RESOLVE_IMPORT(il2cpp_field_set_value);
		RESOLVE_IMPORT(il2cpp_field_get_type);
		RESOLVE_IMPORT(il2cpp_image_get_class);
		RESOLVE_IMPORT(il2cpp_type_get_object);
		RESOLVE_IMPORT(il2cpp_class_get_fields);
		RESOLVE_IMPORT(il2cpp_class_get_nested_types);
		RESOLVE_IMPORT(il2cpp_runtime_object_init);
		RESOLVE_IMPORT(il2cpp_image_get_name);
		RESOLVE_IMPORT(il2cpp_image_get_class_count);
		RESOLVE_IMPORT(il2cpp_type_is_byref);
		RESOLVE_IMPORT(il2cpp_method_get_flags);
		RESOLVE_IMPORT(il2cpp_method_get_return_type);
		RESOLVE_IMPORT(il2cpp_class_from_type);
		RESOLVE_IMPORT(il2cpp_class_get_name);
		RESOLVE_IMPORT(il2cpp_class_get_properties);
		RESOLVE_IMPORT(il2cpp_class_is_enum);
		RESOLVE_IMPORT(il2cpp_method_get_name);
		RESOLVE_IMPORT(il2cpp_method_get_param_count);
		RESOLVE_IMPORT(il2cpp_method_get_param_name);
		RESOLVE_IMPORT(il2cpp_class_get_parent);
		RESOLVE_IMPORT(il2cpp_class_get_interfaces);
		RESOLVE_IMPORT(il2cpp_class_get_namespace);
		RESOLVE_IMPORT(il2cpp_class_get_flags);
		RESOLVE_IMPORT(il2cpp_class_is_valuetype);
		RESOLVE_IMPORT(il2cpp_property_get_flags);
		RESOLVE_IMPORT(il2cpp_property_get_name);
		RESOLVE_IMPORT(il2cpp_property_get_parent);
		RESOLVE_IMPORT(il2cpp_field_get_flags);
		RESOLVE_IMPORT(il2cpp_field_get_name);
		RESOLVE_IMPORT(il2cpp_field_get_parent);
		RESOLVE_IMPORT(il2cpp_field_get_offset);
		RESOLVE_IMPORT(il2cpp_domain_get_assemblies);

		il2cpp_domain = il2cpp_domain_get();
	}
	

	Il2CppMethodPointer get_method_pointer(const char* assemblyName, const char* namespaze,
		const char* klassName, const char* name, int argsCount)
	{
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		if (assembly)
		{
			auto image = il2cpp_assembly_get_image(assembly);
			if (image)
			{
				auto klass = il2cpp_class_from_name(image, namespaze, klassName);
				if (klass)
				{
					auto method = il2cpp_class_get_method_from_name(klass, name, argsCount);
					if (method)
					{
						return method->methodPointer;
					}
				}
			}
		}
		return nullptr;
	}

	void* image_get_class(void* image, size_t index)
	{
		auto klass = il2cpp_image_get_class(image, index);
		Logger::Debug(L"IL2CPP", L"get class from image is %p \n", klass);
		return klass;
	}
	
	void* GetStaticFieldValue(FieldInfo* field)
	{
		void* result = nullptr;
		il2cpp_field_static_get_value(field, &result);
		return result;
	}
	void SetStaticFieldValue(FieldInfo* field, void* value)
	{
		return il2cpp_field_static_set_value(field, value);
	}

	/*void* get_field_value(const char* assemblyName, const char* namespaze, const char* klassName, const char* fieldName) {
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		auto image = il2cpp_assembly_get_image(assembly);
		auto cls = il2cpp_class_from_name(image, namespaze, klassName);
		FieldInfo* info = il2cpp_class_get_field_from_name(cls, fieldName);

		il2cpp_field_get_value()
	}*/

	Il2CppClass* get_class(const char* assemblyName, const char* namespaze, const char* klassName)
	{
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		if (assembly)
		{
			auto image = il2cpp_assembly_get_image(assembly);
			if (image)
			{
				return il2cpp_class_from_name(image, namespaze, klassName);
			}
		}
		return nullptr;
	}

	Il2CppMethodPointer get_method_pointer(const char* assemblyName, const char* namespaze,
		const char* klassName, const char* name, int argsCount, int index)
	{
		//patchCount++;
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		Logger::Debug(L"IL2CPP", L"Trying to get method ptr, assembly=%S, namespace=%S, class=%S, name=%S, argc=%d\n", assemblyName, namespaze, klassName, name, argsCount);
		Logger::Debug(L"IL2CPP", L"get dll success %p\n", assembly);
		auto image = il2cpp_assembly_get_image(assembly);
		Logger::Debug(L"IL2CPP", L"get image success %p\n", image);
		/*auto new_klass = image_get_class(image, 51);
		printf("new_klass=%s\n", ((Il2CppClass*)new_klass)->name);*/
		//class_get_name(new_klass);
		void* klass;
		if (index != -1) {
			klass = image_get_class(image, index);
			Logger::Debug(L"IL2CPP", L"index %d klassname=%S\n",index, ((Il2CppClass*)klass)->name);
		}
		else {
			klass = il2cpp_class_from_name(image, namespaze, klassName);
			//class_get_name(klass);
			//class_get_method(klass);
		}
		//class_get_method(klass);
		Logger::Debug(L"IL2CPP", L"get class success %p\n", klass);
		/*hookStr s = {};
		s.assemblyName = assemblyName;
		s.namespaceName = namespaze;
		s.methodName = name;
		s.className = klassName;
		s.argsCount = argsCount;
		s.addr = klass;
		hooked_addr.push_back(s);*/

		Il2CppMethodPointer ptr = il2cpp_class_get_method_from_name(klass, name, argsCount)->methodPointer;
		Logger::Debug(L"IL2CPP", L"ret ptr=%p\n", ptr);
		return ptr;
	}

	MethodInfo* get_method(const char* assemblyName, const char* namespaze,
						   const char* klassName, const char* name, int argsCount)
	{
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		auto image = il2cpp_assembly_get_image(assembly);
		auto klass = il2cpp_class_from_name(image, namespaze, klassName);

		return il2cpp_class_get_method_from_name(klass, name, argsCount);
	}

	void* find_nested_class_from_name(void* klass, const char* name)
	{
		return find_nested_class(klass, [name = std::string_view(name)](void* nestedClass) {
			return static_cast<Il2CppClassHead*>(nestedClass)->name == name;
			});
	}

	Il2CppMethodPointer find_method(const char* assemblyName, const char* namespaze,
						  const char* klassName, std::function<bool(const MethodInfo*)> predict)
	{
		auto assembly = il2cpp_domain_assembly_open(il2cpp_domain, assemblyName);
		auto image = il2cpp_assembly_get_image(assembly);
		auto klass = il2cpp_class_from_name(image, namespaze, klassName);

		void* iter = nullptr;
		while (const MethodInfo* method = il2cpp_class_get_methods(klass, &iter))
		{
			if (predict(method))
				return method->methodPointer;
		}

		return 0;
	}

	void* get_class_from_instance(const void* instance)
	{
		return *static_cast<void* const*>(std::assume_aligned<alignof(void*)>(instance));
	}
}
