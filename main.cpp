#include <iostream>
#include <string>
#include <fstream>
#include <vector>
// #include <bitset>

using namespace std;

// читаем битики из изображения
vector<bool> read_bits(const string& filename) {
    ifstream file(filename, ios::binary);
    vector<bool> bits;
    char c;
    while (file.get(c)) {
        for (int i = 0; i < 8; i++) {
            bits.push_back((c >> i) & 1);
        }
    }
    return bits;
}

// записываем битики изоборажения в файл
void write_bits(const string& filename, const vector<bool>& bits) {
    ofstream file(filename, ios::binary);
    char c = 0;
    for (size_t i = 0; i < bits.size(); i++) {
        c = (c << 1) | bits[i];
        if ((i + 1) % 8 == 0) {
            file.put(c);
            c = 0;
        }
    }
    if (bits.size() % 8 != 0) {
        file.put(c);
    }
}

// шифровка lsb (попытка в наименьшие значащие биты)
void encode_lsb(const string& text, const string& output_image) {
    vector<bool> bits;
    for (char c : text) {
        for (int i = 0; i < 8; i++) {
            bits.push_back((c >> i) & 1);
        }
    }
    vector<bool> image_bits = read_bits(output_image);
    for (size_t i = 0; i < bits.size(); i++) {
        image_bits[i] = bits[i];
    }
    write_bits(output_image, image_bits);
}

// дешифровка lsb (Least Significant Bit)
string decode_lsb(const string& input_image) {
    vector<bool> bits = read_bits(input_image);
    string text;
    for (size_t i = 0; i < bits.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            c = (c << 1) | bits[i + j];
        }
        text.push_back(c);
    }
    return text;
}

int main() {
    string text, output_image;
    // спрашивать зашифровать ИЛИ расшифровать, в ТУДУ написать отдельную команду для шифровки формата: cipher LSB ./img.txt "hahahaha THIS IS A SECRET"
    cout << "какое сообщение зашифровать? ";
    getline(cin, text);
    cout << "путь к изображению, в которое зашифровать сообщение: ";
    getline(cin, output_image);

    // шифровка lsb
    encode_lsb(text, output_image);
    cout << "ура, можно передавать секретики!" << endl;

    // расшифровка lsb (бонус)
    string decoded_text = decode_lsb(output_image);
    cout << "секретик: " << decoded_text << endl;

    return 0;
}