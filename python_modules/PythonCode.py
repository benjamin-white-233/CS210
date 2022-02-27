import re
import string

# Option 1
def PrintList():
    input_file = open("CS210_Project_Three_Input_File.txt", "r") # open file in read-only
    grocery_item = dict() # initialize empty dictionary

    for i in input_file: # loop through input file and populate dictionary with key/value pair
        i = i.strip()
        items = i.split(" ") # split data by space
        for item in items:
            if item in grocery_item: # if item already exists in dictionary, increment value
                grocery_item[item] = grocery_item[item] + 1
            else:
                grocery_item[item] = 1 # otherwise, set value to 1

    for key in list(grocery_item.keys()): # for each key in dictionary, print key + value
        print(key, ":", grocery_item[key])

    return 0

# Option 2
def PrintQuantity(user_item):

    input_file = open("CS210_Project_Three_Input_File.txt", "r") # open file in read-only
    grocery_item = dict() # initialize empty dictionary
    count = 0 # initialize quantity to 0

    for i in input_file:
        i = i.strip()
        items = i.split(" ") # split data by space
        for item in items:
            if user_item in items: # if user item already exists in dictionary, increment value
                count += 1
            else:
                grocery_item[item] = 1 # otherwise, set value to 1

    print(user_item, ":", count) # print user item + quantity
    return 0

# Option 3
def MakeList():

    input_file = open("CS210_Project_Three_Input_File.txt", "r") # open file in read-only
    grocery_item = dict() # initialize empty dictionary

    for i in input_file:
        i = i.strip()
        items = i.split(" ") # split data by space
        for item in items:
            if item in grocery_item: # if user item already exists in dictionary, increment value
                grocery_item[item] = grocery_item[item] + 1
            else:
                grocery_item[item] = 1 # otherwise, set value to 1

    ### Writing to output file
    output_file = open("frequency.dat", "w+") # create new file in read-write
    for key in list(grocery_item.keys()): # for each key in dictionary, print key + value to new file
        output_file.write(key + " " + str(grocery_item[key]) + "\n")

    output_file.close() # close newly created file
    return 0
