/*
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "widget.h"
#include <iostream>
#include <QIcon>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    str = new QString;
    strResult = new QString;
    fres = new std::vector<short>;
    cache = new std::vector<QString>;
    nums = new std::vector<double>;
    ops = new std::vector<QString>;
    t = new QTextCursor;
    f = new QTextCharFormat;

    fre = 0; // fre初始化为0
    fres->push_back(0);  // fres初始化第一个元素为0
    (*str) = "";  // str初始化
    isDotExited = false;

    // 窗体设计实现
    this->setGeometry(500, 250, 720, 640);  // 主窗口设计
    this->setFixedSize(720, 640);
    this->setWindowTitle("一个简易的计算器");
    this->setWindowIcon(QIcon(".\\icons\\calculate.png"));
    this->setWindowFlags(Qt::WindowCloseButtonHint);

    QFile file(".\\qss\\styleSheet.qss");  // 读取qss样式文件
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    this->setStyleSheet(stylesheet);

    TextEdit_a = new QTextEdit;
    TextEdit_a->setParent(this);
    TextEdit_a->setGeometry(50, 20, 620, 120);
    TextEdit_a->setReadOnly(1);
    TextEdit_a->setStyleSheet("background-color:#ffffff; font-size: 32px;border: 2px solid grey;border-radius:8px");
    (*t) = TextEdit_a->textCursor();
    f->setForeground(QColor("black"));

    PushButton_0 = new QPushButton("0", this);
    PushButton_0->setGeometry(125, 540, 210, 80);

    PushButton_1 = new QPushButton("1", this);
    PushButton_1->setGeometry(125, 450, 80, 80);

    PushButton_2 = new QPushButton("2", this);
    PushButton_2->setGeometry(255, 450, 80, 80);

    PushButton_3 = new QPushButton("3", this);
    PushButton_3->setGeometry(385, 450, 80, 80);

    PushButton_4 = new QPushButton("4", this);
    PushButton_4->setGeometry(125, 360, 80, 80);

    PushButton_5 = new QPushButton("5", this);
    PushButton_5->setGeometry(255, 360, 80, 80);

    PushButton_6 = new QPushButton("6", this);
    PushButton_6->setGeometry(385, 360, 80, 80);

    PushButton_7 = new QPushButton("7", this);
    PushButton_7->setGeometry(125, 270, 80, 80);

    PushButton_8 = new QPushButton("8", this);
    PushButton_8->setGeometry(255, 270, 80, 80);

    PushButton_9 = new QPushButton("9", this);
    PushButton_9->setGeometry(385, 270, 80, 80);

    PushButton_dot = new QPushButton(".", this);
    PushButton_dot->setGeometry(385, 540, 80, 80);

    PushButton_add = new QPushButton("+", this);
    PushButton_add->setGeometry(515, 360, 80, 80);
    PushButton_add->setStyleSheet("color:#00BFFF");

    PushButton_sub = new QPushButton("-", this);
    PushButton_sub->setGeometry(515, 270, 80, 80);
    PushButton_sub->setStyleSheet("color:#00BFFF");

    PushButton_mul = new QPushButton("x", this);
    PushButton_mul->setGeometry(385, 180, 80, 80);
    PushButton_mul->setStyleSheet("color:#00BFFF");

    PushButton_div = new QPushButton("/", this);
    PushButton_div->setGeometry(255, 180, 80, 80);
    PushButton_div->setStyleSheet("color:#00BFFF");

    PushButton_eq = new QPushButton("=", this);
    PushButton_eq->setGeometry(515, 450, 80, 170);
    PushButton_eq->setStyleSheet("color:green");

    PushButton_del = new QPushButton("<-", this);
    PushButton_del->setGeometry(515, 180, 80, 80);
    PushButton_del->setStyleSheet("color:red");

    PushButton_C = new QPushButton("C", this);
    PushButton_C->setGeometry(125, 180, 80, 80);
    PushButton_C->setStyleSheet("color:red");
    // 窗体设计实现

    // 连接信号与槽函数
    connect(PushButton_C, SIGNAL(clicked()), this, SLOT(appendText_C()));
    connect(PushButton_add, SIGNAL(clicked()), this, SLOT(appendText_add()));
    connect(PushButton_sub, SIGNAL(clicked()), this, SLOT(appendText_sub()));
    connect(PushButton_mul, SIGNAL(clicked()), this, SLOT(appendText_mul()));
    connect(PushButton_div, SIGNAL(clicked()), this, SLOT(appendText_div()));
    connect(PushButton_0, SIGNAL(clicked()), this, SLOT(appendText_0()));
    connect(PushButton_1, SIGNAL(clicked()), this, SLOT(appendText_1()));
    connect(PushButton_2, SIGNAL(clicked()), this, SLOT(appendText_2()));
    connect(PushButton_3, SIGNAL(clicked()), this, SLOT(appendText_3()));
    connect(PushButton_4, SIGNAL(clicked()), this, SLOT(appendText_4()));
    connect(PushButton_5, SIGNAL(clicked()), this, SLOT(appendText_5()));
    connect(PushButton_6, SIGNAL(clicked()), this, SLOT(appendText_6()));
    connect(PushButton_7, SIGNAL(clicked()), this, SLOT(appendText_7()));
    connect(PushButton_8, SIGNAL(clicked()), this, SLOT(appendText_8()));
    connect(PushButton_9, SIGNAL(clicked()), this, SLOT(appendText_9()));
    connect(PushButton_eq, SIGNAL(clicked()), this, SLOT(appendText_eq()));
    connect(PushButton_dot, SIGNAL(clicked()), this, SLOT(appendText_dot()));
    connect(PushButton_del, SIGNAL(clicked()), this, SLOT(appendText_del()));
    // 连接信号与槽函数
}

Widget::~Widget() {  // 析构函数释放堆区内存
    delete str;
    delete strResult;
    delete fres;
    delete cache;
    delete nums;
    delete ops;
    delete t;
    delete f;
    delete TextEdit_a;
    delete PushButton_0;
    delete PushButton_1;
    delete PushButton_2;
    delete PushButton_3;
    delete PushButton_4;
    delete PushButton_5;
    delete PushButton_6;
    delete PushButton_7;
    delete PushButton_8;
    delete PushButton_9;
    delete PushButton_dot;
    delete PushButton_C;
    delete PushButton_add;
    delete PushButton_sub;
    delete PushButton_mul;
    delete PushButton_div;
    delete PushButton_del;
    delete PushButton_eq;
}


void Widget::appendText_0(){
    button_nums("0");
}
void Widget::appendText_1(){
    button_nums("1");
}
void Widget::appendText_2(){
    button_nums("2");
}
void Widget::appendText_3(){
    button_nums("3");
}
void Widget::appendText_4(){
    button_nums("4");
}
void Widget::appendText_5(){
    button_nums("5");
}
void Widget::appendText_6(){
    button_nums("6");
}
void Widget::appendText_7(){
    button_nums("7");
}
void Widget::appendText_8(){
    button_nums("8");
}
void Widget::appendText_9(){
    button_nums("9");
}

void Widget::appendText_dot(){
    if (fre == 0 && isDotExited == false){  // 如果fre为0的话，输入“.”应相当于自动输入了“0.”
        fre = -1;
        isDotExited = true;
        fres->push_back(-1);
        fres->push_back(-1);  // fres压两次栈

        t->movePosition(QTextCursor::End);  // 文本框显示
        f->setForeground(QColor("black"));
        t->setCharFormat((*f));
        t->insertText("0.");

        str->push_back("0.");  // str中追加
    }
    else if (fre == -1 && isDotExited == false){  // 如果fre为-1，表示可以直接输入“.”，不需要特殊处理
        isDotExited = true;
        fres->push_back(-1);  // fres压栈

        t->movePosition(QTextCursor::End);  // 文本框显示
        f->setForeground(QColor("black"));
        t->setCharFormat((*f));
        t->insertText(".");

        str->push_back(".");  // str中追加
    }

}


void Widget::appendText_add(){
    button_ops("+");
}
void Widget::appendText_mul(){
    button_ops("*");
}
void Widget::appendText_div(){
    button_ops("/");
}
void Widget::appendText_sub(){
    if (fre == -1){  // fre为-1和1时应同其他操作符一样处理
        fre = 0;
        isDotExited = false;
        fres->push_back(0);
        // TextEdit_a->insertPlainText(op);

        f->setForeground(QColor("DeepSkyBlue"));
        t->movePosition(QTextCursor::End);
        t->setCharFormat((*f));
        t->insertText("-");

        ops->push_back("-");
        cache->push_back((*str));
        nums->push_back(str->toDouble());
        str->clear();
    }
    else if (fre == 1){
        fre = 0;
        isDotExited = false;
        nums->clear();
        nums->push_back(strResult->toDouble());
        ops->clear();
        ops->push_back("-");
        cache->push_back((*strResult));
        for (int i = 0; i < int(strResult->size()); i++){
            fres->push_back(-1);
        }
        fres->push_back(0);

        TextEdit_a->clear();
        t->movePosition(QTextCursor::End);
        f->setForeground(QColor("black"));
        t->setCharFormat((*f));
        t->insertText((*strResult));
        t->movePosition(QTextCursor::End);
        f->setForeground(QColor("DeepSkyBlue"));
        t->setCharFormat((*f));
        t->insertText("-");
    }
    else if (fre == 0 && str->size() == 0) {  // fre为0且str为空时表示此时应处理为负号
        fre = 0;
        fres->push_back(3);  // 此时fre仍然为0即可保证正确的逻辑，但因需要考虑用户退格的情况，所以fres中压入值为3，用于退格时特殊处理

        f->setForeground(QColor("black"));
        t->movePosition(QTextCursor::End);
        t->setCharFormat((*f));
        t->insertText("-");

        str->push_back("-");

    }
}


void Widget::appendText_eq(){
    if (fre == -1){
        fre = 1;
        isDotExited = false;
        //-chu 处理最后一个数
        nums->push_back(str->toDouble());
        str->clear();
        cache->clear();
        fres->clear();
        fres->push_back(0);
        //-chu
        strResult->clear();  // 清空上一次的计算结果用于保存下一步的结算结果
        double result = 0.0;  // 初始化临时结果变量


        // 调试输出信息
        for (int m = 0; m < int(nums->size()); m++) {
            std::cout << (*nums)[m] << ',';
        }
        std::cout << std::endl;
        for (int j = 0; j < int(ops->size()); j++) {
            std::cout << (*ops)[j].toStdString() << ',';
        }
        std::cout << std::endl;
        // 调试输出信息


        //-compute 处理保存的数据并计算出结果  (这可是这个程序的核心，这果然还是一道算法题)
        /*
        (这个算法大体上也不算难，即先进行一次遍历对nums和ops数组进行处理，从左到右计算出乘除运算并将剩下的加减运算
        存储到tempNums和tempOps数组中，最后如果没有出现“0作为被除数”的情况时，再对这两个temp数组从左到右进行计算
        并将计算结果保存到result变量中，就这么简单，时间复杂度为O(n) )
        */
        short ff = 0;
        std::vector<double> tempNums;
        std::vector<QString> tempOps;
        double temp;
        for (int i = 0; i < int(ops->size()); i++) {
            if ((*ops)[i] == "*" && ff == 0){
                ff = 1;
                tempNums.push_back((*nums)[i] * (*nums)[i+1]);
            }
            else if ((*ops)[i] == "*" && ff == 1){
                temp = tempNums[tempNums.size()-1] * (*nums)[i+1];
                tempNums.pop_back();
                tempNums.push_back(temp);
            }
            else if ((*ops)[i] == "/" && ff == 0){
                ff = 1;
                if ((*nums)[i+1] == 0.0){
                    fre = 2;
                    (*strResult) = "不能除以0！";
                    break;
                }
                else {

                    tempNums.push_back((*nums)[i] / (*nums)[i+1]);
                }
            }
            else if ((*ops)[i] == "/" && ff == 1){
                if ((*nums)[i+1] == 0.0){
                    fre = 2;
                    (*strResult) = "不能除以0！";
                    break;
                }
                else {
                    temp = tempNums[tempNums.size()-1] / (*nums)[i+1];
                    tempNums.pop_back();
                    tempNums.push_back(temp);
                }
            }
            else if (((*ops)[i] == "+" || (*ops)[i] == "-") && ff == 0){
                tempNums.push_back((*nums)[i]);
                if ((*ops)[i] == "+") {
                    tempOps.push_back("+");
                }
                else if ((*ops)[i] == "-") {
                    tempOps.push_back("-");
                }
            }
            else if (((*ops)[i] == "+" || (*ops)[i] == "-") && ff == 1){
                tempNums.push_back((*nums)[i+1]);
                if ((*ops)[i] == "+") {
                    tempOps.push_back("+");
                }
                else if ((*ops)[i] == "-") {
                    tempOps.push_back("-");
                }
            }
        }
        if (ff == 0){
            tempNums.push_back((*nums)[nums->size()-1]);
        }


        // 调试输出信息
        for (int m = 0; m < int(tempNums.size()); m++) {
            std::cout << tempNums[m] << ',';
        }
        std::cout << std::endl;
        for (int j = 0; j < int(tempOps.size()); j++) {
            std::cout << tempOps[j].toStdString() << ',';
        }
        std::cout << std::endl;
        // 调试输出信息


        if (fre != 2){
            result = tempNums[0];
            for (int r = 0; r < int(tempOps.size()); r++){
                if (tempOps[r] == "+"){
                    result += tempNums[r+1];
                }
                else{
                    result -= tempNums[r+1];
                }
            }
        //-compute
            std::cout << "result:" << result << std::endl;  // 打印调试信息
            (*strResult) = QString::number(result);  //将结果转为字符串类型并赋值给strResult
            for (int check = 0; check < strResult->size(); check++) {
                if ((*strResult)[check] == 'e' || (*strResult)[check] == 'E') {
                    fre = 2;
                }
            }

            f->setForeground(QColor("black"));
            t->movePosition(QTextCursor::End);
            t->setCharFormat((*f));
            t->insertText("\n=");
            f->setForeground(QColor("green"));
            t->movePosition(QTextCursor::End);
            t->setCharFormat((*f));
            t->insertText((*strResult));
        }
        else{
            f->setForeground(QColor("red"));
            t->movePosition(QTextCursor::End);
            t->setCharFormat((*f));
            t->insertText("\n");
            t->insertText((*strResult));
        }
    }
}

