import re
import os

def remove_lines_above_and_below(input_file, output_file):
    # Define the mapping of smart characters to their corresponding normal characters
    smart_to_normal = {
        '’': "'",  # Smart single quote to regular single quote
        '“': '"',  # Smart double quote to regular double quote
        '”': '"',  # Smart double quote to regular double quote
        '…': '...',  # Ellipsis to three dots
        '—': '-',  # Em dash to hyphen
        '-': '-',  # Hyphen to hyphen (included in the mapping to prevent KeyError)
    }

    # Read the contents of the input file
    with open(input_file, 'r', encoding='utf-8') as file:
        content = file.read()

    # Find the index of the line containing "*** START OF THE PROJECT GUTENBERG EBOOK"
    start_of_project_gutenberg = "*** START OF THE PROJECT GUTENBERG EBOOK"
    start_line_index = content.find(start_of_project_gutenberg)

    # Find the index of the line containing "*** END OF THE PROJECT GUTENBERG EBOOK"
    end_of_project_gutenberg = "*** END OF THE PROJECT GUTENBERG EBOOK"
    end_line_index = content.find(end_of_project_gutenberg)

    # Extract the content between the lines "*** START OF THE PROJECT GUTENBERG EBOOK" and "*** END OF THE PROJECT GUTENBERG EBOOK"
    cleaned_content = content[start_line_index:end_line_index]

    # Remove smart characters using regular expression
    special_char_pattern = r'[’“”…\-]'
    cleaned_content = re.sub(special_char_pattern, lambda x: smart_to_normal[x.group()], cleaned_content)

    # Write the cleaned content back to the file
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(cleaned_content)

def get_files_in_directory(directory_path):
    try:
        # Get a list of all files in the directory
        files = [os.path.relpath(os.path.join(directory_path, f), start=directory_path)
                 for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
        return files
    except OSError:
        print(f"Error reading files from directory: {directory_path}")
        return []

if __name__ == "__main__":
    directory_path = "../Archive"
  
    files = get_files_in_directory("../Archive")
  
    if files:
      print("Files in the directory (relative paths):")
      for file in files:
        input_file_path = os.path.join(directory_path, file)
        output_directory = "../FileOutput"
        output_file_path = os.path.join(output_directory, file)
        os.makedirs(os.path.dirname(output_file_path), exist_ok=True)
        remove_lines_above_and_below(input_file_path, output_file_path)
    else:
        print("No files found in the directory.")


  
  
