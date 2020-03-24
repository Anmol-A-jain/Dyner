dyner()
{
    //GUI Components
    {
        home("menubuttons.cpp")
        {
            // contains buttons to 
            //open other menu option
        }
        order("orderwidget.cpp")
        {
            
        }
        BillRequest("billreqwidget.cpp")
        {
            
        }
        BillHistory("billhistorywidget.cpp")
        {
            
        }
        Admin("adminwidget.cpp")
        {
            //Dialog Box
            {
                addItem("additem.cpp")
                {
                    // add items to Databse
                }   
                editCategory("editcategory.cpp")
                {
                    //perform insert update delete 
                    //on tblCategory for Database
                }
                edittablenoanddiscount("edittablenoanddiscount.cpp")
                {
                    //edit table qty and discount 
                    //value and save it to init.xml
                }
            }

            // widgets
            {       
                itemwidget("itemwidget.cpp")
                {
                    //contains data of tblMenu
                    
                    //Dialog Box       
                    {
                        edititem("edititem.cpp")
                        {
                            //edit data of tblMenu
                        }
                    }
                }
            }
        }   
    }

    //CLI Components
    {
        databasecon("databasecon.cpp")
        {
            //provide easy interface 
            //between databse and application
        }
        globaldata("globaldata.cpp")
        {
            //contains global 
            //data for application
        }
        xmlmanipulation("xmlmanipulation.cpp")
        {
            //provide easy interface 
            //between xml and application
        }
        dynerserver("dynerserver.cpp")
        {
            //creates multi 
            //threaded TCP/IP server
        }
        mytcpsocket("mytcpsocket.cpp")
        {
            //get connect with client
            //TCP/IP socket
        }
    }
}