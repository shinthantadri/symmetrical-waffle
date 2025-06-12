#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define low_threshold_amount 50

// Product struct
typedef struct // Using typedef allows user to create products without using struct keyword everytime
{
  char productID[10];
  char name[50];
  char categoryID[10];
  float price;
  int quantity;
  char supplierID[10];
} Product;

void printWelcomeMessage()
{
  printf("\n");
  printf("******************************************************\n");
  printf("*                                                    *\n");
  printf("*        W E L C O M E   T O   T H E                 *\n");
  printf("*                                                    *\n");
  printf("*          A P U   R E T A I L   S T O R E           *\n");
  printf("*                                                    *\n");
  printf("******************************************************\n");
  printf("\n");
}

void product_management();
void stock_management();
void category_supplier_management();

int main()
{
  int main_menu_option;

  do
  {

    printWelcomeMessage();
    printf("1. Product Management\n2. Inventory and Stock Management\n3. Category and Supplier Management\n4. User and Trasaction Management\n5. Exit\n");

    printf("Please select an option: ");
    scanf("%d", &main_menu_option);
    while(getchar() !='\n');

    switch (main_menu_option)
    {
    case 1:
      product_management();
      break;

    case 2:
      stock_management();
      break;

    case 3:
      category_supplier_management();
      break;

    case 4:
      printf("User and Transaction Management selected.\n");
      break;

    case 5:
      printf("Exiting the program. Goodbye!\n");
      return 0;

    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  } while (main_menu_option != 5);

  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PRODUCT MANAGEMENT SECTION

void addProduct();
void viewProducts();
void deleteProduct();
void updateProduct();

void product_management()
{
  int product_option;

  do
  {
    printf("Product Management selected.\n1. Add Product\n2. Update Product\n3. Delete Product\n4. View Products\n5. Back to Main Menu\nWhat would you like to do?: ");
    scanf("%d", &product_option);

    switch (product_option)
    {
    case 1:
      addProduct();
      break;

    case 2:
      updateProduct();
      break;

    case 3:
      deleteProduct();
      break;

    case 4:
      viewProducts();
      break;

    case 5:
      printf("Returning to Main Menu...\n");
      break;

    default:
      printf("Invalid option. Please try again.\n");
      break;
    }
  } while (product_option != 5);
}

// char findProduct()
// {
//   // return product ID if found, return "000" if not found
// }

// addProduct function
void addProduct()
{
  Product newProduct;

  printf("Enter product id: ");
  scanf(" %s", newProduct.productID);

  printf("Enter product name (Please do not use spaces as the system is not designed for it, use _ instead): ");
  scanf(" %s", newProduct.name);

  printf("Enter quantity: ");
  scanf("%d", &newProduct.quantity);

  printf("Enter categoryID: ");
  scanf(" %s", newProduct.categoryID);

  printf("Enter supplierID: ");
  scanf(" %s", newProduct.supplierID);

  printf("Enter product price: ");
  scanf("%f", &newProduct.price);

  // open the products.txt file and add the product
  FILE *file = fopen("products.txt", "a");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%s,%s,%s,%.2f,%d,%s\n", newProduct.productID, newProduct.name, newProduct.categoryID, newProduct.price, newProduct.quantity, newProduct.supplierID);
  printf("Product added successfully.\n");
  fclose(file);
}

// deleteProduct function
void deleteProduct()
{
  char productIDToDelete[10];
  bool found = false;

  printf("Enter the id of product you want to delete: ");
  scanf(" %s", productIDToDelete);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w"); // temporary file to store the data without the deleted product

  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    char current_id[10];
    sscanf(line, "%[^,]", current_id);

    // 1. Check if the product exist
    if (strcmp(productIDToDelete, current_id) == 0)
    {
      found = true;
      continue;
    }

    fputs(line, temp);
  }

  fclose(temp);
  fclose(file);

  // if found, delete original and rename tempfile. if not found, delete tempfile.
  if (found)
  {
    remove("products.txt");
    rename("temp.txt", "products.txt");

    printf("The product with id %s has been successfully deleted!\n", productIDToDelete);
  }
  else
  {
    remove("temp.txt");
    printf("The product ID does not exist. Please try again");
  }
}

// updateProduct function
void updateProduct()
{
  char productIDToUpdate[10];
  bool found = false;

  printf("Enter the ID of the product you want to update: ");
  scanf(" %s", productIDToUpdate);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file,\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w");

  Product product;
  char line[256];

  while (fgets(line, sizeof(line), file))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%s", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID);

    if (strcmp(productIDToUpdate, product.productID) == 0)
    {
      found = true;

      int choice;
      printf("1. Product ID\n2. Name\n3. CategoryID\n4. Price\n5. Quantity\n6. SupplierID\n7. Exit to Menu\nPlease enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
        printf("Enter the new ID: ");
        scanf(" %s", product.productID);
        break;
      case 2:
        printf("Enter the new name: ");
        scanf(" %s", product.name);
        break;
      case 3:
        printf("Enter the new category ID: ");
        scanf(" %s", product.categoryID);
        break;
      case 4:
        printf("Enter the new price: ");
        scanf("%f", &product.price);
        break;
      case 5:
        printf("Enter new quantity ");
        scanf("%d", &product.quantity);
        break;
      case 6:
        printf("Enter the new supplier ID: ");
        scanf(" %s", product.supplierID);
        break;
      case 7:
        printf("Exiting to Menu...");
        return;
      }

      fprintf(temp, "%s,%s,%s,%.2f,%d,%s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID);
      continue;
    }
    fputs(line, temp);
  }

  fclose(file);
  fclose(temp);

  if (found)
  {
    remove("products.txt");
    rename("temp.txt", "products.txt");
    printf("--------------The product has been successfully updated!-------------\n");
  }
  else
  {
    remove("temp.txt");
    printf("Error: The product ID does not exist. Please try again.\n");
  }
}

// viewProducts function
void viewProducts()
{
  Product product;
  char line[256];

  FILE *file = fopen("products.txt", "r");

  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("| %-8s | %-20s | %-10s | %-8s | %-8s | %-10s |\n",
         "ItemID", "Name", "CategoryID", "Price", "Stock", "SupplierID");
  printf("------------------------------------------------------------------------------------------\n");

  while (fscanf(file, "%[^,],%[^,],%[^,],%f,%d,%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID) != EOF)
  // scan line by line and assigne to each varaible each loop until end of file is reached which then it will exit the loop
  {
    printf("| %-8s | %-20s | %-10s | %8.2f | %-8d | %-10s |\n",
           product.productID,
           product.name,
           product.categoryID,
           product.price,
           product.quantity,
           product.supplierID);
  }
  printf("------------------------------------------------------------------------------------------\n");

  fclose(file);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
// STOCK MANAGEMENT SYSTEM
// We will keep using products.txt since it includes the current stock amount. No need to create a seperate file.

// defining callback type for stock operations
typedef void (*StockCallback)(Product *product, void *data, bool *modified);

void processStockFile(const char *filename, StockCallback callback, void *data)
{
  FILE *productFile = fopen(filename, "r");
  FILE *tempFile = fopen("temp.txt", "w");

  if (productFile == NULL || tempFile == NULL)
  {
    printf("Error opening file. Please try again.\n");
    return;
  }

  char line[256];
  bool modified = false;

  while (fgets(line, sizeof(line), productFile))
  {
    Product product;
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID);

    // call the callback to perform desired stock operations
    callback(&product, data, &modified);

    if (modified)
    {
      // write the modified product to temp file
      fprintf(tempFile, "%s,%s,%s,%.2f,%d,%s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID);
    }
    else
    {
      fputs(line, tempFile);
    }
  }

  fclose(productFile);
  fclose(tempFile);

  remove(filename);
  rename("temp.txt", filename);

  if (!modified)
  {
    printf("Process cancelled (Product NOT EXIST or User cancelled). No changes were made. Please try again.\n");
  }
}

void addStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Enter the amount of stock to add: ");
    scanf("%d", &amount);

    product->quantity += amount;
    *modified = true;

    printf("-----------------------Stock successfully updated for product %s-----------------------\n", product->productID);
  }
}

void addStock()
{
  char productID[10];
  printf("Enter the ID of the product to add stock: ");
  scanf(" %s", productID);

  processStockFile("products.txt", addStockCallback, productID);
}

void deleteStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;
  char choice;

  if (strcmp(productID, product->productID) == 0)
  {
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Do you want to set it to 0? (y/n): ");
    scanf(" %s", &choice);

    if (choice == 'y')
    {
      product->quantity = 0;
      *modified = true;

      printf("-----------------------Stock successfully removed for product %s-----------------------\n", product->productID);
    }
    else if (choice == 'n')
    {
      return;
    }
    else
    {
      printf("Invalid option.\n Please try again\n");
    }
  }
}

void deleteStock()
{
  char productID[10];
  printf("Enter the ID of the product to remove stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", deleteStockCallback, productID);
}

void updateStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);
    printf("Enter the amount of stock to update: ");
    scanf("%d", &amount);

    product->quantity = amount;
    *modified = true;

    printf("-----------------------Stock successfully updated for product %s-----------------------\n", product->productID);
  }
}

