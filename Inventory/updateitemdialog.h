#ifndef UPDATEITEMDIALOG_H
#define UPDATEITEMDIALOG_H

#include <QDialog>
#include "item.h"

namespace Ui {
class UpdateItemDialog;
}

class UpdateItemDialog : public QDialog {
    Q_OBJECT

public:
    explicit UpdateItemDialog(Item* currentItem, QWidget *parent = nullptr);
    ~UpdateItemDialog();

    void confirmUpdate();
    void loadItemImage();

private:
    Ui::UpdateItemDialog *ui;
    Item* currentItem;
    QString filePath;
};

#endif // UPDATEITEMDIALOG_H
