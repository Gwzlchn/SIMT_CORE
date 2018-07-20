#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QObject>
#include <QMetaEnum>

//class TestClass : public QObject {
//    Q_OBJECT   //必须有
//public:
//    enum TestEnum {
//        one = 0,
//        two,
//        three
//    };
//    Q_ENUM(TestEnum)
//    QMetaEnum tenum = QMetaEnum::fromType<TestClass::TestEnum>();

//};
//QMetaEnum tenum = QMetaEnum::fromType<TestClass::TestEnum>();
//qDebug() << tenum.isValid();//判断是否有效
//qDebug() << tenum.name();//枚举名字
//qDebug() << tenum.scope();//范围
////获取枚举数量，根据序号获取字符串
//for(int i = 0; i < tenum.keyCount(); i++)
//        qDebug() << tenum.key(i);
////根据字符串获取值
//qDebug() << tenum.keyToValue("two");
////根据值获取字符串
//qDebug() << tenum.valueToKey(2);
////根据序号获取值
//for(int i = 0; i < tenum.keyCount(); i++)
//    qDebug() << tenum.value(i);
//class Instructions
//{
//public:
//    Instructions();
//};



#endif // INSTRUCTIONS_H