void updateStock()
{
  char productID[10];
  printf("Enter the ID of the product to update stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", updateStockCallback, productID);
}

void removeStockCallback(Product *product, void *data, bool *modified)
{
  char *productID = (char *)data;

  if (strcmp(productID, product->productID) == 0)
  {
    int amount = product->quantity + 1;
    printf("The current stock of product(%s) with ID %s is %d\n", product->name, product->productID, product->quantity);

    while (amount > product->quantity)
    {
      printf("Enter the amount of stock to remove: ");
      scanf("%d", &amount);
    }

    product->quantity -= amount;
    *modified = true;

    printf("-----------------------Stock successfully removed for product %s-----------------------\n", product->productID);
  }
}

void removeStock()
{
  char productID[10];
  printf("Enter the ID of the product to remove stock: ");
  scanf(" %s", productID);
  processStockFile("products.txt", removeStockCallback, productID);
}

void alertStock()
{
  printf("These are the products that are low on amount (<=%d).\n", low_threshold_amount);
  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;

  // Table Header
  printf("--------------------------------------------\n");
  printf("| %-10s | %-20s | %-8s |\n", "ProductID", "Product Name", "Quantity");
  printf("--------------------------------------------\n");

  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID);
    if (product.quantity <= low_threshold_amount)
    {
      printf("| %-10s | %-20s | %-8d |\n", product.productID, product.name, product.quantity);
    }
  }
  printf("---------------------------------------------\n");
  fclose(productFile);
}

