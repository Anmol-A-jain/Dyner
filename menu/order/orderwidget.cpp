#include "orderwidget.h"
#include "ui_orderwidget.h"
#include <QDebug>
#include "data/globaldata.h"
#include "data/xmlmanipulation.h"
#include "DialogBox/addorderitem.h"
#include "data/databasecon.h"
#include "DialogBox/paymentmathod.h"
#include "DialogBox/statusdialogbox.h"
#include <QMessageBox>
#include "dyner.h"


OrderWidget::OrderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderWidget)
{
    ui->setupUi(this);
    this->myParent = parent;

    ui-> lblTblNo->hide();
    ui->cmbTblNo->hide();
    r1 = new QRegExpValidator(QRegExp("[0-9]*"), ui->txtMblNo);
    r2 = new QRegExpValidator(QRegExp("[A-Za-z ]*"), ui->txtMblNo);
    ui->txtMblNo->setValidator(r1);
    ui->txtCustName->setValidator(r2);

    GlobalData g;
    int totalTable = XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable)).toInt();

    QString attribute = g.getattribute(GlobalData::customerNameMblNo);
    QStringList list = attribute.split("-");
    QString name = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(1));
    QString mbl = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(0));

    ui->txtCustName->setText(name);
    ui->txtMblNo->setText(mbl);

    for (int i = 1 ; i <= totalTable ; ++i )
    {
        ui->cmbTblNo->addItem(QString::number(i));
    }

    ui->txtDiscount->setText(XmlManipulation::getData(g.getTagName(g.Discount),g.getattribute(g.Discount)));
    ui->taxValue->setText(XmlManipulation::getData(g.getTagName(g.Tax),g.getattribute(g.Tax)));
    this->loadData();
    ui->txtMblNo->setFocus();
    GlobalData::setShadow(ui->txtMblNo);
    GlobalData::setShadow(ui->txtCustName);
    GlobalData::setShadow(ui->btnAddOrder);
    GlobalData::setShadow(ui->btnClear);
    GlobalData::setShadow(ui->btnPlaceOrder);
    GlobalData::setShadow(ui->cmbTblNo);
    GlobalData::setShadow(ui->cmbOrrderType);
    GlobalData::setShadow(ui->txtTotalAmount);

}

OrderWidget::~OrderWidget()
{
    delete r1;
    delete r2;
    delete ui;
}

int OrderWidget::getTblNo()
{
    if(this->getOrderTypeIndex() == 1)
    {
        qDebug() << "orderwidget.cpp (getTblNo ) : index : " << ui->cmbTblNo->currentText().toInt();
        return ui->cmbTblNo->currentText().toInt();
    }
    else
    {
        return 0;
    }
}

void OrderWidget::loadData()
{
    this->deleterVecterData();
    databaseCon d;
    QString cmd = "SELECT a.*, b.itemName , b.Price , b.category FROM tblTempOrder a LEFT JOIN mstTblMenu b ON a.item_id = b.id;" ;
    QSqlQuery* q = d.execute(cmd);

    int tblNo = this->getTblNo();

    while (q->next())
    {
        if(q->value(0).toInt() == tblNo )
        {
            QString id = q->value(1).toString();
            double qty = q->value(2).toDouble();
            QString name = q->value(3).toString();
            double price = q->value(4).toDouble();
            QString category = q->value(5).toString();

            displayWidget* itemData = new displayWidget(id,name,category,qty,price,tblNo,this);
            ui->displayOrderRow->addWidget(itemData);
            list.push_back(itemData);
        }
    }
    this->updateTotalAmmount();

    for (int i = 0; i < list.count(); ++i) {
       list[i]->setFlag(true);
    }
}

void OrderWidget::deleterVecterData()
{
    for (int i = 0; i < list.count(); ++i)
    {
        delete list[i];
    }
    list.clear();
}

void OrderWidget::deleteCustomerData()
{
    ui->txtMblNo->clear();
    ui->txtCustName->clear();
}

void OrderWidget::resetTotalAmount()
{
    ui->txtAmount->clear();
    ui->txtDiscount->clear();
    ui->taxValue->clear();
    ui->txtTotalAmount->clear();
}

void OrderWidget::updateTotalAmmount()
{
    double amount = 0;
    for (int i = 0; i < list.count(); ++i)
    {

        qDebug() << "orderwidget.cpp (updateTotalAmmount ) :  Updated total amount : " << list[i]->getTotal() ;
        amount += list[i]->getTotal();
    }

    ui->txtAmount->setText(QString::number(amount));

    double discount = ui->txtDiscount->text().toDouble();

    double discountValue = (amount * discount) / 100;

    amount -= discountValue;

    double taxValue = ui->taxValue->text().toDouble();
    double tax = (amount * taxValue) / 100;

    ui->taxValue->setText(QString::number(tax));
    double totalAmount = tax + amount;
    ui->txtTotalAmount->setText(QString::number(totalAmount));

    qDebug() << "orderwidget.cpp (updateTotalAmmount ) :  Updated total amount : " << totalAmount ;
}

int OrderWidget::getOrderTypeIndex()
{
    return ui->cmbOrrderType->currentIndex();
}

void OrderWidget::sendToDataKitchen(qint16 orderNo, qint16 tblNo, QString name)
{
    static_cast<Dyner*>(myParent)->sendToDataKitchen(orderNo,tblNo,name);
}

