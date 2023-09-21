# Memory_Management

This C program is designed to simulate a virtual memory address translator. It takes a user-defined page size (either 4095 or 8191) and translates virtual memory addresses to physical memory addresses using a page table. Here's a step-by-step breakdown of the code:
Overview

The program performs the following main tasks:

    Takes user input for the page size (either 4095 or 8191).
    Initializes a page table based on the chosen page size.
    Prompts the user to enter virtual memory addresses (in hexadecimal).
    Translates virtual memory addresses to physical memory addresses using the page table.
    Outputs the results to the user.

Code Sections
Header and Macros

    The program includes standard C libraries (stdio.h and stdint.h) and defines maximum virtual and physical addresses as macros.

decimalToBinary16 Function

    This function converts a decimal number (provided as a 16-bit unsigned integer) into its binary representation and prints it.

displayHex Function

    This function displays a 32-bit number in hexadecimal format with leading zeros.

main Function

    The main function is where the program execution begins.

User Input

    The program asks the user to enter a page size, which must be either 4095 or 8191.
    If the input is invalid, the program displays an error message and exits with an error code.

Page Table Initialization

    Based on the chosen page size, the program calculates the number of pages that can fit within the virtual address space and creates a page table array accordingly.
    The page table is initialized, and each entry contains either the physical memory address or -1 (indicating the page is on disk).

Virtual Address Translation Loop

    The program enters a loop to handle virtual address translation until the user decides to exit (e.g., by pressing Ctrl+D).
    Inside the loop, the user is prompted to enter a hexadecimal virtual memory address.

Virtual Address Validation

    The program checks if the entered virtual address is within the valid range (0x00000000 - 0x000FFFFF). If it's not, an error message is displayed, and the loop continues for a new address.

Page Number and Offset Calculation

    For a valid virtual address, the program calculates the page number and offset within that page.

Address Translation

    Depending on the page table entry and offset, the program determines whether the virtual page is currently in physical memory or on disk.
    If the page is on disk, it informs the user.
    If the page is in physical memory, it calculates the physical address and displays it.

Program Termination

    The program terminates gracefully when the user chooses to exit the loop.
    It returns 0 as a success code.

Usage

    Compile the code using a C compiler (e.g., gcc -o address_translator address_translator.c).
    Run the executable (e.g., ./address_translator).
    Follow the prompts to enter the page size and virtual memory addresses for translation.
