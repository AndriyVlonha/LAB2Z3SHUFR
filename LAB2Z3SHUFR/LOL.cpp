#include <iostream>
#include <fstream>
#include <bitset>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;

int parityBit(int value, int bits) {
    int count = 0;
    for (int i = 0; i < bits; ++i) {
        if (value & (1 << i)) {
            ++count;
        }
    }
    return count % 2;
}

void encryptText(const string& inputFilePath, const string& outputFilePath) {
    ifstream inFile(inputFilePath);
    if (!inFile) {
        cerr << "�� ������� ������� ���� " << inputFilePath << " ��� �������!" << endl;
        return;
    }

    ofstream outFile(outputFilePath, ios::binary);
    if (!outFile) {
        cerr << "�� ������� ������� ���� " << outputFilePath << " ��� ������!" << endl;
        return;
    }

    string lines[8];
    int index = 0;

    while (index < 8 && getline(inFile, lines[index])) {
        lines[index].resize(8, ' ');
        ++index;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char currentChar = lines[i][j];
            unsigned short encryptedChar = 0;

            // ����� ����� (��� 0-2)
            encryptedChar |= (i & 0x7); // 3 ���

            // ������� ������� � ����� (��� 3-5)
            encryptedChar |= ((j & 0x7) << 3); // 3 ���

            // ��� ������� ������ ���� ���� (�� 6)
            encryptedChar |= (parityBit(i + (j << 3), 6) << 6);

            // ASCII-��� ������� (��� 7-14)
            encryptedChar |= (static_cast<unsigned char>(currentChar) << 7); // 8 ��

            // ��� ������� ��� ASCII-���� (�� 15)
            encryptedChar |= (parityBit(currentChar, 8) << 15);

            // �������� ������������ ������ � ������� ����
            outFile.write(reinterpret_cast<const char*>(&encryptedChar), sizeof(encryptedChar));
        }
    }

    inFile.close();
    outFile.close();
    cout << "���������� ���������." << endl;
}

int main() {
    SetConsoleOutputCP(1251);

    string inputFilePath = "C:\\Users\\westt\\source\\repos\\LAB2Z3SHUFR\\LAB2Z3SHUFR\\input.txt";
    string outputFilePath = "C:\\Users\\westt\\source\\repos\\LAB2Z3SHUFR\\LAB2Z3SHUFR\\encrypted.bin";

    encryptText(inputFilePath, outputFilePath);

    return 0;
}
