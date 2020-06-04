#ifndef ALLACTION_H
#define ALLACTION_H

class ALLAction
{
public:
    ALLAction();
    enum androidAction{error,getTotaltableNo,menuData,getCustInfo,cartData,showNotification};
    enum kitchen{kitchenInfo = 101,individual = 102,deleteOrder = 103,loginKitchen = 104,notification = 105};
};

#endif // ALLACTION_H