void customThreshold();

void generateInventoryReport()
{
  // Table Header
  printf("------------------------------------------------------------------------------------------\n");
  printf("%-10s | %-15s | %-10s\n", "ProductID", "Product_Name", "Current Stock");
  printf("------------------------------------------------------------------------------------------\n");

  FILE *productFile = fopen("products.txt", "r");

  if (productFile == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  char line[256];
  Product product;
  while (fgets(line, sizeof(line), productFile))
  {
    sscanf(line, "%[^,],%[^,],%[^,],%f,%d,%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID);
    printf("| %-10s | %-15s | %-10d |\n", product.productID, product.name, product.quantity);
  }
  printf("--------------------------------------------------------------------------------------\n");
  fclose(productFile);
}

void stock_management()
{
  int stock_choice;
  do
  {
    printf("Stock management selected.\n");
    printf("1. Add stock\n2. Remove stock\n3. Update stock\n4. delete stock(set it to 0)\n5. Alert low stock products\n6. Custom threshold Management\n7. Inventory Report\n8. Exit to main menu\n Please enter your choice: ");
    scanf("%d", &stock_choice);

    switch (stock_choice)
    {
    case 1:
      addStock();
      break;

    case 2:
      removeStock();
      break;

    case 3:
      updateStock();
      break;

    case 4:
      deleteStock();
      break;

    case 5:
      alertStock();
      break;

      // case 6:
      //   customThreshold();
      //   break;

    case 7:
      generateInventoryReport();
      break;

    case 8:
      printf("Returning to the main menu...");
      break;

    default:
      printf("Invalid option. Please try again.");
      break;
    }
  } while (stock_choice != 8);
}
// role 3 category and supplier
typedef struct {
  char categoryID[5];
  char categoryName[50];
} Category;
typedef struct{
  char supplierID[5];
  char suppliername[50];
  char contact[50];
} Supplier;
void addcategory();
void viewcategories();
void updatecategory();
void deletecategory();
void addsupplier();
void viewsupplier();
void updatesupplier();
void deletesupplier();

void category_supplier_management(){
  int choice;
  do{
    printf("\nCategory and Supplier Management\n");
    printf("1.Add Category\n2.View Categories\n3.Update Category\n4.Delete Category\n");
    printf("5.Add Supplier\n6.View Suppliers\n7.Update Supplier\n8.Delete Supplier\n9.Back to main manu\n");
    printf("Choose your option: ");
    scanf("%d",&choice);

    switch (choice){
      case 1: addcategory();break;
      case 2: viewcategories();break;
      case 3: updatecategory();break;
      case 4: deletecategory();break;
      case 5: addsupplier();break;
      case 6: viewsupplier();break;
      case 7: updatesupplier();break;
      case 8: deletesupplier();break;
      case 9: printf("Returning to main menu...\n");break;
      default: printf("Invalid option,please try again!\n");
    }
  }while (choice!=9);
}

void addcategory(){
  Category ct;
  printf("Enter Category ID: ");
  scanf("%s",ct.categoryID);
  printf("Enter Category Name: ");
  scanf("%s",ct.categoryName);

  FILE *c= fopen("category.txt","a");
  if(!c){
    printf("Unable to open the file!\n");
    return;
  }
  fprintf(c, "%s,%s\n",ct.categoryID,ct.categoryName);
  fclose(c);
  printf("Category added succesfully!\n");
}

void viewcategories(){
  Category ct;
  char line[100];
  FILE *c= fopen("category.txt","r");
  if(!c){
    printf("Unable to open this file!\n");
    return;
  }
  printf("-------- Category List --------\n");
  printf("%-10s | %-20s\n", "ID", "Name");
  printf("-------------------------------\n");
 while (fgets(line,sizeof(line),c)){
   sscanf(line, "%[^,],%s",ct.categoryID,ct.categoryName);
   printf("%-10s | %-20s\n",ct.categoryID,ct.categoryName);
 }fclose(c);
  printf("\nPress Enter to return to the menu...");
  getchar();
  getchar();
}

void deletecategory(){
  char id[5],line[100],currentid[10];
  int found = 0;
  printf("Enter category ID to delete: ");
  scanf("%s",id);

  FILE *c=fopen("category.txt","r");
  FILE *temp= fopen("temp.txt","w");

  if(!c||!temp){
    printf("File error\n");
    return;
  }
  while (fgets(line, sizeof(line),c)){
    sscanf(line, "%[^,]", currentid);
    if(strcmp(id, currentid)==0){
      found=1;
      continue;
    }fputs(line, temp);
  } fclose(c);
  fclose(temp);
  if (found){
    remove("category.txt");
    rename("temp.txt","category.txt");
    printf("Category deleted succesfully!\n");
  } else{
    remove("temp.txt");
    printf("Category was not found!\n");
  }
}

void updatecategory(){
  char id[5], newname[50], line[100];
  int found=0;
  Category ct;

  printf("Enter Category ID to update: ");
  scanf(" %s", id);

  FILE *c =fopen("category.txt","r");
  FILE *temp=fopen("temp.txt","w");

  if(!c || !temp){
    printf("file error\n");
    return;
  }
  while (fgets(line, sizeof(line), c)){
    sscanf(line, "%[^,],%s", ct.categoryID,ct.categoryName);
    if(strcmp(id, ct.categoryID)==0){
      printf("Enter new Category Name: ");
      scanf("%s", &newname);
      fprintf(temp, "%s,%s\n",ct.categoryID, newname);
      found=1;
    }else{
      fputs(line, temp);
    }
  } 
  fclose(c);
  fclose(temp);

  if(found){
    remove("category.txt");
    rename("temp.txt","category.txt");
    printf("Category updated succesfully");
  } else {
    remove("temp.txt");
    printf("Category ID not found!\n");
  }
}

void addsupplier(){
Supplier s;
printf("Enter Supplier ID : ");
scanf(" %s", s.supplierID);
printf("Enter Supplier Name : ");
scanf(" %s", s.suppliername);
printf("Enter the contact number: ");
scanf(" %s", s.contact);

FILE *sp=fopen("supplier.txt","a");
if(!sp){
  printf("Error open file!\n");
  return;
}
fprintf(sp, "%s,%s,%s\n", s.supplierID, s.suppliername, s.contact);
fclose(sp);
printf("Supplier added succesfully");
}

void viewsupplier(){
  Supplier s;
  char line[100];
  FILE *sp=fopen("supplier.txt","r");
  if(!sp){
    printf("Error open file\n");
    return;
  }
 printf("-------- Supplier List --------\n");
 printf("%-10s | %-20s | %-30s\n", "ID", "Name", "Contact");
 printf("--------------------------------------------------------------\n");

 while(fgets(line,sizeof(line),sp)){
  sscanf(line, "%[^,],%[^,],%s", s.supplierID, s.suppliername, s.contact);
  printf("%-10s | %-20s | %-30s\n", s.supplierID, s.suppliername, s.contact);
 }
 fclose(sp);
 printf("Press enter to return menu....");
 getchar();
 getchar();
}

void deletesupplier(){
  char id[10], line[100], currentID[10];
  int found=0;
  printf("Enter the Supplier ID to delete: ");
  scanf(" %s", id);
  
  FILE *sp=fopen("supplier.txt","r");
  FILE *temp=fopen("temp.txt","w");

  if(!sp || !temp){
    printf("Error open file!");
    return;
  }
  while (fgets(line, sizeof(line), sp)){
    sscanf(line, "%[^,]", currentID);
    if(strcmp(id, currentID)==0){
      found=1;
      continue;
    } fputs(line, temp);
  } 
  fclose(sp);
  fclose(temp);
  if(found){
    remove("supplier.txt");
    rename("temp.txt","supplier.txt");
    printf("Supplier deleted successfully\n");
  } else {
    remove("temp.txt");
    printf("Supplier not found!");
  }
}

void updatesupplier(){
  char id[10], newspname[50], newcontact[50], line[100];
  int found=0;
  Supplier s;
  
  printf("Enter Supplier id to update: ");
  scanf(" %s", id);

  FILE *sp=fopen("supplier.txt","r");
  FILE *temp=fopen("temp.txt","w");

  if(!sp || !temp){
    printf("Error to open the file\n");
    return;
  }
  while (fgets(line, sizeof(line), sp)){
    sscanf(line, "%[^,],%[^,], %s", s.supplierID, s.suppliername, s.contact);
    if (strcmp(id, s.supplierID)==0){
      printf("Enter new supplier name: ");
      scanf(" %s", newspname);
      printf("Enter new supplier contct: ");
      scanf(" %s", newcontact);
      fprintf(temp, "%s,%s,%s\n", s.supplierID, newspname, newcontact);
      found=1;
    } else {
      fputs(line,temp);
    }
  } 

  fclose(sp);
  fclose(temp);

  if (found){
    remove("supplier.txt");
    rename("temp.txt","supplier.txt");
    printf("Supplier update succesfully");
  } else{
    remove("temp.txt");
    printf("Supplier ID not found!\n");
  }
}


