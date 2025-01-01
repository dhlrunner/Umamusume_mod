// il2cpp-tools.hpp

#pragma once

#include "il2cpp_symbols.hpp"
#include "il2cpp-tabledefs.h"

namespace il2cpp {
    template<typename... T, typename R>
    inline Il2CppDelegate* CreateDelegateStatic(R(*fn)(void*, T...)) {
        auto delegate = reinterpret_cast<Il2CppDelegate*>(il2cpp_object_new(il2cpp_defaults.delegate_class));
        delegate->method_ptr = reinterpret_cast<Il2CppMethodPointer>(fn);

        const auto methodInfo = new MethodInfo{};
        methodInfo->name = "AnonymousStaticMethod";
        methodInfo->methodPointer = delegate->method_ptr;
        methodInfo->klass = il2cpp_defaults.mono_method_class;
        // methodInfo->invoker_method = GetInvokerMethod(fn, index_sequence_for<T...>{});
        methodInfo->slot = kInvalidIl2CppMethodSlot;
        methodInfo->flags = METHOD_ATTRIBUTE_STATIC;
        methodInfo->parameters_count = sizeof...(T);

        methodInfo->nativeFunction = reinterpret_cast<Il2CppMethodPointer>(fn);
        methodInfo->is_marshaled_from_native = true;

        delegate->method = reinterpret_cast<const MethodInfo*>(il2cpp_method_get_object(methodInfo, methodInfo->klass));
        // delegate->invoke_impl = methodInfo->invoker_method;

        return delegate;
    }

    template<typename R>
    inline Il2CppDelegate* CreateDelegateStatic(R(*fn)()) {
        return CreateDelegateStatic(reinterpret_cast<R(*)(void*)>(fn));
    }
}