void Widget::appendText_del(){
    if ((fre == 0 || fre == -1) && fres->size() > 1 ){
        t->movePosition(QTextCursor::Left, QTextCursor::KeepAnchor, 1);
        t->removeSelectedText();
        //-backspace

        if (fre == -1){
            if ((*str).at(str->size()-1) == '.'){
                isDotExited = false;
            }
            str->removeLast();  // 如果fre标志为-1，则只需要删除str变量的最后一个字符
        }
        if (fre == 0){  // 此为fre标志为0的情况
            if ((*fres)[fres->size()-1] == 3) {
                str->removeLast();
            }
            else {
                (*str) = (*cache)[cache->size()-1];
                cache->pop_back();
                nums->pop_back();
                ops->pop_back();
                if (str->indexOf('.') != -1) {
                    isDotExited = true;
                }
            }
        }

        fre = (*fres)[fres->size()-2];  // 最后再使fre变回上一步的标志值并对fres进行一次出栈操作
        fres->pop_back();
        if (fre == 3) {  // 如果fre为3，表示删除的为负号前一个字符，此时应将fre置为0
            fre = 0;
        }
    }
}

void Widget::appendText_C(){  // (这好像不就是一个完全删除的键么，最好写了)
    fre = 0;
    isDotExited = false;
    fres->clear();
    fres->push_back(0);  // 清空并初始化fre栈
    str->clear();  // 清空当前数字保存变量
    nums->clear();  // 清空数字数组
    ops->clear();  // 清空操作符数组
    cache->clear();  // 清空缓存数组
    TextEdit_a->clear();  // 清空文本框
}


