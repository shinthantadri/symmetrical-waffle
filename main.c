#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int main()
{
  int main_menu_option;

  do
  {

    printWelcomeMessage();
    printf("1. Product Management\n2. Inventory and Stock Management\n3. Category and Supplier Management\n4. User and Trasaction Management\n5. Exit\n");

    printf("Please select an option: ");
    scanf("%d", &main_menu_option);

    switch (main_menu_option)
    {
    case 1:
      product_management();
      break;

      // case 2:
      //   inventory_management();
      //   break;

    case 3:
      printf("Category and Supplier Management selected.\n");
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

// JUST AN IDEA --- helper functions
// char findProduct()
// {
//   // return product ID if found, return "000" if not found
// }

// addProduct function
void addProduct()
{
  int stock_quantity;
  char product_id[10], product_name[50], categoryID[20], supplier_ID[20];
  float product_price;

  printf("Enter product id: ");
  scanf(" %s", product_id);

  printf("Enter product name: ");
  scanf(" %s", product_name);

  printf("Enter quantity: ");
  scanf("%d", &stock_quantity);

  printf("Enter categoryID: ");
  scanf(" %s", categoryID);

  printf("Enter supplierID: ");
  scanf(" %s", supplier_ID);

  printf("Enter product price: ");
  scanf("%f", &product_price);

  // open the products.txt file and add the product
  FILE *file = fopen("products.txt", "a");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  fprintf(file, "%s,%s,%d,%s,%s,%.2f\n", product_id, product_name, stock_quantity, categoryID, supplier_ID, product_price);
  printf("Product added successfully.\n");
  fclose(file);
}

// deleteProduct function
void deleteProduct()
{
  char product_id[10];
  char line[256];
  bool found = false;

  printf("Enter the id of product you want to delete: ");
  scanf(" %s", product_id);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w"); // temporary file to store the data without the deleted product

  while (fgets(line, sizeof(line), file))
  {
    char current_id[10];
    sscanf(line, "%[^,]", current_id);

    // 1. Check if the product exist
    if (strcmp(product_id, current_id) == 0)
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

    printf("The product with id %s has been successfully deleted!\n", product_id);
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
  char product_id[10];
  char line[256];
  bool found = false;

  printf("Enter the ID of the product you want to update: ");
  scanf(" %s", product_id);

  FILE *file = fopen("products.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file,\n");
    return;
  }

  FILE *temp = fopen("temp.txt", "w");

  while (fgets(line, sizeof(line), file))
  {
    char current_id[10];

    sscanf(line, "%[^,]", current_id);

    if (strcmp(product_id, current_id) == 0)
    {
      found = true;
      char name[50], categoryID[10], price[10], quantity[10], supplierID[10];
      float priceFloat;

      sscanf(line, "%*[^,],%[^,],%[^,],%[^,],%[^,],%s\n", name, categoryID, price, quantity, supplierID);

      int choice;
      printf("1. Product ID\n2. Name\n3. CategoryID\n4. Price\n5. Quantity\n6. SupplierID\n7. Exit to Menu\nPlease enter your choice: ");
      scanf("%d", &choice);

      switch (choice)
      {
      case 1:
        printf("Enter the new ID: ");
        scanf(" %s", current_id);
        break;
      case 2:
        printf("Enter the new name: ");
        scanf(" %s", name);
        break;
      case 3:
        printf("Enter the new category ID: ");
        scanf(" %s", categoryID);
        break;
      case 4:
        printf("Enter the new price: ");
        scanf(" %s", price);
        break;
      case 5:
        printf("Enter new quantity ");
        scanf(" %s", quantity);
        break;
      case 6:
        printf("Enter the new supplier ID: ");
        scanf(" %s", supplierID);
        break;
      case 7:
        printf("Exiting to Menu...");
        return;
      }

      priceFloat = atof(price);

      fprintf(temp, "%s,%s,%s,%.2f,%s,%s\n", current_id, name, categoryID, priceFloat, quantity, supplierID);
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

  char product_id[10], product_name[50], categoryID[10], supplier_ID[10], price[10], stock_quantity[10];

  FILE *file;
  char line[256];

  file = fopen("products.txt", "r");

  if (file == NULL)
  {
    printf("Error opening file.\n");
    return;
  }

  while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%s\n", product_id, product_name, categoryID, price, stock_quantity, supplier_ID) != EOF)
  // scan line by line and assigne to each varaible each loop until end of file is reached which then it will exit the loop
  {
    printf("ItemID: %s, Name: %s, CategoryID: %s, Price: %s RM, Stock quantity: %s, SupplierID: %s\n", product_id, product_name, categoryID, price, stock_quantity, supplier_ID);
  }

  fclose(file);
}