#include <QCoreApplication>
#include <QDebug>
#include <QMetaEnum>
#include <QObject>

#include<Instructions.h>

int main(int argc, char *argv[]) {

    QMetaEnum tenum = QMetaEnum::fromType<TestClass::TestEnum>();
    qDebug() << tenum.isValid();//判断是否有效
    qDebug() << tenum.name();//枚举名字
    qDebug() << tenum.scope();//范围
    //获取枚举数量，根据序号获取字符串
    for(int i = 0; i < tenum.keyCount(); i++)
            qDebug() << tenum.key(i);
    //根据字符串获取值
    qDebug() << tenum.keyToValue("two");
    //根据值获取字符串
    qDebug() << tenum.valueToKey(2);
    //根据序号获取值
    for(int i = 0; i < tenum.keyCount(); i++)
        qDebug() << tenum.value(i);
    qDebug() << TestClass::getStringByEnum(2);
    return 0;
}
