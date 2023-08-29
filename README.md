# My Generative AI Project

## Description

This is my take on a generative AI. It generates text based on a given dataset using various algorithms.

#### ----- Rules of the Generative AI program -----

1. Ask the user for a one word prompt.
2. Start a sentence with the prompt word.
3. Repeat until the word ends with a period, question mark, or exclamation point:
4. Open the book to a random location.
5. Read words until you find the prompt word.
6. Choose the next word.
7. Add the word to the end of the sentence.
8. This word becomes the next prompt.
9. When the loop exits, print the sentence.

## Requirements

- g++ [Download here](https://code.visualstudio.com/docs/languages/cpp)
- gdb (if you want to debug) [Download here](https://code.visualstudio.com/docs/languages/cpp)
- python [Download here](https://www.python.org/downloads/)

## Getting Started

### Install External Dependencies

1. `mkdir ../CFileRunner`
2. `git clone https://github.com/superg3m/CFileRunner.git ../CFileRunner`

### Running the Program

- `powershell -ExecutionPolicy Bypass -File ../CFileRunner/RunC.ps1`

### Debugging the Program

- `powershell -ExecutionPolicy Bypass -File ../CFileRunner/DebugC.ps1`

### Alternatively

- Compile and run/debug the program using g++/gdb.

### For More Data (Optional)

1. `python .\PythonScripts\WebScrapper.py`
2. `python .\PythonScripts\FormatTxtFiles.py`

## License

This project is licensed under the [MIT License](LICENSE).

## Contact

For questions or support, you can reach to me at jovannidstudent@gmail.com.

## Acknowledgments

Special thanks to **Leo C. Ureel II** at MTU for prompting this idea.
