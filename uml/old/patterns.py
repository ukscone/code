import re

classpattern = """
    ^                       #beginning of string
    \s*                     #leading whitespace
    class\s+
    (\w+)                   #class name
    \s*(?::)?\s*            #inherits?
    ([\w\s,]*)              #inheritance
    """

operationpattern = """
    ^                       #beginning of string
    \s*                     #leading whitespace
    (?:(virtual)\s+)?       #virtual
    ([\w:*]+)\s+            #return type            
    (\w+)                   #function name
    \((.*?)\)               #argument list 
    """
    
attributepattern = """
    ^                       #beginning of string
    \s*                     #leading whitespace
    ([\w:*]+)               #type
    \s+
    ((?:\w+)(?:,\s+\w+)*)   #variable names
    ;                       #end of statement
    """
    
classpat = re.compile(classpattern, re.VERBOSE)
operpat = re.compile(operationpattern, re.VERBOSE)
attrpat = re.compile(attributepattern, re.VERBOSE)

filepat = re.compile(r'.*[.]h$')
