#include <iostream>
#include <cstdint>
#include <fstream>
#include <array>

using namespace std;

int main()
{
    // 查看系统版本信息
    ifstream istream("/proc/version", ios::in);
    array<char, 1000> ver;
    istream.getline(&ver[0], ver.size());
    cout << &ver[0] << endl;

    // 修改系统能够打开的最大文件数量
    fstream iostream("/proc/sys/fs/file-max", ios::in);
    // 首先读取最大数量
    array<char, 100> fileMax;
    iostream >> &fileMax[0];
    cout << "file-max: " << &fileMax[0] << endl;
    // 将其减1后写入文件
    iostream.close();
    iostream.open("/proc/sys/fs/file-max", ios::out);
    if (!iostream.is_open()) {
        cout << "openfile fail" << endl;
        return 0;
    }
    iostream << stoull(string(&fileMax[0])) - 1;
}