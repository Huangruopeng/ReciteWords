/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelTitle;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *minButton;
    QToolButton *maxButton;
    QToolButton *closeButton;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelOnlineStatus;
    QSpacerItem *horizontalSpacer;
    QLabel *labelInfo;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QLineEdit *lineEditPort;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_2;
    QLineEdit *lineEditMaxConnect;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *createServerButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(846, 480);
        Widget->setStyleSheet(QLatin1String(".Widget{		\n"
"	background-color: rgb(170, 170, 255);\n"
"}\n"
""));
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelTitle = new QLabel(Widget);
        labelTitle->setObjectName(QStringLiteral("labelTitle"));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        labelTitle->setFont(font);

        horizontalLayout_2->addWidget(labelTitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        minButton = new QToolButton(Widget);
        minButton->setObjectName(QStringLiteral("minButton"));

        horizontalLayout_2->addWidget(minButton);

        maxButton = new QToolButton(Widget);
        maxButton->setObjectName(QStringLiteral("maxButton"));

        horizontalLayout_2->addWidget(maxButton);

        closeButton = new QToolButton(Widget);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout_2->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout_2);

        tableWidget = new QTableWidget(Widget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelOnlineStatus = new QLabel(Widget);
        labelOnlineStatus->setObjectName(QStringLiteral("labelOnlineStatus"));
        labelOnlineStatus->setStyleSheet(QLatin1String(".QLabel{\n"
"	color: rgb(255, 255, 255);\n"
"}"));

        horizontalLayout->addWidget(labelOnlineStatus);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        labelInfo = new QLabel(Widget);
        labelInfo->setObjectName(QStringLiteral("labelInfo"));

        horizontalLayout->addWidget(labelInfo);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEditPort = new QLineEdit(Widget);
        lineEditPort->setObjectName(QStringLiteral("lineEditPort"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEditPort->sizePolicy().hasHeightForWidth());
        lineEditPort->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditPort);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEditMaxConnect = new QLineEdit(Widget);
        lineEditMaxConnect->setObjectName(QStringLiteral("lineEditMaxConnect"));
        sizePolicy.setHeightForWidth(lineEditMaxConnect->sizePolicy().hasHeightForWidth());
        lineEditMaxConnect->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEditMaxConnect);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        createServerButton = new QPushButton(Widget);
        createServerButton->setObjectName(QStringLiteral("createServerButton"));

        horizontalLayout->addWidget(createServerButton);


        verticalLayout->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        labelTitle->setText(QApplication::translate("Widget", "\345\234\250\347\272\277\350\203\214\345\215\225\350\257\215\346\257\224\350\265\233\346\234\215\345\212\241\347\253\257", nullptr));
        minButton->setText(QApplication::translate("Widget", "...", nullptr));
        maxButton->setText(QApplication::translate("Widget", "...", nullptr));
        closeButton->setText(QApplication::translate("Widget", "...", nullptr));
        labelOnlineStatus->setText(QString());
        labelInfo->setText(QString());
        label->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\357\274\232", nullptr));
        lineEditPort->setText(QApplication::translate("Widget", "6666", nullptr));
        label_2->setText(QApplication::translate("Widget", "\346\234\200\345\244\247\350\277\236\346\216\245\346\225\260\357\274\232", nullptr));
        lineEditMaxConnect->setText(QApplication::translate("Widget", "30", nullptr));
        createServerButton->setText(QApplication::translate("Widget", "\345\274\200\345\220\257\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
