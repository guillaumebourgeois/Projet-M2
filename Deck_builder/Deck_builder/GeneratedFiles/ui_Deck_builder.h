/********************************************************************************
** Form generated from reading UI file 'Deck_builder.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECK_BUILDER_H
#define UI_DECK_BUILDER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Deck_builderClass
{
public:
    QAction *openButton;
    QAction *saveButton;
    QAction *actiontest;
    QWidget *centralWidget;
    QGroupBox *proposalsBox;
    QScrollArea *proposalsArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *deckBox;
    QScrollArea *deckArea;
    QWidget *scrollAreaWidgetContents_2;

    void setupUi(QMainWindow *Deck_builderClass)
    {
        if (Deck_builderClass->objectName().isEmpty())
            Deck_builderClass->setObjectName(QStringLiteral("Deck_builderClass"));
        Deck_builderClass->setEnabled(true);
        Deck_builderClass->resize(1920, 1080);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Deck_builderClass->sizePolicy().hasHeightForWidth());
        Deck_builderClass->setSizePolicy(sizePolicy);
        Deck_builderClass->setMinimumSize(QSize(1920, 1080));
        Deck_builderClass->setMaximumSize(QSize(1920, 1080));
        openButton = new QAction(Deck_builderClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        saveButton = new QAction(Deck_builderClass);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        actiontest = new QAction(Deck_builderClass);
        actiontest->setObjectName(QStringLiteral("actiontest"));
        centralWidget = new QWidget(Deck_builderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        proposalsBox = new QGroupBox(centralWidget);
        proposalsBox->setObjectName(QStringLiteral("proposalsBox"));
        proposalsBox->setGeometry(QRect(0, 0, 1920, 440));
        sizePolicy.setHeightForWidth(proposalsBox->sizePolicy().hasHeightForWidth());
        proposalsBox->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(18);
        proposalsBox->setFont(font);
        proposalsBox->setAutoFillBackground(true);
        proposalsArea = new QScrollArea(proposalsBox);
        proposalsArea->setObjectName(QStringLiteral("proposalsArea"));
        proposalsArea->setGeometry(QRect(0, 50, 1920, 390));
        sizePolicy.setHeightForWidth(proposalsArea->sizePolicy().hasHeightForWidth());
        proposalsArea->setSizePolicy(sizePolicy);
        proposalsArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        proposalsArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        proposalsArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1918, 367));
        proposalsArea->setWidget(scrollAreaWidgetContents);
        deckBox = new QGroupBox(centralWidget);
        deckBox->setObjectName(QStringLiteral("deckBox"));
        deckBox->setGeometry(QRect(0, 436, 1920, 614));
        deckBox->setFont(font);
        deckBox->setAutoFillBackground(true);
        deckArea = new QScrollArea(deckBox);
        deckArea->setObjectName(QStringLiteral("deckArea"));
        deckArea->setGeometry(QRect(0, 50, 1920, 564));
        deckArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        deckArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        deckArea->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 1897, 562));
        deckArea->setWidget(scrollAreaWidgetContents_2);
        Deck_builderClass->setCentralWidget(centralWidget);

        retranslateUi(Deck_builderClass);

        QMetaObject::connectSlotsByName(Deck_builderClass);
    } // setupUi

    void retranslateUi(QMainWindow *Deck_builderClass)
    {
        Deck_builderClass->setWindowTitle(QApplication::translate("Deck_builderClass", "Deck_builder", nullptr));
        openButton->setText(QApplication::translate("Deck_builderClass", "Ouvrir deck", nullptr));
        saveButton->setText(QApplication::translate("Deck_builderClass", "Sauvegarder deck", nullptr));
        actiontest->setText(QApplication::translate("Deck_builderClass", "test", nullptr));
        proposalsBox->setTitle(QApplication::translate("Deck_builderClass", "Propositions", nullptr));
        deckBox->setTitle(QApplication::translate("Deck_builderClass", "Deck", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Deck_builderClass: public Ui_Deck_builderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECK_BUILDER_H
