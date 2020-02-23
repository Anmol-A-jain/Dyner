#include "edittablenoanddiscount.h"
#include "ui_edittablenoanddiscount.h"
#include "data/xmlmanipulation.h"
#include "data/globaldata.h"

EditTableNoAndDiscount::EditTableNoAndDiscount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditTableNoAndDiscount)
{
    ui->setupUi(this);
    GlobalData g;
    ui->txtTableNo->setValue(XmlManipulation::getData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable) ).toInt() );
    ui->txtDicount->setValue(XmlManipulation::getData(g.getTagName(g.Discount),g.getattribute(g.Discount)).toDouble() );
    ui->txtTax->setValue(XmlManipulation::getData(g.getTagName(g.Tax),g.getattribute(g.Tax)).toDouble() );
}

EditTableNoAndDiscount::~EditTableNoAndDiscount()
{
    delete ui;
}

void EditTableNoAndDiscount::on_buttonBox_accepted()
{
    GlobalData g;
    XmlManipulation::setData(g.getTagName(g.QtyTable),g.getattribute(g.QtyTable),ui->txtTableNo->text());
    XmlManipulation::setData(g.getTagName(g.Discount),g.getattribute(g.Discount),ui->txtDicount->text());
    XmlManipulation::setData(g.getTagName(g.Tax),g.getattribute(g.Tax),ui->txtTax->text());
}
