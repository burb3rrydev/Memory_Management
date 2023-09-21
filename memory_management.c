#include <stdio.h>
#include <stdint.h>

// Define maximum virtual and physical addresses
#define MAX_VIRTUAL_ADDRESS 0x000FFFFF
#define MAX_PHYSICAL_ADDRESS 0x0007FFFF

// Function to convert a decimal number to a 16-bit binary representation
void decimalToBinary16(uint16_t num) {
    for (int i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1); // Right shift num by i positions, then bitwise AND with 1 to get the binary representation.
    }
}

// Function to display a 32-bit number in hexadecimal format
void displayHex(uint32_t num) {
    printf("0x%08X\n", num); // Print the number in hexadecimal format with leading zeros.
}

int main() {
    int pageSize;
    printf("Enter the page size (4095 or 8191): ");
    scanf("%d", &pageSize); // Read the page size from the user.

    if (pageSize != 4095 && pageSize != 8191) {
        printf("Invalid page size. Please enter 4095 or 8191.\n");
        return 1; // Exit the program with an error code if the page size is not valid.
    }

    printf("Page size in binary: ");
    decimalToBinary16(pageSize); // Call the function to convert and print the page size in binary.
    printf("\nPage size in hexadecimal: ");
    displayHex(pageSize); // Call the function to display the page size in hexadecimal.

    // Calculate the number of pages based on the page size
    int numPages = MAX_VIRTUAL_ADDRESS / pageSize + 1;

    // Create a page table array
    uint32_t pageTable[numPages];

    // Initialize the page table
    for (int i = 0; i < numPages; i++) {
        // Check if the page can fit within physical memory
        if (i * pageSize <= MAX_PHYSICAL_ADDRESS) {
            pageTable[i] = i * pageSize; // Store the physical address for the page in the page table.
        } else {
            // Page is on disk
            pageTable[i] = -1; // Mark the page as being on disk by setting it to -1.
        }
    }

    while (1) {
      uint32_t virtualAddress; // Declare a variable to store the virtual memory address.
      printf("\nEnter a hexadecimal virtual memory address (0x00000000 - 0x000FFFFF): "); // Prompt the user to enter a hexadecimal virtual memory address.

      // read hexadecimal value from the user and store it in virtualAddress.
      // The %x format specifier is used to interpret the input as a hexadecimal number.
      if (scanf("%x", &virtualAddress) == EOF) {
          break; // If the end of input is reached (e.g., user presses Ctrl+D), exit the loop.
      }

      // Check if the entered virtual address is within the valid range (0x00000000 - 0x000FFFFF).
      if (virtualAddress < 0 || virtualAddress > MAX_VIRTUAL_ADDRESS) {
          printf("Invalid virtual memory address. Please enter a valid address.\n");
          continue; // If the address is invalid, print an error message and skip the rest of the loop to ask for another address.
      }


        // Calculate the page number and offset
        int pageNumber = virtualAddress / pageSize; // Calculate the page number by dividing the virtual address by the page size.
        int offset = virtualAddress % pageSize; // Calculate the offset by taking the remainder of the virtual address divided by the page size.

        if (pageTable[pageNumber] == -1) {
            // If the page table entry for the page number is -1, it means the page is on disk.
            printf("Virtual address 0x%08X is Currently On Disk.\n", virtualAddress);
        } else if (pageTable[pageNumber] + offset > MAX_PHYSICAL_ADDRESS) {
            // If the sum of the page table entry and the offset is greater than the maximum physical address,
            // it means the page is on disk because it's not in physical memory.
            printf("Virtual address 0x%08X is Currently On Disk.\n", virtualAddress);
        } else {
            // If none of the above conditions are met, calculate the physical address and print it.
            uint32_t physicalAddress = pageTable[pageNumber] + offset;
            printf("Virtual address 0x%08X maps to physical address 0x%08X.\n", virtualAddress, physicalAddress);
        }


}

    return 0; // Exit the program with a success code.
}