void Widget::button_nums(const char* num){
    if ((fre == 0 || fre == -1) && str->size() < 9){  // 此处的“str->size() < 9”用来控制用户最多可一次性输入8位数
        fre = -1;
        fres->push_back(-1);  // 将fre压入fres栈中

        f->setForeground(QColor("black"));  // 文本框追加字符
        t->movePosition(QTextCursor::End);
        t->setCharFormat((*f));
        t->insertText(num);

        str->push_back(num);  // 将用户输入的该数字追加在str之后
    }
}

void Widget::button_ops(const char* op){
    if (fre == -1){  // 处理前一个输入为数字的情况
        fre = 0;
        isDotExited = false;  // 更改小数点是否存在的标志
        fres->push_back(0);  // fres压栈

        f->setForeground(QColor("DeepSkyBlue"));  // 文本框追加字符
        t->movePosition(QTextCursor::End);
        t->setCharFormat((*f));
        t->insertText(op);

        ops->push_back(op);  // 将用户输入的操作符压入ops栈中
        cache->push_back((*str));  // 将str压入cache缓存数组中
        nums->push_back(str->toDouble());  // 将str转为double类型后压入nums中
        str->clear();  // 清空str字符
    }
    else if (fre == 1){  // 处理前一个输入为“=”的情况，此时将计算结果作为第一个数压入nums和cache中，用户此次输入的操作符压入ops中， 并为fres标志栈初始化
        fre = 0;
        isDotExited = false;
        nums->clear();
        nums->push_back(strResult->toDouble());  // 处理nums数组
        ops->clear();
        ops->push_back(op);  // 处理ops数组
        cache->push_back((*strResult));  // 处理cache数组
        for (int i = 0; i < int(strResult->size()); i++){
            fres->push_back(-1);
        }
        fres->push_back(0);  // 处理fres数组

        TextEdit_a->clear();  // 文本框显示内容
        t->movePosition(QTextCursor::End);
        f->setForeground(QColor("black"));
        t->setCharFormat((*f));
        t->insertText((*strResult));
        t->movePosition(QTextCursor::End);
        f->setForeground(QColor("DeepSkyBlue"));
        t->setCharFormat((*f));
        t->insertText(op);
    }
}


