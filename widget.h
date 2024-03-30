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

#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <QString>
#include <QTextCursor>
#include <QTextCharFormat>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    void button_ops(const char*);  // 按下运算符按钮时的统一操作
    void button_nums(const char*);  // 按下数字按钮时的统一操作

    void keyPressEvent(QKeyEvent*);

    bool isDotExited;  // 记录一个str中用户是否已经输入过"."
    short fre;  // 作为按钮权限的标志 (详见结尾注释说明)
    QString* str;  // 用户当下正在输入的数
    QString* strResult;  // 记录计算结果
    std::vector<short>* fres;  // 记录fre权限的栈
    std::vector<QString>* cache;  // 缓存输入的str
    std::vector<double>* nums;  // 存储要计算的数
    std::vector<QString>* ops;  // 存储操作符

    QTextEdit* TextEdit_a;  // 文本框指针
    QTextCursor* t;  // 光标变量，用于操作文本框内容
    QTextCharFormat* f;  // 字体变量， 用于控制插入的文本格式

    QPushButton* PushButton_add;
    QPushButton* PushButton_sub;
    QPushButton* PushButton_mul;
    QPushButton* PushButton_div;
    QPushButton* PushButton_0;
    QPushButton* PushButton_1;
    QPushButton* PushButton_2;
    QPushButton* PushButton_3;
    QPushButton* PushButton_4;
    QPushButton* PushButton_5;
    QPushButton* PushButton_6;
    QPushButton* PushButton_7;
    QPushButton* PushButton_8;
    QPushButton* PushButton_9;
    QPushButton* PushButton_C;
    QPushButton* PushButton_eq;
    QPushButton* PushButton_dot;
    QPushButton* PushButton_del;
//   QPushButton* PushButton_close;

private slots:
    void appendText_add();
    void appendText_sub();
    void appendText_mul();
    void appendText_div();
    void appendText_0();
    void appendText_1();
    void appendText_2();
    void appendText_3();
    void appendText_4();
    void appendText_5();
    void appendText_6();
    void appendText_7();
    void appendText_8();
    void appendText_9();
    void appendText_C();
    void appendText_eq();
    void appendText_dot();
    void appendText_del();
};
#endif // WIDGET_H

/*
关于对变量fre的特别说明{
    fre变量初始为0;
    fre可取的值: -1， 0， 1， 2;

    fre为-1时{
        会响应用户的按钮有: 所有的键
        当按钮被有效触发时会使fre = -1的按钮有:  数字和dot键
    }

    fre为0时{
        会响应用户的按钮有:  数字键和dot键， del键， C键
        当按钮被有效触发时会使fre = 0的按钮有:  运算符键， C键
    }

    fre为1时{  (已经按下等于键)
        会响应用户的按钮有:  运算符键
        当按钮被有效触发时会使fre = 1的按钮有:  等于键
    }

    fre为2时{  (出现了被除数为0的情况)
        会响应用户的按钮有:  C键
        当按钮被有效触发时会使fre = 2的按钮有:  等于键::计算中除数为0时
    }

    此外当按下del键时将根据fres栈中的值改变fre的标志值

}
*/
