"""
Project for Week 4 of "Python Data Representations".
Find differences in file contents.

Be sure to read the project description page for further information
about the expected behavior of the program.
"""

IDENTICAL = -1

def singleline_diff(line1, line2):
    """
    Inputs:
      line1 - first single line string
      line2 - second single line string
    Output:
      Returns the index where the first difference between
      line1 and line2 occurs.

      Returns IDENTICAL if the two lines are the same.
    """
    l1_length = len(line1)
    l2_length = len(line2)

    if l1_length <= l2_length:
        shorter_line = l1_length
    else:
        shorter_line = l2_length

    for index in range(shorter_line):
        if line1[index] != line2[index]:
            return index

    if l1_length != l2_length:
        return shorter_line

    return IDENTICAL



# line_1 = 'engineering classes\nscience classes'
# line2 = 'engineering classes\nscienee classes'
# #print(singleline_diff(line1, line2))

def singleline_diff_format(line1, line2, idx):
    """
    Inputs:
      line1 - first single line string
      line2 - second single line string
      idx   - index at which to indicate difference
    Output:
      Returns a three line formatted string showing the location
      of the first difference between line1 and line2.

      If either input line contains a newline or carriage return,
      then returns an empty string.

      If idx is not a valid index, then returns an empty string.
    """
    separator = ''

    if ("\n" in line1 or "\r" in line1) and ("\n" in line2 or "\r" in line2):
        return ""
    elif (idx == -1) or (idx > len(line1)) or (idx > len(line2)):
        return ''
    #first_line = line1[:idx + 1]
    
    for iterate in range(idx):
        print(iterate)
        separator += '='      
    
    return '{}\n{}\n{}\n'.format(line1, separator + '^', line2)


# line1 = "abcd"
# line2 = "abcd"
#print(singleline_diff_format('abcdefg', 'abc', 5))

def multiline_diff(lines1, lines2):
    """
    Inputs:
      lines1 - list of single line strings
      lines2 - list of single line strings
    Output:
      Returns a tuple containing the line number (starting from 0) and
      the index in that line where the first difference between lines1
      and lines2 occurs.

      Returns (IDENTICAL, IDENTICAL) if the two lists are the same.
    """
    l1_length = len(lines1)
    l2_length = len(lines2)

    if l1_length <= l2_length:
        shorter_list = l1_length
    else:
        shorter_list = l2_length
      

    for idx in range(shorter_list):
      
        line_1_list = lines1[idx]
      
        line_2_list = lines2[idx]
      #Index of that particular item(line) 
      # where difference is found
        difference_idx = singleline_diff(line_1_list, line_2_list)

        if difference_idx >= 0:
          # Return index where there is a character difference in both lines
            return (idx, difference_idx)

    if l1_length != l2_length:
        return (shorter_list, 0)

      
      #Idx is the index of the list. First item in both list is the..
      # first line, The 2nd item is the second line..
      # # Therefore the list has multiple lines
      # if line1[idx] != line2[idx]:
      #     # Return index where there is a character difference in both lines
      #     if difference_idx > 0:
      #       return(idx, difference_idx)

      
    
    return (IDENTICAL, IDENTICAL)


def get_file_lines(filename):
    """
    Inputs:
      filename - name of file to read
    Output:
      Returns a list of lines from the file named filename.  Each
      line will be a single line string with no newline ('\n') or
      return ('\r') characters.

      If the file does not exist or is not readable, then the
      behavior of this function is undefined.
    """
    with open(filename, "rt") as datafile:
      # read_text = fileopen.readlines()
        line_list = []
        for line in datafile:
            strip_text_clean = line.rstrip()
            line_list.append(strip_text_clean)
    return line_list


def file_diff_format(filename1, filename2):
    """
    Inputs:
      filename1 - name of first file
      filename2 - name of second file
    Output:
      Returns a four line string showing the location of the first
      difference between the two files named by the inputs.

      If the files are identical, the function instead returns the
      string "No differences\n".

      If either file does not exist or is not readable, then the
      behavior of this function is undefined.
    """
    list_1 = get_file_lines(filename1)
    list_2 = get_file_lines(filename2)

    result_from_multi_line = multiline_diff(list_1, list_2)
    print(result_from_multi_line)
    if (result_from_multi_line[0] != -1) and (result_from_multi_line[1] != -1):
      
        try:
            return "Line " + str(result_from_multi_line[0]) + ":\n" + \
            singleline_diff_format(list_1[result_from_multi_line[0]], 
            list_2[result_from_multi_line[0]], result_from_multi_line[1])
        except IndexError:
            return "Line " + str(result_from_multi_line[0]) + ":\n" + \
            singleline_diff_format(list_1[0], '', result_from_multi_line[1])

    return "No differences\n"

#print(file_diff_format("file1.txt", "file2.txt"))