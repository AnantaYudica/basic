#include "test/Output.h"

#include <cstdio>
#include <cassert>
#include <cstring>

struct Status
{
    void Error()
    {};
};

typedef basic::test::Output<Status> Output;

#define BUFFER_SIZE 1024

#define EMPTY_CSTR ""
#define DEBUG_CSTR "debug"
#define INFO_CSTR "info"
#define ERR_CSTR "error"

void OpenFile(FILE*& rd_tmp_file, const char* file_tmp_name)
{
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    fopen_s(&rd_tmp_file, file_tmp_name, "r");
#else 
    rd_tmp_file = fopen(file_tmp_name, "r");
#endif 
}

void ReadString(FILE*& rd_tmp_file, char * buffer)
{
    buffer[0] = '\0';
#if ((defined(_WIN32) || defined(_WIN64)) && !defined(_CRT_SECURE_NO_WARNINGS))
    fscanf_s(rd_tmp_file, "%s", buffer, BUFFER_SIZE);
#else
    fscanf(rd_tmp_file, "%s", buffer);
#endif
}

int main()
{
    char * buffer = new char[BUFFER_SIZE];
    Status status;
    Output out1(status);

    out1.DebugEnable(false);
    assert(out1.DebugEnable() == false);
    out1.DebugEnable(true);
    assert(out1.DebugEnable() == true);

    out1.InfoEnable(false);
    assert(out1.InfoEnable() == false);
    out1.InfoEnable(true);
    assert(out1.InfoEnable() == true);

    out1.Enable(false);
    assert(out1.Enable() == false);
    out1.Enable(true);
    assert(out1.Enable() == true);

    const char * file_tmp_name = "test.output.txt";
    FILE* rd_tmp_file;
    {
        Output out1(status, file_tmp_name);
        out1.Debug(DEBUG_CSTR "\n");
        out1.Info(INFO_CSTR "\n");
        out1.Error(ERR_CSTR);
    }

    OpenFile(rd_tmp_file, file_tmp_name);
    assert(rd_tmp_file != NULL);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, DEBUG_CSTR) == 0);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, INFO_CSTR) == 0);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, ERR_CSTR) == 0);
    assert(feof(rd_tmp_file));

    fclose(rd_tmp_file);

    {
        Output out1(status, file_tmp_name);
        out1.DebugEnable(false);
        out1.Debug(DEBUG_CSTR "\n");
        out1.Info(INFO_CSTR "\n");
        out1.Error(ERR_CSTR);
    }

    OpenFile(rd_tmp_file, file_tmp_name);
    assert(rd_tmp_file != NULL);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, INFO_CSTR) == 0);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, ERR_CSTR) == 0);
    assert(feof(rd_tmp_file));

    fclose(rd_tmp_file);

    {
        Output out1(status, file_tmp_name);
        out1.InfoEnable(false);
        out1.Debug(DEBUG_CSTR "\n");
        out1.Info(INFO_CSTR "\n");
        out1.Error(ERR_CSTR);
    }

    OpenFile(rd_tmp_file, file_tmp_name);
    assert(rd_tmp_file != NULL);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, DEBUG_CSTR) == 0);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, ERR_CSTR) == 0);
    assert(feof(rd_tmp_file));

    fclose(rd_tmp_file);

    {
        Output out1(status, file_tmp_name);
        out1.Enable(false);
        out1.Debug(DEBUG_CSTR "\n");
        out1.Info(INFO_CSTR "\n");
        out1.Error(ERR_CSTR);
    }

    OpenFile(rd_tmp_file, file_tmp_name);
    assert(rd_tmp_file != NULL);

    ReadString(rd_tmp_file, buffer);
    printf("output : \"%s\"\n", buffer);
    assert(strcmp(buffer, EMPTY_CSTR) == 0);
    assert(feof(rd_tmp_file));

    fclose(rd_tmp_file);

    remove(file_tmp_name);
    delete[] buffer;
}