void OrderWidget::on_cmbOrrderType_currentIndexChanged(int index)
{
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : index : " << index;
    switch (index)
    {
        case 0:
        {
            // self pick up
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->hide();
            ui->cmbTblNo->hide();

            GlobalData g;
            QString attribute = g.getattribute(GlobalData::customerNameMblNo);
            QStringList list = attribute.split("-");
            QString name = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(1));
            QString mbl = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(0));

            ui->txtCustName->setText(name);
            ui->txtMblNo->setText(mbl);

            break;
        }
        case 1:
        {
            // Table no
            qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentIndexChanged ) : switch  case 0 : pickup selected ";

            ui-> lblTblNo->show();
            ui->cmbTblNo->show();

            GlobalData g;
            QString attribute = g.getattribute(GlobalData::customerNameMblNo);
            QStringList list = attribute.split("-");
            QString name = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(1));
            QString mbl = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(0));

            ui->txtCustName->setText(name);
            ui->txtMblNo->setText(mbl);

            break;
        }
    }
}


void OrderWidget::on_cmbTblNo_currentTextChanged(const QString &arg1)
{
    qDebug() << "orderwidget.cpp (on_cmbTblNo_currentTextChanged) : cmbTblNo changed : " << arg1 ;
    this->deleterVecterData();
    this->loadData();
    if(!ui->cmbTblNo->isHidden())
    {
        GlobalData g;
        QString attribute = g.getattribute(GlobalData::customerNameMblNo);
        QStringList list = attribute.split("-");
        QString name = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(1));
        QString mbl = XmlManipulation::getData(g.getTagName(g.customerNameMblNo)+QString::number(getTblNo()),list.at(0));

        ui->txtCustName->setText(name);
        ui->txtMblNo->setText(mbl);
    }
}

void OrderWidget::on_cmbOrrderType_currentTextChanged(const QString &arg1)
{
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentTextChanged) : cmbTblNo changed : " << arg1 ;
    this->deleterVecterData();
    this->loadData();
}

void OrderWidget::on_btnPlaceOrder_clicked()
{
    if(!list.count())
    {
        QMessageBox::information(this,"Information","Cart Is Empty");
        ui->txtMblNo->setFocus();
        return;
    }

    QString custNo = ui->txtMblNo->text();
    QString custName = ui->txtCustName->text();

    if(custNo == "")
    {
        QMessageBox::critical(this,"Information","Please enter Customer Phone Number");
        ui->txtMblNo->setFocus();
    }
    else if(custName == "")
    {
        QMessageBox::critical(this,"Information","Please enter both Customer Name");
        ui->txtCustName->setFocus();
    }
    else if(custNo.count() != 10)
    {
        QMessageBox::critical(this,"Information","Please enter 10 Digit Mobile Number ");
        ui->txtMblNo->setFocus();
    }
    else
    {
        QString orderType = ui->cmbOrrderType->currentText();
        double netAmt = ui->txtTotalAmount->text().toDouble();
        double discount = ui->txtDiscount->text().toDouble();
        double tax = ui->taxValue->text().toDouble();

        paymentMathod* p = new paymentMathod(netAmt,discount,tax,this->getTblNo(),custNo,orderType,custName,this->list,this);
        p->exec();
    }
}

void OrderWidget::on_btnAddOrder_clicked()
{
    AddOrderItem aoi(this);
    aoi.exec();
}

void OrderWidget::on_btnClear_clicked()
{
    if(!list.count())
    {
        QMessageBox::critical(this,"Information","Cart Is Empty! : (");
        return;
    }
    QMessageBox::StandardButton reply;
    reply = QMessageBox::critical(this,"Information","Do you Want to Clear Cart",QMessageBox::Yes|QMessageBox::No,QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        databaseCon d;
        QString cmd = "DELETE FROM tblTempOrder WHERE table_no = "+QString::number(this->getTblNo())+";" ;
        delete d.execute(cmd);
        this->deleterVecterData();
    }
    GlobalData g;
    QString attribute = g.getattribute(GlobalData::customerNameMblNo);
    QStringList list = attribute.split("-");

    XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(getTblNo()),list.at(0),"");
    XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(getTblNo()),list.at(1),"");
}

void OrderWidget::on_txtMblNo_textChanged(const QString &arg1)
{
    GlobalData g;
    QString attribute = g.getattribute(GlobalData::customerNameMblNo);
    QStringList list = attribute.split("-");

    XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(getTblNo()),list.at(0),arg1);
    qDebug() << "orderwidget.cpp (on_cmbOrrderType_currentTextChanged) : MblNo changed : " << arg1 ;
}

void OrderWidget::on_txtCustName_textChanged(const QString &arg1)
{
    GlobalData g;
    QString attribute = g.getattribute(GlobalData::customerNameMblNo);
    QStringList list = attribute.split("-");

    XmlManipulation::setData(g.getTagName(GlobalData::customerNameMblNo)+QString::number(getTblNo()),list.at(1),arg1);
    qDebug() << "orderwidget.cpp (on_txtCustName_textChanged) : name changed : " << arg1 ;
}

void OrderWidget::on_btnStatus_clicked()
{
    StatusDialogBox s(getTblNo(),this);
    s.exec();
}
