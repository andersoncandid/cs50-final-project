# Study Log

#### Video Demo:

Study Log is a command-line interface (CLI) program aimed at loging and organizing the progress of daily studied content in a simple and fast way.
The program, lightweight and written entirely in C, allows storing, editing, searching, and viewing study logs through the terminal.
Each log is subdivided into: subject, topic, start and end date, as well as the current study status, striving to be minimalist and objective.
The logs are saved in a CSV file that can be viewed in a spreadsheet editor.
The idea for the project came from a personal need for a simple study loging tool that worked in the Linux terminal and can be a practical and concise assistant for any student who makes daily use of command-line programs.

> [!NOTE]
> **About data manipulation**
>
> - Each study log is stored in a `char` `struct`: `study_log`, and the struct is added to a dynamic array.
> - On program startup, the CSV file with data from previous sessions is loaded into the array.

## Contents

- [Features](#features)
- [Design Decisions](#design-decisions)
- [Project Layout](#project-layout)
- [How to Run the Project](#how-to-run-the-project)
- [Future Improvements](#future-improvements)
- [References](#references)

## Features

### Add new entry:

The user is prompted to input each log field one at a time, which are:

- `Subject`
- `Topic`
- `Start date`
- `End date`
- `Status`

In order to standardize for data organization and search, I validated the date in ISO 8601 format (`YYYY-MM-DD`). If the input is a value different from expected, the correct format is informed and a correct input is requested again. For `Status`, only `0: In Progress` or `1: Completed` is accepted.

### Search System:

The user chooses one of the log fields and inputs the value to be searched.
All data is sorted based on the selected field, and the search is performed linearly using Regular Expressions (Regex).

### Edit Entries

The user provides the ID to be modified in one of 3 options: Edit the end date, the Status, or Delete the log.

### Data Visualization

Two features for visualizing logs on screen:

- "View 'In Progress' studies": Which searches and shows, up to a maximum of 50 logs, the latest entries with Status = In Progress.
- "View studies by start month": Which searches all logs related to a specific Start date month.

### Save data to CSV

The data can be saved to the `userdata/study.csv` file by selecting the corresponding option or upon exiting the program.

### Open CSV in an external program

In this function, the program directs `study.csv` to the system's default spreadsheet program, as **cross-platform compatibility** (Linux, Mac, and Windows).

## Design Decisions

**Data Structure**

- I chose the size of each entry in the `study_log` struct so that there was more than enough size for an expected entry.
- Because it involves a low volume of data, I chose **not to use an external database**, thus I used the `qsort` sorting algorithm and implemented a linear search with regex.

**UI/UX**

- I used only the `printf` function formatted with _ASCII art_ for all outputs.
- The main menu appears automatically only at program startup, and after each feature's execution, the user can print it again via command.
- Before completing any critical action (such as adding, editing, deleting, or saving), a confirmation of the action is requested from the user.

**Input Values**

- I decided to keep all inputs as fixed-size `char` arrays to facilitate data validation and manipulation.

**Data Search and Editing**

- The use of the `<regex.h>` library simplified the search for any user input pattern.
- For the **Edit > Delete** option, I chose to implement a logical deletion (soft delete). The program updates the entry's `Status` to the value `delete` and, when saving the data to the CSV file, simply ignores the logs marked with this value.

## Project Layout

```
├── Makefile
├── README.md
├── src
│   ├── definitions.h
│   ├── functionality.c
│   ├── functionality.h
│   └── main.c
├── stlog
└── userdata
    └── study.csv
```

### File Description

- `definitions.h`: Header containing all the project's **macros** (`#define`) and **type definitions** (`typedef`).
- `functionality.c`: Internal project functionalities, such as input validation, sorting, searching, adding, and editing study logs.
- `main.c`: Main program file.
  - If there is no `study.csv` file, it creates an empty one.
  - If it already exists, it opens the CSV file, parses the values, and loads them into a dynamic array of `structs`.
  - Executes the main loop with the Menu and calls the appropriate function for each menu entry requested by the user.
  - Saves the values to CSV, and formats the output data.
- `studyLog`: Program execution binary.
- **`stlog`**: Executable Bash script created to facilitate the global execution of the program via terminal.
- `userdata/study.csv`: Saved user data.

## How to Run the Project

1. Clone the repository.
2. Install dependencies: `make`, C Compiler (`gcc`)
3. In the terminal, navigate to the project's root folder and run:

```bash
make
```

4. Run the binary:

```bash
./studyLog
```

(Note: To run the program from any directory in Linux without needing `./`, see the section below).

#### Global Installation (Optional)

<details>
<summary>Linux</summary>

1. Configure the directory path:
   Open the `stlog` script in your text editor (like VS Code) and change the `BIN_PATH` variable to the absolute path of the program's root folder.

```sh
# Change program root folder to the absolute path of the program root folder.
# Ex: /home/cs50-final-project/
BIN_PATH="program_root_folder"
```

2. Grant execution permission:
   Through the terminal, navigate to the program folder and make the script executable:

```bash
chmod +x stlog
```

3. Copy to local binaries
   Still in the program's root folder, copy the file to the binaries folder:

```bash
cp stlog $HOME/.local/bin/
```

4. Verify your PATH
   Make sure the `~/.local/bin/` folder is included in your system's PATH. If not, add the line below to the end of your shell configuration file (e.g., `~/.bashrc`):

```bash
export PATH="$HOME/.local/bin:$PATH"
```

</details>

## Future Improvements

For the project's MVP, I implemented input validation for most cases; for the future, I plan to implement it for _edge cases_.
If maintenance complexity increases, as a future improvement, I plan to implement an SQLite database.

## References

### Online tools and tutorials

- [CS50 Manual Pages](https://manual.cs50.io/)
- **GeeksforGeeks**: [C programming category](https://www.geeksforgeeks.org/category/programming-language/c/).
  Used as the main reference for understanding general C language concepts, standard library functions, and syntax.
- **DelftStack**: [C string manipulation guide](https://www.delftstack.com/howto/c/trim-string-in-c/).
  String tokenization logic adapted from an article on the site.
- **Gemini AI chat**
  Used as a debugging assistant and conceptual tutor, helping with improvement suggestions, solving cross-platform portability issues, refining CLI interface texts, and acting as a technical English translation consultant.
- **Makefile** generated by http://MakeMyMakefile.com

### Courses and books

- **C Programming for Everybody** by Dr. Charles R. Severance: [CC4E](https://www.cc4e.com/)
- KERNIGHAN, Brian W.; RITCHIE, Dennis M. **The C Programming Language**. 2. ed. Englewood Cliffs, NJ: Prentice Hall, 1988.
