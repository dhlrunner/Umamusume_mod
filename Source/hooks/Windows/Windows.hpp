#pragma once
#include "../../stdinclude.h"
#include "../Unity/il2cpp/il2cpp-tools.hpp"
#include "../Unity/il2cpp/il2cpp-hook.h"
#include "../Plugins/libNative.h"
#include "../../Global.h"
#include "../hook-helper.h"
#include <winternl.h>  
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#ifndef NTSTATUS
typedef LONG NTSTATUS;
#endif

#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

#ifndef STATUS_SUCCESS
#define STATUS_SUCCESS ((NTSTATUS)0x00000000)
#endif

#ifndef STATUS_BUFFER_OVERFLOW
// 경고(warning) 레벨: 일부 데이터만 채워졌음
#define STATUS_BUFFER_OVERFLOW ((NTSTATUS)0x80000005)
#endif

#ifndef STATUS_BUFFER_TOO_SMALL
// 오류(error) 레벨: 버퍼가 너무 작음
#define STATUS_BUFFER_TOO_SMALL ((NTSTATUS)0xC0000023)
#endif


// NtQueryValueKey 등에서 사용하는 열거형 (일부 값만 선언)
typedef enum _KEY_VALUE_INFORMATION_CLASS {
    KeyValueBasicInformation = 0,
    KeyValueFullInformation = 1,
    KeyValuePartialInformation = 2,
    // 다른 값들이 필요하면 추가 가능
} KEY_VALUE_INFORMATION_CLASS, * PKEY_VALUE_INFORMATION_CLASS;

#ifndef _KEY_VALUE_PARTIAL_INFORMATION_DEFINED
#define _KEY_VALUE_PARTIAL_INFORMATION_DEFINED

// KEY_VALUE_PARTIAL_INFORMATION 구조체 (문서화된 레이아웃)
typedef struct _KEY_VALUE_PARTIAL_INFORMATION {
    ULONG  TitleIndex;   // 내부용
    ULONG  Type;         // 레지스트리 데이터 타입 (REG_SZ 등)
    ULONG  DataLength;   // Data 배열의 바이트 길이
    UCHAR  Data[1];      // 가변 길이 데이터
} KEY_VALUE_PARTIAL_INFORMATION, * PKEY_VALUE_PARTIAL_INFORMATION;

#endif // _KEY_VALUE_PARTIAL_INFORMATION_DEFINED

typedef struct _KEY_VALUE_PARTIAL_INFORMATION_WIN {
    ULONG TitleIndex;
    ULONG Type;
    ULONG DataLength;
    BYTE  Data[1];
} KEY_VALUE_PARTIAL_INFORMATION_WIN;

/*#ifndef _UNICODE_STRING_DEFINED
#define _UNICODE_STRING_DEFINED

// UNICODE_STRING이 없을 경우 대비
typedef struct _UNICODE_STRING {
    USHORT Length;        // 바이트 단위 (문자 * sizeof(WCHAR))
    USHORT MaximumLength; // 최대 크기 (바이트)
    PWSTR  Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

#endif // _UNICODE_STRING_DEFINED
*/
// NTSTATUS 헬퍼 (Windows.h에 STATUS_SUCCESS 등 없으면)
#ifndef NT_SUCCESS
#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#endif

typedef NTSTATUS(NTAPI* NtQueryValueKey_t)(
    HANDLE KeyHandle,
    PUNICODE_STRING ValueName,
    KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
    PVOID KeyValueInformation,
    ULONG Length,
    PULONG ResultLength
);
void WinHook_init();