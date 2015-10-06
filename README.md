# Shop

The course " Perspectiva XXI cent." C ++ for professionals.
Graduate work "Shop" - console project.

The Shop is designed to work with various categories of products, which differ in their parameters. Categories of products exported from a dynamic link library.
The program works with two categories of products: alive and tools.
These products are inherited from the base class Products.
The category of new product can always be added  - necessary to include the DLL file in the folder with the program (.exe).
When the program starts, Shop in the current folder finds  the libraries categories of product (.dll), if such files are found - unloads them to work with them.
Shop unloads balance, last state for each product category: the number of products, the name, price, etc. (files .db).
Balance allows you to buy products from a supplier if there is enough money in the account Shop, or sell it to the buyer the necessary amount.
Current balance can change - necessary to enter the correct password.
When you exit the program the current state of the Shop will be saved (files .db).

AliveDLL - DYNAMIC LIBRARY (DLL), which exports the class alive
ToolsDLL - DYNAMIC LIBRARY (DLL), which exports a class tools
Library - folder, which contains the base classes from which the class inherits alive and tools
Shop - the main program, which works with unloaded libraries.
Method refresh scans the current directory to search for new DLL, if the DLL was be found - Shop unloads them for further work.
The Files with extension “.dll”, “.db” should be in a folder with the .exe.
