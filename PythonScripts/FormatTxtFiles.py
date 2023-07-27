import re
import os

def extract_content_between_markers(content, start_markers, end_markers):
    # Use regular expressions to find the content between markers
    pattern = re.compile(f'({"|".join(re.escape(m) for m in start_markers)})(.*?)({"|".join(re.escape(m) for m in end_markers)})', re.DOTALL)
    match = pattern.search(content)

    if not match:
        raise ValueError("Invalid markers or markers not found in the input content.")

    return match.group(2).strip()

def remove_smart_characters(input_content):
    # Define the mapping of smart characters to their corresponding normal characters
    smart_to_normal = {
        '’': "'",  # Smart single quote to regular single quote
        '[“”]': '"',  # Smart double quote to regular double quote
        '…': '...',  # Ellipsis to three dots
        '[—-]': '-',  # Em dash or hyphen to hyphen
    }

    # Remove smart characters using regular expression
    special_char_pattern = re.compile('|'.join(re.escape(key) for key in smart_to_normal.keys()))
    cleaned_content = special_char_pattern.sub(lambda x: smart_to_normal[x.group()], input_content)

    return cleaned_content

def remove_lines_above_and_below(input_file, output_file):
    try:
        # Read the contents of the input file
        with open(input_file, 'r', encoding='utf-8') as file:
            content = file.read()

    except Exception as e:
        print(f"Error reading file: {input_file}")
        print(f"Error details: {str(e)}")
        return

    try:
        # Find the start and end of the content based on special markers and their alternatives
        start_markers = [
            "***START**THE SMALL PRINT!",
            "*** START OF THE PROJECT GUTENBERG",
            "*** START OF THIS PROJECT GUTENBERG",
            "**The Project Gutenberg"
        ]
        end_markers = [
            "*** END OF THE PROJECT GUTENBERG",
            "*** END OF THIS PROJECT GUTENBERG",
            "End of The Project Gutenberg"
        ]

        extracted_content = extract_content_between_markers(content, start_markers, end_markers)

        # Check if any smart quotes are present in the extracted content
        if any(smart_char in extracted_content for smart_char in ('’', '“', '”', '…', '—', '-')):
            # Remove smart characters from the extracted content
            cleaned_content = remove_smart_characters(extracted_content)

            # Write the cleaned content back to the output file
            with open(output_file, 'w', encoding='utf-8') as file:
                file.write(cleaned_content)

    except Exception as e:
        print(f"Error processing file: {input_file}")
        print(f"Error details: {str(e)}")

def get_files_in_directory(directory_path):
    try:
        # Get a list of all files in the directory
        files = [f for f in os.listdir(directory_path) if os.path.isfile(os.path.join(directory_path, f))]
        return files
    except OSError:
        print(f"Error reading files from directory: {directory_path}")
        return []

if __name__ == "__main__":
    directory_path = "./Books"
    output_directory = "./FileOutput"
    os.makedirs(output_directory, exist_ok=True)

    files = get_files_in_directory(directory_path)

    if files:
        print(f"Files in the directory {directory_path}:")
        for file in files:
            input_file_path = os.path.join(directory_path, file)
            output_file_path = os.path.join(output_directory, file)
            remove_lines_above_and_below(input_file_path, output_file_path)
    else:
        print("No files found in the directory.")
