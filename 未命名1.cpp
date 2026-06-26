#include <iostream> // 引入输入输出流库，提供 cin（读）和 cout（写
#include <vector> // 引入向量容器库，提供 vector 动态数组
#include <string>
#include <fstream> // 引入文件流库（留着写文件用的）
using namespace std;// 指定标准命名空间，否则要写 std::cout，省去前缀

// 1. 先定义学生结构（这就是你的数据）
struct Student {
    int id;
    string name;
    float score;
};

// 2. 全局变量（存储所有学生）（动态存储）
vector<Student> students;

// 3. 函数声明（先不管具体实现，把名字写上）
void showMenu();
void addStudent();
void showAll();
void deleteStudent();
void modifyStudent(); 
void saveToFile();
void loadFromFile();
int main() {
	loadFromFile(); //程序启动时自动读取
	while (true) {// 无限循环，除非主动 break 或 return 跳出
	showMenu();
        	int choice;
        	cin >> choice;
        
        	switch (choice) {
	            case 1:
	                addStudent(); 
	                break;
	            case 2:
	                showAll();    
	                break;
	            case 3:
	                deleteStudent();    
	                break;
	            case 4:
	                modifyStudent();    
	                break;  
	            case 0:
	                cout << "退出程序" << endl;
	                saveToFile(); //退出时自动保存
	                return 0;
	            default:
	                cout << "输入错误，请重新选择" << endl;
	        }
	    }
    return 0;//彻底结束整个程序 
}

// 4. 菜单界面
void showMenu() {
    cout << "========= 学生管理系统 =========" << endl;
    cout << "  1. 添加学生" << endl;
    cout << "  2. 显示所有学生" << endl;
    cout << "  3. 删除学生" << endl;
    cout << "  4. 修改学生" << endl;
    cout << "  0. 退出" << endl;
    cout << "================================" << endl;
    cout << "请输入选择: ";
}
// 添加学生
void addStudent() {
    Student s;
    cout << "请输入学号: ";
    cin >> s.id;
    cout << "请输入姓名: ";
    cin >> s.name;
    cout << "请输入成绩: ";
    cin >> s.score;
    
    students.push_back(s); // 存入 vector// 将 s 的副本添加到全局 vector 的末尾，vector 自动扩容
    
    cout << "添加成功！当前共有 " << students.size() << " 名学生。" << endl;
}
// 显示所有学生
void showAll() {
    if (students.empty()) {
        cout << "列表为空，请先添加学生！" << endl;
        return;// 提前结束函数，不执行后面的代码
    }
    
    cout << "===== 学生列表 =====" << endl;
    for (int i = 0; i < students.size(); i++) {
        cout << "学号: " << students[i].id 
             << "，姓名: " << students[i].name 
             << "，成绩: " << students[i].score << endl;
    }
}
void deleteStudent(){
	cout<<"请输入要删除的学号：";
	int id;
	cin>>id;
	for(int i=0;i<students.size();i++){
		if(students[i].id==id){
			students.erase(students.begin()+i);//删除vector中的这一条 
			cout<<"成功删除成功！当前剩余"<<students.size()<<"名学生"<<endl;
			return;
		}
	}
	cout<<"没找到该学号"<<endl;
}
void modifyStudent(){
	cout<<"请输入要修改的学号：";
	int id;
	cin>>id;
	for(int i=0;i<students.size();i++){
		if(students[i].id==id){
			cout<<"当前姓名："<<students[i].name<<"成绩"<<students[i].score<<endl;
			cout<<"请输入新姓名：";
			cin>>students[i].name;
			cout<<"请输入新成绩：";
			cin>>students[i].score;
			cout<<"修改成功！"<<endl;
			return;
		}
	}
	cout<<"没找到该学号"<<endl;
}
// 5. 保存数据到文件
void saveToFile() {
    ofstream file("students.txt"); // ofstream 就是用来写文件的
    if (!file) {
        cout << "文件打开失败！" << endl;
        return;
    }
    for (int i = 0; i < students.size(); i++) {
        file << students[i].id << " " 
             << students[i].name << " " 
             << students[i].score << endl;
    }
    file.close();
    cout << "数据已保存到 students.txt" << endl;
}

// 6. 从文件读取数据
void loadFromFile() {
    ifstream file("students.txt"); // ifstream 就是用来读文件的
    if (!file) {
        // 文件不存在是正常的（第一次运行），静默返回即可
        return;//停止这个函数，回到上一级 
    }
    Student s;
    while (file >> s.id >> s.name >> s.score) {
        students.push_back(s);//push_back用于在末尾添加元素 
    }
    file.close();
    cout << "已从文件加载 " << students.size() << " 条数据" << endl;
}
