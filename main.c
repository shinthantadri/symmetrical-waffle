#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
  Product newProduct;

  printf("Enter product id: ");
  scanf(" %s", newProduct.productID);

  printf("Enter product name: ");
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

  while (fscanf(file, "%[^,],%[^,],%[^,],%f,%d,%s\n", product.productID, product.name, product.categoryID, &product.price, &product.quantity, product.supplierID) != EOF)
  // scan line by line and assigne to each varaible each loop until end of file is reached which then it will exit the loop
  {
    printf("ItemID: %s, Name: %s, CategoryID: %s, Price: %.2f RM, Stock quantity: %d, SupplierID: %s\n", product.productID, product.name, product.categoryID, product.price, product.quantity, product.supplierID);
  }

  fclose(file);
}