void Widget::keyPressEvent(QKeyEvent* event){  // 处理键盘输入，根据输入的内容调用相关槽函数
    switch(event->key()){
    case Qt::Key_0:
        appendText_0();
        break;
    case Qt::Key_1:
        appendText_1();
        break;
    case Qt::Key_2:
        appendText_2();
        break;
    case Qt::Key_3:
        appendText_3();
        break;
    case Qt::Key_4:
        appendText_4();
        break;
    case Qt::Key_5:
        appendText_5();
        break;
    case Qt::Key_6:
        appendText_6();
        break;
    case Qt::Key_7:
        appendText_7();
        break;
    case Qt::Key_8:
        appendText_8();
        break;
    case Qt::Key_9:
        appendText_9();
        break;
    case Qt::Key_Period:
        appendText_dot();
        break;
    case Qt::Key_Backspace:
        appendText_del();
        break;
    case Qt::Key_Plus:
        appendText_add();
        break;
    case Qt::Key_Minus:
        appendText_sub();
        break;
    case Qt::Key_Asterisk:
        appendText_mul();
        break;
    case Qt::Key_Slash:
        appendText_div();
        break;
    case Qt::Key_Equal:
        appendText_eq();
        break;
    case Qt::Key_Delete:
        appendText_C();
        break;
    case Qt::Key_Return:
        appendText_eq();
        break;
    case Qt::Key_Enter:
        appendText_eq();
        break;
    }
}

