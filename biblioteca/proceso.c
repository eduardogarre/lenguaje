extern __declspec(dllimport) unsigned long __stdcall GetCurrentProcessId();

int idprocesoactual()
{
    return GetCurrentProcessId();
}
