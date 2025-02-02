#include <windows.h>

extern "C" __declspec(dllexport) HANDLE CreateJob() {
    HANDLE job = CreateJobObject(NULL, NULL);
    return job;
}

extern "C" __declspec(dllexport) void SetMemoryLimit(HANDLE job, DWORD memoryLimitMb) {
    if (job == NULL) return;

    JOBOBJECT_EXTENDED_LIMIT_INFORMATION info;
    ZeroMemory(&info, sizeof(info));
    info.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_JOB_MEMORY;
    info.JobMemoryLimit = memoryLimitMb * 1024 * 1024;

    SetInformationJobObject(job, JobObjectExtendedLimitInformation, &info, sizeof(info));
    AssignProcessToJobObject(job, GetCurrentProcess());
}

extern "C" __declspec(dllexport) void RemoveMemoryLimit(HANDLE job) {
    if (job != NULL) CloseHandle(job);
}
