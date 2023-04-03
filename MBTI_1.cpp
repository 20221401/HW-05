#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

class ReadMBTIData {    // 클래스 선언, 그리고 원하는 클래스 이름을 사용합니다.       
public:                 // 이번 장에 배울 내용입니다. 멤버 함수들부터 써 봅니다.
    ReadMBTIData() {}   // 클래스로 객체를 만들 때 사용하는 생성자입니다. 클래스와 이름이 같아요. 

    // 아래 csv 파일을 읽을 read_data 함수는 지금 구현 방법은 전혀 알 필요가 없습니다. 
    // 선언 방법만 보고 갑니다. 반환하는 내용이 없고, 이름은 read_data고, 매개변수는 string 형태의 파일명만 필요합니다. //
    // 안의 내용은 블랙박스로 그냥 두세요.
    void read_data(string file_path) {
        ifstream input_file(file_path);
        if (!input_file.is_open()) {
            cerr << "Failed to open input file" << endl;
            return;
        }

        int num_rows = 0;
        string line;
        while (getline(input_file, line)) {
            num_rows++;
        }
        input_file.clear();
        input_file.seekg(0, ios::beg);

        name_ = new string[num_rows];
        id_ = new string[num_rows];
        mbti_ = new string[num_rows];

        int i = 0;
        while (getline(input_file, line)) {
            stringstream ss(line);
            string cell;
            int j = 0;
            while (getline(ss, cell, ',')) {
                if (j == 0) {
                    name_[i] = cell;
                }
                else if (j == 1) {
                    id_[i] = cell;
                }
                else if (j == 2) {
                    mbti_[i] = cell;
                }
                j++;
            }
            i++;
        }
        input_file.close();
        num_rows_ = num_rows;
    }

    // print_data 함수는 멤버 변수들을 콘솔창에 출력하는 역할을 합니다. 
    // name_, id_, mbti_ 배열을 for loop를 사용해 num_rows까지 출력합니다. 
    // num_rows는 위 블랙박스에서 계산해 주니 신경 쓰지 마세요.
    void print_data() {
        for (int i = 0; i < num_rows_; i++) {
            cout << name_[i] << " " << id_[i] << " " << mbti_[i] << endl;
        }
    }

    // 소멸자입니다. 
    // 배열들이 지난 시간 소개한 동적배열(포인터를 사용한 배열입니다). 
    // 강의에서 HEAP MEMORY를 사용하는 경우, 이와 같이 메모리를 해제해 줘야 합니다. 
    ~ReadMBTIData() { 	// 객체를 삭제합니다. 소멸자 함수는 ~ 표시를 하고, 클래스 이름을 그대로 써 줍니다.
        delete[] name_; // name 멤버 변수는 num_rows_ 만큼 생성되는 배열입니다. 배열 삭제 시 [] 표시와 함께 삭제해 줍니다.
        delete[] id_;	// id, mbti 모두 name 변수와 동일하게 삭제합니다. 
        delete[] mbti_;
    }

    // 이 클래스에서는 private: 멤버 변수들이 클래스 가장 아래에 있습니다. 
    // 이런 식의 구현도 익숙해 지세요.
    // 두번째 강의에서 private 영역에는 일반적으로 객체의 '상태'를 나타내는 변수들을 정의한다고 했습니다.
    // 우리가 csv 파일에서 읽어올 변수들은 이름, id, mbti입니다.
    // 변수를 모두 포인터를 사용해 dynamic array로 만들었습니다. 
    // 이유는 몇개의 행이 있을지 모르기 때문입니다.
private:
    string* name_; 	// 변수들을 동적(dynamic)으로 만들었습니다. heap memory에 저장하여 stack 메모리가 해제되어도 살아있게 합니다.
    string* id_;	// Heap memory를 사용하는 이유는 객체의 생성, 소멸을 내가 마음대로 조절하고 싶기 때문입니다. 
    string* mbti_;	// stack memory에 자료를 저장하면 함수 호출이 끝날 때 사라지기 때문입니다. 또한 stack은 공간이 작아 많은 데이터를 담기 부적합한 이유도 있어요.
    int num_rows_; 	// 몇 개의 데이터를 읽어 올지는 정해지는 값이기 때문에 굳이 동적으로 할당할 필요가 없겠죠? 
};
class CStudent {    // 옵션 과제를 위한 예시 클래스 입니다. 
    int height_;
public:
    void set_height(int _height) {
        height_ = _height;
    }
    int get_height() {
        return height_;
    }
};
int main() {
    // 클래스 이름, 그리고 클래스로 만들 객체 이름을 써줍니다.
    ReadMBTIData data;

    // 이제 클래스에 구현된 read_data 함수를 이용해 csv 파일을 읽어 보겠습니다.
    // 클래스로 돌아가서 read_data 함수를 보면 csv 파일 명을 읽도록 되어 있어요.

    data.read_data("C:\\Users\\priss\\Downloads\\2023_Students.csv");       // 내 소스 파일이 있는 곳에 csv 파일을 두면 이렇게 경로를 쓰지 않아도 됩니다. 
    //data.read_data("C:\\Users\\Sungshin\\2023_Students.csv");     // 내 소스 파일이 있는 곳이 아닌 다른 위치에 있는 곳에 있는 csv 파일을 읽고 싶다면 경로를 씁니다. 단, \ 표시를 하나가 아니라 두개(\\) 해주는 것을 기억하세요.
    //data.read_data("G:\\내 드라이브\\Class 2023\\Advnaced Cpp\\2023_Students.csv");

    // 클래스의 print_data 함수를 이용해 콘솔창에 출력해 줍니다. 
    data.print_data();

    /*
    // !!!! 옵션 과제 입니다 !!! //
    친구들을 동적 객체로 만들어 보세요.
    먼저 지난 번 숙제처럼 친구 클래스를 만들고, 생성자, getter, setter를 만들어 주는 것은 똑같습니다.
    그리고 main 함수에서 해당 클래스를 이용해 동적으로 객체를 만들면 됩니다(강의자료 24쪽).
    동적으로 객체를 만들면 객체를 삭제해 줘야 하기 때문에, 소멸자도 구현해 보세요(강의 자료 29쪽 참고)
    동적으로 만드는 객체의 수는 본 source.cpp 코드에서 ReadMBTIData의 멤버 변수인 num_rows_ 만큼 만들어 주면 되겠죠?

    동적으로 객체를 만든 뒤 객체의 멤버 변수에 접근하여 MBTI 별로 몇명의 친구들이 있는지 확인해 보세요.
    지난 시간에 배운 string class의 compare 멤버 함수를 사용해 봅니다.
    */

    // !!!! 옵션 과제를 돕기 위한 예시입니다. 잘 안되면 참고해 보세요. !!! //
    // 위에 작게 하나 만들어 둔 CStudent 클래스를 살펴봅시다. 
    CStudent* OStudent = new CStudent[10]; // 강의자료 24쪽에는 배열로 만드는 예시는 없죠? 별다른 건 없어요. 일반 배열과 똑같이 사용합니다. 
    OStudent[0].set_height(190);           // 동적 배열로 만든 첫번째 객체에 setter 멤버 함수를 사용해 키 정보를 줍니다.
    int height = OStudent[0].get_height(); // 그리고 키 정보를 가져옵니다. 별거 없이 똑같죠? 
    // 간접 참조로도 만들어보고, 여러 가지 다양한 방식으로도 구현할 수 있습니다. 예시를 바탕으로 자유롭게 구성해 보세요.
    return 0;
}
