#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "additemdialog.h"
#include "updateitemdialog.h"

#include <QFile>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->menuNewProduct, &QAction::triggered, this, &MainWindow::handleMenuItemNew);
    connect(ui->btnRemove, &QPushButton::clicked, this, &MainWindow::removeSelectedProduct);
    connect(ui->lstProducts, &QListWidget::itemClicked, this, &MainWindow::handleClick);
    connect(ui->menuEditSelectedProduct, &QAction::triggered, this, &MainWindow::handleMenuItemEdit);
    connect(ui->menuSaveProducts, &QAction::triggered, this, &MainWindow::handleSaveItems);
    connect(ui->menuLoadProducts, &QAction::triggered, this, &MainWindow::handleLoadItems);
}


void MainWindow::handleMenuItemNew() {
    Item* newItem = nullptr;
    AddItemDialog addItemDialog(newItem, nullptr);

    addItemDialog.setModal(true);
    addItemDialog.exec();

    if(newItem != nullptr) {
        this->productList.push_back(newItem);
        ui->lstProducts->addItem(newItem->getName());
    }
}

void MainWindow::removeSelectedProduct() {
    auto index{ ui->lstProducts->currentRow() };
    if(index >= 0) {
       // removing from memory
       auto* toRemove = productList.at(index);
       delete toRemove;
       productList.removeAt(index); // removing dangling pointer;

       // removing from ui
       delete ui->lstProducts->currentItem();
    }
}

void MainWindow::handleClick(QListWidgetItem* item) {
    auto index{ item->listWidget()->currentRow() };

    if(index != -1) {
        Item* currentItem = productList.at(index);
        if(currentItem != nullptr) {
            ui->lblProductName->setText(currentItem->getName());
            ui->lblQuantity->setText(QString::number(currentItem->getQuantity()));

            QPixmap pixmap(currentItem->getFilePath());
            ui->lblImage->setPixmap(pixmap);
            ui->lblImage->setScaledContents(true);
        }
    }
}

void MainWindow::handleMenuItemEdit() {
    auto index = ui->lstProducts->currentRow();

    if(index != -1) {
       Item* currentItem = productList.at(index);

       if(currentItem != nullptr) {
           UpdateItemDialog updateItemDialog(currentItem, nullptr);
           updateItemDialog.exec();

           ui->lblProductName->setText(currentItem->getName());
           ui->lblQuantity->setText(QString::number( currentItem->getQuantity()));

           QPixmap pixmap(currentItem->getFilePath());
           ui->lblImage->setPixmap(pixmap);
           ui->lblImage->setScaledContents(true);
       }
    }

}

void MainWindow::handleSaveItems() {
    QFile outputFile{"products.txt"};
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outputFile);

    for(Item* product : productList) {
        out << product->getName() << ",";
        out << product->getQuantity() << ",";
        out << product->getFilePath() << Qt::endl;
    }

    out.flush();
    outputFile.close();
}

void MainWindow::handleLoadItems() {

}

MainWindow::~MainWindow() {
    delete ui;
}

