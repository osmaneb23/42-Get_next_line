# 📖 Get_next_line - Reading Line by Line

Welcome to my **get_next_line** repository! This project is part of the **42 curriculum**, where I've implemented a function that reads from a file descriptor line by line. This project deepened my understanding of file I/O operations, static variables, and memory management in C.

---

## **✅ Project Validation**
- **Validated on:** March 20, 2024
- **Final Score:** 112/100
  - Achieved **bonus part** 🎉 
  - *Note: Despite successful manual testing and validation during evaluations, the moulinette reported compilation issues for the bonus part, explaining my 112 instead of 125.*

---

## **📜 Project Overview**
The goal of this project was to create a function that reads a line from a file descriptor. This implementation handles reading from files, standard input, or any other valid file descriptor, returning one line at a time with each function call.

### **Requirements:**
- Function must return a line that ends with a newline character (`\n`) from a file descriptor.
- When called in a loop, the function should read the text file pointed to by the file descriptor, one line at a time.
- Function should return `NULL` when there is nothing more to read or if an error occurred.
- Function must work properly when reading from a file and when reading from standard input.
- The returned line should include the terminating `\n` character except if the end of file was reached and does not end with a `\n`.
- Must handle appropriate memory management to avoid leaks.
- Must follow **Norminette** coding standards.
- **Only allowed functions:** read, malloc, free
- **Important restrictions:**
  - No use of lseek()
  - No global variables
  - No libft allowed

### **Bonus Part:**
- Use a single static variable.
- Handle multiple file descriptors simultaneously without losing the reading thread of each file descriptor or returning a line from another descriptor.

### **Key Concepts & Skills Developed:**
- **Static Variables:** Understanding and utilizing static variables for state persistence between function calls.
- **File I/O:** Reading from file descriptors, including handling EOF and errors.
- **Memory Management:** Dynamic allocation and proper freeing to prevent memory leaks.
- **Buffer Handling:** Managing buffered input efficiently.
- **Linked Lists:** Using linked lists for storing buffer content (specific to this implementation).
- **Error Handling:** Robust error detection and management.

---

## **📂 Project Structure**
```
get_next_line/
│── get_next_line.c                # Main implementation of get_next_line function
│── get_next_line_utils.c          # Helper functions for the main implementation
│── get_next_line.h                # Header file with function prototypes
│── get_next_line_bonus.c          # Bonus implementation (multiple file descriptors)
│── get_next_line_utils_bonus.c    # Helper functions for bonus implementation
│── get_next_line_bonus.h          # Header file for bonus implementation
```
```

---

## **🛠️ Installation & Usage**

### **📥 Clone & Compile**
```
git clone https://github.com/osmaneb23/42-Get_next_line.git
cd 42-Get_next_line

# Compile with your preferred buffer size
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o get_next_line
```

### **📌 Usage in Your Projects**
Include the function in your project:

```c
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;
    
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (-1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);  // Don't forget to free the allocated memory!
    }
    
    close(fd);
    return (0);
}
```

## **⚙️ Buffer Size**
You can define the buffer size during compilation:

```
gcc -D BUFFER_SIZE=<size> ...
```

The BUFFER_SIZE definition is not mandatory. If you don't specify it during compilation, it defaults to 1.

Common values:
- Small buffer (e.g., 1): Tests edge cases
- Medium buffer (e.g., 42): Balanced performance
- Large buffer (e.g., 10000): Better for large files

---

## **📊 Function Return Values**
The `get_next_line()` function returns:
- A **string containing the line** read from the file descriptor (including the newline character if present).
- **NULL** if there's nothing more to read or if an error occurred.

---

## **💡 Implementation Details**
This implementation uses a linked list approach to store chunks of data read from the file descriptor. Each node contains a portion of the file content, and the function manages these nodes to extract lines efficiently.

The bonus version extends this functionality to handle multiple file descriptors concurrently by maintaining separate linked lists for each descriptor.